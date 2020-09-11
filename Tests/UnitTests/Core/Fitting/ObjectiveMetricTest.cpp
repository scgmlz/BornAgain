#include "Core/Fitting/ObjectiveMetric.h"
#include "Core/Fitting/ObjectiveMetricUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <cmath>

class ObjectiveMetricTest : public ::testing::Test
{
};

TEST_F(ObjectiveMetricTest, Chi2WellFormed)
{
    std::vector<double> sim_data{1.0, 2.0, 3.0, 4.0};
    std::vector<double> exp_data{2.0, 1.0, 4.0, 3.0};
    std::vector<double> uncertainties{0.1, 0.1, 0.5, 0.5};
    std::vector<double> weight_factors{1.0, 1.0, 1.0, 2.0};

    Chi2Metric metric;

    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, sim_data, uncertainties, weight_factors),
                     0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, sim_data, weight_factors), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties, weight_factors),
                     212.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors), 5.0);

    std::vector<double> exp_data_1 = exp_data;
    exp_data_1[0] = -1.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data_1, uncertainties, weight_factors),
                     112.0);

    std::vector<double> uncertainties_1 = uncertainties;
    uncertainties_1[3] = -1.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties_1, weight_factors),
                     204.0);
    uncertainties_1[3] = 0.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties_1, weight_factors),
                     204.0);

    metric.setNorm(ObjectiveMetricUtils::l1Norm());
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties, weight_factors),
                     26.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors), 5.0);

    EXPECT_DOUBLE_EQ(metric.computeFromArrays({}, {}, {}, {}), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays({}, {}, {}), 0.0);
}

TEST_F(ObjectiveMetricTest, Chi2IllFormed)
{
    std::vector<double> sim_data{1.0, 2.0, 3.0, 4.0};
    std::vector<double> exp_data{2.0, 1.0, 4.0, 3.0};
    std::vector<double> uncertainties{0.1, 0.1, 0.5, 0.5};
    std::vector<double> weight_factors{1.0, 1.0, 1.0, 2.0};

    Chi2Metric metric;

    EXPECT_THROW(metric.computeFromArrays({}, {}, {}, {1.0}), std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays({}, {}, {1.0}), std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays(sim_data, exp_data, {}, weight_factors),
                 std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays({}, exp_data, weight_factors), std::runtime_error);

    std::vector<double> sim_data_1 = sim_data;
    sim_data_1[0] = -1.0;
    EXPECT_THROW(metric.computeFromArrays(sim_data_1, exp_data, uncertainties, weight_factors),
                 std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays(sim_data_1, exp_data, weight_factors),
                 std::runtime_error);

    std::vector<double> weight_factors_1(weight_factors.size(), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties, weight_factors_1),
                     0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors_1), 0.0);

    std::vector<double> uncertainties_1 = uncertainties;
    uncertainties_1[0] = std::numeric_limits<double>::min();
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties_1, weight_factors),
                     std::numeric_limits<double>::max());
}

TEST_F(ObjectiveMetricTest, PoissionLikeWellFormed)
{
    std::vector<double> sim_data{1.0, 2.0, 4.0, 4.0};
    std::vector<double> exp_data{2.0, 1.0, 5.0, 3.0};
    std::vector<double> weight_factors{1.0, 1.0, 1.0, 2.0};

    PoissonLikeMetric metric;

    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, sim_data, weight_factors), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors), 2.25);

    std::vector<double> exp_data_1 = exp_data;
    exp_data_1[0] = -1.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data_1, weight_factors), 1.25);

    std::vector<double> sim_data_1 = sim_data;
    sim_data_1[0] = 0.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data_1, exp_data, weight_factors), 5.25);

    metric.setNorm(ObjectiveMetricUtils::l1Norm());

    std::vector<double> sim_data_2 = sim_data;
    sim_data_2[1] = 1.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data_2, exp_data, weight_factors), 2.5);

    EXPECT_DOUBLE_EQ(metric.computeFromArrays({}, {}, {}, {}), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays({}, {}, {}), 0.0);
}

TEST_F(ObjectiveMetricTest, PoissionLikeIllFormed)
{
    std::vector<double> sim_data{1.0, 2.0, 3.0, 4.0};
    std::vector<double> exp_data{2.0, 1.0, 4.0, 3.0};
    std::vector<double> weight_factors{1.0, 1.0, 1.0, 2.0};

    PoissonLikeMetric metric;

    EXPECT_THROW(metric.computeFromArrays({}, {}, {}, {1.0}), std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays({}, {}, {1.0}), std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays(sim_data, exp_data, {}, weight_factors),
                 std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays({}, exp_data, weight_factors), std::runtime_error);

    std::vector<double> sim_data_1 = sim_data;
    sim_data_1[0] = -1.0;
    EXPECT_THROW(metric.computeFromArrays(sim_data_1, exp_data, weight_factors),
                 std::runtime_error);

    std::vector<double> weight_factors_1(weight_factors.size(), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors_1), 0.0);
}

