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

#include "GUI/coregui/Models/TransformToDomain.h"
#include "Core/Basics/Units.h"
#include "Core/Detector/ScanResolution.h"
#include "Core/Instrument/AngularSpecScan.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterPattern.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "Core/Particle/MesoCrystal.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleCoreShell.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/includeIncludes/InterferenceFunctions.h"
#include "GUI/coregui/Models/BeamAngleItems.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/BeamWavelengthItem.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/FTDecayFunctionItems.h"
#include "GUI/coregui/Models/FTDistributionItems.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModelFunctions.h"
#include "GUI/coregui/Models/Lattice2DItems.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/LayerRoughnessItems.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/MesoCrystalItem.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/ParticleCompositionItem.h"
#include "GUI/coregui/Models/ParticleCoreShellItem.h"
#include "GUI/coregui/Models/ParticleDistributionItem.h"
#include "GUI/coregui/Models/ParticleItem.h"
#include "GUI/coregui/Models/ParticleLayoutItem.h"
#include "GUI/coregui/Models/RectangularDetectorItem.h"
#include "GUI/coregui/Models/RotationItems.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Models/SphericalDetectorItem.h"
#include "GUI/coregui/Models/TransformationItem.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"

using SessionItemUtils::GetVectorItem;

namespace
{
template <class T>
void setParameterDistributionToSimulation(const std::string& parameter_name,
                                          const SessionItem* item, Simulation& simulation);

std::unique_ptr<ScanResolution> createScanResolution(const SessionItem* item);
} // namespace

std::unique_ptr<Material> TransformToDomain::createDomainMaterial(const SessionItem& item)
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
    auto cross_corr_length = item.getItemValue(MultiLayerItem::P_CROSS_CORR_LENGTH).toDouble();
    if (cross_corr_length > 0)
        P_multilayer->setCrossCorrLength(cross_corr_length);
    auto external_field = GetVectorItem(item, MultiLayerItem::P_EXTERNAL_FIELD);
    P_multilayer->setExternalField(external_field);
    return P_multilayer;
}

std::unique_ptr<Layer> TransformToDomain::createLayer(const SessionItem& item)
{
    auto P_layer = std::make_unique<Layer>(*createDomainMaterial(item),
                                           item.getItemValue(LayerItem::P_THICKNESS).toDouble());
    P_layer->setNumberOfSlices(item.getItemValue(LayerItem::P_NSLICES).toUInt());
    return P_layer;
}

std::unique_ptr<LayerRoughness>
TransformToDomain::createLayerRoughness(const SessionItem& roughnessItem)
{
    if (roughnessItem.modelType() == "LayerZeroRoughness") {
        return nullptr;
    } else if (roughnessItem.modelType() == "LayerBasicRoughness") {
        return std::make_unique<LayerRoughness>(
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_SIGMA).toDouble(),
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_HURST).toDouble(),
            roughnessItem.getItemValue(LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH).toDouble());
    } else {
        throw GUIHelpers::Error("TransformToDomain::createLayerRoughness() -> Error.");
    }
}

std::unique_ptr<ParticleLayout> TransformToDomain::createParticleLayout(const SessionItem& item)
{
    auto P_layout = std::make_unique<ParticleLayout>();
    auto total_density = item.getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).value<double>();
    auto layout_weight = item.getItemValue(ParticleLayoutItem::P_WEIGHT).value<double>();
    P_layout->setTotalParticleSurfaceDensity(total_density);
    P_layout->setWeight(layout_weight);
    return P_layout;
}

std::unique_ptr<IParticle> TransformToDomain::createIParticle(const SessionItem& item)
{
    std::unique_ptr<IParticle> P_particle;
    if (item.modelType() == "Particle") {
        auto& particle_item = static_cast<const ParticleItem&>(item);
        P_particle = particle_item.createParticle();
    } else if (item.modelType() == "ParticleCoreShell") {
        auto& particle_coreshell_item = static_cast<const ParticleCoreShellItem&>(item);
        P_particle = particle_coreshell_item.createParticleCoreShell();
    } else if (item.modelType() == "ParticleComposition") {
        auto& particle_composition_item = static_cast<const ParticleCompositionItem&>(item);
        P_particle = particle_composition_item.createParticleComposition();
    } else if (item.modelType() == "MesoCrystal") {
        auto& mesocrystal_item = static_cast<const MesoCrystalItem&>(item);
        P_particle = mesocrystal_item.createMesoCrystal();
    }
    return P_particle;
}

std::unique_ptr<ParticleDistribution>
TransformToDomain::createParticleDistribution(const SessionItem& item)
{
    auto& particle_distribution = static_cast<const ParticleDistributionItem&>(item);
    auto P_part_distr = particle_distribution.createParticleDistribution();
    return P_part_distr;
}

