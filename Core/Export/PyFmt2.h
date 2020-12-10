//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/PyFmt2.h
//! @brief     Defines namespace pyfmt2.
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
#ifndef BORNAGAIN_CORE_EXPORT_PYFMT2_H
#define BORNAGAIN_CORE_EXPORT_PYFMT2_H

#include <functional>
#include <string>

class IAxis;
class IDistribution1D;
class IParametricComponent;
class IShape2D;
class ParameterDistribution;
class IRangedDistribution;
class RealParameter;

//! Utility functions for writing Python code snippets.

namespace pyfmt2 {

std::string representShape2D(const std::string& indent, const IShape2D* ishape, bool mask_value,
                             std::function<std::string(double)> printValueFunc);

std::string valueTimesUnit(const RealParameter* par);
std::string argumentList(const IParametricComponent* ip);

std::string printAxis(const IAxis* axis, const std::string& unit);

std::string printDistribution(const IDistribution1D& par_distr, const std::string& units = "");

std::string printParameterDistribution(const ParameterDistribution& par_distr,
                                       const std::string& distVarName,
                                       const std::string& units = "");

std::string printRangedDistribution(const IRangedDistribution& distr);

} // namespace pyfmt2

#endif // BORNAGAIN_CORE_EXPORT_PYFMT2_H
#endif // USER_API
