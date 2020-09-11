// ************************************************************************** //
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
// ************************************************************************** //

#include "GUI/coregui/Models/GUIDomainSampleVisitor.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/Material/Material.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/MultiLayerUtils.h"
#include "Core/Particle/Crystal.h"
#include "Core/Particle/MesoCrystal.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleComposition.h"
#include "Core/Particle/ParticleCoreShell.h"
#include "Core/Particle/ParticleDistribution.h"
#include "Core/includeIncludes/FormFactors.h"
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
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"

using SessionItemUtils::SetVectorItem;

namespace
{
SessionItem* AddFormFactorItem(SessionItem* p_parent, const QString& model_type);
}

GUIDomainSampleVisitor::GUIDomainSampleVisitor() : m_sampleModel(nullptr), m_materialModel(nullptr)
{
}

GUIDomainSampleVisitor::~GUIDomainSampleVisitor() = default;

SessionItem* GUIDomainSampleVisitor::populateSampleModel(SampleModel* sampleModel,
                                                         MaterialModel* materialModel,
                                                         const MultiLayer& sample,
                                                         const QString& sample_name)
{
    m_sampleModel = sampleModel;
    m_materialModel = materialModel;
    m_levelToParentItem.clear();

    m_topSampleName = sample_name;
    if (m_topSampleName.isEmpty())
        m_topSampleName = sample.getName().c_str();

    VisitNodesPreorder(sample, *this);
    SessionItem* result = m_levelToParentItem[1];

    result->setItemName(m_topSampleName);
    return result;
}

void GUIDomainSampleVisitor::visit(const ParticleLayout* p_sample)
{
    SessionItem* p_parent = m_levelToParentItem[depth() - 1];
    SessionItem* p_layout_item(nullptr);
    if (p_parent) {
        p_layout_item =
            m_sampleModel->insertNewItem("ParticleLayout", m_sampleModel->indexOfItem(p_parent));
    } else {
        p_layout_item = m_sampleModel->insertNewItem("ParticleLayout");
    }
    p_layout_item->setItemValue(ParticleLayoutItem::P_TOTAL_DENSITY,
                                p_sample->totalParticleSurfaceDensity());
    p_layout_item->setItemValue(ParticleLayoutItem::P_WEIGHT, p_sample->weight());
    m_levelToParentItem[depth()] = p_layout_item;
}

void GUIDomainSampleVisitor::visit(const Layer* p_sample)
{
    SessionItem* p_parent = m_levelToParentItem[depth() - 1];
    ASSERT(p_parent);

    auto p_multilayer = dynamic_cast<const MultiLayer*>(m_itemToSample[p_parent]);
    ASSERT(p_multilayer);
    size_t layer_index = MultiLayerUtils::IndexOfLayer(*p_multilayer, p_sample);
    const LayerInterface* p_interface =
        MultiLayerUtils::LayerTopInterface(*p_multilayer, layer_index);

    SessionItem* p_layer_item =
        m_sampleModel->insertNewItem("Layer", m_sampleModel->indexOfItem(p_parent));
    p_layer_item->setItemValue(LayerItem::P_MATERIAL,
                               createMaterialFromDomain(p_sample->material()).variant());

    TransformFromDomain::setLayerItem(p_layer_item, p_sample, p_interface);

    m_levelToParentItem[depth()] = p_layer_item;
}

void GUIDomainSampleVisitor::visit(const MultiLayer* p_sample)
{
    SessionItem* p_multilayer_item = m_sampleModel->insertNewItem("MultiLayer");
    p_multilayer_item->setItemName(p_sample->getName().c_str());
    p_multilayer_item->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH,
                                    p_sample->crossCorrLength());
    SetVectorItem(*p_multilayer_item, MultiLayerItem::P_EXTERNAL_FIELD, p_sample->externalField());
    m_levelToParentItem[depth()] = p_multilayer_item;
    m_itemToSample[p_multilayer_item] = p_sample;
}

void GUIDomainSampleVisitor::visit(const Particle* p_sample)
{
    auto p_particle_item = InsertIParticle(p_sample, "Particle");
    p_particle_item->setItemValue(ParticleItem::P_MATERIAL,
                                  createMaterialFromDomain(p_sample->material()).variant());
}

void GUIDomainSampleVisitor::visit(const ParticleDistribution* p_sample)
{
    SessionItem* p_layout_item = m_levelToParentItem[depth() - 1];
    ASSERT(p_layout_item);
    SessionItem* p_particle_distribution_item = m_sampleModel->insertNewItem(
        "ParticleDistribution", m_sampleModel->indexOfItem(p_layout_item));
    ASSERT(p_particle_distribution_item);

    TransformFromDomain::setParticleDistributionItem(p_particle_distribution_item, *p_sample);

    m_levelToParentItem[depth()] = p_particle_distribution_item;
    m_itemToSample[p_particle_distribution_item] = p_sample;
}

