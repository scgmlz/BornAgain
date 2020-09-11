#include "Core/Detector/ScanResolution.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "Tests/GTestWrapper/google_test.h"
#include <cmath>

class ScanResolutionTest : public ::testing::Test
{
protected:
    using DistrOutput = std::vector<std::vector<ParameterSample>>;
    void compareResults(const DistrOutput& lhs, const DistrOutput& rhs);
};

void ScanResolutionTest::compareResults(const DistrOutput& lhs, const DistrOutput& rhs)
{
    EXPECT_EQ(lhs.size(), rhs.size());
    for (size_t i = 0; i < lhs.size(); ++i) {
        EXPECT_EQ(lhs[i].size(), rhs[i].size());
        for (size_t j = 0; j < lhs[i].size(); ++j) {
            EXPECT_NEAR(lhs[i][j].value, rhs[i][j].value, std::abs(lhs[i][j].value) * 1e-10);
            EXPECT_NEAR(lhs[i][j].weight, rhs[i][j].weight, std::abs(lhs[i][j].value) * 1e-10);
        }
    }
}

TEST_F(ScanResolutionTest, RelativeSingleValued)
{
    RangedDistributionGate distr(3, 1.0);
    std::unique_ptr<ScanResolution> resolution(ScanResolution::scanRelativeResolution(distr, 0.1));

    std::vector<double> coordinates = {1.0, 2.0, 3.0};
    std::vector<double> ref_deltas = {0.1, 0.2, 0.3};
    DistrOutput ref_result = resolution->distribution()->generateSamples(coordinates, ref_deltas);
    DistrOutput actual = resolution->generateSamples(coordinates);
    compareResults(ref_result, actual);

    ref_result = DistrOutput(3, resolution->distribution()->generateSamples(1.0, 0.1));
    actual = resolution->generateSamples(1.0, 3);
    compareResults(ref_result, actual);

    std::stringstream print_ref;
    print_ref << "    distribution = ba.RangedDistributionGate(3, 1.0)\n"
              << "    resolution = ba.ScanRelativeResolution(distribution, 0.1)";
    EXPECT_EQ(print_ref.str(), resolution->print());
    EXPECT_THROW(resolution->generateSamples(std::vector<double>()), std::runtime_error);
}

TEST_F(ScanResolutionTest, AbsoluteSingleValued)
{
    RangedDistributionGate distr(3, 1.0);
    std::unique_ptr<ScanResolution> resolution(ScanResolution::scanAbsoluteResolution(distr, 0.1));

    std::vector<double> coordinates = {1.0, 2.0, 3.0};
    std::vector<double> ref_deltas = {0.1, 0.1, 0.1};
    DistrOutput ref_result = resolution->distribution()->generateSamples(coordinates, ref_deltas);
    DistrOutput actual = resolution->generateSamples(coordinates);
    compareResults(ref_result, actual);

    ref_result = DistrOutput(3, resolution->distribution()->generateSamples(1.0, 0.1));
    actual = resolution->generateSamples(1.0, 3);
    compareResults(ref_result, actual);

    std::stringstream print_ref;
    print_ref << "    distribution = ba.RangedDistributionGate(3, 1.0)\n"
              << "    resolution = ba.ScanAbsoluteResolution(distribution, 0.1)";
    EXPECT_EQ(print_ref.str(), resolution->print());
    EXPECT_THROW(resolution->generateSamples(std::vector<double>()), std::runtime_error);
}

TEST_F(ScanResolutionTest, RelativeVectorValued)
{
    RangedDistributionGate distr(3, 1.0);
    EXPECT_THROW(ScanResolution::scanRelativeResolution(distr, std::vector<double>()),
                 std::runtime_error);
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanRelativeResolution(distr, {0.1, 0.2, 0.3}));

    std::vector<double> coordinates = {1.0, 2.0, 3.0};
    DistrOutput ref_result =
        resolution->distribution()->generateSamples(coordinates, {0.1, 0.4, 0.9});
    DistrOutput actual = resolution->generateSamples(coordinates);
    compareResults(ref_result, actual);

    ref_result = DistrOutput({resolution->distribution()->generateSamples(1.0, 0.1),
                              resolution->distribution()->generateSamples(1.0, 0.2),
                              resolution->distribution()->generateSamples(1.0, 0.3)});
    actual = resolution->generateSamples(1.0, 3);
    compareResults(ref_result, actual);

    EXPECT_THROW(resolution->print(), std::runtime_error);
    EXPECT_THROW(resolution->generateSamples(std::vector<double>()), std::runtime_error);
    EXPECT_THROW(resolution->generateSamples(std::vector<double>(2, 1.0)), std::runtime_error);
    EXPECT_THROW(resolution->generateSamples(std::vector<double>(10, 1.0)), std::runtime_error);
}

TEST_F(ScanResolutionTest, AbsoluteVectorValued)
{
    RangedDistributionGate distr(3, 1.0);
    EXPECT_THROW(ScanResolution::scanAbsoluteResolution(distr, std::vector<double>()),
                 std::runtime_error);
    std::unique_ptr<ScanResolution> resolution(
        ScanResolution::scanAbsoluteResolution(distr, {0.2, 0.3, 0.4}));

    std::vector<double> coordinates = {1.0, 2.0, 3.0};
    DistrOutput ref_result =
        resolution->distribution()->generateSamples(coordinates, {0.2, 0.3, 0.4});
    DistrOutput actual = resolution->generateSamples(coordinates);
    compareResults(ref_result, actual);

    ref_result = DistrOutput({resolution->distribution()->generateSamples(1.0, 0.2),
                              resolution->distribution()->generateSamples(1.0, 0.3),
                              resolution->distribution()->generateSamples(1.0, 0.4)});
    actual = resolution->generateSamples(1.0, 3);
    compareResults(ref_result, actual);

    EXPECT_THROW(resolution->print(), std::runtime_error);
    EXPECT_THROW(resolution->generateSamples(std::vector<double>()), std::runtime_error);
    EXPECT_THROW(resolution->generateSamples(std::vector<double>(2, 1.0)), std::runtime_error);
    EXPECT_THROW(resolution->generateSamples(std::vector<double>(10, 1.0)), std::runtime_error);
}
