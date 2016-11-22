// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/MathFunctions.cpp
//! @brief     Implements namespace MathFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MathFunctions.h"
#include "MathConstants.h"
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_sf_erf.h>
#include <gsl/gsl_sf_expint.h>
#include <gsl/gsl_sf_trig.h>
#include <fftw3.h>
#include <chrono>
#include <cstring>
#include <limits>
#include <random>
#include <stdexcept> // need overlooked by g++ 5.4

// ************************************************************************** //
//  Various functions
// ************************************************************************** //

double MathFunctions::StandardNormal(double x)
{
    return std::exp(-x * x / 2.0) / std::sqrt(M_TWOPI);
}

double MathFunctions::Gaussian(double x, double average, double std_dev)
{
    return StandardNormal((x - average) / std_dev) / std_dev;
}

double MathFunctions::IntegratedGaussian(double x, double average, double std_dev)
{
    double normalized_x = (x - average) / std_dev;
    static double root2 = std::sqrt(2.0);
    return (gsl_sf_erf(normalized_x / root2) + 1.0) / 2.0;
}

double MathFunctions::cot(double x)
{
    return tan(M_PI_2-x);
}

double MathFunctions::Si(double x)  // int_0^x du Sin(u)/u
{
    return gsl_sf_Si(x);
}

double MathFunctions::sinc(double x)  // Sin(x)/x
{
    return gsl_sf_sinc(x/M_PI);
}

complex_t MathFunctions::sinc(const complex_t z)  // Sin(x)/x
{
    // This is an exception from the rule that we must not test floating-point numbers for equality.
    // For small non-zero arguments, sin(z) returns quite accurately z or z-z^3/6.
    // There is no loss of precision in computing sin(z)/z.
    // Therefore there is no need for an expensive test like abs(z)<eps.
    if( z==complex_t(0.,0.) )
        return 1.0;
    return std::sin(z)/z;
}

complex_t MathFunctions::tanhc(const complex_t z)  // tanh(x)/x
{
    if(std::abs(z)<std::numeric_limits<double>::epsilon())
        return 1.0;
    return std::tanh(z)/z;
}

complex_t MathFunctions::Laue(const complex_t z, size_t N) // Exp(iNx/2)*Sin((N+1)x)/Sin(x)
{
    if (N==0)
        return 1.0;
    if(std::abs(z)<std::numeric_limits<double>::epsilon())
        return N+1.0;
    return exp_I(N/2.0*z)*std::sin(z*(N+1.0)/2.0)/std::sin(z/2.0);
}

// ************************************************************************** //
//  Bessel functions
// ************************************************************************** //

namespace MathFunctions
{
//! Computes complex Bessel function J0(z), using power series and asymptotic expansion
    BA_CORE_API_ complex_t Bessel_J0_PowSer(const complex_t z);

//! Computes complex Bessel function J0(z), using power series and asymptotic expansion
    BA_CORE_API_ complex_t Bessel_J1_PowSer(const complex_t z);
}

double MathFunctions::Bessel_J0(double x)
{
    return gsl_sf_bessel_J0(x);
}

double MathFunctions::Bessel_J1(double x)
{
    return gsl_sf_bessel_J1(x);
}

double MathFunctions::Bessel_J1c(double x)
{
    return x==0 ? 0.5 : gsl_sf_bessel_J1(x)/x;
}

complex_t MathFunctions::Bessel_J0(const complex_t z)
{
    if (std::imag(z)==0)
        return gsl_sf_bessel_J0(std::real(z));
    return Bessel_J0_PowSer(z);
}

complex_t MathFunctions::Bessel_J1(const complex_t z)
{
    if (std::imag(z)==0)
        return gsl_sf_bessel_J1(std::real(z));
    return Bessel_J1_PowSer(z);
}

complex_t MathFunctions::Bessel_J1c(const complex_t z)
{
    if (std::imag(z)==0) {
        double xv = std::real(z);
        return xv==0 ? 0.5 : gsl_sf_bessel_J1(xv)/xv;
    }
    return z==0. ? 0.5 : MathFunctions::Bessel_J1_PowSer(z)/z;
}

