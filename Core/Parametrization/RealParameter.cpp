// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/RealParameter.cpp
//! @brief     Implements class RealParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Parametrization/RealParameter.h"
#include <sstream>

RealParameter::RealParameter(const std::string& name, double* par, const std::string& parent_name,
                             const std::function<void()>& onChange, const RealLimits& limits,
                             const Attributes& attr)
    : IParameter<double>(name, par, parent_name, onChange), m_limits(limits), m_attr(attr)
{
    if (!m_limits.isInRange(value())) {
        std::ostringstream message;
        message << "Cannot initialize parameter " << fullName() << " with value " << value()
                << ": out of bounds [" << limits << "]\n";
        throw std::runtime_error(message.str());
    }
}

RealParameter* RealParameter::clone(const std::string& new_name) const
{
    auto* ret = new RealParameter(new_name != "" ? new_name : getName(), m_data, m_parent_name,
                                  m_onChange, m_limits);
    ret->setUnit(unit());
    return ret;
}

void RealParameter::setValue(double value)
{
    if (value == *m_data)
        return; // nothing to do

    if (isNull())
        throw std::runtime_error("RealParameter::setValue() -> Error. Non-initialized parameter '"
                                 + fullName() + "'");

    if (!m_limits.isInRange(value)) {
        std::ostringstream message;
        message << "Cannot set parameter " << fullName() << " to value " << value
                << ": out of bounds [" << m_limits << "]\n";
        throw std::runtime_error(message.str());
    }

    if (m_attr.isFixed())
        throw std::runtime_error("Parameter " + fullName() + " is fixed");

    *m_data = value;
    if (m_onChange)
        m_onChange();
}

double RealParameter::value() const
{
    return *m_data;
}

RealParameter& RealParameter::setLimits(const RealLimits& limits)
{
    m_limits = limits;
    return *this;
}

RealLimits RealParameter::limits() const
{
    return m_limits;
}

RealParameter& RealParameter::setLimited(double lower, double upper)
{
    setLimits(RealLimits::limited(lower, upper));
    return *this;
}

RealParameter& RealParameter::setPositive()
{
    setLimits(RealLimits::positive());
    return *this;
}

RealParameter& RealParameter::setNonnegative()
{
    setLimits(RealLimits::nonnegative());
    return *this;
}

RealParameter& RealParameter::setUnit(const std::string& name)
{
    if (!(name == "" || name == "nm" || name == "rad" || name == "nm^2"))
        throw std::runtime_error("RealParameter::setUnit() -> Error. Unexpected unit name " + name);

    m_unit.setUnit(name);
    return *this;
}

std::string RealParameter::unit() const
{
    return m_unit.getName();
}
