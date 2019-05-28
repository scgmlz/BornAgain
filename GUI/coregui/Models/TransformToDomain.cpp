// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformToDomain.cpp
//! @brief     Implements class TransformToDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "TransformToDomain.h"
#include "BeamAngleItems.h"
#include "BeamItems.h"
#include "BeamWavelengthItem.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "DetectorItems.h"
#include "SphericalDetectorItem.h"
#include "FlatDetectorItem.h"
#include "Distributions.h"
#include "FTDecayFunctionItems.h"
#include "FTDistributionItems.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "InterferenceFunctions.h"
#include "JobItem.h"
#include "JobModelFunctions.h"
#include "Lattice2DItems.h"
#include "LayerItem.h"
#include "LayerRoughnessItems.h"
#include "MaskItems.h"
#include "MaterialItemUtils.h"
#include "MesoCrystal.h"
#include "MesoCrystalItem.h"
#include "MultiLayerItem.h"
#include "ParameterPattern.h"
#include "Particle.h"
#include "ParticleCompositionItem.h"
#include "ParticleCoreShell.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistributionItem.h"
#include "ParticleItem.h"
#include "ParticleLayoutItem.h"
#include "RotationItems.h"
#include "SessionItemUtils.h"
#include "SimulationOptionsItem.h"
#include "SpecularBeamInclinationItem.h"
#include "SpecularSimulation.h"
#include "TransformationItem.h"
#include "Units.h"
#include "VectorItem.h"

using SessionItemUtils::GetVectorItem;

namespace
{
template <class T>
void setParameterDistributionToSimulation(const std::string& parameter_name,
                                          const SessionItem* item, Simulation& simulation);
}

std::unique_ptr<Material>
TransformToDomain::createDomainMaterial(const SessionItem& item)
{
    auto parent_job = JobModelFunctions::findJobItem(&item);
    const MaterialItemContainer* container =
        parent_job ? parent_job->materialContainerItem() : nullptr;
    QString tag = MaterialItemUtils::materialTag(item);
    ExternalProperty property = item.getItemValue(tag).value<ExternalProperty>();
    return container ? MaterialItemUtils::createDomainMaterial(property, *container)
                     : MaterialItemUtils::createDomainMaterial(property);
}

std::unique_ptr<MultiLayer> TransformToDomain::createMultiLayer(const SessionItem& item)
{
    auto P_multilayer = std::make_unique<MultiLayer>();
    auto cross_corr_length
        = item.getItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH).toDouble();
    if (cross_corr_length > 0)
        P_multilayer->setCrossCorrLength(cross_corr_length);
    auto external_field = GetVectorItem(item, MultiLayerItem::P_EXTERNAL_FIELD);
    P_multilayer->setExternalField(external_field);
    return P_multilayer;
}

std::unique_ptr<Layer> TransformToDomain::createLayer(const SessionItem& item)
{
    auto P_layer = std::make_unique<Layer>(
        *createDomainMaterial(item),
        item.getItemValue(LayerItem::P_THICKNESS).toDouble());
    P_layer->setNumberOfSlices(item.getItemValue(LayerItem::P_NSLICES).toUInt());
    return P_layer;
}

std::unique_ptr<LayerRoughness>
TransformToDomain::createLayerRoughness(const SessionItem& roughnessItem)
{
    if (roughnessItem.modelType() == Constants::LayerZeroRoughnessType) {
        return nullptr;
    } else if (roughnessItem.modelType() == Constants::LayerBasicRoughnessType) {
        return std::make_unique<LayerRoughness>(
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_SIGMA).toDouble(),
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_HURST).toDouble(),
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH)
                .toDouble());
    } else {
        throw GUIHelpers::Error("TransformToDomain::createLayerRoughness() -> Error.");
    }
}

std::unique_ptr<ParticleLayout> TransformToDomain::createParticleLayout(const SessionItem& item)
{
    auto P_layout = std::make_unique<ParticleLayout>();
    auto prop = item.getItemValue(ParticleLayoutItem::P_APPROX).value<ComboProperty>();
    QString approximation = prop.getValue();
    if (approximation == Constants::LAYOUT_DA) {
        P_layout->setApproximation(ILayout::DA);
    } else if (approximation == Constants::LAYOUT_SSCA) {
        P_layout->setApproximation(ILayout::SSCA);
    }
    auto total_density = item.getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).value<double>();
    auto layout_weight = item.getItemValue(ParticleLayoutItem::P_WEIGHT).value<double>();
    P_layout->setTotalParticleSurfaceDensity(total_density);
    P_layout->setWeight(layout_weight);
    return P_layout;
}

std::unique_ptr<IParticle> TransformToDomain::createIParticle(const SessionItem& item)
{
    std::unique_ptr<IParticle> P_particle;
    if (item.modelType() == Constants::ParticleType) {
        auto& particle_item = static_cast<const ParticleItem&>(item);
        P_particle = particle_item.createParticle();
    } else if (item.modelType() == Constants::ParticleCoreShellType) {
        auto& particle_coreshell_item = static_cast<const ParticleCoreShellItem&>(item);
        P_particle = particle_coreshell_item.createParticleCoreShell();
    } else if (item.modelType() == Constants::ParticleCompositionType) {
        auto& particle_composition_item = static_cast<const ParticleCompositionItem&>(item);
        P_particle = particle_composition_item.createParticleComposition();
    } else if (item.modelType() == Constants::MesoCrystalType) {
        auto& mesocrystal_item = static_cast<const MesoCrystalItem&>(item);
        P_particle = mesocrystal_item.createMesoCrystal();
    }
    return P_particle;
}

