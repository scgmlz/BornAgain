//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Math/Numeric.h
//! @brief     Defines constants and "almost equal" in namespace Numeric.
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
#ifndef BORNAGAIN_BASE_MATH_NUMERIC_H
#define BORNAGAIN_BASE_MATH_NUMERIC_H

#include <limits>

//! Floating-point approximations.

namespace Numeric {

double GetAbsoluteDifference(double a, double b);

double GetRelativeDifference(double a, double b);

double GetLogDifference(double a, double b);

} // namespace Numeric

#endif // BORNAGAIN_BASE_MATH_NUMERIC_H
#endif // USER_API
