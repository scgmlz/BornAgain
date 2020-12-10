#include "Base/Const/Units.h"
#include "Base/Vector/Direction.h"
#include "Sample/LegacyRT/SpecularMagneticStrategy_v1.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Processed/ProcessedSample.h"
#include "Sample/RT/SimulationOptions.h"
#include "Sample/Specular/SpecularScalarTanhStrategy.h"
#include "Tests/GTestWrapper/google_test.h"

class SpecularMagnetic_v1Test : public ::testing::Test {};

TEST_F(SpecularMagnetic_v1Test, initial) {
    MultiLayer mLayer;
    kvector_t v;

    // @Error: Throws exception (Layer index is out of bounds)
    // matrix.execute(mLayer, v, coeff);

    Material air = HomogeneousMaterial("Air", 0, 1.0);
    Layer layer0(air, 0 * Units::nm);
    mLayer.addLayer(layer0);
    SimulationOptions options;
    ProcessedSample sample(mLayer, options);
    std::make_unique<SpecularMagneticStrategy_v1>()->Execute(sample.slices(), v);
}

TEST_F(SpecularMagnetic_v1Test, zerofield) {
    double eps = 1e-10;

    kvector_t substr_field(0.0, 0.0, 0.0);
    kvector_t k1 = vecOfLambdaAlphaPhi(1.0, -0.1 * Units::deg, 0.0);
    kvector_t k2 = vecOfLambdaAlphaPhi(1.0, -2.0 * Units::deg, 0.0);
    kvector_t k3 = vecOfLambdaAlphaPhi(1.0, -10.0 * Units::deg, 0.0);

    MultiLayer multi_layer_scalar;
    Material substr_material_scalar = HomogeneousMaterial("Substrate", 7e-6, 2e-8);
    Layer vacuum_layer(HomogeneousMaterial("Vacuum", 0.0, 0.0));
    Layer substr_layer_scalar(substr_material_scalar);
    multi_layer_scalar.addLayer(vacuum_layer);
    multi_layer_scalar.addLayer(substr_layer_scalar);

    MultiLayer multi_layer_zerofield;
    Material substr_material_zerofield = HomogeneousMaterial("Substrate", 7e-6, 2e-8, substr_field);
    Layer substr_layer_zerofield(substr_material_zerofield);
    multi_layer_zerofield.addLayer(vacuum_layer);
    multi_layer_zerofield.addLayer(substr_layer_zerofield);

    SimulationOptions options;
    ProcessedSample sample_scalar(multi_layer_scalar, options);
    ProcessedSample sample_zerofield(multi_layer_zerofield, options);

    // k1
    auto coeffs_scalar =
        std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_scalar.slices(), k1);
    ScalarRTCoefficients RTScalar =
        *dynamic_cast<const ScalarRTCoefficients*>(coeffs_scalar[1].get());
    Eigen::Vector2cd TPS = RTScalar.T1plus() + RTScalar.T2plus();
    Eigen::Vector2cd RPS = RTScalar.R1plus() + RTScalar.R2plus();
    Eigen::Vector2cd TMS = RTScalar.T1min() + RTScalar.T2min();
    Eigen::Vector2cd RMS = RTScalar.R1min() + RTScalar.R2min();

    auto coeffs_zerofield =
        std::make_unique<SpecularMagneticStrategy_v1>()->Execute(sample_zerofield.slices(), k1);
    MatrixRTCoefficients_v1 RTMatrix =
        *dynamic_cast<const MatrixRTCoefficients_v1*>(coeffs_zerofield[1].get());
    Eigen::Vector2cd TPM = RTMatrix.T1plus() + RTMatrix.T2plus();
    Eigen::Vector2cd RPM = RTMatrix.R1plus() + RTMatrix.R2plus();
    Eigen::Vector2cd TMM = RTMatrix.T1min() + RTMatrix.T2min();
    Eigen::Vector2cd RMM = RTMatrix.R1min() + RTMatrix.R2min();

    EXPECT_NEAR(0.0, std::abs(TPS(0) - TPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TPS(1) - TPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(0) - RPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(1) - RPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(0) - TMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(1) - TMM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(0) - RMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(1) - RMM(1)), eps);

    // k2
    coeffs_scalar =
        std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_scalar.slices(), k2);
    RTScalar = *dynamic_cast<const ScalarRTCoefficients*>(coeffs_scalar[1].get());
    TPS = RTScalar.T1plus() + RTScalar.T2plus();
    RPS = RTScalar.R1plus() + RTScalar.R2plus();
    TMS = RTScalar.T1min() + RTScalar.T2min();
    RMS = RTScalar.R1min() + RTScalar.R2min();

    coeffs_zerofield =
        std::make_unique<SpecularMagneticStrategy_v1>()->Execute(sample_zerofield.slices(), k2);
    RTMatrix = *dynamic_cast<const MatrixRTCoefficients_v1*>(coeffs_zerofield[1].get());
    TPM = RTMatrix.T1plus() + RTMatrix.T2plus();
    RPM = RTMatrix.R1plus() + RTMatrix.R2plus();
    TMM = RTMatrix.T1min() + RTMatrix.T2min();
    RMM = RTMatrix.R1min() + RTMatrix.R2min();

    EXPECT_NEAR(0.0, std::abs(TPS(0) - TPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TPS(1) - TPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(0) - RPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(1) - RPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(0) - TMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(1) - TMM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(0) - RMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(1) - RMM(1)), eps);

    // k3
    coeffs_scalar =
        std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_scalar.slices(), k3);
    RTScalar = *dynamic_cast<const ScalarRTCoefficients*>(coeffs_scalar[1].get());
    TPS = RTScalar.T1plus() + RTScalar.T2plus();
    RPS = RTScalar.R1plus() + RTScalar.R2plus();
    TMS = RTScalar.T1min() + RTScalar.T2min();
    RMS = RTScalar.R1min() + RTScalar.R2min();

    coeffs_zerofield =
        std::make_unique<SpecularMagneticStrategy_v1>()->Execute(sample_zerofield.slices(), k3);
    RTMatrix = *dynamic_cast<const MatrixRTCoefficients_v1*>(coeffs_zerofield[1].get());
    TPM = RTMatrix.T1plus() + RTMatrix.T2plus();
    RPM = RTMatrix.R1plus() + RTMatrix.R2plus();
    TMM = RTMatrix.T1min() + RTMatrix.T2min();
    RMM = RTMatrix.R1min() + RTMatrix.R2min();

    EXPECT_NEAR(0.0, std::abs(TPS(0) - TPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TPS(1) - TPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(0) - RPM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RPS(1) - RPM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(0) - TMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(TMS(1) - TMM(1)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(0) - RMM(0)), eps);
    EXPECT_NEAR(0.0, std::abs(RMS(1) - RMM(1)), eps);
}
