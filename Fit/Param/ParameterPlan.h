//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Param/ParameterPlan.h
//! @brief     Defines class ParameterPlan
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
#ifndef BORNAGAIN_FIT_PARAM_PARAMETERPLAN_H
#define BORNAGAIN_FIT_PARAM_PARAMETERPLAN_H

#include "Fit/Param/Parameter.h"

//! Defines initial settings of single fit parameter and the final value which has to be found
//! in the course of the fit.

class ParameterPlan {
public:
    ParameterPlan(const mumufit::Parameter& param, double expected_value, double tolerance = 0.01)
        : m_expected_value(expected_value), m_tolerance(tolerance), m_parameter(param) {}

    mumufit::Parameter fitParameter() const { return m_parameter; }
    double expectedValue() const { return m_expected_value; }
    double tolerance() const { return m_tolerance; }

    void setTolerance(double tolerance) { m_tolerance = tolerance; }

private:
    double m_expected_value;        //!< expected value to find in the fit
    double m_tolerance;             //!< tolerance on found value wrt expected value
    mumufit::Parameter m_parameter; //!< initial parameter settings
};

#endif // BORNAGAIN_FIT_PARAM_PARAMETERPLAN_H
#endif // USER_API
