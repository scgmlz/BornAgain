#include "Base/Const/Units.h"
#include "Sample/LegacyRT/SpecularMagneticStrategy_v2.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Processed/ProcessedSample.h"
#include "Sample/RT/SimulationOptions.h"
#include "Sample/Slice/KzComputation.h"
#include "Sample/Specular/SpecularMagneticTanhStrategy.h"
#include "Tests/GTestWrapper/google_test.h"

class SpecularMagneticConsistencyTest : public ::testing::Test {
protected:
    auto static constexpr eps = 1.e-10;

    std::unique_ptr<ProcessedSample> sample_1();

    template <typename Strategy1, typename Strategy2>
    void testcase(const std::vector<Slice>& slices, double k);
};

std::unique_ptr<ProcessedSample> SpecularMagneticConsistencyTest::sample_1() {
    MultiLayer multi_layer_scalar;
    Material substr_material_scalar = HomogeneousMaterial("Substrate", 7e-6, 2e-8);
    Material layer_material = HomogeneousMaterial("Layer", 3e-6, 1e-8, kvector_t{1.e7, 0, 1.e7});

    Layer vacuum_layer(HomogeneousMaterial("Vacuum", 0.0, 0.0));
    Layer substr_layer_scalar(substr_material_scalar);
    Layer layer(layer_material, 10. * Units::nm);

    multi_layer_scalar.addLayer(vacuum_layer);
    multi_layer_scalar.addLayer(layer);
    multi_layer_scalar.addLayer(substr_layer_scalar);

    SimulationOptions options;
    auto sample_scalar = std::make_unique<ProcessedSample>(multi_layer_scalar, options);

    return sample_scalar;
}

template <typename Strategy1, typename Strategy2>
void SpecularMagneticConsistencyTest::testcase(const std::vector<Slice>& slices, double k) {

    const auto kz = kvector_t{0., 0., k};
    const auto coeffs1 = std::make_unique<Strategy1>()->Execute(
        slices, KzComputation::computeKzFromRefIndices(slices, kz));
    const auto coeffs2 = std::make_unique<Strategy2>()->Execute(
        slices, KzComputation::computeKzFromRefIndices(slices, kz));

    for (size_t i = 0; i < coeffs1.size(); ++i) {
        EXPECT_NEAR_MATRIXCOEFF(coeffs1[i], coeffs2[i], eps);
    }
}

TEST_F(SpecularMagneticConsistencyTest, NewOld) {
    using Strategy1 = SpecularMagneticTanhStrategy;
    using Strategy2 = SpecularMagneticStrategy_v2;

    const auto sample = sample_1();
    const auto slices = sample->slices();

    const std::vector<double> kzs = {1.e-9, 1.e-5, 0.1, 2.0, 10.0};

    for (const auto& k : kzs) {
        testcase<Strategy1, Strategy2>(slices, k);
        testcase<Strategy1, Strategy2>(slices, -k);
    }
}
