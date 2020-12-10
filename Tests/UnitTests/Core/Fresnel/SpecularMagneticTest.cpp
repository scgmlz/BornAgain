#include "Base/Const/Units.h"
#include "Base/Vector/Direction.h"
#include "Sample/LegacyRT/SpecularMagneticStrategy_v2.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Processed/ProcessedSample.h"
#include "Sample/RT/SimulationOptions.h"
#include "Sample/Slice/KzComputation.h"
#include "Sample/Specular/SpecularMagneticTanhStrategy.h"
#include "Sample/Specular/SpecularScalarTanhStrategy.h"
#include "Tests/GTestWrapper/google_test.h"
#include <utility>

class SpecularMagneticTest : public ::testing::Test {
protected:
    auto static constexpr eps = 1.e-10;

    std::unique_ptr<ProcessedSample> sample_zerofield(bool slab);
    std::unique_ptr<ProcessedSample> sample_degenerate();

    template <typename Strategy> void test_degenerate();
    template <typename Strategy>
    void testZeroField(const kvector_t& k, const ProcessedSample& sample);
    template <typename Strategy>
    void testcase_zerofield(std::vector<double>&& angles, bool slab = false);
};

template <> void SpecularMagneticTest::test_degenerate<SpecularMagneticTanhStrategy>() {
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
    auto result = std::make_unique<SpecularMagneticTanhStrategy>()->Execute(sample->slices(), v);
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

//! Compares results with scalar case
template <typename Strategy>
void SpecularMagneticTest::testZeroField(const kvector_t& k, const ProcessedSample& sample) {
    auto coeffs_scalar = std::make_unique<SpecularScalarTanhStrategy>()->Execute(
        sample.slices(), KzComputation::computeKzFromRefIndices(sample.slices(), k));
    auto coeffs_zerofield = std::make_unique<Strategy>()->Execute(
        sample.slices(), KzComputation::computeKzFromRefIndices(sample.slices(), k));

    EXPECT_EQ(coeffs_scalar.size(), coeffs_zerofield.size());

    for (size_t i = 0; i < coeffs_scalar.size(); ++i) {
        auto* RTScalar = coeffs_scalar[i].get();
        auto* RTMatrix = coeffs_zerofield[i].get();

        EXPECT_NEAR_VECTOR2CD(RTMatrix->T1plus(), RTScalar->T1plus(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix->T2plus(), RTScalar->T2plus(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix->R1plus(), RTScalar->R1plus(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix->R2plus(), RTScalar->R2plus(), eps);

        EXPECT_NEAR_VECTOR2CD(RTMatrix->T1min(), RTScalar->T1min(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix->T2min(), RTScalar->T2min(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix->R1min(), RTScalar->R1min(), eps);
        EXPECT_NEAR_VECTOR2CD(RTMatrix->R2min(), RTScalar->R2min(), eps);

        EXPECT_NEAR_VECTOR2CD(RTMatrix->getKz(), RTScalar->getKz(), eps);
    }
}

std::unique_ptr<ProcessedSample> SpecularMagneticTest::sample_degenerate() {
    MultiLayer mLayer;
    Material air = HomogeneousMaterial("Vacuum", 0, 1.0);
    mLayer.addLayer(Layer(air, 0 * Units::nm));
    return std::make_unique<ProcessedSample>(mLayer, SimulationOptions());
}

TEST_F(SpecularMagneticTest, degenerate_) {
    test_degenerate<SpecularMagneticTanhStrategy>();
}

std::unique_ptr<ProcessedSample> SpecularMagneticTest::sample_zerofield(bool slab) {
    MultiLayer multi_layer_scalar;
    Material substr_material_scalar = HomogeneousMaterial("Substrate", 7e-6, 2e-8);
    Layer vacuum_layer(HomogeneousMaterial("Vacuum", 0.0, 0.0));
    Layer substr_layer_scalar(substr_material_scalar);
    multi_layer_scalar.addLayer(vacuum_layer);

    if (slab) {
        Material layer_material = HomogeneousMaterial("Layer", 3e-6, 1e-8);
        Layer layer(layer_material, 10. * Units::nm);
        multi_layer_scalar.addLayer(layer);
    }

    multi_layer_scalar.addLayer(substr_layer_scalar);

    SimulationOptions options;
    auto sample_scalar = std::make_unique<ProcessedSample>(multi_layer_scalar, options);

    return sample_scalar;
}

template <typename Strategy>
void SpecularMagneticTest::testcase_zerofield(std::vector<double>&& angles, bool slab) {
    for (auto& angle : angles) {
        auto sample = sample_zerofield(slab);
        kvector_t k = vecOfLambdaAlphaPhi(1.0, angle * Units::deg, 0.0);
        testZeroField<Strategy>(k, *sample);
    }
}

TEST_F(SpecularMagneticTest, zerofield_v2_negative_k) {
    testcase_zerofield<SpecularMagneticStrategy_v2>({-0.1, -2.0, -10.0});
}

TEST_F(SpecularMagneticTest, zerofield_v2_positive_k) {
    testcase_zerofield<SpecularMagneticStrategy_v2>({0.1, 2.0, 10.0});
}

TEST_F(SpecularMagneticTest, zerofield2_v2_negative_k) {
    testcase_zerofield<SpecularMagneticStrategy_v2>({-0.1, -2.0, -10.0}, true);
}

TEST_F(SpecularMagneticTest, zerofield2_v2_positive_k) {
    testcase_zerofield<SpecularMagneticStrategy_v2>({0.1, 2.0, 10.0}, true);
}

TEST_F(SpecularMagneticTest, zerofield_positive_k) {
    testcase_zerofield<SpecularMagneticTanhStrategy>({0.0, 1.e-9, 1.e-5, 0.1, 2.0, 10.0});
}

TEST_F(SpecularMagneticTest, zerofield_negative_k) {
    testcase_zerofield<SpecularMagneticTanhStrategy>({-0.0, -1.e-9, -1.e-5, -0.1, -2.0, -10.0});
}

TEST_F(SpecularMagneticTest, zerofield2_positive_k) {
    testcase_zerofield<SpecularMagneticTanhStrategy>({0.0, 1.e-9, 1.e-5, 0.1, 2.0, 10.0}, true);
}

TEST_F(SpecularMagneticTest, zerofield2_negative_k) {
    testcase_zerofield<SpecularMagneticTanhStrategy>({-0.0, -1.e-9, -1.e-5, -0.1, -2.0, -10.0},
                                                     true);
}
