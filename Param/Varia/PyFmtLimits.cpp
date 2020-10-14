// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Varia/PyFmtLimits.cpp
//! @brief     Implements functions from namespace pyfmt.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Param/Varia/PyFmtLimits.h"
#include "Base/Utils/PyFmt.h"
#include "Fit/Tools/RealLimits.h"
#include <iomanip>

namespace pyfmt
{

std::string printRealLimits(const RealLimits& limits, const std::string& units)
{
    std::ostringstream result;

    if (limits.isLimitless()) {
        result << "RealLimits()";
    }

    else if (limits.isPositive()) {
        result << "RealLimits.positive()";
    }

    else if (limits.isNonnegative()) {
        result << "RealLimits.nonnegative()";
    }

    else if (limits.isLowerLimited()) {
        result << "RealLimits.lowerLimited(" << pyfmt::printValue(limits.lowerLimit(), units)
               << ")";
    }

    else if (limits.isUpperLimited()) {
        result << "RealLimits.upperLimited(" << pyfmt::printValue(limits.upperLimit(), units)
               << ")";
    }

    else if (limits.isLimited()) {
        result << "RealLimits.limited(" << pyfmt::printValue(limits.lowerLimit(), units) << ", "
               << pyfmt::printValue(limits.upperLimit(), units) << ")";
    }

    return result.str();
}

//! Prints RealLimits in the form of argument (in the context of ParameterDistribution and
//! similar). Default RealLimits will not be printed, any other will be printed as
//! ", ba.RealLimits.limited(1*deg, 2*deg)"

std::string printRealLimitsArg(const RealLimits& limits, const std::string& units)
{
    return limits.isLimitless() ? "" : ", ba." + printRealLimits(limits, units);
}

} // namespace pyfmt
