#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "Tests/GTestWrapper/google_test.h"

class RangedDistributionTest : public ::testing::Test
{
protected:
    void checkDefaults(const RangedDistribution& distr);

    template <class T> void checkThrows();

    template <class T> void checkStandardSampling();

    template <class T> void checkPrinting(std::string expected_name);

    template <class T> void checkZeroWidth();
};

void RangedDistributionTest::checkDefaults(const RangedDistribution& distr)
{
    EXPECT_EQ(distr.nSamples(), 5u);
    EXPECT_EQ(distr.sigmaFactor(), 2.0);
    EXPECT_EQ(distr.limits(), RealLimits::limitless());
}

template <class T> void RangedDistributionTest::checkThrows()
{
    EXPECT_THROW(T(0, 1.0, 0.0, 1.0), std::runtime_error);
    EXPECT_THROW(T(1, 1.0, 1.0, -1.0), std::runtime_error);
    EXPECT_THROW(T(1, 1.0, 1.0, -1.0), std::runtime_error);
    EXPECT_THROW(T(8, 5.0, RealLimits::limited(1.0, 0.2)), std::runtime_error);
    EXPECT_THROW(T(8, -5.0), std::runtime_error);
    EXPECT_NO_THROW(T(1, 0.1, 0.0, 0.1));
    EXPECT_NO_THROW(T(1, 0.0, 0.0, 1.0));
    EXPECT_NO_THROW(T(1, 0.1));
    EXPECT_NO_THROW(T(2, 0.1));
}

template <class T> void RangedDistributionTest::checkStandardSampling()
{
    T distr(3, 1.0);

    const double mean = 1.0;
    const double stddev = 0.5;

    EXPECT_THROW(distr.distribution(mean, -1.0), std::runtime_error);
    EXPECT_THROW(distr.generateSamples({mean, mean, mean}, {stddev, stddev}), std::runtime_error);
    EXPECT_NO_THROW(distr.distribution(mean, 0.0));

    auto distr_impl = distr.distribution(mean, stddev);
    EXPECT_DOUBLE_EQ(distr_impl->getMean(), mean);

    auto samples = distr.generateSamples(mean, stddev);
    double sum_weights = 0.0;
    for (size_t i = 0; i < samples.size(); ++i)
        sum_weights += samples[i].weight;
    EXPECT_DOUBLE_EQ(sum_weights, 1.0);
    EXPECT_EQ(samples.size(), 3u);

    auto samples_2 = distr.generateSamples({mean, mean, mean}, {stddev, stddev, stddev});
    for (size_t i = 0; i < samples_2.size(); ++i) {
        sum_weights = 0.0;
        for (size_t j = 0; j < samples_2[i].size(); ++j)
            sum_weights += samples_2[i][j].weight;
        EXPECT_DOUBLE_EQ(sum_weights, 1.0);
        EXPECT_EQ(samples_2[i].size(), 3u);
    }
    EXPECT_EQ(samples_2.size(), 3u);
}

template <class T> void RangedDistributionTest::checkPrinting(std::string expected_name)
{
    T distr(3, 1.0);
    std::stringstream print_ref;
    print_ref << "    distribution = ba." << expected_name << "(3, 1.0)";
    std::string actual = distr.print();
    EXPECT_EQ(print_ref.str(), actual);

    T distr2(3, 1.0, 1.0, 2.0);
    std::stringstream print_ref2;
    print_ref2 << "    distribution = ba." << expected_name
               << "(3, 1.0, ba.RealLimits.limited(1.0, 2.0))";
    actual = distr2.print();
    EXPECT_EQ(print_ref2.str(), actual);
}

template <class T> void RangedDistributionTest::checkZeroWidth()
{
    T distr(/*n_samples = */ 10, /*sigma_factor = */ 3.0);
    const std::vector<ParameterSample>& samples = distr.generateSamples(1.0, 0.0);
    EXPECT_EQ(distr.nSamples(), samples.size());

    double sum_weights = 0.0;
    for (size_t i = 0; i < samples.size(); ++i)
        sum_weights += samples[i].weight;
    EXPECT_DOUBLE_EQ(1.0, sum_weights);

    const std::vector<std::vector<ParameterSample>>& samples2 =
        distr.generateSamples({1.0, 1.0}, {1.0, 0.0});
    for (size_t i = 0; i < samples2.size(); ++i) {
        const std::vector<ParameterSample>& sample_row = samples2[i];
        EXPECT_EQ(distr.nSamples(), sample_row.size());

        double sum_weights = 0.0;
        for (size_t j = 0; j < sample_row.size(); ++j)
            sum_weights += sample_row[j].weight;
        EXPECT_DOUBLE_EQ(1.0, sum_weights);
    }
}

TEST_F(RangedDistributionTest, GateDistribution)
{
    checkDefaults(RangedDistributionGate());
    checkThrows<RangedDistributionGate>();
    checkStandardSampling<RangedDistributionGate>();
    checkPrinting<RangedDistributionGate>("RangedDistributionGate");
    checkZeroWidth<RangedDistributionGate>();
}

TEST_F(RangedDistributionTest, LorentzDistribution)
{
    checkDefaults(RangedDistributionLorentz());
    checkThrows<RangedDistributionLorentz>();
    checkStandardSampling<RangedDistributionLorentz>();
    checkPrinting<RangedDistributionLorentz>("RangedDistributionLorentz");
    checkZeroWidth<RangedDistributionLorentz>();
}

TEST_F(RangedDistributionTest, GaussianDistribution)
{
    checkDefaults(RangedDistributionGaussian());
    checkThrows<RangedDistributionGaussian>();
    checkStandardSampling<RangedDistributionGaussian>();
    checkPrinting<RangedDistributionGaussian>("RangedDistributionGaussian");
    checkZeroWidth<RangedDistributionGaussian>();
}

TEST_F(RangedDistributionTest, LogNormalDistribution)
{
    checkDefaults(RangedDistributionLogNormal());
    checkThrows<RangedDistributionLogNormal>();
    checkStandardSampling<RangedDistributionLogNormal>();
    checkPrinting<RangedDistributionLogNormal>("RangedDistributionLogNormal");
    checkZeroWidth<RangedDistributionLogNormal>();

    RangedDistributionLogNormal log_norm;
    EXPECT_THROW(log_norm.distribution(-1.0, 1.0), std::runtime_error);
}

TEST_F(RangedDistributionTest, CosineDistribution)
{
    checkDefaults(RangedDistributionCosine());
    checkThrows<RangedDistributionCosine>();
    checkStandardSampling<RangedDistributionCosine>();
    checkPrinting<RangedDistributionCosine>("RangedDistributionCosine");
    checkZeroWidth<RangedDistributionCosine>();
}
