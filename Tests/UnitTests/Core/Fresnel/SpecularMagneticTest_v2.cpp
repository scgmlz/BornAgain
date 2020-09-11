#include "Core/Basics/Units.h"
#include "Core/Computation/ProcessedSample.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/SpecularMagneticStrategy.h"
#include "Core/Multilayer/SpecularScalarTanhStrategy.h"
#include "Core/Parametrization/SimulationOptions.h"
#include "Tests/GTestWrapper/google_test.h"

constexpr double eps = 1e-10;

class SpecularMagneticTest_v2 : public ::testing::Test
{
protected:
    //! Compares results with scalar case
    void testZeroField(const kvector_t& k, const ProcessedSample& m_layer_scalar,
                       const ProcessedSample& m_layer_zerofield);

    void ifEqual(const Eigen::Vector2cd& lhs, const Eigen::Vector2cd& rhs);
};

void SpecularMagneticTest_v2::testZeroField(const kvector_t& k,
                                            const ProcessedSample& sample_scalar,
                                            const ProcessedSample& sample_zerofield)
{
    auto coeffs_scalar =
        std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_scalar.slices(), k);
    auto coeffs_zerofield =
        std::make_unique<SpecularMagneticStrategy>()->Execute(sample_zerofield.slices(), k);

    EXPECT_EQ(coeffs_scalar.size(), coeffs_zerofield.size());

    for (size_t i = 0; i < coeffs_scalar.size(); ++i) {
        const ScalarRTCoefficients& RTScalar =
            *dynamic_cast<const ScalarRTCoefficients*>(coeffs_scalar[i].get());
        Eigen::Vector2cd TPS = RTScalar.T1plus() + RTScalar.T2plus();
        Eigen::Vector2cd RPS = RTScalar.R1plus() + RTScalar.R2plus();
        Eigen::Vector2cd TMS = RTScalar.T1min() + RTScalar.T2min();
        Eigen::Vector2cd RMS = RTScalar.R1min() + RTScalar.R2min();

        const MatrixRTCoefficients_v2& RTMatrix =
            *dynamic_cast<const MatrixRTCoefficients_v2*>(coeffs_zerofield[i].get());
        Eigen::Vector2cd TPM = RTMatrix.T1plus() + RTMatrix.T2plus();
        Eigen::Vector2cd RPM = RTMatrix.R1plus() + RTMatrix.R2plus();
        Eigen::Vector2cd TMM = RTMatrix.T1min() + RTMatrix.T2min();
        Eigen::Vector2cd RMM = RTMatrix.R1min() + RTMatrix.R2min();

        ifEqual(TPS, TPM);
        ifEqual(RPS, RPM);
        ifEqual(TMS, TMM);
        ifEqual(RMS, RMM);

        ifEqual(RTScalar.getKz(), RTMatrix.getKz());
    }
}

void SpecularMagneticTest_v2::ifEqual(const Eigen::Vector2cd& lhs, const Eigen::Vector2cd& rhs)
{
    EXPECT_NEAR(0.0, std::abs(lhs(0) - rhs(0)), eps);
    EXPECT_NEAR(0.0, std::abs(lhs(1) - rhs(1)), eps);
}

TEST_F(SpecularMagneticTest_v2, degenerate)
{
    MultiLayer mLayer;
    kvector_t v;

    Material air = HomogeneousMaterial("air", 0, 1.0);
    mLayer.addLayer(Layer(air, 0 * Units::nanometer));
    ProcessedSample sample(mLayer, SimulationOptions());

    Eigen::Vector2cd Tp_ref{0.5, 0.0};
    Eigen::Vector2cd Rp_ref{-0.5, 0.0};
    Eigen::Vector2cd Tm_ref{0.0, 0.5};
    Eigen::Vector2cd Rm_ref{0.0, -0.5};

    auto result = std::make_unique<SpecularMagneticStrategy>()->Execute(sample.slices(), v);
    for (auto& coeff : result) {
        ifEqual(coeff->T1plus(), Tp_ref);
        ifEqual(coeff->T2plus(), Tp_ref);
        ifEqual(coeff->T1min(), Tm_ref);
        ifEqual(coeff->T2min(), Tm_ref);
        ifEqual(coeff->R1plus(), Rp_ref);
        ifEqual(coeff->R2plus(), Rp_ref);
        ifEqual(coeff->R1min(), Rm_ref);
        ifEqual(coeff->R2min(), Rm_ref);
    }
}

TEST_F(SpecularMagneticTest_v2, zerofield)
{
    kvector_t substr_field(0.0, 0.0, 0.0);
    kvector_t k1 = vecOfLambdaAlphaPhi(1.0, -0.1 * Units::deg, 0.0);
    kvector_t k2 = vecOfLambdaAlphaPhi(1.0, -2.0 * Units::deg, 0.0);
    kvector_t k3 = vecOfLambdaAlphaPhi(1.0, -10.0 * Units::deg, 0.0);

    MultiLayer multi_layer_scalar;
    Material substr_material_scalar = HomogeneousMaterial("Substrate", 7e-6, 2e-8);
    Layer air_layer(HomogeneousMaterial("Air", 0.0, 0.0));
    Layer substr_layer_scalar(substr_material_scalar);
    multi_layer_scalar.addLayer(air_layer);
    multi_layer_scalar.addLayer(substr_layer_scalar);
    std::vector<ScalarRTCoefficients> coeffs_scalar;

    MultiLayer multi_layer_zerofield;
    Material substr_material_zerofield = HomogeneousMaterial("Substrate", 7e-6, 2e-8, substr_field);
    Layer substr_layer_zerofield(substr_material_zerofield);
    multi_layer_zerofield.addLayer(air_layer);
    multi_layer_zerofield.addLayer(substr_layer_zerofield);

    SimulationOptions options;
    ProcessedSample sample_scalar(multi_layer_scalar, options);
    ProcessedSample sample_zerofield(multi_layer_zerofield, options);

    testZeroField(k1, sample_scalar, sample_zerofield);
    testZeroField(k2, sample_scalar, sample_zerofield);
    testZeroField(k3, sample_scalar, sample_zerofield);
}
