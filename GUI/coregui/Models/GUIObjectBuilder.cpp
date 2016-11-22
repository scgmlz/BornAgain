// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIObjectBuilder.cpp
//! @brief     Implements class GUIObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIObjectBuilder.h"
#include "BeamDistributionItem.h"
#include "BeamItem.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "Crystal.h"
#include "DetectorItems.h"
#include "DocumentModel.h"
#include "FormFactorItems.h"
#include "FormFactors.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "IMaterial.h"
#include "InstrumentModel.h"
#include "IMultiLayerBuilder.h"
#include "Layer.h"
#include "LayerItem.h"
#include "MaterialModel.h"
#include "MaterialSvc.h"
#include "MaterialUtils.h"
#include "MultiLayer.h"
#include "MultiLayerItem.h"
#include "ParticleComposition.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "ParticleLayout.h"
#include "ParticleLayoutItem.h"
#include "RectangularDetector.h"
#include "RotationItems.h"
#include "SampleModel.h"
#include "SimulationOptionsItem.h"
#include "SphericalDetector.h"
#include "TransformFromDomain.h"
#include "TransformationItem.h"
#include "Units.h"
#include "VectorItem.h"
#include <QDebug>

GUIObjectBuilder::GUIObjectBuilder()
    : m_sampleModel(0)
{
}

SessionItem* GUIObjectBuilder::populateSampleModel(
    SampleModel* sampleModel, const GISASSimulation& simulation, const QString& sampleName)
{
    std::unique_ptr<ISample> P_sample;
    if(simulation.getSampleBuilder()) {
        P_sample.reset(simulation.getSampleBuilder()->buildSample());
    } else if(simulation.getSample()) {
        P_sample.reset(simulation.getSample()->clone());
    } else {
        throw GUIHelpers::Error("GUIObjectBuilder::populateSampleModel() -> No valid sample");
    }

    return populateSampleModel(sampleModel,* P_sample, sampleName);
}

SessionItem* GUIObjectBuilder::populateSampleModel(
    SampleModel* sampleModel, const ISample& sample, const QString& sampleName)
{
    Q_ASSERT(sampleModel);

    m_levelToParentItem.clear();

    m_topSampleName = sampleName;
    if(m_topSampleName.isEmpty()) m_topSampleName = sample.getName().c_str();

    m_sampleModel = sampleModel;

    VisitSampleTreePreorder(sample, *this);
    SessionItem* result = m_levelToParentItem[1];

    result->setItemName(m_topSampleName);
    return result;
}

SessionItem* GUIObjectBuilder::populateInstrumentModel(
    InstrumentModel* instrumentModel,
    const GISASSimulation& simulation, const QString& instrumentName)
{
    Q_ASSERT(instrumentModel);
    SessionItem* instrumentItem =
            instrumentModel->insertNewItem(Constants::InstrumentType);

    if(instrumentName.isEmpty()) {
        instrumentItem->setItemName(simulation.getInstrument().getName().c_str());
    } else {
        instrumentItem->setItemName(instrumentName);
    }

    // beam
    BeamItem* beamItem = dynamic_cast<BeamItem*>(instrumentModel->insertNewItem(
                Constants::BeamType,
                instrumentModel->indexOfItem(instrumentItem)));

    TransformFromDomain::setItemFromSample(beamItem, simulation);

    // detector
    DetectorItem* detectorItem = dynamic_cast<DetectorItem*>(instrumentModel->insertNewItem(
        Constants::DetectorType, instrumentModel->indexOfItem(instrumentItem)));
    TransformFromDomain::setItemFromSample(detectorItem, simulation);

    // detector masks
    TransformFromDomain::setDetectorMasks(detectorItem, simulation);


    return instrumentItem;
}

SessionItem* GUIObjectBuilder::populateDocumentModel(DocumentModel* documentModel,
                                                     const GISASSimulation& simulation)
{
    SimulationOptionsItem* optionsItem = dynamic_cast<SimulationOptionsItem*>(
            documentModel->insertNewItem(Constants::SimulationOptionsType));
    Q_ASSERT(optionsItem);
    if(simulation.getOptions().isIntegrate()) {
        optionsItem->setComputationMethod(Constants::SIMULATION_MONTECARLO);
        optionsItem->setNumberOfMonteCarloPoints(simulation.getOptions().getMcPoints());
    }
    return optionsItem;
}


