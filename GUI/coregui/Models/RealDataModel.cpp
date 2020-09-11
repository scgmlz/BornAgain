// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/RealDataModel.cpp
//! @brief     Implements class RealDataModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/RealDataItem.h"

RealDataModel::RealDataModel(QObject* parent) : SessionModel(SessionXML::RealDataModelTag, parent)
{
    setObjectName(SessionXML::RealDataModelTag);
}

// Qt::ItemFlags RealDataModel::flags(const QModelIndex &index) const
//{
//    Qt::ItemFlags result_flags =  SessionModel::flags(index);
//    result_flags |= Qt::ItemIsEditable;
//    return result_flags;
//}

QVector<SessionItem*> RealDataModel::nonXMLData() const
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
