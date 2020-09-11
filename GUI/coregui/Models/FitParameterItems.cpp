// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitParameterItems.cpp
//! @brief     Implements FitParameterItems family of classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/FitParameterItems.h"
#include "Fit/Kernel/Parameter.h"
#include "Fit/Kernel/Parameters.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <cmath>

namespace
{

ComboProperty fitParameterTypeCombo()
{
    QStringList tooltips = QStringList() << "Fixed at given value"
                                         << "Limited in the range [min, max]"
                                         << "Limited at lower bound [min, inf]"
                                         << "Limited at upper bound [-inf, max]"
                                         << "No limits imposed to parameter value";

    ComboProperty result;
    result << "fixed"
           << "limited"
           << "lower limited"
           << "upper limited"
           << "free";
    result.setValue("limited");
    result.setToolTips(tooltips);
    return result;
}

const double range_factor = 0.5;
} // namespace

// ----------------------------------------------------------------------------

const QString FitParameterLinkItem::P_LINK = "Link";
const QString FitParameterLinkItem::P_DOMAIN = "Domain";

FitParameterLinkItem::FitParameterLinkItem() : SessionItem("FitParameterLink")
{
    addProperty(P_LINK, "");
    addProperty(P_DOMAIN, "");
}

// ----------------------------------------------------------------------------

const QString FitParameterItem::P_TYPE = "Type";
const QString FitParameterItem::P_START_VALUE = "Value";
const QString FitParameterItem::P_MIN = "Min";
const QString FitParameterItem::P_MAX = "Max";
const QString FitParameterItem::T_LINK = "Link tag";

FitParameterItem::FitParameterItem() : SessionItem("FitParameter")
{
    addProperty(P_TYPE, fitParameterTypeCombo().variant());
    addProperty(P_START_VALUE, 0.0)->setEditorType("ScientificSpinBox");
    addProperty(P_MIN, 0.0)->setEditorType("ScientificSpinBox");
    addProperty(P_MAX, 0.0)->setEditorType("ScientificSpinBox").setEnabled(false);
    registerTag(T_LINK, 0, -1, QStringList() << "FitParameterLink");
    setDefaultTag(T_LINK);

    getItem(P_START_VALUE)->setLimits(RealLimits::limitless());
    getItem(P_MIN)->setLimits(RealLimits::limitless());
    getItem(P_MAX)->setLimits(RealLimits::limitless());

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_TYPE)
            onTypeChange();
    });

    onTypeChange();
}

//! Inits P_MIN and P_MAX taking into account current value and external limits

void FitParameterItem::initMinMaxValues(const RealLimits& limits)
{
    double value = getItemValue(P_START_VALUE).toDouble();

    double dr(0);
    if (value == 0.0) {
        dr = 1.0 * range_factor;
    } else {
        dr = std::abs(value) * range_factor;
    }

    double min = value - dr;
    double max = value + dr;

    if (limits.hasLowerLimit() && min < limits.lowerLimit())
        min = limits.lowerLimit();

    if (limits.hasUpperLimit() && max > limits.upperLimit())
        max = limits.upperLimit();

    setItemValue(P_MIN, min);
    getItem(P_MIN)->setLimits(limits);
    setItemValue(P_MAX, max);
    getItem(P_MAX)->setLimits(limits);

    getItem(P_START_VALUE)->setLimits(limits);
}

//! Constructs Limits correspodning to current GUI settings.

AttLimits FitParameterItem::attLimits() const
{
    if (isFixed()) {
        return AttLimits::fixed();
    }

    else if (isLimited()) {
        return AttLimits::limited(getItemValue(P_MIN).toDouble(), getItemValue(P_MAX).toDouble());
    }

    else if (isLowerLimited()) {
        return AttLimits::lowerLimited(getItemValue(P_MIN).toDouble());
    }

    else if (isUpperLimited()) {
        return AttLimits::upperLimited(getItemValue(P_MAX).toDouble());
    }

    else if (isFree()) {
        return AttLimits::limitless();
    }

    else {
        throw GUIHelpers::Error("FitParameterItem::attLimits() -> Error. Unknown limit type");
    }
}

bool FitParameterItem::isValid() const
{
    if (isFixed() || isFree())
        return true;

    double value = getItemValue(P_START_VALUE).toDouble();
    double min = getItemValue(P_MIN).toDouble();
    double max = getItemValue(P_MAX).toDouble();

    if (isLowerLimited())
        return min <= value;
    if (isUpperLimited())
        return value <= max;
    return min <= value && value <= max;
}

QString FitParameterItem::parameterType() const
{
    ComboProperty partype = getItemValue(P_TYPE).value<ComboProperty>();
    return partype.getValue();
}

