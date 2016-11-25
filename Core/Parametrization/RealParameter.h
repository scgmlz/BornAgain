// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/RealParameter.h
//! @brief     Defines class RealParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef REALPARAMETER_H
#define REALPARAMETER_H

#include "Attributes.h"
#include "IParameter.h"
#include "RealLimits.h"
#include "Unit.h"
#include <string>

class ParameterPool;

//! Wraps a parameter of type double.
//! In addition to name and on-change callback held by the parent class IParameter,
//! this class holds Limits, Attributes (currently only fixed or not), and a Unit.
//! @ingroup tools_internal

class BA_CORE_API_ RealParameter : public IParameter<double>
{
public:
    RealParameter(
        const std::string& name, volatile double* par, const std::string& parent_name,
        const std::function<void()>& onChange, const RealLimits& limits = RealLimits::limitless(),
        const Attributes& attr = Attributes::free());

    RealParameter* clone(const std::string& new_name = "") const;

    //! Sets value of wrapped parameter and emit signal
    void setValue(double value);

    //! Returns value of wrapped parameter
    double getValue() const { return *m_data; }

    RealParameter& setLimits(const RealLimits& limits)
    {
        m_limits = limits;
        return *this;
    }
    RealLimits getLimits() const { return m_limits; }

    RealParameter& setLimited(double lower, double upper);
    RealParameter& setPositive();
    RealParameter& setNonnegative();

    bool operator==(const RealParameter& other) const
    {
        return m_limits == other.m_limits && m_attr == other.m_attr
            && *static_cast<const IParameter*>(this) == *static_cast<const IParameter*>(&other);
    }

    RealParameter& setUnit(const std::string& name)
    {
        m_unit.setUnit(name);
        return *this;
    }
    std::string unit() const { return m_unit.getName(); }

protected:
    RealLimits m_limits;
    Attributes m_attr;
    Unit m_unit;
};

#endif // REALPARAMETER_H
