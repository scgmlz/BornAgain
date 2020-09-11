// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainSimulationBuilder.cpp
//! @brief     Implements class DomainSimulationBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/DomainSimulationBuilder.h"
#include "Core/Basics/Units.h"
#include "Core/Beam/IFootprintFactor.h"
#include "Core/Computation/IBackground.h"
#include "Core/Instrument/AngularSpecScan.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecSimulation.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/BackgroundItems.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/DepthProbeInstrumentItem.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/DomainObjectBuilder.h"
#include "GUI/coregui/Models/FootprintItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Models/TransformToDomain.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace
{
void addBackgroundToSimulation(const InstrumentItem& instrument, Simulation& simulation);

std::unique_ptr<GISASSimulation> createGISASSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                                                       const GISASInstrumentItem* gisasInstrument,
                                                       const SimulationOptionsItem* optionsItem);

std::unique_ptr<OffSpecSimulation>
createOffSpecSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                        const OffSpecInstrumentItem* offspecInstrument,
                        const SimulationOptionsItem* optionsItem);

std::unique_ptr<SpecularSimulation>
createSpecularSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                         const SpecularInstrumentItem* specular_instrument,
                         const SimulationOptionsItem* options_item);

std::unique_ptr<DepthProbeSimulation>
createDepthProbeSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                           const DepthProbeInstrumentItem* instrument,
                           const SimulationOptionsItem* options_item);

} // namespace

std::unique_ptr<Simulation>
DomainSimulationBuilder::createSimulation(const MultiLayerItem* sampleItem,
                                          const InstrumentItem* instrumentItem,
                                          const SimulationOptionsItem* optionsItem)
{
    if (sampleItem == nullptr || instrumentItem == nullptr) {
        QString message("DomainSimulationBuilder::getSimulation() -> Error. Either MultiLayerItem "
                        " or InstrumentItem is not defined.");
        throw GUIHelpers::Error(message);
    }

    auto P_multilayer = DomainObjectBuilder::buildMultiLayer(*sampleItem);

    if (auto gisasInstrument = dynamic_cast<const GISASInstrumentItem*>(instrumentItem))
        return createGISASSimulation(std::move(P_multilayer), gisasInstrument, optionsItem);
    else if (auto offspecInstrument = dynamic_cast<const OffSpecInstrumentItem*>(instrumentItem))
        return createOffSpecSimulation(std::move(P_multilayer), offspecInstrument, optionsItem);
    else if (auto specular_instrument = dynamic_cast<const SpecularInstrumentItem*>(instrumentItem))
        return createSpecularSimulation(std::move(P_multilayer), specular_instrument, optionsItem);
    else if (auto penetrator = dynamic_cast<const DepthProbeInstrumentItem*>(instrumentItem))
        return createDepthProbeSimulation(std::move(P_multilayer), penetrator, optionsItem);

    throw GUIHelpers::Error(
        "DomainSimulationBuilder::createSimulation() -> Error. Not yet implemented");
}

namespace
{
void addBackgroundToSimulation(const InstrumentItem& instrument, Simulation& simulation)
{
    auto P_background = instrument.backgroundItem()->createBackground();
    if (P_background)
        simulation.setBackground(*P_background);
}

std::unique_ptr<GISASSimulation> createGISASSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                                                       const GISASInstrumentItem* gisasInstrument,
                                                       const SimulationOptionsItem* optionsItem)
{
    std::unique_ptr<GISASSimulation> gisas(new GISASSimulation);
    auto P_instrument = DomainObjectBuilder::buildInstrument(*gisasInstrument);
    gisas->setSample(*P_multilayer);
    gisas->setInstrument(*P_instrument);
    TransformToDomain::addDistributionParametersToSimulation(*gisasInstrument->beamItem(),
                                                             *gisas.get());

    // Simulation options
    if (optionsItem)
        TransformToDomain::setSimulationOptions(gisas.get(), *optionsItem);

    addBackgroundToSimulation(*gisasInstrument, *gisas);

    return gisas;
}

std::unique_ptr<OffSpecSimulation>
createOffSpecSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                        const OffSpecInstrumentItem* offspecInstrument,
                        const SimulationOptionsItem* optionsItem)
{
    std::unique_ptr<OffSpecSimulation> offspec(new OffSpecSimulation);
    auto P_instrument = DomainObjectBuilder::buildInstrument(*offspecInstrument);
    offspec->setSample(*P_multilayer);
    offspec->setInstrument(*P_instrument);

    auto beamItem = offspecInstrument->beamItem();
    auto axisItem = dynamic_cast<BasicAxisItem*>(
        offspecInstrument->getItem(OffSpecInstrumentItem::P_ALPHA_AXIS));
    offspec->setBeamParameters(beamItem->getWavelength(), *axisItem->createAxis(Units::degree),
                               beamItem->getAzimuthalAngle());

    // TODO Take care about distributions
    // TransformToDomain::addDistributionParametersToSimulation(*gisasInstrument->beamItem(),
    //                                                          gisas.get());

    // Simulation options
    if (optionsItem)
        TransformToDomain::setSimulationOptions(offspec.get(), *optionsItem);

    addBackgroundToSimulation(*offspecInstrument, *offspec);

    return offspec;
}

std::unique_ptr<SpecularSimulation>
createSpecularSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                         const SpecularInstrumentItem* specular_instrument,
                         const SimulationOptionsItem* options_item)
{
    std::unique_ptr<SpecularSimulation> specular_simulation =
        std::make_unique<SpecularSimulation>(*P_multilayer);

    auto beam_item = specular_instrument->beamItem();
    const auto axis_item = beam_item->currentInclinationAxisItem();
    const auto footprint = beam_item->currentFootprintItem();

    AngularSpecScan scan(beam_item->getWavelength(), *axis_item->createAxis(Units::degree));
    scan.setFootprintFactor(footprint->createFootprint().get());

    TransformToDomain::addBeamDivergencesToScan(*beam_item, scan);

    specular_simulation->setBeamIntensity(beam_item->getIntensity());
    specular_simulation->setScan(scan);

    // Simulation options
    if (options_item)
        TransformToDomain::setSimulationOptions(specular_simulation.get(), *options_item);

    addBackgroundToSimulation(*specular_instrument, *specular_simulation);

    return specular_simulation;
}

std::unique_ptr<DepthProbeSimulation>
createDepthProbeSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                           const DepthProbeInstrumentItem* instrument,
                           const SimulationOptionsItem* options_item)
{
    std::unique_ptr<DepthProbeSimulation> simulation = instrument->createSimulation();
    simulation->setSample(*P_multilayer.get());

    if (options_item)
        TransformToDomain::setSimulationOptions(simulation.get(), *options_item);

    return simulation;
}

} // namespace
