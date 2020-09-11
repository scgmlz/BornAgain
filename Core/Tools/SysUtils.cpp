// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/SysUtils.cpp
//! @brief     Implements various stuff in namespace Utils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Tools/SysUtils.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::string SysUtils::getCurrentDateAndTime()
{
    using clock = std::chrono::system_clock;

    std::stringstream output;
    std::time_t current_time = clock::to_time_t(clock::now());
    output << std::put_time(std::gmtime(&current_time), "%Y-%b-%d %T");
    return output.str();
}

//! enables exception throw in the case of NaN, Inf
void SysUtils::enableFloatingPointExceptions()
{
#ifdef DEBUG_FPE
#ifndef _WIN32
    std::cout << "SysUtils::EnableFloatingPointExceptions() -> "
                 "Enabling floating point exception debugging\n";
    feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW);
//    feenableexcept(-1);
#endif // _WIN32
#else
    std::cout << "SysUtils::EnableFloatingPointExceptions() -> "
                 "Can't enable floating point exceptions. Available in debug mode only.\n";
#endif
}

std::string SysUtils::getenv(const std::string& name)
{
    if (char* c = std::getenv(name.c_str()))
        return c;
    else
        return "";
}

bool SysUtils::isWindowsHost()
{
#ifdef _WIN32
    return true;
#else
    return false;
#endif
}