void GUIObjectBuilder::visit(const ParticleLayout* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleLayout*)"  << depth();
    SessionItem* parent = m_levelToParentItem[depth()-1];
    SessionItem* item(0);
    if (parent) {
        item = m_sampleModel->insertNewItem(Constants::ParticleLayoutType,
                                         m_sampleModel->indexOfItem(parent));
    } else {
        item = m_sampleModel->insertNewItem(Constants::ParticleLayoutType);
    }

    ComboProperty approx_prop;
    approx_prop << "Decoupling Approximation"
                << "Size Space Coupling Approximation";
    ILayout::EInterferenceApproximation approx = sample->getApproximation();
    switch(approx)
    {
    case ILayout::DA:
        approx_prop.setValue("Decoupling Approximation");
        break;
    case ILayout::SSCA:
        approx_prop.setValue("Size Space Coupling Approximation");
        break;
    default:
        approx_prop.setValue("Decoupling Approximation");
        break;
    }
    item->setItemValue(ParticleLayoutItem::P_APPROX, approx_prop.getVariant());
    item->setItemValue(ParticleLayoutItem::P_TOTAL_DENSITY,
                       sample->getTotalParticleSurfaceDensity());
    m_levelToParentItem[depth()] = item;
}

void GUIObjectBuilder::visit(const Layer* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const Layer*)"  << depth();
    SessionItem* parent = m_levelToParentItem[depth()-1];
    Q_ASSERT(parent);

    auto multilayer = dynamic_cast<const MultiLayer*>(m_itemToSample[parent]);
    Q_ASSERT(multilayer);
    int layer_index = multilayer->getIndexOfLayer(sample);
    Q_ASSERT(layer_index != -1);
    const LayerInterface* interface = multilayer->getLayerTopInterface(layer_index);

    SessionItem* layerItem = m_sampleModel->insertNewItem(
        Constants::LayerType, m_sampleModel->indexOfItem(parent));
    layerItem->setItemValue(LayerItem::P_MATERIAL,
        createMaterialFromDomain(sample->getMaterial()).getVariant());

    TransformFromDomain::setItemFromSample(layerItem, sample, interface);

    m_levelToParentItem[depth()] = layerItem;
}

void GUIObjectBuilder::visit(const LayerInterface*)
{
    qDebug() << "GUIObjectBuilder::visit(const LayerInterface*)" << depth();
}

void GUIObjectBuilder::visit(const MultiLayer* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const MultiLayer*)" << depth();

    SessionItem* item =
            m_sampleModel->insertNewItem(Constants::MultiLayerType);
    item->setItemName(sample->getName().c_str());
    item->setItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH, sample->getCrossCorrLength());
    m_levelToParentItem[depth()] = item;
    m_itemToSample[item] = sample;
}

void GUIObjectBuilder::visit(const Particle* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const Particle*)" << depth();

    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);

    SessionItem* particleItem(0);
    if (parent->modelType() == Constants::ParticleCoreShellType) {
        const ParticleCoreShell* coreshell
            = dynamic_cast<const ParticleCoreShell*>(m_itemToSample[parent]);
        Q_ASSERT(coreshell);
        if (sample == coreshell->getCoreParticle()) {
            particleItem = m_sampleModel->insertNewItem(Constants::ParticleType,
                                                        m_sampleModel->indexOfItem(parent), -1,
                                                        ParticleCoreShellItem::T_CORE);
            Q_ASSERT(particleItem);
        } else if (sample == coreshell->getShellParticle()) {
            particleItem = m_sampleModel->insertNewItem(Constants::ParticleType,
                                                        m_sampleModel->indexOfItem(parent), -1,
                                                        ParticleCoreShellItem::T_SHELL);
            Q_ASSERT(particleItem);
        } else {
            throw GUIHelpers::Error(
                "GUIObjectBuilder::visit"
                "(const Particle* sample) -> Error. Logically should not be here");
        }
    } else if (parent->modelType() == Constants::ParticleCompositionType
               || parent->modelType() == Constants::ParticleLayoutType
               || parent->modelType() == Constants::ParticleDistributionType) {
        particleItem = m_sampleModel->insertNewItem(Constants::ParticleType,
                                                    m_sampleModel->indexOfItem(parent));
    } else {
        throw GUIHelpers::Error("GUIObjectBuilder::visit"
                                "(const Particle* sample) -> Logic error.");
    }

    buildPositionInfo(particleItem, sample);

    particleItem->setItemValue(ParticleItem::P_ABUNDANCE, sample->getAbundance());
    particleItem->setItemValue(ParticleItem::P_MATERIAL,
        createMaterialFromDomain(sample->getMaterial()).getVariant());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const ParticleDistribution* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleDistribution*)" << depth();

    SessionItem* layoutItem = m_levelToParentItem[depth() - 1];
    Q_ASSERT(layoutItem);
    SessionItem* particle_distribution_item = m_sampleModel->insertNewItem(
        Constants::ParticleDistributionType, m_sampleModel->indexOfItem(layoutItem));
    Q_ASSERT(particle_distribution_item);

    TransformFromDomain::setItemFromSample(particle_distribution_item, sample);

    m_levelToParentItem[depth()] = particle_distribution_item;
    m_itemToSample[particle_distribution_item] = sample;
}

