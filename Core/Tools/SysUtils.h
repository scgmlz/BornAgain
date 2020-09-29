// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/SysUtils.h
//! @brief     Defines various stuff in namespace Utils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_TOOLS_SYSUTILS_H
#define BORNAGAIN_CORE_TOOLS_SYSUTILS_H

#include <string>

//! Utility functions getCurrentDateAndTime, enableFloatingPointExceptions.

namespace SysUtils
{

std::string getCurrentDateAndTime();

//! Enables exception throw in the case of NaN, Inf.
void enableFloatingPointExceptions();

//! Returns environment variable.
std::string getenv(const std::string& name);

//! Returns true if operation system is Windows.
bool isWindowsHost();

} // namespace SysUtils

#endif // BORNAGAIN_CORE_TOOLS_SYSUTILS_H
