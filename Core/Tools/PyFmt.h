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
#include <string>

class RealLimits;

//! Utility functions for writing Python code snippets.

namespace pyfmt
{

std::string scriptPreamble();
std::string getSampleFunctionName();

std::string printInt(int value);
std::string printBool(double value);
std::string printDouble(double input);
std::string printNm(double input);
std::string printNm2(double input);
std::string printScientificDouble(double input);
std::string printDegrees(double input);
std::string printValue(double value, const std::string& units = "");
std::string printString(const std::string& value);

std::string printRealLimits(const RealLimits& limits, const std::string& units = "");
std::string printRealLimitsArg(const RealLimits& limits, const std::string& units = "");

bool isSquare(double length1, double length2, double angle);
bool isHexagonal(double length1, double length2, double angle);
std::string printKvector(const kvector_t value);
bool isDefaultDirection(const kvector_t direction);

//! Returns a string of blanks with given width. By default
//! the width equals standard offset in python files.
std::string indent(size_t width = 4u);

} // namespace pyfmt

#endif // BORNAGAIN_CORE_TOOLS_PYFMT_H
