// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTreeItems.cpp
//! @brief     Implements classes for ParameterTreeItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/FitParameterHelper.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/SessionModel.h"

// ----------------------------------------------------------------------------

ParameterLabelItem::ParameterLabelItem() : SessionItem("Parameter Label")
{
    const QString T_CHILDREN = "children tag";
    registerTag(T_CHILDREN, 0, -1,
                QStringList() << "Parameter Label"
                              << "Parameter");
    setDefaultTag(T_CHILDREN);
}

const QString ParameterItem::P_LINK = "Link";
const QString ParameterItem::P_BACKUP = "Backup";
const QString ParameterItem::P_DOMAIN = "Domain";
ParameterItem::ParameterItem() : SessionItem("Parameter")
{
    // Link to original PropertyItem in one of components of MultiLayerItem or InstrumentItem
    addProperty(P_LINK, "");
    // The back up value of PropertyItem to be able to reset parameter tuning tree to initial state
    addProperty(P_BACKUP, 0.0);
    // The domain name of corresponding ISample's registered parameter
    addProperty(P_DOMAIN, "");
}

// ----------------------------------------------------------------------------

//! Sets current value to the original PropertyItem of MultiLayerItem/InstrumentItem.

void ParameterItem::propagateValueToLink(double newValue)
{
    setValue(newValue);

    if (SessionItem* item = linkedItem())
        item->setValue(newValue);
}

//! Returns corresponding linked item in MultiLayerItem/IsntrumentItem

SessionItem* ParameterItem::linkedItem()
{
    const SessionItem* jobItem = ModelPath::ancestor(this, "JobItem");
    ASSERT(jobItem);
    QString link = jobItem->itemName() + "/" + getItemValue(P_LINK).toString();
    return model()->itemForIndex(ModelPath::getIndexFromPath(model(), link));
}

//! Restore the value from backup and propagate it to the linked item.

void ParameterItem::restoreFromBackup()
{
    double newValue = getItemValue(P_BACKUP).toDouble();
    propagateValueToLink(newValue);
}

// ----------------------------------------------------------------------------

ParameterContainerItem::ParameterContainerItem() : SessionItem("Parameter Container")
{
    const QString T_CHILDREN = "children tag";
    registerTag(T_CHILDREN, 0, -1, QStringList() << "Parameter Label");
    setDefaultTag(T_CHILDREN);
}
