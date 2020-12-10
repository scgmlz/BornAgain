//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIDomainSampleVisitor.cpp
//! @brief     Implements class GUIDomainSampleVisitor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/GUIDomainSampleVisitor.h"
#include "Base/Const/Units.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/FormFactorItems.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/MesoCrystalItem.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/ParticleCoreShellItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/RotationItems.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/TransformFromDomain.h"
#include "GUI/coregui/Models/TransformationItem.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "Param/Node/NodeUtils.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/HardParticles.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Multilayer/MultiLayerUtils.h"
#include "Sample/Particle/Crystal.h"
#include "Sample/Particle/MesoCrystal.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleComposition.h"
#include "Sample/Particle/ParticleCoreShell.h"
#include "Sample/Particle/ParticleDistribution.h"
#include "Sample/SoftParticle/SoftParticles.h"

using SessionItemUtils::SetVectorItem;

namespace {
SessionItem* AddFormFactorItem(SessionItem* parent, const QString& model_type) {
    auto parent_type = parent->modelType();
    QString property_name;
    if (parent_type == "Particle")
        property_name = ParticleItem::P_FORM_FACTOR;
    else if (parent_type == "MesoCrystal")
        property_name = MesoCrystalItem::P_OUTER_SHAPE;
    if (property_name.isEmpty())
        throw GUIHelpers::Error("AddFormFactorItem: parent is neither ParticleItem or "
                                "MesoCrystalItem");
    return parent->setGroupProperty(property_name, model_type);
}
} // namespace

GUIDomainSampleVisitor::GUIDomainSampleVisitor()
    : m_sampleModel(nullptr), m_materialModel(nullptr) {}

GUIDomainSampleVisitor::~GUIDomainSampleVisitor() = default;

SessionItem* GUIDomainSampleVisitor::populateSampleModel(SampleModel* sampleModel,
                                                         MaterialModel* materialModel,
                                                         const MultiLayer& sample,
                                                         const QString& sample_name) {
    m_sampleModel = sampleModel;
    m_materialModel = materialModel;
    m_levelToParentItem.clear();

    m_topSampleName = sample_name;
    if (m_topSampleName.isEmpty())
        m_topSampleName = sample.getName().c_str();

    for (const auto& [child, depth, parent] : NodeUtils::progenyPlus(&sample)) {
        setDepth(depth + 1);
        child->accept(this);
    }
    SessionItem* result = m_levelToParentItem[1];

    result->setItemName(m_topSampleName);
    return result;
}

void GUIDomainSampleVisitor::visit(const ParticleLayout* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    SessionItem* layout_item(nullptr);
    if (parent)
        layout_item =
            m_sampleModel->insertNewItem("ParticleLayout", m_sampleModel->indexOfItem(parent));
    else
        layout_item = m_sampleModel->insertNewItem("ParticleLayout");
    layout_item->setItemValue(ParticleLayoutItem::P_TOTAL_DENSITY,
                              sample->totalParticleSurfaceDensity());
    layout_item->setItemValue(ParticleLayoutItem::P_WEIGHT, sample->weight());
    m_levelToParentItem[depth()] = layout_item;
}

void GUIDomainSampleVisitor::visit(const Layer* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);

    const auto* multilayer = dynamic_cast<const MultiLayer*>(m_itemToSample[parent]);
    ASSERT(multilayer);
    size_t layer_index = MultiLayerUtils::IndexOfLayer(*multilayer, sample);
    const LayerInterface* top_interface =
        layer_index == 0 ? nullptr : multilayer->layerInterface(layer_index - 1);

    SessionItem* layer_item =
        m_sampleModel->insertNewItem("Layer", m_sampleModel->indexOfItem(parent));
    layer_item->setItemValue(LayerItem::P_MATERIAL,
                             createMaterialFromDomain(sample->material()).variant());

    TransformFromDomain::setLayerItem(layer_item, sample, top_interface);

    m_levelToParentItem[depth()] = layer_item;
}

