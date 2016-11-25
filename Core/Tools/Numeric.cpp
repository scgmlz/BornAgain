// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Numeric.cpp
//! @brief     Implements "almost equal" in namespace Numeric.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Numeric.h"
#include <algorithm>
#include <cmath>
#include <limits>

//! Floating-point epsilon, tolerances, almost-equal.

namespace Numeric
{

//! Returns true if two doubles agree within epsilon*tolerance.
bool areAlmostEqual(double a, double b, double tolerance)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    return std::abs(a - b)
        <= eps * std::max(tolerance * eps, std::max(1., tolerance) * std::abs(b));
}

//! Returns the safe relative difference, which is |(a-b)/b| except in special cases.
double get_relative_difference(double a, double b)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    // return 0.0 if relative error smaller than epsilon
    if (std::abs(a - b) <= eps * std::abs(b))
        return 0.0;
    // for small numbers, divide by epsilon (to avoid catastrophic cancellation)
    if (std::abs(b) <= eps)
        return std::abs((a - b) / eps);
    return std::abs((a - b) / b);
}

} // Numeric namespace
