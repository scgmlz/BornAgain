// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitParameterHelper.cpp
//! @brief     Implements class FitModelHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/FitParameterHelper.h"
#include "GUI/coregui/Models/FitParameterItems.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"

//! Creates fit parameter from given ParameterItem, sets starting value to the value
//! of ParameterItem, copies link.

void FitParameterHelper::createFitParameter(FitParameterContainerItem* container,
                                            ParameterItem* parameterItem)
{
    ASSERT(container);
    ASSERT(parameterItem);

    removeFromFitParameters(container, parameterItem);

    FitParameterItem* fitPar = dynamic_cast<FitParameterItem*>(
        container->model()->insertNewItem("FitParameter", container->index()));
    ASSERT(fitPar);
    fitPar->setDisplayName("par");
    SessionItem* link = fitPar->model()->insertNewItem("FitParameterLink", fitPar->index());
    fitPar->setItemValue(FitParameterItem::P_START_VALUE, parameterItem->value());
    link->setItemValue(FitParameterLinkItem::P_LINK, getParameterItemPath(parameterItem));

    fitPar->initMinMaxValues(parameterItem->linkedItem()->limits());
}

//! Removes link to given parameterItem from fit parameters

void FitParameterHelper::removeFromFitParameters(FitParameterContainerItem* container,
                                                 ParameterItem* parameterItem)
{
    FitParameterItem* fitParItem = getFitParameterItem(container, parameterItem);

    if (fitParItem) {
        for (auto linkItem : fitParItem->getItems(FitParameterItem::T_LINK)) {
            if (getParameterItemPath(parameterItem)
                == linkItem->getItemValue(FitParameterLinkItem::P_LINK)) {
                fitParItem->model()->removeRow(linkItem->index().row(), linkItem->index().parent());
                break;
            }
        }
    }
}

//! Adds given parameterItem to the existing fit parameter with display name fitParName.
//! If parameterItem is already linked with another fitParameter, it will be relinked

void FitParameterHelper::addToFitParameter(FitParameterContainerItem* container,
                                           ParameterItem* parameterItem, const QString& fitParName)
{
    ASSERT(container);

    removeFromFitParameters(container, parameterItem);
    for (auto fitPar : container->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        if (fitPar->displayName() == fitParName) {
            SessionItem* link = fitPar->model()->insertNewItem("FitParameterLink", fitPar->index());
            link->setItemValue(FitParameterLinkItem::P_LINK, getParameterItemPath(parameterItem));
            break;
        }
    }
}

//! Returns fFitParameterItem corresponding to given ParameterItem

FitParameterItem* FitParameterHelper::getFitParameterItem(FitParameterContainerItem* container,
                                                          ParameterItem* parameterItem)
{
    ASSERT(container);
    return container->fitParameterItem(getParameterItemPath(parameterItem));
}

//! Returns list of fit parameter display names

QStringList FitParameterHelper::getFitParameterNames(FitParameterContainerItem* container)
{
    ASSERT(container);
    QStringList result;
    for (auto item : container->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        result.append(item->displayName());
    }
    return result;
}

//! return path to given item in the ParameterTreeContainer

QString FitParameterHelper::getParameterItemPath(const ParameterItem* parameterItem)
{
    QString result = ModelPath::getPathFromIndex(parameterItem->index());
    QString containerPrefix = "Parameter Container/";
    int containerEnd = result.indexOf(containerPrefix) + containerPrefix.size();
    result = result.mid(containerEnd);
    return result;
}

//! Returns ParameterItem corresponding to given link.
//! Link is relative to ParameterContainerItem, so first we have to find it

ParameterItem* FitParameterHelper::getParameterItem(FitParameterContainerItem* container,
                                                    const QString& link)
{
    SessionItem* cur = container;
    while (cur && cur->modelType() != "JobItem") {
        cur = cur->parent();
    }
    ASSERT(cur && cur->modelType() == "JobItem");
    JobItem* jobItem = dynamic_cast<JobItem*>(cur);
    ASSERT(jobItem);
    return dynamic_cast<ParameterItem*>(
        ModelPath::getItemFromPath(link, jobItem->parameterContainerItem()));
}
