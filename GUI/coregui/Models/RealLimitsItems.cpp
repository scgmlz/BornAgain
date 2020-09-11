// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RealLimitsItems.cpp
//! @brief     Defines RealLimitsItems's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/RealLimitsItems.h"

namespace
{
const QString tooltip_min_value = "Minimum allowed value, value included.";
const QString tooltip_max_value = "Maximum allowed value, value excluded.";
} // namespace

const QString RealLimitsItem::P_XMIN = "Min";
const QString RealLimitsItem::P_XMAX = "Max";

RealLimitsItem::RealLimitsItem(const QString& name) : SessionItem(name) {}

// --------------------------------------------------------------------------------------------- //

LimitlessItem::LimitlessItem() : RealLimitsItem("RealLimitsLimitless") {}

RealLimits LimitlessItem::createRealLimits(double /*scale_factor*/) const
{
    return RealLimits();
}

// --------------------------------------------------------------------------------------------- //

PositiveItem::PositiveItem() : RealLimitsItem("RealLimitsPositive") {}

RealLimits PositiveItem::createRealLimits(double /*scale_factor*/) const
{
    return RealLimits::positive();
}

// --------------------------------------------------------------------------------------------- //

NonnegativeItem::NonnegativeItem() : RealLimitsItem("RealLimitsNonnegative") {}

RealLimits NonnegativeItem::createRealLimits(double /*scale_factor*/) const
{
    return RealLimits::nonnegative();
}

// --------------------------------------------------------------------------------------------- //

LowerLimitedItem::LowerLimitedItem() : RealLimitsItem("RealLimitsLowerLimited")
{
    addProperty(P_XMIN, 0.0)->setToolTip(tooltip_min_value).setLimits(RealLimits::limitless());
}

RealLimits LowerLimitedItem::createRealLimits(double scale_factor) const
{
    return RealLimits::lowerLimited(scale_factor * getItemValue(P_XMIN).toDouble());
}

// --------------------------------------------------------------------------------------------- //

UpperLimitedItem::UpperLimitedItem() : RealLimitsItem("RealLimitsUpperLimited")
{
    addProperty(P_XMAX, 1.0)->setToolTip(tooltip_max_value).setLimits(RealLimits::limitless());
}

RealLimits UpperLimitedItem::createRealLimits(double scale_factor) const
{
    return RealLimits::upperLimited(scale_factor * getItemValue(P_XMAX).toDouble());
}

// --------------------------------------------------------------------------------------------- //

LimitedItem::LimitedItem() : RealLimitsItem("RealLimitsLimited")
{
    addProperty(P_XMIN, 0.0)->setToolTip(tooltip_min_value).setLimits(RealLimits::limitless());
    addProperty(P_XMAX, 1.0)->setToolTip(tooltip_max_value).setLimits(RealLimits::limitless());
}

RealLimits LimitedItem::createRealLimits(double scale_factor) const
{
    return RealLimits::limited(scale_factor * getItemValue(P_XMIN).toDouble(),
                               scale_factor * getItemValue(P_XMAX).toDouble());
}
