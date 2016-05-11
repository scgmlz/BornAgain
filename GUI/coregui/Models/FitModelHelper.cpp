// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitModelHelper.cpp
//! @brief     Implements class FitModelHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitModelHelper.h"
#include "JobItem.h"
#include "FitParameterItems.h"
#include "JobModel.h"
#include "ParameterTreeItems.h"
#include "ModelPath.h"

//! Creates fit parameter from given ParameterItem, sets starting value to the value
//! of ParameterItem, copies link.
void FitModelHelper::createFitParameter(FitParameterContainerItem *container, ParameterItem *parameterItem)
{
    Q_ASSERT(container);

    SessionItem *fitPar = container->model()->insertNewItem(Constants::FitParameterType, container->index());
    fitPar->setDisplayName(QStringLiteral("par"));
    Q_ASSERT(fitPar);

//    SessionItem *link = fitPar->model()->insertNewItem(Constants::FitParameterLinkType, fitPar->index());
//    Q_ASSERT(link);
//    link->setItemValue(FitParameterLinkItem::P_LINK, "xxx");
//    SessionItem *link2 = fitPar->model()->insertNewItem(Constants::FitParameterLinkType, fitPar->index());
//    link2->setItemValue(FitParameterLinkItem::P_LINK, "yyy");


    if(parameterItem) {
        fitPar->setItemValue(FitParameterItem::P_START_VALUE, parameterItem->value());
        SessionItem *link = fitPar->model()->insertNewItem(Constants::FitParameterLinkType, fitPar->index());
        link->setItemValue(FitParameterLinkItem::P_LINK, getParameterItemPath(parameterItem));
    }

}

//! Removes link to given parameterItem from fit parameters
void FitModelHelper::removeFromFitParameters(FitParameterContainerItem *container, ParameterItem *parameterItem)
{
    FitParameterItem *fitParItem = getFitParameterItem(container, parameterItem);

    if(fitParItem) {
        foreach(SessionItem *linkItem, fitParItem->getItems(FitParameterItem::T_LINK)) {
            if(getParameterItemPath(parameterItem) == linkItem->getItemValue(FitParameterLinkItem::P_LINK)) {
                fitParItem->model()->removeRow(linkItem->index().row(), linkItem->index().parent());
                break;
            }
        }
    }
}

//! Adds given parameterItem to the existing fit parameter with display name fitParName.
//! If parameterItem is already linked with another fitParameter, it will be relinked
void FitModelHelper::addToFitParameter(FitParameterContainerItem *container, ParameterItem *parameterItem, const QString &fitParName)
{
    Q_ASSERT(container);

    removeFromFitParameters(container, parameterItem);
    foreach(SessionItem *fitPar, container->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        if(fitPar->displayName() == fitParName) {
            SessionItem *link = fitPar->model()->insertNewItem(Constants::FitParameterLinkType, fitPar->index());
            link->setItemValue(FitParameterLinkItem::P_LINK, getParameterItemPath(parameterItem));
            break;
        }
    }
}

//! Returns fFitParameterItem corresponding to given ParameterItem
FitParameterItem *FitModelHelper::getFitParameterItem(FitParameterContainerItem *container, ParameterItem *parameterItem)
{
    Q_ASSERT(container);
    return container->getFitParameterItem(getParameterItemPath(parameterItem));
}

//! Returns list of fit parameter display names
QStringList FitModelHelper::getFitParameterNames(FitParameterContainerItem *container)
{
    Q_ASSERT(container);
    QStringList result;
    foreach(SessionItem *item, container->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        result.append(item->displayName());
    }
    return result;
}

//! return path to given item in the ParameterTreeContainer
QString FitModelHelper::getParameterItemPath(ParameterItem *parameterItem)
{
    QString result = ModelPath::getPathFromIndex(parameterItem->index());
    QString containerPrefix = Constants::ParameterContainerType+"/";
    int containerEnd = result.indexOf(containerPrefix) + containerPrefix.size();
    result = result.mid(containerEnd);
    return result;
}
