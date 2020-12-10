//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Math/Bessel.cpp
//! @brief     Implements Bessel functions in namespace Math.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Base/Math/Bessel.h"
#include "Base/Math/Constants.h"
#include <gsl/gsl_sf_bessel.h>

namespace {

//! Computes the complex Bessel function J0(z), using power series and asymptotic expansion.
//!
//! Forked from unoptimized code at http://www.crbond.com/math.htm,
//! who refers to "Computation of Special Functions", Zhang and Jin, John Wiley and Sons, 1996.

complex_t J0_PowSer(const complex_t z) {
    complex_t cj0;
    static const double eps = 1e-15;
    static double a[] = {-7.03125e-2,           0.112152099609375,     -0.5725014209747314,
                         6.074042001273483,     -1.100171402692467e2,  3.038090510922384e3,
                         -1.188384262567832e5,  6.252951493434797e6,   -4.259392165047669e8,
                         3.646840080706556e10,  -3.833534661393944e12, 4.854014686852901e14,
                         -7.286857349377656e16, 1.279721941975975e19};
    static double b[] = {7.32421875e-2,         -0.2271080017089844,  1.727727502584457,
                         -2.438052969955606e1,  5.513358961220206e2,  -1.825775547429318e4,
                         8.328593040162893e5,   -5.006958953198893e7, 3.836255180230433e9,
                         -3.649010818849833e11, 4.218971570284096e13, -5.827244631566907e15,
                         9.476288099260110e17,  -1.792162323051699e20};

    double a0 = std::abs(z);
    complex_t z1 = z;
    if (a0 == 0.0)
        return 1.0;
    if (std::real(z) < 0.0)
        z1 = -z;
    if (a0 <= 12.0) {
        // standard power series [http://dlmf.nist.gov/10.2 (10.2.2)]
        complex_t z2 = 0.25 * z * z;
        cj0 = 1.0;
        complex_t cr = 1.0;
        for (size_t k = 1; k <= 40; ++k) {
            cr *= -z2 / (double)(k * k);
            cj0 += cr;
            if (std::abs(cr) < std::abs(cj0) * eps)
                break;
        }
    } else {
        // Hankel's asymptotic expansion [http://dlmf.nist.gov/10.17 (10.17.3)]
        size_t kz;
        if (a0 >= 50.0)
            kz = 8; // can be changed to 10
        else if (a0 >= 35.0)
            kz = 10; //   "      "     "  12
        else
            kz = 12; //   "      "     "  14
        complex_t ct1 = z1 - M_PI_4;
        complex_t cp0 = 1.0;
        complex_t cq0 = -0.125;
        const complex_t z1m2 = 1. / (z1 * z1); // faster than std::pow(z1, -2.0) ??
        complex_t ptmp = z1m2;
        for (size_t k = 0; k < kz; ++k) {
            cp0 += a[k] * ptmp;
            cq0 += b[k] * ptmp;
            ptmp *= z1m2;
        }
        cj0 = std::sqrt(M_2_PI / z1) * (cp0 * std::cos(ct1) - cq0 / z1 * std::sin(ct1));
    }
    return cj0;
}

//! Computes the complex Bessel function J1(z), using power series and asymptotic expansion.
//!
//! Forked from same source as for J0_PowSer

complex_t J1_PowSer(const complex_t z) {
    complex_t cj1;
    static const double eps = 1e-15;

    static double a1[] = {0.1171875,
                          -0.1441955566406250,
                          0.6765925884246826,
                          -6.883914268109947,
                          1.215978918765359e2,
                          -3.302272294480852e3,
                          1.276412726461746e5,
                          -6.656367718817688e6,
                          4.502786003050393e8,
                          -3.833857520742790e10,
                          4.011838599133198e12,
                          -5.060568503314727e14,
                          7.572616461117958e16,
                          -1.326257285320556e19};
    static double b1[] = {-0.1025390625,         0.2775764465332031,    -1.993531733751297,
                          2.724882731126854e1,   -6.038440767050702e2,  1.971837591223663e4,
                          -8.902978767070678e5,  5.310411010968522e7,   -4.043620325107754e9,
                          3.827011346598605e11,  -4.406481417852278e13, 6.065091351222699e15,
                          -9.833883876590679e17, 1.855045211579828e20};

    double a0 = std::abs(z);
    if (a0 == 0.0)
        return 0.0;

    complex_t z1 = z;
    if (std::real(z) < 0.0)
        z1 = -z;
    if (a0 <= 12.0) {
        // standard power series [http://dlmf.nist.gov/10.2 (10.2.2)]
        const complex_t z2 = 0.25 * z * z;
        cj1 = 1.0;
        complex_t cr = 1.0; // powers will be computed recursively
        for (int k = 1; k <= 40; ++k) {
            cr *= -z2 / (double)(k * (k + 1));
            cj1 += cr;
            if (std::abs(cr) < std::abs(cj1) * eps)
                break;
        }
        cj1 *= 0.5 * z1;
    } else {
        // Hankel's asymptotic expansion [http://dlmf.nist.gov/10.17 (10.17.3)]
        size_t kz;
        if (a0 >= 50.0)
            kz = 8; // can be changed to 10
        else if (a0 >= 35.0)
            kz = 10; //   "      "     "  12
        else
            kz = 12; //   "      "     "  14
        complex_t cp1 = 1.0;
        complex_t cq1 = 0.375;                 // division by z1 postponed to final sum
        const complex_t z1m2 = 1. / (z1 * z1); // faster than std::pow(z1, -2.0) ??
        complex_t ptmp = z1m2;                 // powers will be computed recursively
        for (size_t k = 0; k < kz; ++k) {
            cp1 += a1[k] * ptmp;
            cq1 += b1[k] * ptmp; // division by z1 postponed to final sum
            ptmp *= z1m2;
        }
        const complex_t ct2 = z1 - 0.75 * M_PI;
        cj1 = std::sqrt(M_2_PI / z1) * (cp1 * std::cos(ct2) - cq1 / z1 * std::sin(ct2));
    }
    if (std::real(z) < 0.0)
        cj1 = -cj1;
    return cj1;
}

} // namespace

//  ************************************************************************************************
//  Bessel functions
//  ************************************************************************************************

double Math::Bessel::J0(double x) {
    return gsl_sf_bessel_J0(x);
}

double Math::Bessel::J1(double x) {
    return gsl_sf_bessel_J1(x);
}

double Math::Bessel::J1c(double x) {
    return x == 0 ? 0.5 : gsl_sf_bessel_J1(x) / x;
}

double Math::Bessel::I0(double x) {
    return gsl_sf_bessel_I0(x);
}

complex_t Math::Bessel::J0(const complex_t z) {
    if (std::imag(z) == 0)
        return gsl_sf_bessel_J0(std::real(z));
    return J0_PowSer(z);
}

complex_t Math::Bessel::J1(const complex_t z) {
    if (std::imag(z) == 0)
        return gsl_sf_bessel_J1(std::real(z));
    return J1_PowSer(z);
}

complex_t Math::Bessel::J1c(const complex_t z) {
    if (std::imag(z) == 0) {
        double xv = std::real(z);
        return xv == 0 ? 0.5 : gsl_sf_bessel_J1(xv) / xv;
    }
    return z == 0. ? 0.5 : J1_PowSer(z) / z;
}
