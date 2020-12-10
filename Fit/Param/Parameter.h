//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Param/Parameter.h
//! @brief     Defines class Parameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_FIT_PARAM_PARAMETER_H
#define BORNAGAIN_FIT_PARAM_PARAMETER_H

#include "Fit/Param/AttLimits.h"
#include <string>

namespace mumufit {

//! A fittable parameter with value, error, step, and limits.
//! @ingroup fitting

class Parameter {
public:
    Parameter();

    //! Fit parameter constructor.
    //! @param name: unique name of fit parameters
    //! @param value: starting value of fit parameter
    //! @param limits: fit parameter limits
    //! @param step: initial step of fit parameter during the minimization,
    //! will be calculated automatically, if zero.
    Parameter(const std::string& name, double value,
              const AttLimits& limits = AttLimits::limitless(), double step = 0.0);

    std::string name() const;

    double startValue() const;

    AttLimits limits() const;

    double value() const;
    void setValue(double value);

    double step() const;

    double error() const;
    void setError(double value);

private:
    std::string m_name;   //!< unique fit parameter name
    double m_start_value; //!< starting value of fit parameters
    double m_value;       //!< current value of fit parameters
    double m_step;        //!< approximate initial step for the minimizer
    double m_error;       //!< error of fit parameter calculated by the minimizer
    AttLimits m_limits;
};

} // namespace mumufit

#endif // BORNAGAIN_FIT_PARAM_PARAMETER_H
