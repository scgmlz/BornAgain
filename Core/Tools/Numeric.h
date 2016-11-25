// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/Numeric.h
//! @brief     Defines constants and "almost equal" in namespace Numeric.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef NUMERIC_H
#define NUMERIC_H

#include "WinDllMacros.h"
#include <limits>

//! Floating-point epsilon, tolerances, almost-equal.

namespace Numeric
{

bool BA_CORE_API_ areAlmostEqual(double a, double b, double tolerance_factor = 1.0);

double BA_CORE_API_ get_relative_difference(double a, double b);

} // Numeric namespace

#endif // NUMERIC_H
