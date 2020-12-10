//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Base/Unit.h
//! @brief     Defines class Unit.
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
#ifndef BORNAGAIN_PARAM_BASE_UNIT_H
#define BORNAGAIN_PARAM_BASE_UNIT_H

#include <string>

//! A physical unit.

class Unit {
public:
    explicit Unit(const std::string& name = "") : m_name(name) {}
    void setUnit(const std::string& name) { m_name = name; }
    const std::string& getName() const { return m_name; }

private:
    std::string m_name;
};

#endif // BORNAGAIN_PARAM_BASE_UNIT_H
#endif // USER_API
