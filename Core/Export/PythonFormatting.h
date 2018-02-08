// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/PythonFormatting.h
//! @brief     Defines PythonFormatting namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PYTHONFORMATTING_H
#define PYTHONFORMATTING_H

#include "Vectors3D.h"
#include <functional>
#include <string>

class IDistribution1D;
class IParameterized;
class IShape2D;
class RealParameter;
class ParameterDistribution;
class RealLimits;
class IAxis;

//! Utility functions for writing Python code snippets.

namespace PythonFormatting
{

BA_CORE_API_ std::string scriptPreamble();
BA_CORE_API_ std::string getSampleFunctionName();

BA_CORE_API_ std::string representShape2D(const std::string& indent, const IShape2D* ishape,
                                          bool mask_value,
                                          std::function<std::string(double)> printValueFunc);

BA_CORE_API_ std::string printInt(int value);
BA_CORE_API_ std::string printBool(double value);
BA_CORE_API_ std::string printDouble(double input);
BA_CORE_API_ std::string printNm(double input);
BA_CORE_API_ std::string printScientificDouble(double input);
BA_CORE_API_ std::string printDegrees(double input);
BA_CORE_API_ std::string printValue(double value, const std::string& units = "");
BA_CORE_API_ std::string printString(const std::string& value);

BA_CORE_API_ bool isSquare(double length1, double length2, double angle);
BA_CORE_API_ bool isHexagonal(double length1, double length2, double angle);
BA_CORE_API_ std::string printKvector(const kvector_t value);
BA_CORE_API_ bool isDefaultDirection(const kvector_t direction);
BA_CORE_API_ std::string valueTimesUnit(const RealParameter* par);
BA_CORE_API_ std::string argumentList(const IParameterized* ip);

BA_CORE_API_ std::string printDistribution(const IDistribution1D& par_distr,
                                           const std::string& units = "");

BA_CORE_API_ std::string printRealLimits(const RealLimits& limits, const std::string& units = "");
BA_CORE_API_ std::string printRealLimitsArg(const RealLimits& limits,
                                            const std::string& units = "");

BA_CORE_API_ std::string printParameterDistribution(const ParameterDistribution& par_distr,
                                                    const std::string& distVarName,
                                                    const std::string& units = "");

BA_CORE_API_ std::string printAxis(const IAxis& axis, const std::string& units = "");
}

#endif // PYTHONFORMATTING_H
