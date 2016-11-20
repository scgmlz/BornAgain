// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/FitParameter.h
//! @brief     Defines class FitParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITPARAMETER_H
#define FITPARAMETER_H

#include "IFitParameter.h"
#include "AttLimits.h"
#include <string>

//! A fittable parameter with value, error, step, and limits.
//! @ingroup fitting

class BA_CORE_API_ FitParameter : public IFitParameter
{
public:
    FitParameter();
    FitParameter(const std::string& name, double value,
                 const AttLimits& limits=AttLimits::limitless(), double step=0.0);
    virtual ~FitParameter(){}

    FitParameter* clone() const;

    std::string name() const;

    double startValue() const;

    double value() const;
    virtual void setValue(double value);

    double step() const;
    FitParameter& setStep(double value);

    double error() const;
    void setError(double value);

    const AttLimits& limits() const;
    AttLimits& limits();

    FitParameter& setLimits(const AttLimits& limits);

    FitParameter& setLowerLimited(double bound_value);
    FitParameter& setPositive();
    FitParameter& setNonnegative();
    FitParameter& setUpperLimited(double bound_value);
    FitParameter& setLimited(double left_bound_value, double right_bound_value);
    FitParameter& setFixed();

    virtual std::string toString() const;

protected:
    FitParameter(const FitParameter& other);

private:
    std::string m_name;
    double m_start_value;
    double m_value;
    double m_step;
    double m_error;
    AttLimits m_limits;
};

#endif // FITPARAMETER_H
