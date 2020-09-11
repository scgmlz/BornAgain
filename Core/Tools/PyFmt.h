// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/PyFmt.h
//! @brief     Defines namespace pyfmt.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_TOOLS_PYFMT_H
#define BORNAGAIN_CORE_TOOLS_PYFMT_H

#include "Core/Vector/Vectors3D.h"
#include "Wrap/WinDllMacros.h"
#include <string>

class RealLimits;

//! Utility functions for writing Python code snippets.

namespace pyfmt
{

BA_CORE_API_ std::string scriptPreamble();
BA_CORE_API_ std::string getSampleFunctionName();

BA_CORE_API_ std::string printInt(int value);
BA_CORE_API_ std::string printBool(double value);
BA_CORE_API_ std::string printDouble(double input);
BA_CORE_API_ std::string printNm(double input);
BA_CORE_API_ std::string printNm2(double input);
BA_CORE_API_ std::string printScientificDouble(double input);
BA_CORE_API_ std::string printDegrees(double input);
BA_CORE_API_ std::string printValue(double value, const std::string& units = "");
BA_CORE_API_ std::string printString(const std::string& value);

BA_CORE_API_ std::string printRealLimits(const RealLimits& limits, const std::string& units = "");
BA_CORE_API_ std::string printRealLimitsArg(const RealLimits& limits,
                                            const std::string& units = "");

BA_CORE_API_ bool isSquare(double length1, double length2, double angle);
BA_CORE_API_ bool isHexagonal(double length1, double length2, double angle);
BA_CORE_API_ std::string printKvector(const kvector_t value);
BA_CORE_API_ bool isDefaultDirection(const kvector_t direction);

//! Returns a string of blanks with given width. By default
//! the width equals standard offset in python files.
BA_CORE_API_ std::string indent(size_t width = 4u);

} // namespace pyfmt

#endif // BORNAGAIN_CORE_TOOLS_PYFMT_H
