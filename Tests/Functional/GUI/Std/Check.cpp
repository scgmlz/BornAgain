//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Tests/Functional/GUI/Std/Check.cpp
//! @brief     Implements function checkSimulation for GUI standard test
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Simulation/ISimulation.h"
#include "Device/Data/DataUtils.h"
#include "GUI/coregui/Models/DocumentModel.h"
#include "GUI/coregui/Models/DomainSimulationBuilder.h"
#include "GUI/coregui/Models/GUIObjectBuilder.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/SampleModel.h"

namespace {

std::unique_ptr<OutputData<double>> domainData(const std::string& /*test_name*/,
                                               const ISimulation& direct_simulation)
{
    // initializing necessary GUI
    DocumentModel documentModel;
    SampleModel sampleModel;
    InstrumentModel instrumentModel;
    MaterialModel materialModel;

    // populating GUI models from domain
    GUIObjectBuilder::populateSampleModelFromSim(&sampleModel, &materialModel, direct_simulation);
    GUIObjectBuilder::populateInstrumentModel(&instrumentModel, direct_simulation);
    GUIObjectBuilder::populateDocumentModel(&documentModel, direct_simulation);

    std::unique_ptr<ISimulation> domain_simulation = DomainSimulationBuilder::createSimulation(
        sampleModel.multiLayerItem(), instrumentModel.instrumentItems().front(),
        documentModel.simulationOptionsItem());

    domain_simulation->runSimulation();
    return std::unique_ptr<OutputData<double>>(domain_simulation->result().data());
}

} // namespace

//! Run simulation directly (in core) and through GUI model, and compare results.

bool checkSimulation(const std::string& name, const ISimulation& direct_simulation,
                     const double limit)
{
    const std::unique_ptr<OutputData<double>> domain_data = domainData(name, direct_simulation);

    const std::unique_ptr<OutputData<double>> ref_data = direct_simulation.result().data();

    return DataUtils::checkRelativeDifference(*domain_data, *ref_data, limit);
}
