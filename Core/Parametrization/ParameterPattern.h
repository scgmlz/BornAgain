// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPattern.h
//! @brief     Defines class ParameterPattern
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERPATTERN_H
#define BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERPATTERN_H

#include "Wrap/WinDllMacros.h"
#include <string>

//! Helper class for constructing parameter patterns.
//! @ingroup tools_internal

class BA_CORE_API_ ParameterPattern
{
public:
    ParameterPattern() {}
    ParameterPattern(std::string root_object) : m_pattern("/" + root_object) {}

    ParameterPattern& beginsWith(std::string start_type);
    ParameterPattern& add(std::string object_type);

    std::string toStdString() const { return m_pattern; }

private:
    std::string m_pattern;
};

#endif // BORNAGAIN_CORE_PARAMETRIZATION_PARAMETERPATTERN_H
