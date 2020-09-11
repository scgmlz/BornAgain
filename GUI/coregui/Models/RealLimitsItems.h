// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RealLimitsItems.h
//! @brief     Defines RealLimitsItems's classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_REALLIMITSITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_REALLIMITSITEMS_H

#include "Fit/Tools/RealLimits.h"
#include "GUI/coregui/Models/SessionItem.h"

class BA_CORE_API_ RealLimitsItem : public SessionItem
{
public:
    static const QString P_XMIN;
    static const QString P_XMAX;
    RealLimitsItem(const QString& name);
    virtual ~RealLimitsItem() {}
    virtual RealLimits createRealLimits(double scale_factor = 1.0) const = 0;
};

class BA_CORE_API_ LimitlessItem : public RealLimitsItem
{
public:
    LimitlessItem();
    RealLimits createRealLimits(double scale_factor = 1.0) const;
};

class BA_CORE_API_ PositiveItem : public RealLimitsItem
{
public:
    PositiveItem();
    RealLimits createRealLimits(double scale_factor = 1.0) const;
};

class BA_CORE_API_ NonnegativeItem : public RealLimitsItem
{
public:
    NonnegativeItem();
    RealLimits createRealLimits(double scale_factor = 1.0) const;
};

class BA_CORE_API_ LowerLimitedItem : public RealLimitsItem
{
public:
    LowerLimitedItem();
    RealLimits createRealLimits(double scale_factor = 1.0) const;
};

class BA_CORE_API_ UpperLimitedItem : public RealLimitsItem
{
public:
    UpperLimitedItem();
    RealLimits createRealLimits(double scale_factor = 1.0) const;
};

class BA_CORE_API_ LimitedItem : public RealLimitsItem
{
public:
    LimitedItem();
    RealLimits createRealLimits(double scale_factor = 1.0) const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_REALLIMITSITEMS_H
