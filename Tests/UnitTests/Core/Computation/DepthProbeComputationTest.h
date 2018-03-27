#include "google_test.h"

#define private public
#define protected public

#include "DepthProbeComputation.h"
#include "DepthProbeElement.h"
#include "FixedBinAxis.h"
#include "IFresnelMap.h"
#include "Layer.h"
#include "MathConstants.h"
#include "MaterialFactoryFuncs.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "Units.h"

class DepthProbeComputationTest : public ::testing::Test
{
protected:
    DepthProbeComputationTest();
    ~DepthProbeComputationTest();

    double getIntensityInLayer(size_t i_layer, double position);

    //constants
    const double delta_0 = 0.0;
    const double delta_1 = 0.05;
    const double delta_2 = 0.06;
    const double d_layer = 10 * Units::nm;
    const double wavelength = M_TWOPI;
    const double alpha_i = M_PI / 6.0;
    const kvector_t K = vecOfLambdaAlphaPhi(wavelength, -alpha_i, 0.0);

    FixedBinAxis z_axis;
    MultiLayer multilayer;
    ProgressHandler progress;
    std::vector<DepthProbeElement> elements;
    std::unique_ptr<DepthProbeComputation> p_computation;
};

DepthProbeComputationTest::DepthProbeComputationTest()
    : z_axis("z_axis", 20, -15.0, 5.0)
{
    // creating multilayer
    Material mat0 = HomogeneousMaterial("ambience", delta_0, 0.0);
    Material mat1 = HomogeneousMaterial("PartA", delta_1, 0.0);
    Material mat2 = HomogeneousMaterial("substrate", delta_2, 0.0);

    Layer layer0(mat0);
    Layer layer1(mat1, d_layer);
    Layer layer2(mat2);

    multilayer.addLayer(layer0);
    multilayer.addLayer(layer1);
    multilayer.addLayer(layer2);

    // creating depth probe element
    elements.push_back(DepthProbeElement(wavelength, -alpha_i, &z_axis));

    // creating computation
    p_computation = std::make_unique<DepthProbeComputation>(multilayer, SimulationOptions(),
                                                            progress, elements.begin(),
                                                            elements.end());
    p_computation->run();
}

DepthProbeComputationTest::~DepthProbeComputationTest() = default;

double DepthProbeComputationTest::getIntensityInLayer(size_t i_layer, double position)
{
    const auto coeff = p_computation->mP_fresnel_map->getInCoefficients(elements[0], i_layer);

    const complex_t kz_out = coeff->getScalarKz(); // kz for outgoing wave
    const complex_t kz_in = -kz_out; // kz_in = kz for incoming wave
    const complex_t R = coeff->getScalarR();
    const complex_t T = coeff->getScalarT();

    const double local_position = position - multilayer.layerTopZ(i_layer);

    return std::norm(R * exp_I(kz_out * local_position) + T * exp_I(kz_in * local_position));
}

TEST_F(DepthProbeComputationTest, IntensityTest)
{
    const std::valarray<double> results = elements.begin()->getIntensities();
    for (size_t i = 0; i < results.size(); ++i) {
        size_t i_layer = z_axis[i] < -d_layer ? 2u : z_axis[i] > 0 ? 0u : 1u;
        EXPECT_EQ(results[i], getIntensityInLayer(i_layer, z_axis[i]));
    }
}

#undef private
#undef protected