//! adds DistributionParameters to the Simulation
void TransformToDomain::addDistributionParametersToSimulation(const SessionItem& beam_item,
                                                              GISASSimulation& simulation)
{
    if (beam_item.modelType() != "GISASBeam") {
        ASSERT(beam_item.modelType() == "GISASBeam");
        return;
    }

    setParameterDistributionToSimulation<BeamWavelengthItem>(
        "Wavelength", beam_item.getItem(BeamItem::P_WAVELENGTH), simulation);
    setParameterDistributionToSimulation<BeamInclinationAngleItem>(
        "InclinationAngle", beam_item.getItem(BeamItem::P_INCLINATION_ANGLE), simulation);
    setParameterDistributionToSimulation<BeamAzimuthalAngleItem>(
        "AzimuthalAngle", beam_item.getItem(BeamItem::P_AZIMUTHAL_ANGLE), simulation);
}

void TransformToDomain::addBeamDivergencesToScan(const SessionItem& beam_item,
                                                 AngularSpecScan& scan)
{
    if (beam_item.modelType() != "SpecularBeam") {
        ASSERT(beam_item.modelType() == "SpecularBeam");
        return;
    }

    auto resolution = createScanResolution(beam_item.getItem(SpecularBeamItem::P_WAVELENGTH));
    if (resolution)
        scan.setWavelengthResolution(*resolution);
    resolution = createScanResolution(beam_item.getItem(SpecularBeamItem::P_INCLINATION_ANGLE));
    if (resolution)
        scan.setAngleResolution(*resolution);
}

void TransformToDomain::setBeamDistribution(const std::string& parameter_name,
                                            const BeamDistributionItem& item,
                                            Simulation& simulation)
{
    ParameterPattern parameter_pattern;
    parameter_pattern.beginsWith("*").add("Beam").add(parameter_name);

    auto P_par_distr = item.getParameterDistributionForName(parameter_pattern.toStdString());
    if (P_par_distr)
        simulation.addParameterDistribution(*P_par_distr);
}

void TransformToDomain::setSimulationOptions(Simulation* simulation, const SessionItem& item)
{
    ASSERT(item.modelType() == "SimulationOptions");

    if (auto optionItem = dynamic_cast<const SimulationOptionsItem*>(&item)) {
        simulation->getOptions().setNumberOfThreads(optionItem->getNumberOfThreads());
        if (optionItem->getComputationMethod() == "Monte-Carlo Integration") {
            simulation->getOptions().setMonteCarloIntegration(
                true, optionItem->getNumberOfMonteCarloPoints());
        }
        if (optionItem->getFresnelMaterialMethod() == "Average Layer Material")
            simulation->getOptions().setUseAvgMaterials(true);
        if (optionItem->getIncludeSpecularPeak() == "Yes")
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
        if (children[i]->modelType() == "Rotation") {
            auto& rot_item = children[i]->groupItem<RotationItem>(TransformationItem::P_ROT);
            auto rotation = rot_item.createRotation();
            if (rotation)
                result->setRotation(*rotation);
            break;
        }
    }
}

namespace
{
template <class T>
void setParameterDistributionToSimulation(const std::string& parameter_name,
                                          const SessionItem* item, Simulation& simulation)
{
    const auto parameter_item = dynamic_cast<const T*>(item);
    if (!parameter_item) {
        ASSERT(parameter_item);
        return;
    }

    ParameterPattern parameter_pattern;
    parameter_pattern.beginsWith("*").add("Beam").add(parameter_name);

    auto P_par_distr =
        parameter_item->getParameterDistributionForName(parameter_pattern.toStdString());
    if (P_par_distr)
        simulation.addParameterDistribution(*P_par_distr);
}

std::unique_ptr<ScanResolution> createScanResolution(const SessionItem* item)
{
    auto beam_item = dynamic_cast<const BeamDistributionItem*>(item);
    if (!beam_item)
        return nullptr;

    auto distr_item = dynamic_cast<const SymmetricDistributionItem*>(
        beam_item->getGroupItem(BeamDistributionItem::P_DISTRIBUTION));
    if (!distr_item)
        return nullptr;

    const double scale = beam_item->scaleFactor();
    auto ranged_distr = distr_item->createRangedDistribution(scale);
    if (!ranged_distr)
        return nullptr;

    const double deviation = distr_item->deviation(scale);
    return std::unique_ptr<ScanResolution>(
        ScanResolution::scanAbsoluteResolution(*ranged_distr, deviation));
}
} // namespace
