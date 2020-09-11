// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPattern.cpp
//! @brief     Implements class ParameterPattern
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Parametrization/ParameterPattern.h"

ParameterPattern& ParameterPattern::beginsWith(std::string start_type)
{
    m_pattern = start_type;
    return *this;
}

ParameterPattern& ParameterPattern::add(std::string object_type)
{
    m_pattern = m_pattern + "/" + object_type;
    return *this;
}
