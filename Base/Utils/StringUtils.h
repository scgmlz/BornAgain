//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Utils/StringUtils.h
//! @brief     Defines a few helper functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_BASE_UTILS_STRINGUTILS_H
#define BORNAGAIN_BASE_UTILS_STRINGUTILS_H

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

//! Utility functions to analyze or modify strings.

namespace StringUtils {

//! Returns true if text matches pattern with wildcards '*' and '?'.
bool matchesPattern(const std::string& text, const std::string& wildcardPattern);

std::string padRight(const std::string& name, size_t length);

//! Split string into vector of string using delimeter.
std::vector<std::string> split(const std::string& text, const std::string& delimeter);

//! Replaces all occurrences of items from string text with delimiter
void replaceItemsFromString(std::string& text, const std::vector<std::string>& items,
                            const std::string& replacement = "");

//! Returns string obtain by joining vector elements
std::string join(const std::vector<std::string>& joinable, const std::string& joint);

//! Removes multiple occurrences of given substring from a string and returns result.
std::string removeSubstring(const std::string& text, const std::string& substr);

//! Returns scientific string representing given value of any numeric type.
template <typename T> std::string scientific(const T value, int n = 10);

//! Returns new string which is lower case of text.
std::string to_lower(std::string text);

//! Cuts any of the chars given in whitespace from start and end of str.
std::string trim(const std::string& str, const std::string& whitespace = " \t");

} // namespace StringUtils

template <typename T> std::string StringUtils::scientific(const T value, int n) {
    std::ostringstream out;
    out << std::scientific << std::setprecision(n) << value;
    return out.str();
}

#endif // BORNAGAIN_BASE_UTILS_STRINGUTILS_H
#endif // USER_API