TEST_F(ObjectiveMetricTest, LogWellFormed)
{
    std::vector<double> sim_data{1.0, 10.0, 1.e+2, 1.e+4};
    std::vector<double> exp_data{10.0, 1.0, 1.e+3, 1.e+5};
    std::vector<double> uncertainties{0.1, 0.1, 0.5, 0.5};
    std::vector<double> weight_factors{1.0, 1.0, 1.0, 2.0};

    LogMetric metric;

    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, sim_data, uncertainties, weight_factors),
                     0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, sim_data, weight_factors), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties, weight_factors),
                     8.00040101e+10 * std::log(10.0) * std::log(10.0));
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors), 5.0);

    std::vector<double> exp_data_1 = exp_data;
    exp_data_1[0] = -1.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data_1, uncertainties, weight_factors),
                     8.00040001e+10 * std::log(10.0) * std::log(10.0));
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data_1, weight_factors), 4.0);

    std::vector<double> uncertainties_1 = uncertainties;
    uncertainties_1[3] = -1.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties_1, weight_factors),
                     4.0101e+6 * std::log(10.0) * std::log(10.0));
    uncertainties_1[3] = 0.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties_1, weight_factors),
                     4.0101e+6 * std::log(10.0) * std::log(10.0));

    metric.setNorm(ObjectiveMetricUtils::l1Norm());
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties, weight_factors),
                     4.0211e+5 * std::log(10.0));
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors), 5.0);

    EXPECT_DOUBLE_EQ(metric.computeFromArrays({}, {}, {}, {}), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays({}, {}, {}), 0.0);
}

TEST_F(ObjectiveMetricTest, LogIllFormed)
{
    std::vector<double> sim_data{1.0, 10.0, 1.e+2, 1.e+4};
    std::vector<double> exp_data{10.0, 1.0, 1.e+3, 1.e+5};
    std::vector<double> uncertainties{0.1, 0.1, 0.5, 0.5};
    std::vector<double> weight_factors{1.0, 1.0, 1.0, 2.0};

    LogMetric metric;

    EXPECT_THROW(metric.computeFromArrays({}, {}, {}, {1.0}), std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays({}, {}, {1.0}), std::runtime_error);

    std::vector<double> sim_data_1 = sim_data;
    sim_data_1[0] = -1.0;
    EXPECT_THROW(metric.computeFromArrays(sim_data_1, exp_data, uncertainties, weight_factors),
                 std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays(sim_data_1, exp_data, weight_factors),
                 std::runtime_error);

    std::vector<double> weight_factors_1(weight_factors.size(), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties, weight_factors_1),
                     0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors_1), 0.0);

    std::vector<double> uncertainties_1 = uncertainties;
    uncertainties_1[0] = std::numeric_limits<double>::min();
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties_1, weight_factors),
                     std::numeric_limits<double>::max());
}

TEST_F(ObjectiveMetricTest, RelativeDifferenceWellFormed)
{
    std::vector<double> sim_data{1.0, 2.0, 4.0, 4.0};
    std::vector<double> exp_data{2.0, 1.0, 2.0, 2.0};
    std::vector<double> uncertainties{1.0, 1.0, 2.0, 1.0};
    std::vector<double> weight_factors{1.0, 1.0, 2.0, 1.0};

    RelativeDifferenceMetric metric;

    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, sim_data, weight_factors), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors), 5.0 / 9.0);

    std::vector<double> exp_data_1 = exp_data;
    exp_data_1[0] = -1.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data_1, weight_factors), 4.0 / 9.0);

    std::vector<double> sim_data_1 = sim_data;
    sim_data_1[0] = 0.0;
    exp_data_1[0] = 0.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data_1, exp_data_1, weight_factors), 4.0 / 9.0);

    metric.setNorm(ObjectiveMetricUtils::l1Norm());
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors), 5.0 / 3.0);

    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties, weight_factors),
                     6.0);

    EXPECT_DOUBLE_EQ(metric.computeFromArrays({}, {}, {}, {}), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays({}, {}, {}), 0.0);
}

TEST_F(ObjectiveMetricTest, RelativeDifferenceIllFormed)
{
    std::vector<double> sim_data{1.0, 2.0, 4.0, 4.0};
    std::vector<double> exp_data{2.0, 1.0, 3.0, 2.0};
    std::vector<double> uncertainties{1.0, 1.0, 2.0, 1.0};
    std::vector<double> weight_factors{1.0, 1.0, 2.0, 1.0};

    RelativeDifferenceMetric metric;

    EXPECT_THROW(metric.computeFromArrays(sim_data, {}, uncertainties, weight_factors),
                 std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays(sim_data, {}, weight_factors), std::runtime_error);

    std::vector<double> sim_data_1 = sim_data;
    sim_data_1[0] = -1.0;
    EXPECT_THROW(metric.computeFromArrays(sim_data_1, exp_data, uncertainties, weight_factors),
                 std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays(sim_data_1, exp_data, weight_factors),
                 std::runtime_error);

    std::vector<double> weight_factors_1(weight_factors.size(), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties, weight_factors_1),
                     0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors_1), 0.0);
}

