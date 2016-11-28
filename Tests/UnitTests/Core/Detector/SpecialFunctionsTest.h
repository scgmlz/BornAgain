// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/UnitTests/Core/3/SpecialFunctionsTest.h
//! @brief     Defines unit test for Form factors.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECIALFUNCTIONSTEST_H
#define SPECIALFUNCTIONSTEST_H

#include "MathFunctions.h"
#include "MathConstants.h"

#define EXPECT_CNEAR(a,b,epsi) \
  EXPECT_NEAR((a).real(),(b).real(),epsi); EXPECT_NEAR((a).imag(),(b).imag(),epsi);

class SpecialFunctionsTest : public ::testing::Test
{
protected:
    SpecialFunctionsTest(){}
};

// Test complex Bessel function J1
TEST_F(SpecialFunctionsTest, BesselJ1)
{
    const double eps = 4.7e-16; // more than twice the machine precision
    complex_t res;

    // Test four arbitrary function values.
    // Reference values are computed using dev-tools/math/cbesselJ01.c,
    //   from which BesselJ1 has been derived. So this is _not_ an independent
    //   for numeric accuracy, but only for invariance.
    // However, the four specific results below have also been checked against the
    //   online calculator http://keisan.casio.com/exec/system/1180573474.
    //   Agreement is excellent, except for the dominantly imaginary argument .01+100i.
    //   In conclusion, Bessel_J1 is clearly good enough for our purpose.
    res = MathFunctions::Bessel_J1(complex_t(0.8,1.5));
    EXPECT_NEAR( res.real(), 0.72837687825769404, eps*std::abs(res) ); // Keisan ..69398...
    EXPECT_NEAR( res.imag(), 0.75030568686427268, eps*std::abs(res) ); // Keisan ..27264...

    res = MathFunctions::Bessel_J1(complex_t(1e-2,1e2));
    EXPECT_NEAR( res.real(), 1.0630504683139779e+40, eps*std::abs(res) ); // Keisan 1.063015...
    EXPECT_NEAR( res.imag(), 1.0683164984973165e+42, eps*std::abs(res) ); // Keisan ..73162...

    res = MathFunctions::Bessel_J1(complex_t(-1e2,1e-2));
    EXPECT_NEAR( res.real(), 0.077149198549289394, eps*std::abs(res) );  // Keisan ..89252...
    EXPECT_NEAR( res.imag(), 2.075766253119904e-4, eps*std::abs(res) ); // Keisan ..19951...

    res = MathFunctions::Bessel_J1(complex_t(7,9));
    EXPECT_NEAR( res.real(), 370.00180888861155, eps*std::abs(res) ); // Keisan ..61107...
    EXPECT_NEAR( res.imag(), 856.00300811057934, eps*std::abs(res) ); // Keisan ..57940...
}

// Test accuracy of complex function sinc(z) near the removable singularity at z=0

TEST_F(SpecialFunctionsTest, csinc)
{
    const double eps = 4.7e-16; // more than twice the machine precision

    for( int i=0; i<24; ++i ) {
        double ph = M_TWOPI*i/24;
        //std::cout << "---------------------------------------------------------------------\n";
        //std::cout << "phase = " << ph << "\n";
        EXPECT_EQ( MathFunctions::sinc(complex_t(0,0)),       complex_t(1.,0.) );
        complex_t z;
        z=std::polar(1e-17,ph); EXPECT_CNEAR( MathFunctions::sinc(z), complex_t(1.,0.), eps );
        z=std::polar(2e-17,ph); EXPECT_CNEAR( MathFunctions::sinc(z), complex_t(1.,0.), eps );
        z=std::polar(5e-17,ph); EXPECT_CNEAR( MathFunctions::sinc(z), complex_t(1.,0.), eps );
        z=std::polar(1e-16,ph); EXPECT_CNEAR( MathFunctions::sinc(z), complex_t(1.,0.), eps );
        z=std::polar(2e-16,ph); EXPECT_CNEAR( MathFunctions::sinc(z), complex_t(1.,0.), eps );
        z=std::polar(5e-16,ph); EXPECT_CNEAR( MathFunctions::sinc(z), complex_t(1.,0.), eps );
        z=std::polar(1e-15,ph); EXPECT_CNEAR( MathFunctions::sinc(z), complex_t(1.,0.), eps );
        z=std::polar(1e-13,ph); EXPECT_CNEAR( MathFunctions::sinc(z), complex_t(1.,0.), eps );
        z=std::polar(1e-11,ph); EXPECT_CNEAR( MathFunctions::sinc(z), complex_t(1.,0.), eps );
        z=std::polar(1e-9, ph); EXPECT_CNEAR( MathFunctions::sinc(z), complex_t(1.,0.), eps );
        z=std::polar(5e-8,ph); EXPECT_CNEAR( MathFunctions::sinc(z), 1.-z*z/6., eps );
        z=std::polar(2e-8,ph); EXPECT_CNEAR( MathFunctions::sinc(z), 1.-z*z/6., eps );
        z=std::polar(1e-8,ph); EXPECT_CNEAR( MathFunctions::sinc(z), 1.-z*z/6., eps );
        z=std::polar(5e-7,ph); EXPECT_CNEAR( MathFunctions::sinc(z), 1.-z*z/6., eps );
        z=std::polar(2e-7,ph); EXPECT_CNEAR( MathFunctions::sinc(z), 1.-z*z/6., eps );
        z=std::polar(1e-7,ph); EXPECT_CNEAR( MathFunctions::sinc(z), 1.-z*z/6., eps );
        z=std::polar(1e-6,ph); EXPECT_CNEAR( MathFunctions::sinc(z), 1.-z*z/6., eps );
        z=std::polar(1e-5,ph); EXPECT_CNEAR( MathFunctions::sinc(z), 1.-z*z/6., eps );
        z=std::polar(1e-4,ph); EXPECT_CNEAR( MathFunctions::sinc(z), 1.-z*z/6.*(1.-z*z/20.), eps );
        z=std::polar(1e-3,ph); EXPECT_CNEAR( MathFunctions::sinc(z), 1.-z*z/6.*(1.-z*z/20.), eps );
    }
}

#endif // SPECIALFUNCTIONSTEST_H
