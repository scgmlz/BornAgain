// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/MinimizerUtils.h
//! @brief     Declares namespace MinimizerUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_TOOLS_MINIMIZERUTILS_H
#define BORNAGAIN_FIT_TOOLS_MINIMIZERUTILS_H

#include <map>
#include <string>
#include <vector>

//! Utility functions for fit library

namespace MinimizerUtils
{

std::string toString(const std::vector<std::string>& v, const std::string& delim = "");

std::map<int, std::string> gslErrorDescriptionMap();

std::string gslErrorDescription(int errorCode);

bool numbersDiffer(double a, double b, double tol);

std::string sectionString(const std::string& sectionName = "", size_t report_width = 80);

} // namespace MinimizerUtils

#endif // BORNAGAIN_FIT_TOOLS_MINIMIZERUTILS_H
