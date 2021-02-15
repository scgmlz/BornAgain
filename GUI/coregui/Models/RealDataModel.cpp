//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/RealDataModel.cpp
//! @brief     Implements class RealDataModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/RealDataItem.h"

RealDataModel::RealDataModel(QObject* parent) : SessionModel(SessionXML::RealDataModelTag, parent)
{
    setObjectName(SessionXML::RealDataModelTag);
}

QVector<SessionItem*> RealDataModel::nonXMLItems() const
{
    QVector<SessionItem*> result;

    for (auto realData : topItems<RealDataItem>()) {
        if (auto intensityItem = realData->dataItem())
            result.push_back(intensityItem);
        if (auto native_data_item = realData->nativeData())
            result.push_back(native_data_item);
    }

    return result;
}

Qt::ItemFlags RealDataModel::flags(const QModelIndex& index) const
{
    return SessionModel::flags(index) | Qt::ItemIsEditable;
}

bool RealDataModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    if (role == Qt::EditRole) {
        SessionItem* item = itemForIndex(index);
        if (item) {
            item->setItemName(value.toString());
            return true;
        }
    }

    return SessionModel::setData(index, value, role);
}

RealDataItem* RealDataModel::insertRealDataItem()
{
    return insertItem<RealDataItem>();
}

QVector<RealDataItem*> RealDataModel::realDataItems() const
{
    return topItems<RealDataItem>();
}