void GUIDomainSampleVisitor::visit(const MultiLayer* sample) {
    SessionItem* multilayer_item = m_sampleModel->insertNewItem("MultiLayer");
    multilayer_item->setItemName(sample->getName().c_str());
    multilayer_item->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH, sample->crossCorrLength());
    SetVectorItem(*multilayer_item, MultiLayerItem::P_EXTERNAL_FIELD, sample->externalField());
    m_levelToParentItem[depth()] = multilayer_item;
    m_itemToSample[multilayer_item] = sample;
}

void GUIDomainSampleVisitor::visit(const Particle* sample) {
    auto particle_item = InsertIParticle(sample, "Particle");
    particle_item->setItemValue(ParticleItem::P_MATERIAL,
                                createMaterialFromDomain(sample->material()).variant());
}

void GUIDomainSampleVisitor::visit(const ParticleDistribution* sample) {
    SessionItem* layout_item = m_levelToParentItem[depth() - 1];
    ASSERT(layout_item);
    SessionItem* particle_distribution_item = m_sampleModel->insertNewItem(
        "ParticleDistribution", m_sampleModel->indexOfItem(layout_item));
    ASSERT(particle_distribution_item);

    TransformFromDomain::setParticleDistributionItem(particle_distribution_item, *sample);

    m_levelToParentItem[depth()] = particle_distribution_item;
    m_itemToSample[particle_distribution_item] = sample;
}

void GUIDomainSampleVisitor::visit(const ParticleCoreShell* sample) {
    InsertIParticle(sample, "ParticleCoreShell");
}

void GUIDomainSampleVisitor::visit(const ParticleComposition* sample) {
    InsertIParticle(sample, "ParticleComposition");
}

void GUIDomainSampleVisitor::visit(const MesoCrystal* sample) {
    InsertIParticle(sample, "MesoCrystal");
}

