//  ************************************************************************************************
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
//  ************************************************************************************************

#include "GUI/coregui/Models/DomainSimulationBuilder.h"
#include "Base/Const/Units.h"
#include "Core/Computation/IBackground.h"
#include "Core/Scan/AngularSpecScan.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecularSimulation.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Device/Beam/IFootprintFactor.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/BackgroundItems.h"
#include "GUI/coregui/Models/DepthProbeInstrumentItem.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/DomainObjectBuilder.h"
#include "GUI/coregui/Models/FootprintItems.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Models/TransformToDomain.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace {
void addBackgroundToSimulation(const InstrumentItem& instrument, ISimulation& simulation);

std::unique_ptr<GISASSimulation> createGISASSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                                                       const GISASInstrumentItem* gisasInstrument,
                                                       const SimulationOptionsItem* optionsItem);

std::unique_ptr<OffSpecularSimulation>
createOffSpecularSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                            const OffSpecularInstrumentItem* offspecInstrument,
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

std::unique_ptr<ISimulation>
DomainSimulationBuilder::createSimulation(const MultiLayerItem* sampleItem,
                                          const InstrumentItem* instrumentItem,
                                          const SimulationOptionsItem* optionsItem) {
    if (sampleItem == nullptr || instrumentItem == nullptr) {
        QString message("DomainSimulationBuilder::getSimulation() -> Error. Either MultiLayerItem "
                        " or InstrumentItem is not defined.");
        throw GUIHelpers::Error(message);
    }

    auto P_multilayer = DomainObjectBuilder::buildMultiLayer(*sampleItem);

    if (auto gisasInstrument = dynamic_cast<const GISASInstrumentItem*>(instrumentItem))
        return createGISASSimulation(std::move(P_multilayer), gisasInstrument, optionsItem);
    else if (auto offspecInstrument =
                 dynamic_cast<const OffSpecularInstrumentItem*>(instrumentItem))
        return createOffSpecularSimulation(std::move(P_multilayer), offspecInstrument, optionsItem);
    else if (auto specular_instrument = dynamic_cast<const SpecularInstrumentItem*>(instrumentItem))
        return createSpecularSimulation(std::move(P_multilayer), specular_instrument, optionsItem);
    else if (auto penetrator = dynamic_cast<const DepthProbeInstrumentItem*>(instrumentItem))
        return createDepthProbeSimulation(std::move(P_multilayer), penetrator, optionsItem);

    throw GUIHelpers::Error(
        "DomainSimulationBuilder::createSimulation() -> Error. Not yet implemented");
}

namespace {
void addBackgroundToSimulation(const InstrumentItem& instrument, ISimulation& simulation) {
    auto P_background = instrument.backgroundItem()->createBackground();
    if (P_background)
        simulation.setBackground(*P_background);
}

std::unique_ptr<GISASSimulation> createGISASSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                                                       const GISASInstrumentItem* instrument,
                                                       const SimulationOptionsItem* optionsItem) {
    std::unique_ptr<GISASSimulation> ret(new GISASSimulation);
    auto P_instrument = DomainObjectBuilder::buildInstrument(*instrument);
    ret->setSample(*P_multilayer);
    ret->setInstrument(*P_instrument);
    TransformToDomain::addDistributionParametersToSimulation(*instrument->beamItem(), *ret);

    // ISimulation options
    if (optionsItem)
        TransformToDomain::setSimulationOptions(ret.get(), *optionsItem);

    addBackgroundToSimulation(*instrument, *ret);

    return ret;
}

std::unique_ptr<OffSpecularSimulation>
createOffSpecularSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                            const OffSpecularInstrumentItem* instrument,
                            const SimulationOptionsItem* optionsItem) {
    std::unique_ptr<OffSpecularSimulation> ret(new OffSpecularSimulation);
    auto P_instrument = DomainObjectBuilder::buildInstrument(*instrument);
    ret->setSample(*P_multilayer);
    ret->setInstrument(*P_instrument);

    auto beamItem = instrument->beamItem();
    auto axisItem =
        dynamic_cast<BasicAxisItem*>(instrument->getItem(OffSpecularInstrumentItem::P_ALPHA_AXIS));
    ret->setBeamParameters(beamItem->wavelength(), *axisItem->createAxis(Units::deg),
                           beamItem->getAzimuthalAngle());

    // TODO Take care about distributions
    // TransformToDomain::addDistributionParametersToSimulation(*gisasInstrument->beamItem(),
    //                                                          gisas.get());

    // ISimulation options
    if (optionsItem)
        TransformToDomain::setSimulationOptions(ret.get(), *optionsItem);

    addBackgroundToSimulation(*instrument, *ret);

    return ret;
}

std::unique_ptr<SpecularSimulation>
createSpecularSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                         const SpecularInstrumentItem* instrument,
                         const SimulationOptionsItem* options_item) {
    std::unique_ptr<SpecularSimulation> ret = std::make_unique<SpecularSimulation>();
    ret->setSample(*P_multilayer);

    auto beam_item = instrument->beamItem();
    const auto axis_item = beam_item->currentInclinationAxisItem();
    const auto footprint = beam_item->currentFootprintItem();

    AngularSpecScan scan(beam_item->wavelength(), *axis_item->createAxis(Units::deg));
    scan.setFootprintFactor(footprint->createFootprint().get());

    TransformToDomain::addBeamDivergencesToScan(*beam_item, scan);

    ret->beam().setIntensity(beam_item->intensity());
    ret->setScan(scan);

    // ISimulation options
    if (options_item)
        TransformToDomain::setSimulationOptions(ret.get(), *options_item);

    addBackgroundToSimulation(*instrument, *ret);

    return ret;
}

std::unique_ptr<DepthProbeSimulation>
createDepthProbeSimulation(std::unique_ptr<MultiLayer> P_multilayer,
                           const DepthProbeInstrumentItem* instrument,
                           const SimulationOptionsItem* options_item) {
    std::unique_ptr<DepthProbeSimulation> ret = instrument->createSimulation();
    ret->setSample(*P_multilayer);

    if (options_item)
        TransformToDomain::setSimulationOptions(ret.get(), *options_item);

    return ret;
}

} // namespace
