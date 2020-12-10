#include "Base/Math/Bessel.h"
#include "Tests/GTestWrapper/google_test.h"

class BesselTest : public ::testing::Test {};

// Test complex Bessel function J1
TEST_F(BesselTest, BesselJ1) {
    const double eps = 4.7e-16; // more than twice the machine precision
    complex_t res;

    // Test four arbitrary function values.
    // Reference values are computed using dev-tools/math/cbesselJ01.c,
    //   from which BesselJ1 has been derived. So this is _not_ an independent
    //   for numeric accuracy, but only for invariance.
    // However, the four specific results below have also been checked against the
    //   online calculator http://keisan.casio.com/exec/system/1180573474.
    //   Agreement is excellent, except for the dominantly imaginary argument .01+100i.
    //   In conclusion, Bessel::J1 is clearly good enough for our purpose.
    res = Math::Bessel::J1(complex_t(0.8, 1.5));
    EXPECT_NEAR(res.real(), 0.72837687825769404, eps * std::abs(res)); // Keisan ..69398...
    EXPECT_NEAR(res.imag(), 0.75030568686427268, eps * std::abs(res)); // Keisan ..27264...

    res = Math::Bessel::J1(complex_t(1e-2, 1e2));
    EXPECT_NEAR(res.real(), 1.0630504683139779e+40, eps * std::abs(res)); // Keisan 1.063015...
    EXPECT_NEAR(res.imag(), 1.0683164984973165e+42, eps * std::abs(res)); // Keisan ..73162...

    res = Math::Bessel::J1(complex_t(-1e2, 1e-2));
    EXPECT_NEAR(res.real(), 0.077149198549289394, eps * std::abs(res)); // Keisan ..89252...
    EXPECT_NEAR(res.imag(), 2.075766253119904e-4, eps * std::abs(res)); // Keisan ..19951...

    res = Math::Bessel::J1(complex_t(7, 9));
    EXPECT_NEAR(res.real(), 370.00180888861155, eps * std::abs(res)); // Keisan ..61107...
    EXPECT_NEAR(res.imag(), 856.00300811057934, eps * std::abs(res)); // Keisan ..57940...
}
