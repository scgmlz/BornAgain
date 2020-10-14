#include "Base/Const/Units.h"
#include "Core/Computation/ProcessedSample.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/KzComputation.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/SpecularMagneticNewTanhStrategy.h"
#include "Core/Multilayer/SpecularMagneticStrategy.h"
#include "Core/Multilayer/SpecularScalarTanhStrategy.h"
#include "Core/RT/SimulationOptions.h"
#include "Tests/GTestWrapper/google_test.h"
#include <utility>

constexpr double eps = 1e-10;

class SpecularMagneticTest : public ::testing::Test
{
protected:
    std::unique_ptr<ProcessedSample> sample_zerofield();

    std::unique_ptr<ProcessedSample> sample_degenerate();
    //! Compares results with scalar case
    template <typename Strategy>
    void testZeroField(const kvector_t& k, const ProcessedSample& sample);
    template <typename Strategy> void testcase_zerofield(std::vector<double>&& angles);

    template <typename Strategy> void test_degenerate();
};

template <> void SpecularMagneticTest::test_degenerate<SpecularMagneticNewTanhStrategy>()
{
    kvector_t v;

    Eigen::Vector2cd T1p{0.0, 0.0};
    Eigen::Vector2cd T2p{1.0, 0.0};
    Eigen::Vector2cd R1p{0.0, 0.0};
    Eigen::Vector2cd R2p{0.0, 0.0};
    Eigen::Vector2cd T1m{0.0, 1.0};
    Eigen::Vector2cd T2m{0.0, 0.0};
    Eigen::Vector2cd R1m{0.0, 0.0};
    Eigen::Vector2cd R2m{0.0, 0.0};

    auto sample = sample_degenerate();
    auto result = std::make_unique<SpecularMagneticNewTanhStrategy>()->Execute(sample->slices(), v);
    for (auto& coeff : result) {
        EXPECT_NEAR_VECTOR2CD(coeff->T1plus(), T1p, eps);
        EXPECT_NEAR_VECTOR2CD(coeff->T2plus(), T2p, eps);
        EXPECT_NEAR_VECTOR2CD(coeff->T1min(), T1m, eps);
        EXPECT_NEAR_VECTOR2CD(coeff->T2min(), T2m, eps);
        EXPECT_NEAR_VECTOR2CD(coeff->R1plus(), R1p, eps);
        EXPECT_NEAR_VECTOR2CD(coeff->R2plus(), R2p, eps);
        EXPECT_NEAR_VECTOR2CD(coeff->R1min(), R1m, eps);
        EXPECT_NEAR_VECTOR2CD(coeff->R2min(), R2m, eps);
    }
}

template <typename Strategy>
void SpecularMagneticTest::testZeroField(const kvector_t& k, const ProcessedSample& sample)
{
    auto coeffs_scalar = std::make_unique<SpecularScalarTanhStrategy>()->Execute(
        sample.slices(), KzComputation::computeKzFromRefIndices(sample.slices(), k));
    auto coeffs_zerofield = std::make_unique<Strategy>()->Execute(
        sample.slices(), KzComputation::computeKzFromRefIndices(sample.slices(), k));

    EXPECT_EQ(coeffs_scalar.size(), coeffs_zerofield.size());

    for (size_t i = 0; i < coeffs_scalar.size(); ++i) {
        const ScalarRTCoefficients& RTScalar =
            *dynamic_cast<const ScalarRTCoefficients*>(coeffs_scalar[i].get());

        auto& RTMatrix =
            *dynamic_cast<const typename Strategy::coefficient_type*>(coeffs_zerofield[i].get());

        EXPECT_NEAR_VECTOR2CD(RTMatrix.T1plus(), RTScalar.T1plus(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix.T2plus(), RTScalar.T2plus(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix.R1plus(), RTScalar.R1plus(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix.R2plus(), RTScalar.R2plus(), eps);

        EXPECT_NEAR_VECTOR2CD(RTMatrix.T1min(), RTScalar.T1min(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix.T2min(), RTScalar.T2min(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix.R1min(), RTScalar.R1min(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix.R2min(), RTScalar.R2min(), eps);

        EXPECT_NEAR_VECTOR2CD(RTScalar.getKz(), RTMatrix.getKz(), eps);
    }
}

std::unique_ptr<ProcessedSample> SpecularMagneticTest::sample_degenerate()
{
    MultiLayer mLayer;
    Material air = HomogeneousMaterial("Vacuum", 0, 1.0);
    mLayer.addLayer(Layer(air, 0 * Units::nanometer));
    return std::make_unique<ProcessedSample>(mLayer, SimulationOptions());
}

TEST_F(SpecularMagneticTest, degenerate_new)
{
    test_degenerate<SpecularMagneticNewTanhStrategy>();
}

std::unique_ptr<ProcessedSample> SpecularMagneticTest::sample_zerofield()
{
    MultiLayer multi_layer_scalar;
    Material substr_material_scalar = HomogeneousMaterial("Substrate", 7e-6, 2e-8);
    Layer vacuum_layer(HomogeneousMaterial("Vacuum", 0.0, 0.0));
    Layer substr_layer_scalar(substr_material_scalar);
    multi_layer_scalar.addLayer(vacuum_layer);
    multi_layer_scalar.addLayer(substr_layer_scalar);

    SimulationOptions options;
    auto sample_scalar = std::make_unique<ProcessedSample>(multi_layer_scalar, options);

    return sample_scalar;
}

template <typename Strategy>
void SpecularMagneticTest::testcase_zerofield(std::vector<double>&& angles)
{
    for (auto& angle : angles) {
        auto sample = sample_zerofield();
        kvector_t k = vecOfLambdaAlphaPhi(1.0, angle * Units::deg, 0.0);
        testZeroField<Strategy>(k, *sample);
    }
}

TEST_F(SpecularMagneticTest, zerofield)
{
    testcase_zerofield<SpecularMagneticStrategy>({-0.1, -2.0, -10.0});
}

TEST_F(SpecularMagneticTest, zerofield_new)
{
    testcase_zerofield<SpecularMagneticNewTanhStrategy>({-0.0, -1.e-9, -1.e-5, -0.1, -2.0, -10.0});
}
