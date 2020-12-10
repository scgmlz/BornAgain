//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Varia/ParameterPattern.h
//! @brief     Defines class ParameterPattern
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
#ifndef BORNAGAIN_PARAM_VARIA_PARAMETERPATTERN_H
#define BORNAGAIN_PARAM_VARIA_PARAMETERPATTERN_H

#include <string>

//! Helper class for constructing parameter patterns.
//! @ingroup tools_internal

class ParameterPattern {
public:
    ParameterPattern() {}
    ParameterPattern(std::string root_object) : m_pattern("/" + root_object) {}

    ParameterPattern& beginsWith(std::string start_type);
    ParameterPattern& add(std::string object_type);

    std::string toStdString() const { return m_pattern; }

private:
    std::string m_pattern;
};

#endif // BORNAGAIN_PARAM_VARIA_PARAMETERPATTERN_H
#endif // USER_API
