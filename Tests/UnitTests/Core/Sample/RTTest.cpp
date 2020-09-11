#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Computation/ProcessedSample.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/SpecularScalarTanhStrategy.h"
#include "Core/Parametrization/SimulationOptions.h"
#include "Tests/GTestWrapper/google_test.h"

class RTTest : public ::testing::Test
{
protected:
    ~RTTest();
    void printCoeffs(const std::vector<ScalarRTCoefficients>& coeffs)
    { // for debug phases
        for (size_t i = 0; i < coeffs.size(); ++i) {
            const ScalarRTCoefficients& coeff = coeffs[i];
            std::cout << i << " " << coeff.t_r(0) << " " << coeff.t_r(1) << "\n";
        }
    }
    void compareCoeffs(const ScalarRTCoefficients& coeff1, const ScalarRTCoefficients& coeff2)
    {
        EXPECT_NEAR(abs(coeff1.t_r(0)), abs(coeff2.t_r(0)), 5e-14);
        EXPECT_NEAR(coeff1.t_r(0).real(), coeff2.t_r(0).real(), 1e-10);
        EXPECT_NEAR(coeff1.t_r(0).imag(), coeff2.t_r(0).imag(), 1e-10);
        EXPECT_NEAR(abs(coeff1.t_r(1)), abs(coeff2.t_r(1)), 5e-14);
        EXPECT_NEAR(coeff1.t_r(1).real(), coeff2.t_r(1).real(), 1e-10);
        EXPECT_NEAR(coeff1.t_r(1).imag(), coeff2.t_r(1).imag(), 1e-10);
    }
    std::vector<ScalarRTCoefficients> getCoeffs(ISpecularStrategy::coeffs_t&& inputCoeffs)
    {
        std::vector<ScalarRTCoefficients> result;
        for (auto& coeff : inputCoeffs)
            result.push_back(*dynamic_cast<const ScalarRTCoefficients*>(coeff.get()));

        return result;
    }
    const Material air = HomogeneousMaterial("air", 1e-8, 1e-8);
    const Material amat = HomogeneousMaterial("material A", 2e-6, 8e-7);
    const Material bmat = HomogeneousMaterial("material B (high absorption)", 3e-5, 2e-4);
    const Material stone = HomogeneousMaterial("substrate material", 1e-6, 1e-7);
    const Layer topLayer{air, 0};
    const Layer substrate{stone, 0};
    const kvector_t k{1, 0, -1e-3};
    MultiLayer sample1, sample2;
    std::vector<ScalarRTCoefficients> coeffs1, coeffs2;
};

RTTest::~RTTest() = default;

TEST_F(RTTest, SplitLayer)
{
    const int n = 40;

    sample1.addLayer(topLayer);
    sample1.addLayer(Layer(amat, n * 10));
    sample1.addLayer(substrate);

    sample2.addLayer(topLayer);
    for (size_t i = 0; i < n; ++i)
        sample2.addLayer(Layer(amat, 10));
    sample2.addLayer(substrate);

    SimulationOptions options;
    ProcessedSample sample_1(sample1, options);
    ProcessedSample sample_2(sample2, options);

    coeffs1 =
        getCoeffs(std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_1.slices(), k));
    coeffs2 =
        getCoeffs(std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_2.slices(), k));

    // printCoeffs( coeffs1 );
    // printCoeffs( coeffs2 );

    compareCoeffs(coeffs1[0], coeffs2[0]);
    compareCoeffs(coeffs1[1], coeffs2[1]);
    compareCoeffs(coeffs1.back(), coeffs2.back());
}

TEST_F(RTTest, SplitBilayers)
{
    // With exaggerated values of #layers, layer thickness, and absorption
    // so that we also test correct handling of floating-point overflow.
    const int n = 200;

    sample1.addLayer(topLayer);
    for (size_t i = 0; i < n; ++i) {
        sample1.addLayer(Layer(amat, 100));
        sample1.addLayer(Layer(bmat, 200));
    }
    sample1.addLayer(substrate);

    sample2.addLayer(topLayer);
    for (size_t i = 0; i < n; ++i) {
        sample2.addLayer(Layer(amat, 100));
        sample2.addLayer(Layer(bmat, 100));
        sample2.addLayer(Layer(amat, 0));
        sample2.addLayer(Layer(bmat, 100));
    }
    sample2.addLayer(substrate);

    SimulationOptions options;
    ProcessedSample sample_1(sample1, options);
    ProcessedSample sample_2(sample2, options);

    coeffs1 =
        getCoeffs(std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_1.slices(), k));
    coeffs2 =
        getCoeffs(std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_2.slices(), k));

    //     printCoeffs( coeffs1 );
    //     printCoeffs( coeffs2 );

    compareCoeffs(coeffs1[0], coeffs2[0]);
    compareCoeffs(coeffs1[1], coeffs2[1]);

    // Amplitudes at bottom must be strictly zero.
    // The new algorithm handles this without an overflow
    EXPECT_EQ(complex_t(), coeffs1[coeffs1.size() - 2].t_r(0));
    EXPECT_EQ(complex_t(), coeffs1[coeffs1.size() - 2].t_r(1));
    EXPECT_EQ(complex_t(), coeffs2[coeffs2.size() - 2].t_r(0));
    EXPECT_EQ(complex_t(), coeffs2[coeffs2.size() - 2].t_r(1));
}

TEST_F(RTTest, Overflow)
{
    // Text extra thick layers to also provoke an overflow in the new algorithm
    const int n = 5;

    sample1.addLayer(topLayer);
    for (size_t i = 0; i < n; ++i) {
        sample1.addLayer(Layer(amat, 1000));
        sample1.addLayer(Layer(bmat, 200000));
    }
    sample1.addLayer(substrate);

    sample2.addLayer(topLayer);
    for (size_t i = 0; i < n; ++i) {
        sample2.addLayer(Layer(amat, 1000));
        sample2.addLayer(Layer(bmat, 100000));
        sample2.addLayer(Layer(amat, 0));
        sample2.addLayer(Layer(bmat, 100000));
    }
    sample2.addLayer(substrate);

    SimulationOptions options;
    ProcessedSample sample_1(sample1, options);
    ProcessedSample sample_2(sample2, options);

    coeffs1 =
        getCoeffs(std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_1.slices(), k));
    coeffs2 =
        getCoeffs(std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_2.slices(), k));

    //     printCoeffs( coeffs1 );
    //     printCoeffs( coeffs2 );

    compareCoeffs(coeffs1[0], coeffs2[0]);
    compareCoeffs(coeffs1[1], coeffs2[1]);

    // If floating-point overflow is handled correctly, amplitudes at bottom must be strictly zero.
    EXPECT_EQ(complex_t(), coeffs1[coeffs1.size() - 2].t_r(0));
    EXPECT_EQ(complex_t(), coeffs1[coeffs1.size() - 2].t_r(1));
    EXPECT_EQ(complex_t(), coeffs2[coeffs2.size() - 2].t_r(0));
    EXPECT_EQ(complex_t(), coeffs2[coeffs2.size() - 2].t_r(1));
}
