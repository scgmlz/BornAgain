// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/MathFunctions.h
//! @brief     Defines namespace MathFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_TOOLS_MATHFUNCTIONS_H
#define BORNAGAIN_CORE_TOOLS_MATHFUNCTIONS_H

#include "Core/Basics/Complex.h"
#include <vector>

//! Various mathematical functions.

namespace MathFunctions
{

// ************************************************************************** //
//  Various functions
// ************************************************************************** //

double StandardNormal(double x);
double Gaussian(double x, double average, double std_dev);
double IntegratedGaussian(double x, double average, double std_dev);

//! cotangent function: \f$cot(x)\equiv1/tan(x)\f$
double cot(double x);

//! Sine integral function: \f$Si(x)\equiv\int_0^x du \sin(u)/u\f$
double Si(double x);

//! sinc function: \f$sinc(x)\equiv\sin(x)/x\f$
double sinc(double x);

//! Complex sinc function: \f$sinc(x)\equiv\sin(x)/x\f$
complex_t sinc(const complex_t z);

//! Complex tanhc function: \f$tanhc(x)\equiv\tanh(x)/x\f$
complex_t tanhc(const complex_t z);

//! Real Laue function: \f$Laue(x,N)\equiv\sin(Nx)/sin(x)\f$
double Laue(const double x, size_t N);

//! Error function of real-valued argument
double erf(double arg);

// ************************************************************************** //
//  Bessel functions
// ************************************************************************** //

//! Bessel function of the first kind and order 0
double Bessel_J0(double x);

//! Bessel function of the first kind and order 1
double Bessel_J1(double x);

//! Bessel function  Bessel_J1(x)/x
double Bessel_J1c(double x);

//! Modified Bessel function of the first kind and order 0
double Bessel_I0(double x);

//! Complex Bessel function of the first kind and order 0
complex_t Bessel_J0(const complex_t z);

//! Complex Bessel function of the first kind and order 1
complex_t Bessel_J1(const complex_t z);

//! Complex Bessel function  Bessel_J1(x)/x
complex_t Bessel_J1c(const complex_t z);

// ************************************************************************** //
//  Fourier transform and convolution
// ************************************************************************** //

// TODO move elsewhere, and rm #include <vector>

enum EFFTDirection { FORWARD_FFT, BACKWARD_FFT };

// TODO: name these two functions differently (SWIG warning 509)
std::vector<complex_t> FastFourierTransform(const std::vector<complex_t>& data,
                                            EFFTDirection tcase);
std::vector<complex_t> FastFourierTransform(const std::vector<double>& data, EFFTDirection tcase);

std::vector<complex_t> ConvolveFFT(const std::vector<double>& signal,
                                   const std::vector<double>& resfunc);

// ************************************************************************** //
//  Random number generators
// ************************************************************************** //

double GenerateUniformRandom();
double GenerateStandardNormalRandom();
double GenerateNormalRandom(double average, double std_dev);
double GeneratePoissonRandom(double average);

} // Namespace MathFunctions

#endif // BORNAGAIN_CORE_TOOLS_MATHFUNCTIONS_H
