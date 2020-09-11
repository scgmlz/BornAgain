// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitParameterItems.h
//! @brief     Defines FitParameterItems family of classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_FITPARAMETERITEMS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_FITPARAMETERITEMS_H

#include "Fit/Tools/AttLimits.h"
#include "GUI/coregui/Models/SessionItem.h"

//! FitParameterItems is a collection of items to define fit parameters in GUI.

//! The FitParameterLinkItem class holds a link to ParameterItem in tuning tree.

class BA_CORE_API_ FitParameterLinkItem : public SessionItem
{

public:
    static const QString P_LINK;
    static const QString P_DOMAIN;
    FitParameterLinkItem();
};

//! The FitParameterItem class represents a fit parameter in GUI. Contains links to corresponding
//! ParameterItem's in a tuning tree.

class BA_CORE_API_ FitParameterItem : public SessionItem
{

public:
    static const QString P_TYPE;
    static const QString P_START_VALUE;
    static const QString P_MIN;
    static const QString P_MAX;
    static const QString T_LINK;
    FitParameterItem();

    void initMinMaxValues(const RealLimits& limits);

    AttLimits attLimits() const;

    bool isValid() const;

private:
    QString parameterType() const;
    void onTypeChange();
    void setLimitEnabled(const QString& name, bool enabled);
    bool isLimited() const;
    bool isFree() const;
    bool isLowerLimited() const;
    bool isUpperLimited() const;
    bool isFixed() const;
};

//! The FitParameterContainerItem class is a collection of all defined fit parameters in JobItem.

namespace Fit
{
class Parameters;
}

class BA_CORE_API_ FitParameterContainerItem : public SessionItem
{

public:
    static const QString T_FIT_PARAMETERS;
    FitParameterContainerItem();
    FitParameterItem* fitParameterItem(const QString& link);
    QVector<FitParameterItem*> fitParameterItems();
    bool isEmpty();
    void setValuesInParameterContainer(const QVector<double>& values,
                                       class ParameterContainerItem* parameterContainer);
    Fit::Parameters createParameters() const;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_FITPARAMETERITEMS_H