std::unique_ptr<ParticleDistribution> TransformToDomain::createParticleDistribution(
        const SessionItem& item)
{
    auto& particle_distribution = static_cast<const ParticleDistributionItem&>(item);
    auto P_part_distr = particle_distribution.createParticleDistribution();
    return P_part_distr;
}

//! adds DistributionParameters to the Simulation
void TransformToDomain::addDistributionParametersToSimulation(const SessionItem& beam_item,
                                                              GISASSimulation& simulation)
{
    if (beam_item.modelType() != Constants::GISASBeamType) {
        Q_ASSERT(beam_item.modelType() == Constants::GISASBeamType);
        return;
    }

    setParameterDistributionToSimulation<BeamWavelengthItem>(
        BornAgain::Wavelength, beam_item.getItem(BeamItem::P_WAVELENGTH), simulation);
    setParameterDistributionToSimulation<BeamInclinationAngleItem>(
        BornAgain::Inclination, beam_item.getItem(BeamItem::P_INCLINATION_ANGLE), simulation);
    setParameterDistributionToSimulation<BeamAzimuthalAngleItem>(
        BornAgain::Azimuth, beam_item.getItem(BeamItem::P_AZIMUTHAL_ANGLE), simulation);
}

void TransformToDomain::addDistributionParametersToSimulation(const SessionItem& beam_item,
                                                              SpecularSimulation& simulation)
{
    if (beam_item.modelType() != Constants::SpecularBeamType) {
        Q_ASSERT(beam_item.modelType() == Constants::SpecularBeamType);
        return;
    }

    setParameterDistributionToSimulation<BeamWavelengthItem>(
        BornAgain::Wavelength, beam_item.getItem(SpecularBeamItem::P_WAVELENGTH), simulation);
    setParameterDistributionToSimulation<SpecularBeamInclinationItem>(
        BornAgain::Inclination, beam_item.getItem(SpecularBeamItem::P_INCLINATION_ANGLE),
        simulation);
}

// TODO Consider removal addDistributionParametersToSimulation and
// template <class T> void setParameterDistributionToSimulation in the favor
// of setBeamDistribution.

void TransformToDomain::setBeamDistribution(const std::string& parameter_name,
                              const BeamDistributionItem& item, Simulation& simulation)
{
    ParameterPattern parameter_pattern;
    parameter_pattern.beginsWith("*").add(BornAgain::BeamType).add(parameter_name);

    auto P_par_distr = item.getParameterDistributionForName(parameter_pattern.toStdString());
    if (P_par_distr)
        simulation.addParameterDistribution(*P_par_distr);
}

void TransformToDomain::setSimulationOptions(Simulation* simulation,
                                             const SessionItem& item)
{
    Q_ASSERT(item.modelType() == Constants::SimulationOptionsType);

    if (auto optionItem = dynamic_cast<const SimulationOptionsItem*>(&item)) {
        simulation->getOptions().setNumberOfThreads(optionItem->getNumberOfThreads());
        if (optionItem->getComputationMethod() == Constants::SIMULATION_MONTECARLO) {
            simulation->getOptions().setMonteCarloIntegration(true,
                    optionItem->getNumberOfMonteCarloPoints());
        }
        if (optionItem->getFresnelMaterialMethod() == Constants::AVERAGE_LAYER_MATERIAL)
            simulation->getOptions().setUseAvgMaterials(true);
        if (optionItem->getIncludeSpecularPeak() == Constants::Yes)
            simulation->getOptions().setIncludeSpecular(true);
    }
}

void TransformToDomain::setTransformationInfo(IParticle* result, const SessionItem& item)
{
    setPositionInfo(result, item);
    setRotationInfo(result, item);
}

void TransformToDomain::setPositionInfo(IParticle* result, const SessionItem& item)
{
    kvector_t pos = GetVectorItem(item, ParticleItem::P_POSITION);
    result->setPosition(pos.x(), pos.y(), pos.z());
}

void TransformToDomain::setRotationInfo(IParticle* result, const SessionItem& item)
{
    QVector<SessionItem*> children = item.children();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i]->modelType() == Constants::RotationType) {
            auto& rot_item = children[i]->groupItem<RotationItem>(TransformationItem::P_ROT);
            auto rotation = rot_item.createRotation();
            if (rotation)
                result->setRotation(*rotation);
            break;
        }
    }
}

namespace  {
template <class T>
void setParameterDistributionToSimulation(const std::string& parameter_name,
                                          const SessionItem* item, Simulation& simulation)
{
    const auto parameter_item = dynamic_cast<const T*>(item);
    if (!parameter_item) {
        Q_ASSERT(parameter_item);
        return;
    }

    ParameterPattern parameter_pattern;
    parameter_pattern.beginsWith("*").add(BornAgain::BeamType).add(parameter_name);

    auto P_par_distr
        = parameter_item->getParameterDistributionForName(parameter_pattern.toStdString());
    if (P_par_distr)
        simulation.addParameterDistribution(*P_par_distr);
}
}
