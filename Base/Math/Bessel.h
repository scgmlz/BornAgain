//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Math/Bessel.h
//! @brief     Defines Bessel functions in namespace Math.
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
#ifndef BORNAGAIN_BASE_MATH_BESSEL_H
#define BORNAGAIN_BASE_MATH_BESSEL_H

#include "Base/Types/Complex.h"
#include <vector>

namespace Math {

//! Real and complex Bessel functions
namespace Bessel {

//! Bessel function of the first kind and order 0
double J0(double x);

//! Bessel function of the first kind and order 1
double J1(double x);

//! Bessel function  J1(x)/x
double J1c(double x);

//! Modified Bessel function of the first kind and order 0
double I0(double x);

//! Complex Bessel function of the first kind and order 0
complex_t J0(const complex_t z);

//! Complex Bessel function of the first kind and order 1
complex_t J1(const complex_t z);

//! Complex Bessel function  J1(x)/x
complex_t J1c(const complex_t z);

} // namespace Bessel
} // namespace Math

#endif // BORNAGAIN_BASE_MATH_BESSEL_H
#endif // USER_API
