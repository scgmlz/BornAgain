// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Utils/StringUtils.h
//! @brief     Defines a few helper functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "WinDllMacros.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

//! Utility functions to analyze or modify strings.

namespace StringUtils {

//! Returns true if text matches pattern with wildcards '*' and '?'.
BA_CORE_API_ bool matchesPattern(const std::string& text, const std::string& wildcardPattern);

BA_CORE_API_ std::string padRight(const std::string& name, int length);

//! Split string into vector of string using delimeter.
BA_CORE_API_ std::vector<std::string> split(const std::string& text, const std::string& delimeter);

//! Replaces all occurences of items from string text with delimiter
BA_CORE_API_ void replaceItemsFromString(
    std::string& text, const std::vector<std::string>& items, const std::string& replacement="");

//! Returns string obtain by joining vector elements
BA_CORE_API_ std::string join(const std::vector<std::string>& joinable, const std::string& joint);

//! Removes multiple occurences of given substring from a string and returns result.
BA_CORE_API_ std::string removeSubstring(const std::string& text, const std::string& substr);

//! Returns scientific string representing given value of any numeric type.
template <typename T> std::string scientific(const T value, int n = 10); // implementation below

} // namespace StringUtils

// ************************************************************************** //
// implementation
// ************************************************************************** //

template <typename T> std::string StringUtils::scientific(const T value, int n)
{
    std::ostringstream out;
    out << std::scientific << std::setprecision(n) << value;
    return out.str();
}

#endif // STRINGUTILS_H
