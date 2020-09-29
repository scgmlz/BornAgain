// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterUtils.h
//! @brief     Defines namespace ParameterUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERUTILS_H
#define BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERUTILS_H

#include <string>

class IParameterized;

namespace ParameterUtils
{

//! Returns true if given parameter name is related to angles.
bool isAngleRelated(const std::string& par_name);

//! Returns units of main parameter.
std::string poolParameterUnits(const IParameterized& node, const std::string& parName);

} // namespace ParameterUtils

#endif // BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERUTILS_H