//! Computes the complex Bessel function J0(z), using power series and asymptotic expansion.
//!
//! Forked from unoptimized code at http://www.crbond.com/math.htm,
//! who refers to "Computation of Special Functions", Zhang and Jin, John Wiley and Sons, 1996.

complex_t MathFunctions::Bessel_J0_PowSer(const complex_t z)
{
    complex_t cj0;
    static const complex_t cone(1.0, 0.0);
    static const complex_t czero(0.0, 0.0);
    static const double eps = 1e-15;
    static double a[] = { -7.03125e-2,           0.112152099609375,     -0.5725014209747314,
                          6.074042001273483,     -1.100171402692467e2,  3.038090510922384e3,
                          -1.188384262567832e5,  6.252951493434797e6,   -4.259392165047669e8,
                          3.646840080706556e10,  -3.833534661393944e12, 4.854014686852901e14,
                          -7.286857349377656e16, 1.279721941975975e19 };
    static double b[] = { 7.32421875e-2,         -0.2271080017089844,  1.727727502584457,
                          -2.438052969955606e1,  5.513358961220206e2,  -1.825775547429318e4,
                          8.328593040162893e5,   -5.006958953198893e7, 3.836255180230433e9,
                          -3.649010818849833e11, 4.218971570284096e13, -5.827244631566907e15,
                          9.476288099260110e17,  -1.792162323051699e20 };

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
        const complex_t z1m2 = 1. / (z1*z1); // faster than std::pow(z1, -2.0) ??
        complex_t ptmp = z1m2;
        for (size_t k = 0; k < kz; ++k) {
            cp0 += a[k] * ptmp;
            cq0 += b[k] * ptmp;
            ptmp *= z1m2;
        }
        cj0 = std::sqrt(M_2_PI / z1) * (cp0 * std::cos(ct1) - cq0/z1 * std::sin(ct1));
    }
    return cj0;
}

//! Computes the complex Bessel function J1(z), using power series and asymptotic expansion.
//!
//! Forked from same source as for Bessel_J0_PowSer

complex_t MathFunctions::Bessel_J1_PowSer(const complex_t z)
{
    complex_t cj1;
    static const double eps = 1e-15;

    static double a1[] = { 0.1171875,             -0.1441955566406250,  0.6765925884246826,
                           -6.883914268109947,    1.215978918765359e2,  -3.302272294480852e3,
                           1.276412726461746e5,   -6.656367718817688e6, 4.502786003050393e8,
                           -3.833857520742790e10, 4.011838599133198e12, -5.060568503314727e14,
                           7.572616461117958e16,  -1.326257285320556e19 };
    static double b1[] = { -0.1025390625,         0.2775764465332031,    -1.993531733751297,
                           2.724882731126854e1,   -6.038440767050702e2,  1.971837591223663e4,
                           -8.902978767070678e5,  5.310411010968522e7,   -4.043620325107754e9,
                           3.827011346598605e11,  -4.406481417852278e13, 6.065091351222699e15,
                           -9.833883876590679e17, 1.855045211579828e20 };

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
        complex_t cq1 = 0.375; // division by z1 postponed to final sum
        const complex_t z1m2 = 1. / (z1*z1); // faster than std::pow(z1, -2.0) ??
        complex_t ptmp = z1m2; // powers will be computed recursively
        for (size_t k = 0; k < kz; ++k) {
            cp1 += a1[k] * ptmp;
            cq1 += b1[k] * ptmp; // division by z1 postponed to final sum
            ptmp *= z1m2;
        }
        const complex_t ct2 = z1 - 0.75 * M_PI;
        cj1 = std::sqrt(M_2_PI / z1) * (cp1 * std::cos(ct2) - cq1/z1 * std::sin(ct2));
    }
    if (std::real(z) < 0.0)
        cj1 = -cj1;
    return cj1;
}

