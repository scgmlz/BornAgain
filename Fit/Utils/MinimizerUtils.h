// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Utils/MinimizerUtils.h
//! @brief     Declares namespace MinimizerUtils.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef  MINIMIZERUTILS_H
#define  MINIMIZERUTILS_H

#include "WinDllMacros.h"
#include <string>
#include <vector>
#include <map>

//! Utility functions for fit library

namespace MinimizerUtils {

BA_CORE_API_ std::string toString(const std::vector<std::string>& v, const std::string& delim="");

BA_CORE_API_ std::map<int, std::string> gslErrorDescriptionMap();

BA_CORE_API_ std::string gslErrorDescription(int errorCode);

BA_CORE_API_ bool numbersDiffer(double a, double b, double tol);

BA_CORE_API_ std::string sectionString(const std::string& sectionName="", int report_width=80);

} // namespace MinimizerUtils

#endif