void GUIDomainSampleVisitor::visit(const ParticleCoreShell* p_sample)
{
    InsertIParticle(p_sample, "ParticleCoreShell");
}

void GUIDomainSampleVisitor::visit(const ParticleComposition* p_sample)
{
    InsertIParticle(p_sample, "ParticleComposition");
}

void GUIDomainSampleVisitor::visit(const MesoCrystal* p_sample)
{
    InsertIParticle(p_sample, "MesoCrystal");
}

void GUIDomainSampleVisitor::visit(const Crystal* p_sample)
{
    SessionItem* p_mesocrystal_item = m_levelToParentItem[depth() - 1];
    ASSERT(p_mesocrystal_item);
    if (p_mesocrystal_item->modelType() != "MesoCrystal") {
        throw GUIHelpers::Error("GUIObjectBuilder::visit(const Crystal*) "
                                "-> Error. Parent is not a MesoCrystal");
    }
    auto lattice = p_sample->transformedLattice();
    auto vector_a = lattice.getBasisVectorA();
    auto vector_b = lattice.getBasisVectorB();
    auto vector_c = lattice.getBasisVectorC();

    SetVectorItem(*p_mesocrystal_item, MesoCrystalItem::P_VECTOR_A, vector_a);
    SetVectorItem(*p_mesocrystal_item, MesoCrystalItem::P_VECTOR_B, vector_b);
    SetVectorItem(*p_mesocrystal_item, MesoCrystalItem::P_VECTOR_C, vector_c);

    // Since there is no CrystalItem, set the parent map to the MesoCrystalItem
    m_levelToParentItem[depth()] = p_mesocrystal_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorAnisoPyramid* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "AnisoPyramid");
    p_ff_item->setItemValue(AnisoPyramidItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(AnisoPyramidItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(AnisoPyramidItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(AnisoPyramidItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorBarGauss* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "BarGauss");
    p_ff_item->setItemValue(BarGaussItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(BarGaussItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(BarGaussItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorBarLorentz* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "BarLorentz");
    p_ff_item->setItemValue(BarLorentzItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(BarLorentzItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(BarLorentzItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorBox* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Box");
    p_ff_item->setItemValue(BoxItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(BoxItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(BoxItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCone* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Cone");
    p_ff_item->setItemValue(ConeItem::P_RADIUS, p_sample->getRadius());
    p_ff_item->setItemValue(ConeItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(ConeItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCone6* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Cone6");
    p_ff_item->setItemValue(Cone6Item::P_BASEEDGE, p_sample->getBaseEdge());
    p_ff_item->setItemValue(Cone6Item::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(Cone6Item::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCuboctahedron* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Cuboctahedron");
    p_ff_item->setItemValue(CuboctahedronItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(CuboctahedronItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(CuboctahedronItem::P_HEIGHT_RATIO, p_sample->getHeightRatio());
    p_ff_item->setItemValue(CuboctahedronItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCylinder* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Cylinder");
    p_ff_item->setItemValue(CylinderItem::P_RADIUS, p_sample->getRadius());
    p_ff_item->setItemValue(CylinderItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorDodecahedron* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Dodecahedron");
    p_ff_item->setItemValue(DodecahedronItem::P_EDGE, p_sample->getEdge());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorDot* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Dot");
    p_ff_item->setItemValue(FullSphereItem::P_RADIUS, p_sample->getRadius());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorEllipsoidalCylinder* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "EllipsoidalCylinder");
    p_ff_item->setItemValue(EllipsoidalCylinderItem::P_RADIUS_X, p_sample->getRadiusX());
    p_ff_item->setItemValue(EllipsoidalCylinderItem::P_RADIUS_Y, p_sample->getRadiusY());
    p_ff_item->setItemValue(EllipsoidalCylinderItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorFullSphere* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "FullSphere");
    p_ff_item->setItemValue(FullSphereItem::P_RADIUS, p_sample->getRadius());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorFullSpheroid* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "FullSpheroid");
    p_ff_item->setItemValue(FullSpheroidItem::P_RADIUS, p_sample->getRadius());
    p_ff_item->setItemValue(FullSpheroidItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorIcosahedron* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Icosahedron");
    p_ff_item->setItemValue(IcosahedronItem::P_EDGE, p_sample->getEdge());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorHemiEllipsoid* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "HemiEllipsoid");
    p_ff_item->setItemValue(HemiEllipsoidItem::P_RADIUS_X, p_sample->getRadiusX());
    p_ff_item->setItemValue(HemiEllipsoidItem::P_RADIUS_Y, p_sample->getRadiusY());
    p_ff_item->setItemValue(HemiEllipsoidItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorPrism3* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Prism3");
    p_ff_item->setItemValue(Prism3Item::P_BASEEDGE, p_sample->getBaseEdge());
    p_ff_item->setItemValue(Prism3Item::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorPrism6* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Prism6");
    p_ff_item->setItemValue(Prism6Item::P_BASEEDGE, p_sample->getBaseEdge());
    p_ff_item->setItemValue(Prism6Item::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorPyramid* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Pyramid");
    p_ff_item->setItemValue(PyramidItem::P_BASEEDGE, p_sample->getBaseEdge());
    p_ff_item->setItemValue(PyramidItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(PyramidItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCosineRippleBox* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "CosineRippleBox");
    p_ff_item->setItemValue(CosineRippleBoxItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(CosineRippleBoxItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(CosineRippleBoxItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCosineRippleGauss* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "CosineRippleGauss");
    p_ff_item->setItemValue(CosineRippleGaussItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(CosineRippleGaussItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(CosineRippleGaussItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorCosineRippleLorentz* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "CosineRippleLorentz");
    p_ff_item->setItemValue(CosineRippleLorentzItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(CosineRippleLorentzItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(CosineRippleLorentzItem::P_HEIGHT, p_sample->getHeight());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorSawtoothRippleBox* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "SawtoothRippleBox");
    p_ff_item->setItemValue(SawtoothRippleBoxItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(SawtoothRippleBoxItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(SawtoothRippleBoxItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(SawtoothRippleBoxItem::P_ASYMMETRY, p_sample->getAsymmetry());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorSawtoothRippleGauss* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "SawtoothRippleGauss");
    p_ff_item->setItemValue(SawtoothRippleGaussItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(SawtoothRippleGaussItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(SawtoothRippleGaussItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(SawtoothRippleGaussItem::P_ASYMMETRY, p_sample->getAsymmetry());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorSawtoothRippleLorentz* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "SawtoothRippleLorentz");
    p_ff_item->setItemValue(SawtoothRippleLorentzItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(SawtoothRippleLorentzItem::P_WIDTH, p_sample->getWidth());
    p_ff_item->setItemValue(SawtoothRippleLorentzItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(SawtoothRippleLorentzItem::P_ASYMMETRY, p_sample->getAsymmetry());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorTetrahedron* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "Tetrahedron");
    p_ff_item->setItemValue(TetrahedronItem::P_BASEEDGE, p_sample->getBaseEdge());
    p_ff_item->setItemValue(TetrahedronItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(TetrahedronItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorTruncatedCube* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "TruncatedCube");
    p_ff_item->setItemValue(TruncatedCubeItem::P_LENGTH, p_sample->getLength());
    p_ff_item->setItemValue(TruncatedCubeItem::P_REMOVED_LENGTH, p_sample->getRemovedLength());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorTruncatedSphere* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "TruncatedSphere");
    p_ff_item->setItemValue(TruncatedSphereItem::P_RADIUS, p_sample->getRadius());
    p_ff_item->setItemValue(TruncatedSphereItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(TruncatedSphereItem::P_REMOVED_TOP, p_sample->getRemovedTop());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const FormFactorTruncatedSpheroid* p_sample)
{
    SessionItem* p_particle_item = m_levelToParentItem[depth() - 1];
    SessionItem* p_ff_item = AddFormFactorItem(p_particle_item, "TruncatedSpheroid");
    p_ff_item->setItemValue(TruncatedSpheroidItem::P_RADIUS, p_sample->getRadius());
    p_ff_item->setItemValue(TruncatedSpheroidItem::P_HEIGHT, p_sample->getHeight());
    p_ff_item->setItemValue(TruncatedSpheroidItem::P_HFC, p_sample->getHeightFlattening());
    p_ff_item->setItemValue(TruncatedSpheroidItem::P_REMOVED_TOP, p_sample->getRemovedTop());
    m_levelToParentItem[depth()] = p_particle_item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunction1DLattice* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item =
        m_sampleModel->insertNewItem("Interference1DLattice", m_sampleModel->indexOfItem(parent),
                                     -1, ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::set1DLatticeItem(item, *p_sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunction2DLattice* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item =
        m_sampleModel->insertNewItem("Interference2DLattice", m_sampleModel->indexOfItem(parent),
                                     -1, ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::set2DLatticeItem(item, *p_sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunction2DParaCrystal* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem("Interference2DParaCrystal",
                                                     m_sampleModel->indexOfItem(parent), -1,
                                                     ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::set2DParaCrystalItem(item, *p_sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunctionFinite2DLattice* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem("InterferenceFinite2DLattice",
                                                     m_sampleModel->indexOfItem(parent), -1,
                                                     ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::setFinite2DLatticeItem(item, *p_sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunctionHardDisk* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item =
        m_sampleModel->insertNewItem("InterferenceHardDisk", m_sampleModel->indexOfItem(parent), -1,
                                     ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::setHardDiskItem(item, *p_sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const InterferenceFunctionRadialParaCrystal* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem("InterferenceRadialParaCrystal",
                                                     m_sampleModel->indexOfItem(parent), -1,
                                                     ParticleLayoutItem::T_INTERFERENCE);
    ASSERT(item);
    TransformFromDomain::setRadialParaCrystalItem(item, *p_sample);
    m_levelToParentItem[depth()] = item;
}

void GUIDomainSampleVisitor::visit(const RotationX* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        "Rotation", m_sampleModel->indexOfItem(parent), -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* p_rotationItem =
        transformation_item->setGroupProperty(TransformationItem::P_ROT, "XRotation");
    p_rotationItem->setItemValue(XRotationItem::P_ANGLE, Units::rad2deg(p_sample->getAngle()));
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIDomainSampleVisitor::visit(const RotationY* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        "Rotation", m_sampleModel->indexOfItem(parent), -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* p_rotationItem =
        transformation_item->setGroupProperty(TransformationItem::P_ROT, "YRotation");
    p_rotationItem->setItemValue(YRotationItem::P_ANGLE, Units::rad2deg(p_sample->getAngle()));
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIDomainSampleVisitor::visit(const RotationZ* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        "Rotation", m_sampleModel->indexOfItem(parent), -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* p_rotationItem =
        transformation_item->setGroupProperty(TransformationItem::P_ROT, "ZRotation");
    p_rotationItem->setItemValue(ZRotationItem::P_ANGLE, Units::rad2deg(p_sample->getAngle()));
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIDomainSampleVisitor::visit(const RotationEuler* p_sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        "Rotation", m_sampleModel->indexOfItem(parent), -1, ParticleItem::T_TRANSFORMATION);
    ASSERT(transformation_item);
    SessionItem* p_rotationItem =
        transformation_item->setGroupProperty(TransformationItem::P_ROT, "EulerRotation");
    p_rotationItem->setItemValue(EulerRotationItem::P_ALPHA, Units::rad2deg(p_sample->getAlpha()));
    p_rotationItem->setItemValue(EulerRotationItem::P_BETA, Units::rad2deg(p_sample->getBeta()));
    p_rotationItem->setItemValue(EulerRotationItem::P_GAMMA, Units::rad2deg(p_sample->getGamma()));
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIDomainSampleVisitor::buildPositionInfo(SessionItem* p_particle_item,
                                               const IParticle* p_sample)
{
    kvector_t position = p_sample->position();
    SetVectorItem(*p_particle_item, ParticleItem::P_POSITION, position);
}

ExternalProperty GUIDomainSampleVisitor::createMaterialFromDomain(const Material* material)
{
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

SessionItem* GUIDomainSampleVisitor::InsertIParticle(const IParticle* p_particle,
                                                     QString model_type)
{
    auto p_parent = m_levelToParentItem[depth() - 1];
    ASSERT(p_parent);

    QString tag;
    auto parent_type = p_parent->modelType();
    if (model_type == "Particle") {
        if (parent_type == "ParticleCoreShell") {
            const ParticleCoreShell* p_coreshell =
                dynamic_cast<const ParticleCoreShell*>(m_itemToSample[p_parent]);
            ASSERT(p_coreshell);
            if (p_particle == p_coreshell->coreParticle()) {
                tag = ParticleCoreShellItem::T_CORE;
            } else if (p_particle == p_coreshell->shellParticle()) {
                tag = ParticleCoreShellItem::T_SHELL;
            } else {
                throw GUIHelpers::Error("GUIObjectBuilder::InsertIParticle:"
                                        "Particle not found in parent ParticleCoreShell");
            }
        }
    }
    SessionItem* p_particle_item =
        m_sampleModel->insertNewItem(model_type, m_sampleModel->indexOfItem(p_parent), -1, tag);

    ASSERT(p_particle_item);
    p_particle_item->setItemValue(ParticleItem::P_ABUNDANCE, p_particle->abundance());
    buildPositionInfo(p_particle_item, p_particle);

    m_levelToParentItem[depth()] = p_particle_item;
    m_itemToSample[p_particle_item] = p_particle;

    return p_particle_item;
}

namespace
{
SessionItem* AddFormFactorItem(SessionItem* p_parent, const QString& model_type)
{
    auto parent_type = p_parent->modelType();
    QString property_name;
    if (parent_type == "Particle") {
        property_name = ParticleItem::P_FORM_FACTOR;
    } else if (parent_type == "MesoCrystal") {
        property_name = MesoCrystalItem::P_OUTER_SHAPE;
    }
    if (property_name.isEmpty()) {
        throw GUIHelpers::Error("AddFormFactorItem: parent is neither ParticleItem or "
                                "MesoCrystalItem");
    }
    return p_parent->setGroupProperty(property_name, model_type);
}
} // namespace
