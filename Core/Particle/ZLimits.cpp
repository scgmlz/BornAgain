// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ZLimits.cpp
//! @brief     Defines class ZLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //


#include "ZLimits.h"
#include <algorithm>
#include <stdexcept>

ZLimits::ZLimits()
    : m_lower { true, 0 }
    , m_upper { true, 0 }
{}

ZLimits::ZLimits(double min, double max)
    : ZLimits( { false, min }, { false, max } )
{}

ZLimits::ZLimits(OneSidedLimit lower_limit, OneSidedLimit upper_limit)
    : m_lower(std::move(lower_limit))
    , m_upper(std::move(upper_limit))
{
    if (!lower_limit.m_limitless && !upper_limit.m_limitless
        && lower_limit.m_value > upper_limit.m_value)
        throw std::runtime_error("ZLimits constructor: "
                                 "lower limit bigger than upper limit.");
}

bool ZLimits::isFinite() const
{
    if (m_lower.m_limitless || m_upper.m_limitless)
        return false;
    return true;
}

OneSidedLimit ZLimits::lowerLimit() const
{
    return m_lower;
}

OneSidedLimit ZLimits::upperLimit() const
{
    return m_upper;
}

OneSidedLimit MinLimit(const OneSidedLimit& left, const OneSidedLimit& right)
{
    if (left.m_limitless || right.m_limitless)
        return { true, 0 };
    return { false, std::min(left.m_value, right.m_value) };
}

OneSidedLimit MaxLimit(const OneSidedLimit& left, const OneSidedLimit& right)
{
    if (left.m_limitless || right.m_limitless)
        return { true, 0 };
    return { false, std::max(left.m_value, right.m_value) };
}

bool operator==(const OneSidedLimit& left, const OneSidedLimit& right)
{
    if (left.m_limitless != right.m_limitless) return false;
    if (!left.m_limitless && left.m_value != right.m_value) return false;
    return true;
}

bool operator!=(const OneSidedLimit& left, const OneSidedLimit& right)
{
    return !(left==right);
}

std::ostream& operator<<(std::ostream& ostr, const OneSidedLimit& limit)
{
    return ostr << "{" << (limit.m_limitless ? "true, " : "false, ") << limit.m_value << "}";
}

ZLimits ConvexHull(const ZLimits& left, const ZLimits& right)
{
    return { MinLimit(left.lowerLimit(), right.lowerLimit()),
             MaxLimit(left.upperLimit(), right.upperLimit()) };
}

bool operator==(const ZLimits& left, const ZLimits& right)
{
    return (   left.lowerLimit()==right.lowerLimit()
            && left.upperLimit()==right.upperLimit());
}

bool operator!=(const ZLimits& left, const ZLimits& right)
{
    return !(left==right);
}

std::ostream& operator<<(std::ostream& ostr, const ZLimits& limits) {
    return ostr << "Lower: " << limits.lowerLimit() << ", Upper: " << limits.upperLimit();
}
