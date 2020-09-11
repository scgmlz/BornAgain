#include "Core/Fitting/FitObjective.h"
#include "Fit/Kernel/Parameters.h"
#include "Tests/GTestWrapper/google_test.h"
#include "Tests/UnitTests/Core/Fitting/FittingTestHelper.h"

class FitObjectiveTest : public ::testing::Test
{
};

TEST_F(FitObjectiveTest, twoDatasets)
{
    // creating two simulation builders
    FittingTestHelper helper1(2, 3);
    simulation_builder_t builder1 = [&](const Fit::Parameters& pars) {
        return helper1.createSimulation(pars);
    };

    FittingTestHelper helper2(3, 4);
    simulation_builder_t builder2 = [&](const Fit::Parameters& pars) {
        return helper2.createSimulation(pars);
    };

    // creating two datasets
    const double exp_value1 = 10.0;
    const double exp_value2 = 20.0;
    auto data1 = helper1.createData(exp_value1);
    auto data2 = helper2.createData(exp_value2);

    // creating FitObjective with two simulation/data pairs.
    FitObjective objective;
    objective.addSimulationAndData(builder1, *data1, nullptr);
    objective.addSimulationAndData(builder2, *data2, nullptr);

    // running simulation once
    Fit::Parameters params;
    objective.evaluate(params);

    // number of fit elements should be the sum of two dataset sizes
    EXPECT_EQ(helper1.m_builder_calls, 1u);
    EXPECT_EQ(helper2.m_builder_calls, 1u);
    EXPECT_EQ(objective.numberOfFitElements(), helper1.size() + helper2.size());

    // checking flat array with experimental data made of two OutputData
    std::vector<double> expected_exp1(helper1.size(), exp_value1);
    std::vector<double> expected_exp2(helper2.size(), exp_value2);
    expected_exp1.insert(expected_exp1.end(), expected_exp2.begin(), expected_exp2.end());

    EXPECT_EQ(expected_exp1, objective.experimental_array());
}