// ************************************************************************** //
//  Fourier transform and convolution
// ************************************************************************** //

//! @brief simple (and unoptimized) wrapper function
//!   for the discrete fast Fourier transformation library (fftw3)

std::vector<complex_t>
MathFunctions::FastFourierTransform(const std::vector<complex_t> &data,
                                    MathFunctions::EFFTDirection ftCase)
{
    double scale(1.);
    size_t npx = data.size();

    fftw_complex *ftData = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * npx);
    fftw_complex *ftResult = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * npx);
    memset(ftData, 0, sizeof(fftw_complex) * npx);
    memset(ftResult, 0, sizeof(fftw_complex) * npx);

    for (size_t i = 0; i < npx; i++) {
        ftData[i][0] = data[i].real();
        ftData[i][1] = data[i].imag();
    }

    fftw_plan plan;
    switch (ftCase) {
    case MathFunctions::FORWARD_FFT:
        plan = fftw_plan_dft_1d((int)npx, ftData, ftResult, FFTW_FORWARD, FFTW_ESTIMATE);
        break;
    case MathFunctions::BACKWARD_FFT:
        plan = fftw_plan_dft_1d((int)npx, ftData, ftResult, FFTW_BACKWARD, FFTW_ESTIMATE);
        scale = 1. / double(npx);
        break;
    default:
        throw std::runtime_error(
            "MathFunctions::FastFourierTransform -> Panic! Unknown transform case.");
    }

    fftw_execute(plan);

    // saving data for user
    std::vector<complex_t> outData;
    outData.resize(npx);
    for (size_t i = 0; i < npx; i++)
        outData[i] = scale * complex_t(ftResult[i][0], ftResult[i][1]);

    fftw_destroy_plan(plan);
    fftw_free(ftData);
    fftw_free(ftResult);

    return outData;
}

//! @brief simple (and unoptimized) wrapper function
//!   for the discrete fast Fourier transformation library (fftw3);
//!   transforms real to complex

std::vector<complex_t> MathFunctions::FastFourierTransform(
    const std::vector<double> &data, MathFunctions::EFFTDirection ftCase)
{
    std::vector<complex_t> cdata;
    cdata.resize(data.size());
    for (size_t i = 0; i < data.size(); i++)
        cdata[i] = complex_t(data[i], 0);
    return MathFunctions::FastFourierTransform(cdata, ftCase);
}

//! convolution of two real vectors of equal size

std::vector<complex_t>
MathFunctions::ConvolveFFT(const std::vector<double> &signal,
                           const std::vector<double> &resfunc)
{
    if (signal.size() != resfunc.size())
        throw std::runtime_error("MathFunctions::ConvolveFFT() -> This convolution works only for "
                                 "two vectors of equal size. Use Convolve class instead.");
    std::vector<complex_t> fft_signal
        = MathFunctions::FastFourierTransform(signal, MathFunctions::FORWARD_FFT);
    std::vector<complex_t> fft_resfunc
        = MathFunctions::FastFourierTransform(resfunc, MathFunctions::FORWARD_FFT);

    std::vector<complex_t> fft_prod;
    fft_prod.resize(fft_signal.size());
    for (size_t i = 0; i < fft_signal.size(); i++)
        fft_prod[i] = fft_signal[i] * fft_resfunc[i];

    std::vector<complex_t> result
        = MathFunctions::FastFourierTransform(fft_prod, MathFunctions::BACKWARD_FFT);
    return result;
}


// ************************************************************************** //
//  Random number generators
// ************************************************************************** //

double MathFunctions::GenerateUniformRandom()
{
    int random_int = std::rand();
    return (double)random_int / RAND_MAX;
}

double MathFunctions::GenerateNormalRandom(double average, double std_dev)
{
    return GenerateStandardNormalRandom()*std_dev + average;
}

double MathFunctions::GenerateStandardNormalRandom() // using c++11 standard library
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}