void GUIObjectBuilder::visit(const ParticleCoreShell* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleCoreShell*)" << depth();

    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);

    SessionItem* coreshellItem = m_sampleModel->insertNewItem(
        Constants::ParticleCoreShellType, m_sampleModel->indexOfItem(parent));
    coreshellItem->setItemValue(ParticleItem::P_ABUNDANCE, sample->getAbundance());

    buildPositionInfo(coreshellItem, sample);

    m_levelToParentItem[depth()] = coreshellItem;
    m_itemToSample[coreshellItem] = sample;
}

void GUIObjectBuilder::visit(const ParticleComposition* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const ParticleComposition*)" << depth();

    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);
    SessionItem* particle_composition_item = m_sampleModel->insertNewItem(
        Constants::ParticleCompositionType, m_sampleModel->indexOfItem(parent));
    particle_composition_item->setItemValue(ParticleItem::P_ABUNDANCE, sample->getAbundance());

    buildPositionInfo(particle_composition_item, sample);

    m_levelToParentItem[depth()] = particle_composition_item;
    m_itemToSample[particle_composition_item] = sample;
}

void GUIObjectBuilder::visit(const FormFactorAnisoPyramid* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::AnisoPyramidType);
    ffItem->setItemValue(AnisoPyramidItem::P_LENGTH, sample->getLength());
    ffItem->setItemValue(AnisoPyramidItem::P_WIDTH, sample->getWidth());
    ffItem->setItemValue(AnisoPyramidItem::P_HEIGHT, sample->getHeight());
    ffItem->setItemValue(AnisoPyramidItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorBox* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::BoxType);
    ffItem->setItemValue(BoxItem::P_LENGTH, sample->getLength());
    ffItem->setItemValue(BoxItem::P_WIDTH, sample->getWidth());
    ffItem->setItemValue(BoxItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorCone* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::ConeType);
    ffItem->setItemValue(ConeItem::P_RADIUS, sample->getRadius());
    ffItem->setItemValue(ConeItem::P_HEIGHT, sample->getHeight());
    ffItem->setItemValue(ConeItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorCone6* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Cone6Type);
    ffItem->setItemValue(Cone6Item::P_BASEEDGE, sample->getBaseEdge());
    ffItem->setItemValue(Cone6Item::P_HEIGHT, sample->getHeight());
    ffItem->setItemValue(Cone6Item::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorCuboctahedron* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::CuboctahedronType);
    ffItem->setItemValue(CuboctahedronItem::P_LENGTH, sample->getLength());
    ffItem->setItemValue(CuboctahedronItem::P_HEIGHT, sample->getHeight());
    ffItem->setItemValue(CuboctahedronItem::P_HEIGHT_RATIO, sample->getHeightRatio());
    ffItem->setItemValue(CuboctahedronItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorCylinder* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::CylinderType);
    ffItem->setItemValue(CylinderItem::P_RADIUS, sample->getRadius());
    ffItem->setItemValue(CylinderItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorDodecahedron* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::DodecahedronType);
    ffItem->setItemValue(DodecahedronItem::P_EDGE, sample->getEdge());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorEllipsoidalCylinder* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
       ParticleItem::P_FORM_FACTOR, Constants::EllipsoidalCylinderType);
    ffItem->setItemValue(EllipsoidalCylinderItem::P_RADIUS_X, sample->getRadiusX());
    ffItem->setItemValue(EllipsoidalCylinderItem::P_RADIUS_Y, sample->getRadiusY());
    ffItem->setItemValue(EllipsoidalCylinderItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorFullSphere* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::FullSphereType);
    ffItem->setItemValue(FullSphereItem::P_RADIUS, sample->getRadius());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorFullSpheroid* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::FullSpheroidType);
    ffItem->setItemValue(FullSpheroidItem::P_RADIUS, sample->getRadius());
    ffItem->setItemValue(FullSpheroidItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorIcosahedron* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::IcosahedronType);
    ffItem->setItemValue(IcosahedronItem::P_EDGE, sample->getEdge());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorHemiEllipsoid* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::HemiEllipsoidType);
    ffItem->setItemValue(HemiEllipsoidItem::P_RADIUS_X, sample->getRadiusX());
    ffItem->setItemValue(HemiEllipsoidItem::P_RADIUS_Y, sample->getRadiusY());
    ffItem->setItemValue(HemiEllipsoidItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorPrism3* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Prism3Type);
    ffItem->setItemValue(Prism3Item::P_BASEEDGE, sample->getBaseEdge());
    ffItem->setItemValue(Prism3Item::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorPrism6* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Prism6Type);
    ffItem->setItemValue(Prism6Item::P_BASEEDGE, sample->getBaseEdge());
    ffItem->setItemValue(Prism6Item::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorPyramid* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::PyramidType);
    ffItem->setItemValue(PyramidItem::P_BASEEDGE, sample->getBaseEdge());
    ffItem->setItemValue(PyramidItem::P_HEIGHT, sample->getHeight());
    ffItem->setItemValue(PyramidItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorRipple1* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Ripple1Type);
    ffItem->setItemValue(Ripple1Item::P_LENGTH, sample->getLength());
    ffItem->setItemValue(Ripple1Item::P_WIDTH, sample->getWidth());
    ffItem->setItemValue(Ripple1Item::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorRipple2* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::Ripple2Type);
    ffItem->setItemValue(Ripple2Item::P_LENGTH, sample->getLength());
    ffItem->setItemValue(Ripple2Item::P_WIDTH, sample->getWidth());
    ffItem->setItemValue(Ripple2Item::P_HEIGHT, sample->getHeight());
    ffItem->setItemValue(Ripple2Item::P_ASYMMETRY, sample->getAsymmetry());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorTetrahedron* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::TetrahedronType);
    ffItem->setItemValue(TetrahedronItem::P_BASEEDGE, sample->getBaseEdge());
    ffItem->setItemValue(TetrahedronItem::P_HEIGHT, sample->getHeight());
    ffItem->setItemValue(TetrahedronItem::P_ALPHA, Units::rad2deg(sample->getAlpha()));
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorTruncatedCube* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::TruncatedCubeType);
    ffItem->setItemValue(TruncatedCubeItem::P_LENGTH, sample->getLength());
    ffItem->setItemValue(TruncatedCubeItem::P_REMOVED_LENGTH, sample->getRemovedLength());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorTruncatedSphere* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
        ParticleItem::P_FORM_FACTOR, Constants::TruncatedSphereType);
    ffItem->setItemValue(TruncatedSphereItem::P_RADIUS, sample->getRadius());
    ffItem->setItemValue(TruncatedSphereItem::P_HEIGHT, sample->getHeight());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const FormFactorTruncatedSpheroid* sample)
{
    SessionItem* particleItem = m_levelToParentItem[depth()-1];
    SessionItem* ffItem = particleItem->setGroupProperty(
                ParticleItem::P_FORM_FACTOR, Constants::TruncatedSpheroidType);
    ffItem->setItemValue(TruncatedSpheroidItem::P_RADIUS, sample->getRadius());
    ffItem->setItemValue(TruncatedSpheroidItem::P_HEIGHT, sample->getHeight());
    ffItem->setItemValue(TruncatedSpheroidItem::P_HFC, sample->getHeightFlattening());
    m_levelToParentItem[depth()] = particleItem;
}

