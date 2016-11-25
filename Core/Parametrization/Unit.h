// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/Unit.h
//! @brief     Defines class Unit.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef UNIT_H
#define UNIT_H

#include "INamed.h"
#include <string>

//! A physical unit.

class Unit : public INamed
{
public:
    Unit(const std::string& name = "") { setUnit(name); }
    void setUnit(const std::string& name);
};

#endif // UNIT_H
