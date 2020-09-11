// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/TestEngine/Numeric.cpp
//! @brief     Implements "almost equal" in namespace Numeric.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/TestEngine/Numeric.h"
#include <algorithm>
#include <cmath>
#include <limits>

//! Floating-point epsilon, tolerances, almost-equal.

namespace Numeric
{

//! Returns true if two doubles agree within epsilon*tolerance.
bool AreAlmostEqual(double a, double b, double tolerance)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    return std::abs(a - b)
           <= eps * std::max(tolerance * eps, std::max(1., tolerance) * std::abs(b));
}

//! Returns the absolute value of the difference between a and b.
double GetAbsoluteDifference(double a, double b)
{
    return std::abs(a - b);
}

//! Returns the safe relative difference, which is 2(|a-b|)/(|a|+|b|) except in special cases.
double GetRelativeDifference(double a, double b)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    const double avg_abs = (std::abs(a) + std::abs(b)) / 2.0;
    // return 0.0 if relative error smaller than epsilon
    if (std::abs(a - b) <= eps * avg_abs)
        return 0.0;
    return std::abs(a - b) / avg_abs;
}

//! Returns the difference of the logarithm; input values are truncated at the minimum positive
//! value
double GetLogDifference(double a, double b)
{
    double a_t = std::max(a, std::numeric_limits<double>::min());
    double b_t = std::max(b, std::numeric_limits<double>::min());
    return std::abs(std::log(a_t) - std::log(b_t));
}

} // namespace Numeric
