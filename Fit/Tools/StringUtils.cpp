//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/StringUtils.cpp
//! @brief     Implements a few helper functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Fit/Tools/StringUtils.h"
#include <boost/algorithm/string.hpp>
#include <regex>

namespace mumufit {

//! Returns true if text matches pattern with wildcards '*' and '?'.
bool stringUtils::matchesPattern(const std::string& text, const std::string& wildcardPattern) {
    // escape all regex special characters, except '?' and '*'
    std::string mywildcardPattern = wildcardPattern;
    boost::replace_all(mywildcardPattern, "\\", "\\\\");
    boost::replace_all(mywildcardPattern, "^", "\\^");
    boost::replace_all(mywildcardPattern, ".", "\\.");
    boost::replace_all(mywildcardPattern, "$", "\\$");
    boost::replace_all(mywildcardPattern, "|", "\\|");
    boost::replace_all(mywildcardPattern, "(", "\\(");
    boost::replace_all(mywildcardPattern, ")", "\\)");
    boost::replace_all(mywildcardPattern, "[", "\\[");
    boost::replace_all(mywildcardPattern, "]", "\\]");
    boost::replace_all(mywildcardPattern, "+", "\\+");
    boost::replace_all(mywildcardPattern, "/", "\\/");

    // Convert chars '*?' to their regex equivalents
    boost::replace_all(mywildcardPattern, "?", ".");
    boost::replace_all(mywildcardPattern, "*", ".*");

    // constructing regexp pattern
    mywildcardPattern = "^" + mywildcardPattern + "$";
    std::regex pattern(mywildcardPattern);

    // applaying match
    return std::regex_match(text, pattern);
}

//! Returns token vector obtained by splitting string at delimiters.
std::vector<std::string> stringUtils::split(const std::string& text, const std::string& delimiter) {
    std::vector<std::string> tokens;
    boost::split(tokens, text, boost::is_any_of(delimiter));
    return tokens;
}

} // namespace mumufit
