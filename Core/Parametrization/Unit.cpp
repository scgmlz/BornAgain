// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Unit.cpp
//! @brief     Implements class Unit.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Unit.h"
#include <stdexcept>

void Unit::setUnit(const std::string& name)
{
    if (!(name == "" || name == "nm" || name == "rad"))
        throw std::runtime_error("Bug: call to Unit::Unit with unexpected name " + name);
    setName(name);
}
