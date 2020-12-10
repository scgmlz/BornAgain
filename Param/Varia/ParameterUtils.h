//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Varia/ParameterUtils.h
//! @brief     Defines namespace ParameterUtils
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
#ifndef BORNAGAIN_PARAM_VARIA_PARAMETERUTILS_H
#define BORNAGAIN_PARAM_VARIA_PARAMETERUTILS_H

#include <string>

class IParametricComponent;

namespace ParameterUtils {

//! Returns true if given parameter name is related to angles.
bool isAngleRelated(const std::string& par_name);

//! Returns units of main parameter.
std::string poolParameterUnits(const IParametricComponent& node, const std::string& parName);

} // namespace ParameterUtils

#endif // BORNAGAIN_PARAM_VARIA_PARAMETERUTILS_H
#endif // USER_API
