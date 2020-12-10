#include "Base/Math/Constants.h"
#include "Base/Math/Functions.h"
#include "Tests/GTestWrapper/google_test.h"

#define EXPECT_CNEAR(a, b, epsi)                                                                   \
    EXPECT_NEAR((a).real(), (b).real(), epsi);                                                     \
    EXPECT_NEAR((a).imag(), (b).imag(), epsi);

class SpecialFunctionsTest : public ::testing::Test {};

// Test accuracy of complex function sinc(z) near the removable singularity at z=0

TEST_F(SpecialFunctionsTest, csinc) {
    const double eps = 4.7e-16; // more than twice the machine precision

    for (int i = 0; i < 24; ++i) {
        double ph = M_TWOPI * i / 24;
        // std::cout << "---------------------------------------------------------------------\n";
        // std::cout << "phase = " << ph << "\n";
        EXPECT_EQ(Math::sinc(complex_t(0, 0)), complex_t(1., 0.));
        complex_t z;
        z = std::polar(1e-17, ph);
        EXPECT_CNEAR(Math::sinc(z), complex_t(1., 0.), eps);
        z = std::polar(2e-17, ph);
        EXPECT_CNEAR(Math::sinc(z), complex_t(1., 0.), eps);
        z = std::polar(5e-17, ph);
        EXPECT_CNEAR(Math::sinc(z), complex_t(1., 0.), eps);
        z = std::polar(1e-16, ph);
        EXPECT_CNEAR(Math::sinc(z), complex_t(1., 0.), eps);
        z = std::polar(2e-16, ph);
        EXPECT_CNEAR(Math::sinc(z), complex_t(1., 0.), eps);
        z = std::polar(5e-16, ph);
        EXPECT_CNEAR(Math::sinc(z), complex_t(1., 0.), eps);
        z = std::polar(1e-15, ph);
        EXPECT_CNEAR(Math::sinc(z), complex_t(1., 0.), eps);
        z = std::polar(1e-13, ph);
        EXPECT_CNEAR(Math::sinc(z), complex_t(1., 0.), eps);
        z = std::polar(1e-11, ph);
        EXPECT_CNEAR(Math::sinc(z), complex_t(1., 0.), eps);
        z = std::polar(1e-9, ph);
        EXPECT_CNEAR(Math::sinc(z), complex_t(1., 0.), eps);
        z = std::polar(5e-8, ph);
        EXPECT_CNEAR(Math::sinc(z), 1. - z * z / 6., eps);
        z = std::polar(2e-8, ph);
        EXPECT_CNEAR(Math::sinc(z), 1. - z * z / 6., eps);
        z = std::polar(1e-8, ph);
        EXPECT_CNEAR(Math::sinc(z), 1. - z * z / 6., eps);
        z = std::polar(5e-7, ph);
        EXPECT_CNEAR(Math::sinc(z), 1. - z * z / 6., eps);
        z = std::polar(2e-7, ph);
        EXPECT_CNEAR(Math::sinc(z), 1. - z * z / 6., eps);
        z = std::polar(1e-7, ph);
        EXPECT_CNEAR(Math::sinc(z), 1. - z * z / 6., eps);
        z = std::polar(1e-6, ph);
        EXPECT_CNEAR(Math::sinc(z), 1. - z * z / 6., eps);
        z = std::polar(1e-5, ph);
        EXPECT_CNEAR(Math::sinc(z), 1. - z * z / 6., eps);
        z = std::polar(1e-4, ph);
        EXPECT_CNEAR(Math::sinc(z), 1. - z * z / 6. * (1. - z * z / 20.), eps);
        z = std::polar(1e-3, ph);
        EXPECT_CNEAR(Math::sinc(z), 1. - z * z / 6. * (1. - z * z / 20.), eps);
    }
}
