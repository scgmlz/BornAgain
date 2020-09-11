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

#include "Wrap/WinDllMacros.h"
#include <string>

//! Utility functions getCurrentDateAndTime, enableFloatingPointExceptions.

namespace SysUtils
{

BA_CORE_API_ std::string getCurrentDateAndTime();

//! Enables exception throw in the case of NaN, Inf.
BA_CORE_API_ void enableFloatingPointExceptions();

//! Returns environment variable.
BA_CORE_API_ std::string getenv(const std::string& name);

//! Returns true if operation system is Windows.
BA_CORE_API_ bool isWindowsHost();

} // namespace SysUtils

#endif // BORNAGAIN_CORE_TOOLS_SYSUTILS_H