void GUIObjectBuilder::visit(const InterferenceFunctionRadialParaCrystal* sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunctionRadialParaCrystalType, m_sampleModel->indexOfItem(parent),
                -1, ParticleLayoutItem::T_INTERFERENCE);
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[depth()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction2DParaCrystal* sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction2DParaCrystalType, m_sampleModel->indexOfItem(parent),
                -1, ParticleLayoutItem::T_INTERFERENCE);
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[depth()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction1DLattice* sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction1DLatticeType, m_sampleModel->indexOfItem(parent),
                -1, ParticleLayoutItem::T_INTERFERENCE);
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[depth()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunction2DLattice* sample)
{
    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);
    SessionItem* item = m_sampleModel->insertNewItem(
        Constants::InterferenceFunction2DLatticeType, m_sampleModel->indexOfItem(parent),
                -1, ParticleLayoutItem::T_INTERFERENCE);
    Q_ASSERT(item);
    TransformFromDomain::setItemFromSample(item, sample);
    m_levelToParentItem[depth()] = item;
}

void GUIObjectBuilder::visit(const InterferenceFunctionNone*)
{
    qDebug() << "GUIObjectBuilder::visit(const InterferenceFunctionNone*)"
             << depth();
}

void GUIObjectBuilder::visit(const LayerRoughness*)
{
    qDebug() << "GUIObjectBuilder::visit(const LayerRoughness*)" << depth();
}

