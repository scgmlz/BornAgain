// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/RealParameter.cpp
//! @brief     Implements class RealParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RealParameter.h"
#include <sstream>

RealParameter::RealParameter(
    const std::string& name, volatile double* par, const std::string& parent_name,
    const std::function<void()>& onChange, const RealLimits& limits, const Attributes& attr)
    : IParameter<double>(name, par, parent_name, onChange), m_limits(limits), m_attr(attr)
{
    if (!m_limits.isInRange(getValue())) {
        std::ostringstream message;
        message << "Cannot initialize parameter " << fullName() << " with value " << getValue()
                << ": out of bounds [" << limits << "]\n";
        throw std::runtime_error(message.str());
    }
}

RealParameter* RealParameter::clone(const std::string& new_name) const
{
    auto* ret = new RealParameter(
        new_name != "" ? new_name : getName(), m_data, m_parent_name, m_onChange, m_limits);
    ret->setUnit(unit());
    return ret;
}

void RealParameter::setValue(double value)
{
    if (value == *m_data)
        return; // nothing to do
    if (!m_limits.isInRange(value)) {
        std::ostringstream message;
        message << "Cannot set parameter " << fullName() << " to value " << value
                << ": out of bounds [" << m_limits << "]\n";
        throw std::runtime_error(message.str());
    }
    if (m_attr.isFixed())
        throw std::runtime_error("Parameter " + fullName() + " is fixed");
    *m_data = value;
    m_onChange();
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
