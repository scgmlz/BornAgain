// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/BatchSimulation.cpp
//! @brief     Defines BatchSimulation class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "BatchSimulation.h"
#include "Simulation.h"
#include "SimulationFactory.h"
#include "IFunctionalTest.h"
#include "IntensityDataFunctions.h"
#include "SampleBuilderFactory.h"
#include <iostream>
#include <memory>

bool BatchSimulation::runTest()
{
    SimulationFactory sim_registry;
    const std::unique_ptr<Simulation> simulation = sim_registry.create("MiniGISAS");

    SampleBuilderFactory sampleFactory;
    std::shared_ptr<class IMultiLayerBuilder> builder(
        sampleFactory.create("CylindersInBABuilder").release());
    simulation->setSampleBuilder(builder);
    simulation->runSimulation();
    auto sim_result = simulation->result();
    const std::unique_ptr<OutputData<double>> reference(sim_result.data());
    const std::unique_ptr<OutputData<double>> result(reference->clone());
    result->setAllTo(0.0);

    const unsigned n_batches = 9;
    const double threshold = 2e-10;
    for(unsigned i_batch=0; i_batch < n_batches; ++i_batch) {
        const std::unique_ptr<Simulation> batch(simulation->clone());
        ThreadInfo threadInfo;
        threadInfo.n_threads = 1;
        threadInfo.n_batches = n_batches;
        threadInfo.current_batch = i_batch;
        batch->getOptions().setThreadInfo(threadInfo);
        batch->runSimulation();
        auto batch_result = batch->result();
        std::unique_ptr<OutputData<double>> batchResult(batch_result.data());
        *result += *batchResult.get();
    }

    double diff = IntensityDataFunctions::getRelativeDifference(*result, *reference);

    std::cout << "BatchSimulation" << " " << "Running simulations in batch mode" << " " << diff
              << " " << (diff>threshold ? "[FAILED]" : "[OK]") << "\n";

    return diff <= threshold;
}
