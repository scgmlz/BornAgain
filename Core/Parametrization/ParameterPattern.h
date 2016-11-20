// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPattern.h
//! @brief     Defines class ParameterPattern
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERPATTERN_H
#define PARAMETERPATTERN_H

#include "WinDllMacros.h"
#include <string>

//! Helper class for constructing parameter patterns.
//! @ingroup tools_internal

class BA_CORE_API_ ParameterPattern
{
public:
    ParameterPattern() {}
    ParameterPattern(std::string root_object) : m_pattern ( "/" + root_object ) {}

    ParameterPattern& beginsWith(std::string start_type);
    ParameterPattern& add(std::string object_type);

    std::string toStdString() const { return m_pattern; }

private:
    std::string m_pattern;
};

#endif // PARAMETERPATTERN_H
