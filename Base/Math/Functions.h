//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Math/Functions.h
//! @brief     Defines functions in namespace Math.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_BASE_MATH_FUNCTIONS_H
#define BORNAGAIN_BASE_MATH_FUNCTIONS_H

#include "Base/Types/Complex.h"
#include <vector>

//! Various mathematical functions.

namespace Math {

//  ************************************************************************************************
//  Various functions
//  ************************************************************************************************

double StandardNormal(double x);
double Gaussian(double x, double average, double std_dev);
double IntegratedGaussian(double x, double average, double std_dev);

//! cotangent function: \f$cot(x)\equiv1/tan(x)\f$
double cot(double x);

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

//  ************************************************************************************************
//  Random number generators
//  ************************************************************************************************

// double GenerateUniformRandom();
// double GenerateStandardNormalRandom();
// double GenerateNormalRandom(double average, double std_dev);
double GeneratePoissonRandom(double average);

} // Namespace Math

#endif // BORNAGAIN_BASE_MATH_FUNCTIONS_H
#endif // USER_API
