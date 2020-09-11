// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/TestEngine/Numeric.h
//! @brief     Defines constants and "almost equal" in namespace Numeric.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_TESTENGINE_NUMERIC_H
#define BORNAGAIN_FIT_TESTENGINE_NUMERIC_H

#include "Wrap/WinDllMacros.h"
#include <limits>

//! Floating-point epsilon, tolerances, almost-equal.

namespace Numeric
{

bool BA_CORE_API_ AreAlmostEqual(double a, double b, double tolerance_factor = 1.0);

double BA_CORE_API_ GetAbsoluteDifference(double a, double b);

double BA_CORE_API_ GetRelativeDifference(double a, double b);

double BA_CORE_API_ GetLogDifference(double a, double b);

} // namespace Numeric

#endif // BORNAGAIN_FIT_TESTENGINE_NUMERIC_H
