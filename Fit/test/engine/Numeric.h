// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/engine/Numeric.h
//! @brief     Defines constants and "almost equal" in namespace Numeric.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef NUMERIC_H
#define NUMERIC_H

#include "WinDllMacros.h"
#include <limits>

//! Floating-point epsilon, tolerances, almost-equal.

namespace Numeric
{

bool BA_CORE_API_ AreAlmostEqual(double a, double b, double tolerance_factor = 1.0);

double BA_CORE_API_ GetAbsoluteDifference(double a, double b);

double BA_CORE_API_ GetRelativeDifference(double a, double b);

double BA_CORE_API_ GetLogDifference(double a, double b);

} // namespace Numeric

#endif // NUMERIC_H
