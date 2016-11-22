// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Utils/StringUtils.cpp
//! @brief     Implements a few helper functions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StringUtils.h"
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

//! Returns true if text matches pattern with wildcards '*' and '?'.
bool StringUtils::matchesPattern(const std::string& text, const std::string& wildcardPattern)
{
    bool caseSensitive(true);

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
    boost::regex pattern(mywildcardPattern,
                         caseSensitive ? boost::regex::normal : boost::regex::icase);

    // applaying match
    return boost::regex_match(text, pattern);
}

//! Returns string right-padded with blanks.
std::string StringUtils::padRight(const std::string& name, int length)
{
    std::string result = name;
    result.resize(length,' ');
    return result;
}

//! Returns token vector obtained by splitting string at delimiters.
std::vector<std::string> StringUtils::split(const std::string& text, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    boost::split(tokens, text, boost::is_any_of(delimiter));
    return tokens;
}

void StringUtils::replaceItemsFromString(
    std::string& text, const std::vector<std::string>& items, const std::string& replacement)
{
    for(size_t i=0; i<items.size(); ++i)
        boost::replace_all(text, items[i], replacement);
}

std::string StringUtils::join(const std::vector<std::string>& joinable, const std::string& joint)
{
    std::string result;
    size_t n = joinable.size();
    for(size_t i=0; i<n-1; ++i)
        result += joinable[i] + joint;
    result += joinable[n-1];
    return result;
}

std::string StringUtils::removeSubstring(const std::string &text, const std::string &substr)
{
    std::string result = text;
    for(std::string::size_type i=result.find(substr); i!=std::string::npos; i=result.find(substr))
        result.erase(i, substr.length());
    return result;
}
