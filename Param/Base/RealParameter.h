//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Base/RealParameter.h
//! @brief     Defines class RealParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_PARAM_BASE_REALPARAMETER_H
#define BORNAGAIN_PARAM_BASE_REALPARAMETER_H

#include "Fit/Param/Attributes.h"
#include "Fit/Param/RealLimits.h"
#include "Param/Base/IParameter.h"
#include "Param/Base/Unit.h"
#include <string>

class ParameterPool;

//! Wraps a parameter of type double.
//! In addition to name and on-change callback held by the parent class IParameter,
//! this class holds Limits, Attributes (currently only fixed or not), and a Unit.
//! @ingroup tools_internal

class RealParameter : public IParameter<double> {
public:
    RealParameter(const std::string& name, double* par, const std::string& parent_name = "",
                  const std::function<void()>& onChange = std::function<void()>(),
                  const RealLimits& limits = RealLimits::limitless(),
                  const Attributes& attr = Attributes::free());
    virtual ~RealParameter() = default;

    RealParameter* clone(const std::string& new_name = "") const;

    //! Sets value of wrapped parameter and emit signal
    void setValue(double value);

    //! Returns value of wrapped parameter
    double value() const;

    RealParameter& setLimits(const RealLimits& limits);
    RealLimits limits() const;

    RealParameter& setLimited(double lower, double upper);
    RealParameter& setPositive();
    RealParameter& setNonnegative();

    RealParameter& setUnit(const std::string& name);
    std::string unit() const;

protected:
    RealLimits m_limits;
    Attributes m_attr;
    Unit m_unit;
};

#endif // BORNAGAIN_PARAM_BASE_REALPARAMETER_H
