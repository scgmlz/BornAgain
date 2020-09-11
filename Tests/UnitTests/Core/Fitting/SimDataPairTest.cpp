#include "Core/Fitting/SimDataPair.h"
#include "Fit/Kernel/Parameters.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/Core/Fitting/FittingTestHelper.h"

class SimDataPairTest : public ::testing::Test
{
};

TEST_F(SimDataPairTest, standardPair)
{
    FittingTestHelper helper;

    simulation_builder_t builder = [&](const Fit::Parameters& pars) {
        return helper.createSimulation(pars);
    };

    const double exp_value(10.0);
    const double dataset_weight(0.5);

    SimDataPair obj(builder, *helper.createData(exp_value), nullptr, dataset_weight);

    // default state, no simulation has been called yet
    EXPECT_EQ(obj.numberOfFitElements(), 0u);
    EXPECT_THROW(obj.uncertainties_array(), std::runtime_error);
    EXPECT_THROW(obj.user_weights_array(), std::runtime_error);
    EXPECT_THROW(obj.simulation_array(), std::runtime_error);
    EXPECT_THROW(obj.experimental_array(), std::runtime_error);
    EXPECT_THROW(obj.simulationResult(), std::runtime_error);
    EXPECT_THROW(obj.experimentalData(), std::runtime_error);

    // calling builder once
    Fit::Parameters params;
    EXPECT_EQ(helper.m_builder_calls, 0u);
    obj.runSimulation(params);
    EXPECT_EQ(helper.m_builder_calls, 1u);

    // checking simulated and experimental data
    const size_t expected_size = helper.m_nx * helper.m_ny;
    EXPECT_EQ(obj.numberOfFitElements(), expected_size);
    EXPECT_EQ(obj.simulationResult().size(), expected_size);
    EXPECT_EQ(obj.experimentalData().size(), expected_size);

    // checking arrays
    auto array = obj.simulation_array();
    EXPECT_EQ(array.size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), 0.0);
    array = obj.experimental_array();
    EXPECT_EQ(obj.experimental_array().size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), expected_size * exp_value);

    // calling builder second time
    obj.runSimulation(params);
    EXPECT_EQ(helper.m_builder_calls, 2u);

    // checking arrays
    array = obj.simulation_array();
    EXPECT_EQ(array.size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), 0.0);
    array = obj.experimental_array();
    EXPECT_EQ(obj.experimental_array().size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), expected_size * exp_value);
}

TEST_F(SimDataPairTest, moveTest)
{
    FittingTestHelper helper;

    simulation_builder_t builder = [&](const Fit::Parameters& pars) {
        return helper.createSimulation(pars);
    };

    const double exp_value(10.0);
    const double dataset_weight(0.5);

    SimDataPair obj(builder, *helper.createData(exp_value), nullptr, dataset_weight);
    // calling builder once
    Fit::Parameters params;
    EXPECT_EQ(helper.m_builder_calls, 0u);
    obj.runSimulation(params);
    EXPECT_EQ(helper.m_builder_calls, 1u);

    // checking simulated and experimental data
    const size_t expected_size = helper.m_nx * helper.m_ny;
    EXPECT_EQ(obj.numberOfFitElements(), expected_size);
    EXPECT_EQ(obj.simulationResult().size(), expected_size);
    EXPECT_EQ(obj.experimentalData().size(), expected_size);

    // Making clone.
    SimDataPair moved = std::move(obj);

    // Checking clone properties
    EXPECT_EQ(moved.numberOfFitElements(), expected_size);
    EXPECT_EQ(moved.uncertainties_array().size(), expected_size);
    EXPECT_EQ(moved.user_weights_array().size(), expected_size);
    EXPECT_EQ(moved.simulation_array().size(), expected_size);
    EXPECT_EQ(moved.experimental_array().size(), expected_size);
    EXPECT_EQ(moved.simulationResult().size(), expected_size);
    EXPECT_EQ(moved.experimentalData().size(), expected_size);

    // calling clone's builder once
    moved.runSimulation(params);
    EXPECT_EQ(helper.m_builder_calls, 2u);

    // checking simulated and experimental data
    EXPECT_EQ(moved.numberOfFitElements(), expected_size);
    EXPECT_EQ(moved.simulationResult().size(), expected_size);
    EXPECT_EQ(moved.experimentalData().size(), expected_size);
}
