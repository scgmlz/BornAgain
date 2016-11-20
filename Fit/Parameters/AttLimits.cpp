// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/AttLimits.cpp
//! @brief     Implements and implements class AttLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AttLimits.h"
#include <sstream>
#include <iomanip>

AttLimits::AttLimits()
    : m_limits(RealLimits::limitless())
    , m_att_fixed(Attributes::free())
{}

AttLimits::AttLimits(const RealLimits &limits, const Attributes &fixedAttr)
    : m_limits(limits)
    , m_att_fixed(fixedAttr)
{}

AttLimits AttLimits::limitless()
{
    return AttLimits();
}

AttLimits AttLimits::lowerLimited(double bound_value)
{
    return AttLimits(RealLimits::lowerLimited(bound_value), Attributes::free());
}

AttLimits AttLimits::positive()
{
    return AttLimits(RealLimits::positive(), Attributes::free());
}

AttLimits AttLimits::nonnegative()
{
    return AttLimits(RealLimits::nonnegative(), Attributes::free());
}

AttLimits AttLimits::upperLimited(double bound_value)
{
    return AttLimits(RealLimits::upperLimited(bound_value), Attributes::free());
}

AttLimits AttLimits::limited(double left_bound_value, double right_bound_value)
{
    return AttLimits(RealLimits::limited(left_bound_value, right_bound_value), Attributes::free());
}

AttLimits AttLimits::fixed()
{
    return AttLimits(RealLimits::limitless(), Attributes::fixed());
}

bool AttLimits::isFixed() const
{
    return m_att_fixed.isFixed();
}

bool AttLimits::isLimited() const
{
    return m_att_fixed.isFree() && m_limits.hasLowerAndUpperLimits();
}

bool AttLimits::isUpperLimited() const
{
    return m_att_fixed.isFree() && !m_limits.hasLowerLimit() && m_limits.hasUpperLimit();
}

bool AttLimits::isLowerLimited() const
{
    return m_att_fixed.isFree() && m_limits.hasLowerLimit() && !m_limits.hasUpperLimit();
}

bool AttLimits::isLimitless() const
{
    return m_att_fixed.isFree() && !m_limits.hasLowerLimit() && !m_limits.hasUpperLimit();
}

double AttLimits::lowerLimit() const
{
    return m_limits.getLowerLimit();
}

double AttLimits::upperLimit() const
{
    return m_limits.getUpperLimit();
}

void AttLimits::setFixed(bool isFixed)
{
    m_limits.removeLimits();
    m_att_fixed.setFixed(isFixed);
}

bool AttLimits::operator==(const AttLimits &other) const
{
    return m_limits == other.m_limits && m_att_fixed == other.m_att_fixed;
}

std::string AttLimits::toString() const
{
    std::ostringstream result;

    if(isFixed()) {
        result << "fixed";
    }else if(isLimitless()) {
        result << "free";
    } else if(isLowerLimited()) {
        result << "lim("  << std::fixed <<std::setprecision(2) << lowerLimit() << ",)";
    }else if(isUpperLimited()) {
        result << "lim(," << std::fixed <<std::setprecision(2) << upperLimit() << ",)";
    }else if(isLimited()) {
        result << "lim(" << std::fixed <<std::setprecision(2) << lowerLimit() << "," <<
            std::fixed <<std::setprecision(2) << upperLimit() << ")";
    }
    return result.str();
}
