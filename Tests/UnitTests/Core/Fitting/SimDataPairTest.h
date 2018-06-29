#include "google_test.h"
#include "SimDataPair.h"
#include "Parameters.h"
#include "FittingTestHelper.h"


class SimDataPairTest : public ::testing::Test
{
public:
    ~SimDataPairTest();

protected:
};

SimDataPairTest::~SimDataPairTest() = default;

TEST_F(SimDataPairTest, standardPair)
{
    FittingTestHelper helper;

    simulation_builder_t builder = [&](const Fit::Parameters &pars){
        return helper.createSimulation(pars);
    };

    const double exp_value(10.0);
    const double dataset_weight(0.5);
    auto data = helper.createData(exp_value);

    SimDataPair obj(builder, *data, dataset_weight);

    // default state, no simulation has been called yet
    EXPECT_EQ(obj.numberOfFitElements(), 0u);
    EXPECT_EQ(obj.weight(), dataset_weight);
    EXPECT_TRUE(obj.simulation_array().empty());
    EXPECT_TRUE(obj.experimental_array().empty());
    EXPECT_THROW(obj.simulationResult().size(), std::runtime_error);
    EXPECT_THROW(obj.experimentalData().size(), std::runtime_error);

    // calling builder once
    Fit::Parameters params;
    EXPECT_EQ(helper.m_builder_calls, 0u);
    obj.runSimulation(params);
    EXPECT_EQ(helper.m_builder_calls, 1u);

    // checking simulated and experimental data
    const size_t expected_size = helper.m_nx*helper.m_ny;
    EXPECT_EQ(obj.numberOfFitElements(), expected_size);
    EXPECT_EQ(obj.simulationResult().size(), expected_size);
    EXPECT_EQ(obj.experimentalData().size(), expected_size);

    // checking arrays
    auto array = obj.simulation_array();
    EXPECT_EQ(array.size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), 0.0);
    array = obj.experimental_array();
    EXPECT_EQ(obj.experimental_array().size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), expected_size*exp_value);

    // calling builder second time
    obj.runSimulation(params);
    EXPECT_EQ(helper.m_builder_calls, 2u);

    // checking arrays
    array = obj.simulation_array();
    EXPECT_EQ(array.size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), 0.0);
    array = obj.experimental_array();
    EXPECT_EQ(obj.experimental_array().size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), expected_size*exp_value);
}


TEST_F(SimDataPairTest, clone)
{
    FittingTestHelper helper;

    simulation_builder_t builder = [&](const Fit::Parameters &pars){
        return helper.createSimulation(pars);
    };

    const double exp_value(10.0);
    const double dataset_weight(0.5);
    auto data = helper.createData(exp_value);

    SimDataPair obj(builder, *data, dataset_weight);
    // calling builder once
    Fit::Parameters params;
    EXPECT_EQ(helper.m_builder_calls, 0u);
    obj.runSimulation(params);
    EXPECT_EQ(helper.m_builder_calls, 1u);

    // checking simulated and experimental data
    const size_t expected_size = helper.m_nx*helper.m_ny;
    EXPECT_EQ(obj.numberOfFitElements(), expected_size);
    EXPECT_EQ(obj.simulationResult().size(), expected_size);
    EXPECT_EQ(obj.experimentalData().size(), expected_size);

    // Making clone.
    std::unique_ptr<SimDataPair> clone(obj.clone());

    // Checking clone properties
    EXPECT_EQ(clone->numberOfFitElements(), 0u);
    EXPECT_EQ(clone->weight(), dataset_weight);
    EXPECT_TRUE(clone->simulation_array().empty());
    EXPECT_TRUE(clone->experimental_array().empty());
    EXPECT_THROW(clone->simulationResult().size(), std::runtime_error);
    EXPECT_THROW(clone->experimentalData().size(), std::runtime_error);

    // calling clone's builder once
    clone->runSimulation(params);
    EXPECT_EQ(helper.m_builder_calls, 2u);

    // checking simulated and experimental data
    EXPECT_EQ(clone->numberOfFitElements(), expected_size);
    EXPECT_EQ(clone->simulationResult().size(), expected_size);
    EXPECT_EQ(clone->experimentalData().size(), expected_size);
}