TEST_F(ObjectiveMetricTest, RQ4WellFormed)
{
    std::vector<double> sim_data{1.0, 2.0, 4.0, 4.0};
    std::vector<double> exp_data{2.0, 1.0, 2.0, 2.0};
    std::vector<double> uncertainties{1.0, 1.0, 2.0, 1.0};
    std::vector<double> weight_factors{1.0, 1.0, 2.0, 1.0};

    RQ4Metric metric;

    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, sim_data, weight_factors), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors), 14.0);

    std::vector<double> exp_data_1 = exp_data;
    exp_data_1[0] = -1.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data_1, weight_factors), 13.0);

    std::vector<double> sim_data_1 = sim_data;
    sim_data_1[0] = 0.0;
    exp_data_1[0] = 0.0;
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data_1, exp_data_1, weight_factors), 13.0);

    metric.setNorm(ObjectiveMetricUtils::l1Norm());
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors), 8.0);

    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties, weight_factors),
                     6.0);

    EXPECT_DOUBLE_EQ(metric.computeFromArrays({}, {}, {}, {}), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays({}, {}, {}), 0.0);
}

TEST_F(ObjectiveMetricTest, RQ4IllFormed)
{
    std::vector<double> sim_data{1.0, 2.0, 4.0, 4.0};
    std::vector<double> exp_data{2.0, 1.0, 3.0, 2.0};
    std::vector<double> uncertainties{1.0, 1.0, 2.0, 1.0};
    std::vector<double> weight_factors{1.0, 1.0, 2.0, 1.0};

    RQ4Metric metric;

    EXPECT_THROW(metric.computeFromArrays(sim_data, exp_data, {}, weight_factors),
                 std::runtime_error);
    EXPECT_THROW(metric.computeFromArrays({}, exp_data, weight_factors), std::runtime_error);

    std::vector<double> sim_data_1 = sim_data;
    sim_data_1[0] = -1.0;
    EXPECT_THROW(metric.computeFromArrays(sim_data_1, exp_data, uncertainties, weight_factors),
                 std::runtime_error);

    std::vector<double> weight_factors_1(weight_factors.size(), 0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, uncertainties, weight_factors_1),
                     0.0);
    EXPECT_DOUBLE_EQ(metric.computeFromArrays(sim_data, exp_data, weight_factors_1), 0.0);
}

TEST_F(ObjectiveMetricTest, createMetric)
{
    auto result = ObjectiveMetricUtils::createMetric("Poisson-like");
    EXPECT_TRUE(dynamic_cast<PoissonLikeMetric*>(result.get()));
    // Since norm functions lack equality comparison, check the equality of applying them
    EXPECT_DOUBLE_EQ(result->norm()(2.0), ObjectiveMetricUtils::l2Norm()(2.0));

    result = ObjectiveMetricUtils::createMetric("Poisson-Like", "L1");
    EXPECT_TRUE(dynamic_cast<PoissonLikeMetric*>(result.get()));
    EXPECT_DOUBLE_EQ(result->norm()(2.0), ObjectiveMetricUtils::l1Norm()(2.0));

    result = ObjectiveMetricUtils::createMetric("poisson-like", "l1");
    EXPECT_TRUE(dynamic_cast<PoissonLikeMetric*>(result.get()));
    EXPECT_DOUBLE_EQ(result->norm()(2.0), ObjectiveMetricUtils::l1Norm()(2.0));

    result = ObjectiveMetricUtils::createMetric("poissoN-likE", "L2");
    EXPECT_TRUE(dynamic_cast<PoissonLikeMetric*>(result.get()));
    EXPECT_DOUBLE_EQ(result->norm()(2.0), ObjectiveMetricUtils::l2Norm()(2.0));

    result = ObjectiveMetricUtils::createMetric("poisson-like");
    EXPECT_TRUE(dynamic_cast<PoissonLikeMetric*>(result.get()));
    EXPECT_DOUBLE_EQ(result->norm()(2.0), ObjectiveMetricUtils::l2Norm()(2.0));

    result = ObjectiveMetricUtils::createMetric("chi2");
    EXPECT_TRUE(dynamic_cast<Chi2Metric*>(result.get()));

    result = ObjectiveMetricUtils::createMetric("Chi2");
    EXPECT_TRUE(dynamic_cast<Chi2Metric*>(result.get()));

    result = ObjectiveMetricUtils::createMetric("Log");
    EXPECT_TRUE(dynamic_cast<LogMetric*>(result.get()));

    result = ObjectiveMetricUtils::createMetric("log");
    EXPECT_TRUE(dynamic_cast<LogMetric*>(result.get()));

    result = ObjectiveMetricUtils::createMetric("reldiff");
    EXPECT_TRUE(dynamic_cast<RelativeDifferenceMetric*>(result.get()));

    result = ObjectiveMetricUtils::createMetric("RelDiff");
    EXPECT_TRUE(dynamic_cast<RelativeDifferenceMetric*>(result.get()));

    result = ObjectiveMetricUtils::createMetric("RQ4");
    EXPECT_TRUE(dynamic_cast<RQ4Metric*>(result.get()));

    result = ObjectiveMetricUtils::createMetric("rq4");
    EXPECT_TRUE(dynamic_cast<RQ4Metric*>(result.get()));
}