void GUIDomainSampleVisitor::visit(const Crystal* sample) {
    SessionItem* mesocrystal_item = m_levelToParentItem[depth() - 1];
    ASSERT(mesocrystal_item);
    if (mesocrystal_item->modelType() != "MesoCrystal") {
        throw GUIHelpers::Error("GUIObjectBuilder::visit(const Crystal*) "
                                "-> Error. Parent is not a MesoCrystal");
    }
    auto lattice = sample->transformedLattice();
    auto vector_a = lattice.getBasisVectorA();
    auto vector_b = lattice.getBasisVectorB();
    auto vector_c = lattice.getBasisVectorC();

    SetVectorItem(*mesocrystal_item, MesoCrystalItem::P_VECTOR_A, vector_a);
    SetVectorItem(*mesocrystal_item, MesoCrystalItem::P_VECTOR_B, vector_b);
    SetVectorItem(*mesocrystal_item, MesoCrystalItem::P_VECTOR_C, vector_c);

    // Since there is no CrystalItem, set the parent map to the MesoCrystalItem
    m_levelToParentItem[depth()] = mesocrystal_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorAnisoPyramid* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "AnisoPyramid");
    ff_item->setItemValue(AnisoPyramidItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(AnisoPyramidItem::P_WIDTH, sample->getWidth());
    ff_item->setItemValue(AnisoPyramidItem::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(AnisoPyramidItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorBarGauss* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "BarGauss");
    ff_item->setItemValue(BarGaussItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(BarGaussItem::P_WIDTH, sample->getWidth());
    ff_item->setItemValue(BarGaussItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorBarLorentz* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "BarLorentz");
    ff_item->setItemValue(BarLorentzItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(BarLorentzItem::P_WIDTH, sample->getWidth());
    ff_item->setItemValue(BarLorentzItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorBox* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Box");
    ff_item->setItemValue(BoxItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(BoxItem::P_WIDTH, sample->getWidth());
    ff_item->setItemValue(BoxItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCone* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Cone");
    ff_item->setItemValue(ConeItem::P_RADIUS, sample->getRadius());
    ff_item->setItemValue(ConeItem::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(ConeItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCone6* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Cone6");
    ff_item->setItemValue(Cone6Item::P_BASEEDGE, sample->getBaseEdge());
    ff_item->setItemValue(Cone6Item::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(Cone6Item::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCuboctahedron* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Cuboctahedron");
    ff_item->setItemValue(CuboctahedronItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(CuboctahedronItem::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(CuboctahedronItem::P_HEIGHT_RATIO, sample->getHeightRatio());
    ff_item->setItemValue(CuboctahedronItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCylinder* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Cylinder");
    ff_item->setItemValue(CylinderItem::P_RADIUS, sample->getRadius());
    ff_item->setItemValue(CylinderItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorDodecahedron* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Dodecahedron");
    ff_item->setItemValue(DodecahedronItem::P_EDGE, sample->getEdge());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorDot* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Dot");
    ff_item->setItemValue(FullSphereItem::P_RADIUS, sample->getRadius());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorEllipsoidalCylinder* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "EllipsoidalCylinder");
    ff_item->setItemValue(EllipsoidalCylinderItem::P_RADIUS_X, sample->getRadiusX());
    ff_item->setItemValue(EllipsoidalCylinderItem::P_RADIUS_Y, sample->getRadiusY());
    ff_item->setItemValue(EllipsoidalCylinderItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorFullSphere* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "FullSphere");
    ff_item->setItemValue(FullSphereItem::P_RADIUS, sample->getRadius());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorFullSpheroid* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "FullSpheroid");
    ff_item->setItemValue(FullSpheroidItem::P_RADIUS, sample->getRadius());
    ff_item->setItemValue(FullSpheroidItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorIcosahedron* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Icosahedron");
    ff_item->setItemValue(IcosahedronItem::P_EDGE, sample->getEdge());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorHemiEllipsoid* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "HemiEllipsoid");
    ff_item->setItemValue(HemiEllipsoidItem::P_RADIUS_X, sample->getRadiusX());
    ff_item->setItemValue(HemiEllipsoidItem::P_RADIUS_Y, sample->getRadiusY());
    ff_item->setItemValue(HemiEllipsoidItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorPrism3* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Prism3");
    ff_item->setItemValue(Prism3Item::P_BASEEDGE, sample->getBaseEdge());
    ff_item->setItemValue(Prism3Item::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorPrism6* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Prism6");
    ff_item->setItemValue(Prism6Item::P_BASEEDGE, sample->getBaseEdge());
    ff_item->setItemValue(Prism6Item::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorPyramid* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Pyramid");
    ff_item->setItemValue(PyramidItem::P_BASEEDGE, sample->getBaseEdge());
    ff_item->setItemValue(PyramidItem::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(PyramidItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCosineRippleBox* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "CosineRippleBox");
    ff_item->setItemValue(CosineRippleBoxItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(CosineRippleBoxItem::P_WIDTH, sample->getWidth());
    ff_item->setItemValue(CosineRippleBoxItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCosineRippleGauss* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "CosineRippleGauss");
    ff_item->setItemValue(CosineRippleGaussItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(CosineRippleGaussItem::P_WIDTH, sample->getWidth());
    ff_item->setItemValue(CosineRippleGaussItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCosineRippleLorentz* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "CosineRippleLorentz");
    ff_item->setItemValue(CosineRippleLorentzItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(CosineRippleLorentzItem::P_WIDTH, sample->getWidth());
    ff_item->setItemValue(CosineRippleLorentzItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorSawtoothRippleBox* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "SawtoothRippleBox");
    ff_item->setItemValue(SawtoothRippleBoxItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(SawtoothRippleBoxItem::P_WIDTH, sample->getWidth());
    ff_item->setItemValue(SawtoothRippleBoxItem::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(SawtoothRippleBoxItem::P_ASYMMETRY, sample->getAsymmetry());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorSawtoothRippleGauss* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "SawtoothRippleGauss");
    ff_item->setItemValue(SawtoothRippleGaussItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(SawtoothRippleGaussItem::P_WIDTH, sample->getWidth());
    ff_item->setItemValue(SawtoothRippleGaussItem::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(SawtoothRippleGaussItem::P_ASYMMETRY, sample->getAsymmetry());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorSawtoothRippleLorentz* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "SawtoothRippleLorentz");
    ff_item->setItemValue(SawtoothRippleLorentzItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(SawtoothRippleLorentzItem::P_WIDTH, sample->getWidth());
    ff_item->setItemValue(SawtoothRippleLorentzItem::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(SawtoothRippleLorentzItem::P_ASYMMETRY, sample->getAsymmetry());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorTetrahedron* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "Tetrahedron");
    ff_item->setItemValue(TetrahedronItem::P_BASEEDGE, sample->getBaseEdge());
    ff_item->setItemValue(TetrahedronItem::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(TetrahedronItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorTruncatedCube* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "TruncatedCube");
    ff_item->setItemValue(TruncatedCubeItem::P_LENGTH, sample->getLength());
    ff_item->setItemValue(TruncatedCubeItem::P_REMOVED_LENGTH, sample->getRemovedLength());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorTruncatedSphere* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "TruncatedSphere");
    ff_item->setItemValue(TruncatedSphereItem::P_RADIUS, sample->getRadius());
    ff_item->setItemValue(TruncatedSphereItem::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(TruncatedSphereItem::P_REMOVED_TOP, sample->getRemovedTop());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorTruncatedSpheroid* sample) {
    SessionItem* particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* ff_item = AddFormFactorItem(particle_item, "TruncatedSpheroid");
    ff_item->setItemValue(TruncatedSpheroidItem::P_RADIUS, sample->getRadius());
    ff_item->setItemValue(TruncatedSpheroidItem::P_HEIGHT, sample->getHeight());
    ff_item->setItemValue(TruncatedSpheroidItem::P_HFC, sample->getHeightFlattening());
    ff_item->setItemValue(TruncatedSpheroidItem::P_REMOVED_TOP, sample->getRemovedTop());
    m_levelToParentItem[depth()] = particle_item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunction1DLattice* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item =
        m_sampleModel->insertNewItem("Interference1DLattice", m_sampleModel->indexOfItem(parent),
                                     -1, ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::set1DLatticeItem(item, *sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunction2DLattice* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item =
        m_sampleModel->insertNewItem("Interference2DLattice", m_sampleModel->indexOfItem(parent),
                                     -1, ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::set2DLatticeItem(item, *sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunction2DParaCrystal* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem("Interference2DParaCrystal",
                                                     m_sampleModel->indexOfItem(parent), -1,
                                                     ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::set2DParaCrystalItem(item, *sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunctionFinite2DLattice* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem("InterferenceFinite2DLattice",
                                                     m_sampleModel->indexOfItem(parent), -1,
                                                     ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::setFinite2DLatticeItem(item, *sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunctionHardDisk* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item =
        m_sampleModel->insertNewItem("InterferenceHardDisk", m_sampleModel->indexOfItem(parent), -1,
                                     ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::setHardDiskItem(item, *sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunctionRadialParaCrystal* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem("InterferenceRadialParaCrystal",
                                                     m_sampleModel->indexOfItem(parent), -1,
                                                     ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::setRadialParaCrystalItem(item, *sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const RotationX* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        "Rotation", m_sampleModel->indexOfItem(parent), -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* rotationItem =
        transformation_item->setGroupProperty(TransformationItem::P_ROT, "XRotation");
    rotationItem->setItemValue(XRotationItem::P_ANGLE, Units::rad2deg(sample->getAngle()));
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIDomainSampleVisitor::visit(const RotationY* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        "Rotation", m_sampleModel->indexOfItem(parent), -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* rotationItem =
        transformation_item->setGroupProperty(TransformationItem::P_ROT, "YRotation");
    rotationItem->setItemValue(YRotationItem::P_ANGLE, Units::rad2deg(sample->getAngle()));
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIDomainSampleVisitor::visit(const RotationZ* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        "Rotation", m_sampleModel->indexOfItem(parent), -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* rotationItem =
        transformation_item->setGroupProperty(TransformationItem::P_ROT, "ZRotation");
    rotationItem->setItemValue(ZRotationItem::P_ANGLE, Units::rad2deg(sample->getAngle()));
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIDomainSampleVisitor::visit(const RotationEuler* sample) {
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        "Rotation", m_sampleModel->indexOfItem(parent), -1, ParticleItem::T_TRANSFORMATION);
    ASSERT(transformation_item);
    SessionItem* rotationItem =
        transformation_item->setGroupProperty(TransformationItem::P_ROT, "EulerRotation");
    rotationItem->setItemValue(EulerRotationItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    rotationItem->setItemValue(EulerRotationItem::P_BETA, Units::rad2deg(sample->getBeta()));
    rotationItem->setItemValue(EulerRotationItem::P_GAMMA, Units::rad2deg(sample->getGamma()));
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIDomainSampleVisitor::buildPositionInfo(SessionItem* particle_item,
                                               const IParticle* sample) {
    kvector_t position = sample->position();
    SetVectorItem(*particle_item, ParticleItem::P_POSITION, position);
}

ExternalProperty GUIDomainSampleVisitor::createMaterialFromDomain(const Material* material) {
    QString materialName = m_topSampleName + QString("_") + QString(material->getName().c_str());

    if (auto material = m_materialModel->materialFromName(materialName))
        return MaterialItemUtils::materialProperty(*material);

    complex_t material_data = material->materialData();
    MaterialItem* materialItem(nullptr);
    if (material->typeID() == MATERIAL_TYPES::RefractiveMaterial) {
        materialItem = m_materialModel->addRefractiveMaterial(materialName, material_data.real(),
                                                              material_data.imag());
    } else if (material->typeID() == MATERIAL_TYPES::MaterialBySLD) {
        materialItem = m_materialModel->addSLDMaterial(materialName, material_data.real(),
                                                       material_data.imag());
    } else {
        throw GUIHelpers::Error("GUIObjectBuilder::createMaterialFromDomain() -> Error. "
                                "Unsupported material");
    }

    SetVectorItem(*materialItem, MaterialItem::P_MAGNETIZATION, material->magnetization());
    return MaterialItemUtils::materialProperty(*materialItem);
}

SessionItem* GUIDomainSampleVisitor::InsertIParticle(const IParticle* particle,
                                                     QString model_type) {
    auto parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);

    QString tag;
    auto parent_type = parent->modelType();
    if (model_type == "Particle") {
        if (parent_type == "ParticleCoreShell") {
            const ParticleCoreShell* coreshell =
                dynamic_cast<const ParticleCoreShell*>(m_itemToSample[parent]);
            ASSERT(coreshell);
            if (particle == coreshell->coreParticle()) {
                tag = ParticleCoreShellItem::T_CORE;
            } else if (particle == coreshell->shellParticle()) {
                tag = ParticleCoreShellItem::T_SHELL;
            } else {
                throw GUIHelpers::Error("GUIObjectBuilder::InsertIParticle:"
                                        "Particle not found in parent ParticleCoreShell");
            }
        }
    }
    SessionItem* particle_item =
        m_sampleModel->insertNewItem(model_type, m_sampleModel->indexOfItem(parent), -1, tag);

    ASSERT(particle_item);
    particle_item->setItemValue(ParticleItem::P_ABUNDANCE, particle->abundance());
    buildPositionInfo(particle_item, particle);

    m_levelToParentItem[depth()] = particle_item;
    m_itemToSample[particle_item] = particle;

    return particle_item;
}