//! Enables/disables min, max properties on FitParameterItem's type

void FitParameterItem::onTypeChange()
{
    if (isFixed()) {
        setLimitEnabled(P_MIN, false);
        setLimitEnabled(P_MAX, false);
    }

    else if (isLimited()) {
        setLimitEnabled(P_MIN, true);
        setLimitEnabled(P_MAX, true);
    }

    else if (isLowerLimited()) {
        setLimitEnabled(P_MIN, true);
        setLimitEnabled(P_MAX, false);
    }

    else if (isUpperLimited()) {
        setLimitEnabled(P_MIN, false);
        setLimitEnabled(P_MAX, true);
    }

    else if (isFree()) {
        setLimitEnabled(P_MIN, false);
        setLimitEnabled(P_MAX, false);
    }
}

//! Set limit property with given name to the enabled state

void FitParameterItem::setLimitEnabled(const QString& name, bool enabled)
{
    if (isTag(name)) {
        SessionItem* propertyItem = getItem(name);
        ASSERT(propertyItem);
        propertyItem->setEnabled(enabled);
        propertyItem->setEditable(enabled);
    }
}

bool FitParameterItem::isLimited() const
{
    return parameterType() == "limited";
}

bool FitParameterItem::isFree() const
{
    return parameterType() == "free";
}

bool FitParameterItem::isLowerLimited() const
{
    return parameterType() == "lower limited";
}

bool FitParameterItem::isUpperLimited() const
{
    return parameterType() == "upper limited";
}

bool FitParameterItem::isFixed() const
{
    return parameterType() == "fixed";
}

// ----------------------------------------------------------------------------

const QString FitParameterContainerItem::T_FIT_PARAMETERS = "Data tag";

FitParameterContainerItem::FitParameterContainerItem() : SessionItem("FitParameterContainer")
{
    registerTag(T_FIT_PARAMETERS, 0, -1, QStringList() << "FitParameter");
    setDefaultTag(T_FIT_PARAMETERS);
}

//! returns FitParameterItem for given link (path in model)

FitParameterItem* FitParameterContainerItem::fitParameterItem(const QString& link)
{
    for (auto item : getItems(T_FIT_PARAMETERS)) {
        for (auto linkItem : item->getItems(FitParameterItem::T_LINK)) {
            if (link == linkItem->getItemValue(FitParameterLinkItem::P_LINK))
                return dynamic_cast<FitParameterItem*>(item);
        }
    }
    return nullptr;
}

QVector<FitParameterItem*> FitParameterContainerItem::fitParameterItems()
{
    QVector<FitParameterItem*> result;
    for (auto parItem : getItems(T_FIT_PARAMETERS))
        result.push_back(dynamic_cast<FitParameterItem*>(parItem));
    return result;
}

bool FitParameterContainerItem::isEmpty()
{
    return getItems(T_FIT_PARAMETERS).isEmpty();
}

//! Propagate values to the corresponding parameter tree items of parameterContainer.

void FitParameterContainerItem::setValuesInParameterContainer(
    const QVector<double>& values, ParameterContainerItem* parameterContainer)
{
    ASSERT(parameterContainer);

    QVector<SessionItem*> fitPars = getItems(FitParameterContainerItem::T_FIT_PARAMETERS);

    int index(0);
    for (int i = 0; i < fitPars.size(); ++i) {
        auto link_list = fitPars[i]->getItems(FitParameterItem::T_LINK);
        if (link_list.size() == 0)
            continue;
        for (auto linkItem : link_list) {
            QString parPath = linkItem->getItemValue(FitParameterLinkItem::P_LINK).toString();
            auto itemInTuningTree = dynamic_cast<ParameterItem*>(
                ModelPath::getItemFromPath(parPath, parameterContainer));
            if (itemInTuningTree)
                itemInTuningTree->propagateValueToLink(values[index]);
        }
        index++;
    }
}

Fit::Parameters FitParameterContainerItem::createParameters() const
{
    Fit::Parameters result;

    int index(0);
    for (auto item : getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        auto fitPar = dynamic_cast<FitParameterItem*>(item);
        if (!fitPar->isValid()) {
            std::stringstream ss;
            ss << "FitParameterContainerItem::createParameters(): invalid starting value "
                  "or (min, max) range in fitting parameter par"
               << index;
            std::string message = ss.str();
            throw GUIHelpers::Error(QString::fromStdString(ss.str()));
        }
        double startValue = fitPar->getItemValue(FitParameterItem::P_START_VALUE).toDouble();
        AttLimits limits = fitPar->attLimits();
        QString name = QString("par%1").arg(index);
        result.add(Fit::Parameter(name.toStdString(), startValue, limits));
        ++index;
    }

    return result;
}
