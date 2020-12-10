#include "Sample/Fresnel/FormFactorCoherentSum.h"
#include "Sample/FFCompute/ComputeBA.h"
#include "Sample/HardParticle/FormFactorDot.h"
#include "Tests/GTestWrapper/google_test.h"

class FormFactorCoherentSumTest : public ::testing::Test {};

TEST_F(FormFactorCoherentSumTest, RelAbundance) {
    const double epsilon = 1e-12;
    FormFactorDot ff(5.0);
    FormFactorCoherentSum ffw(1.0);
    FormFactorCoherentPart part(new ComputeBA(ff));
    ffw.addCoherentPart(part);
    EXPECT_EQ(1.0, ffw.relativeAbundance());
    EXPECT_EQ(0.0, ffw.radialExtension());
    ffw.scaleRelativeAbundance(2.0);
    EXPECT_NEAR(0.5, ffw.relativeAbundance(), epsilon);
    EXPECT_THROW(ffw.scaleRelativeAbundance(0.0), std::runtime_error);
    EXPECT_EQ(0.0, ffw.radialExtension());
}
