// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/ParameterPlan.h
//! @brief     Defines class ParameterPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PARAMETERPLAN_H
#define PARAMETERPLAN_H

#include "WinDllMacros.h"
#include "Parameter.h"

//! Defines initial settings of single fit parameter and the final value which has to be found
//! in the course of the fit.

class BA_CORE_API_ ParameterPlan
{
public:
    ParameterPlan(const Fit::Parameter& param, double expected_value, double tolerance = 0.01);

    Fit::Parameter fitParameter() const;

    double expectedValue() const { return m_expected_value; }

    double tolerance() const { return m_tolerance; }
    void setTolerance(double tolerance) { m_tolerance = tolerance; }

private:
    double m_expected_value;    //!< expected value to find in the fit
    double m_tolerance;         //!< tolerance on found value wrt expected value
    Fit::Parameter m_parameter; //!< initial parameter settings
};

#endif // PARAMETERPLAN_H
