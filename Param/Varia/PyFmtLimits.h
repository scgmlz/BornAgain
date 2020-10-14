// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Varia/PyFmtLimits.h
//! @brief     Defines functions in namespace pyfmt.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_PYFMTLIMITS_H
#define BORNAGAIN_CORE_PARAMETRIZATION_PYFMTLIMITS_H

#include <string>

class RealLimits;

//! Utility functions for writing Python code snippets.

namespace pyfmt
{
std::string printRealLimits(const RealLimits& limits, const std::string& units = "");
std::string printRealLimitsArg(const RealLimits& limits, const std::string& units = "");
} // namespace pyfmt

#endif // BORNAGAIN_CORE_PARAMETRIZATION_PYFMTLIMITS_H