void GUIObjectBuilder::visit(const RotationX* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const RotationX*)" << depth();

    SessionItem* parent = m_levelToParentItem[depth()-1];
    Q_ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent),
                -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* p_rotationItem = transformation_item->setGroupProperty(
                TransformationItem::P_ROT, Constants::XRotationType);
    p_rotationItem->setItemValue(XRotationItem::P_ANGLE,
                                          Units::rad2deg(sample->getAngle()) );
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIObjectBuilder::visit(const RotationY* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const RotationY*)" << depth();

    SessionItem* parent = m_levelToParentItem[depth() - 1];
    Q_ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent),
                -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* p_rotationItem = transformation_item->setGroupProperty(
        TransformationItem::P_ROT, Constants::YRotationType);
    p_rotationItem->setItemValue(YRotationItem::P_ANGLE, Units::rad2deg(sample->getAngle()));
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIObjectBuilder::visit(const RotationZ* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const RotationZ*)" << depth();

    SessionItem* parent = m_levelToParentItem[depth()-1];
    Q_ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent),
                -1, ParticleItem::T_TRANSFORMATION);
    SessionItem* p_rotationItem = transformation_item->setGroupProperty(
                TransformationItem::P_ROT, Constants::ZRotationType);
    p_rotationItem->setItemValue(ZRotationItem::P_ANGLE, Units::rad2deg(sample->getAngle()) );
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIObjectBuilder::visit(const RotationEuler* sample)
{
    qDebug() << "GUIObjectBuilder::visit(const RotationEuler*)" << depth();

    SessionItem* parent = m_levelToParentItem[depth()-1];
    Q_ASSERT(parent);

    SessionItem* transformation_item = m_sampleModel->insertNewItem(
        Constants::TransformationType, m_sampleModel->indexOfItem(parent),
                -1, ParticleItem::T_TRANSFORMATION);
    Q_ASSERT(transformation_item);
    SessionItem* p_rotationItem = transformation_item->setGroupProperty(
                TransformationItem::P_ROT, Constants::EulerRotationType);
    p_rotationItem->setItemValue(EulerRotationItem::P_ALPHA,  Units::rad2deg(sample->getAlpha()) );
    p_rotationItem->setItemValue(EulerRotationItem::P_BETA, Units::rad2deg(sample->getBeta()) );
    p_rotationItem->setItemValue(EulerRotationItem::P_GAMMA, Units::rad2deg(sample->getGamma()) );
    m_levelToParentItem[depth()] = transformation_item;
}

void GUIObjectBuilder::buildPositionInfo(SessionItem* particleItem, const IParticle* sample)
{
    kvector_t position = sample->getPosition();
    SessionItem* positionItem = particleItem->getItem(ParticleItem::P_POSITION);
    Q_ASSERT(positionItem);
    positionItem->setItemValue(VectorItem::P_X, position.x());
    positionItem->setItemValue(VectorItem::P_Y, position.y());
    positionItem->setItemValue(VectorItem::P_Z, position.z());
}

MaterialProperty GUIObjectBuilder::createMaterialFromDomain(
        const IMaterial* material)
{
    QString materialName = m_topSampleName + QString("_") + QString(material->getName().c_str());

    MaterialProperty materialProperty = MaterialSvc::getMaterialProperty(materialName);
    if(materialProperty.isDefined()) return materialProperty;

    MaterialModel* model = MaterialSvc::getMaterialModel();

    if(material->isScalarMaterial()) {
        complex_t rindex = material->getRefractiveIndex();
        MaterialItem* materialItem  =
            model->addMaterial(materialName, 1-rindex.real(),rindex.imag());
        return MaterialProperty(materialItem->getIdentifier());
    } else {
        throw GUIHelpers::Error("GUIObjectBuilder::createMaterialFromDomain()"
                                " -> Not implemented.");
    }
}
