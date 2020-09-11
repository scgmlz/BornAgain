// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/BatchSimulation.cpp
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>
#include <memory>

class BatchSimulation : public ::testing::Test
{
};

TEST_F(BatchSimulation, BatchSimulation)
{
    SimulationFactory sim_registry;
    const std::unique_ptr<Simulation> simulation = sim_registry.createItemPtr("MiniGISAS");

    SampleBuilderFactory sampleFactory;
    std::shared_ptr<class IMultiLayerBuilder> builder(
        sampleFactory.createItemPtr("CylindersInBABuilder").release());
    simulation->setSampleBuilder(builder);
    simulation->runSimulation();
    auto sim_result = simulation->result();
    const auto reference = sim_result.data();
    const auto result = reference->clone();
    result->setAllTo(0.0);

    const unsigned n_batches = 9;
    const double threshold = 2e-10;
    for (unsigned i_batch = 0; i_batch < n_batches; ++i_batch) {
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

    EXPECT_LE(diff, threshold);
}
