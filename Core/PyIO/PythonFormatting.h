// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/PyIO/PythonFormatting.h
//! @brief     Defines namespace pyfmt2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PYIO_PYTHONFORMATTING_H
#define BORNAGAIN_CORE_PYIO_PYTHONFORMATTING_H

#include "Wrap/WinDllMacros.h"
#include <functional>
#include <string>

class IDistribution1D;
class IParameterized;
class IShape2D;
class RealParameter;
class ParameterDistribution;
class IAxis;

//! Utility functions for writing Python code snippets.

namespace pyfmt2
{

BA_CORE_API_ std::string representShape2D(const std::string& indent, const IShape2D* ishape,
                                          bool mask_value,
                                          std::function<std::string(double)> printValueFunc);

BA_CORE_API_ std::string valueTimesUnit(const RealParameter* par);
BA_CORE_API_ std::string argumentList(const IParameterized* ip);

BA_CORE_API_ std::string printDistribution(const IDistribution1D& par_distr,
                                           const std::string& units = "");

BA_CORE_API_ std::string printParameterDistribution(const ParameterDistribution& par_distr,
                                                    const std::string& distVarName,
                                                    const std::string& units = "");

//! Prints python-script definition for given axis.
//! offset is used for alignment and indentation in multiple-line definitions
BA_CORE_API_ std::string printAxis(const IAxis& axis, const std::string& units, size_t offset);

} // namespace pyfmt2

#endif // BORNAGAIN_CORE_PYIO_PYTHONFORMATTING_H
