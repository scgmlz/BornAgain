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
#include "GUI/coregui/utils/MessageService.h"

RealDataModel::RealDataModel(QObject* parent)
    : SessionModel(SessionXML::RealDataModelTag, parent), m_instrumentModel(nullptr)
{
    setObjectName(SessionXML::RealDataModelTag);

    connect(this, &SessionModel::rowsInserted, this, &RealDataModel::onRowsChange);
    connect(this, &SessionModel::rowsRemoved, this, &RealDataModel::onRowsChange);
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

void RealDataModel::readFrom(QXmlStreamReader* reader, MessageService* messageService /*= 0*/)
{
    // do not send added-notifications until completely read - otherwise partially
    // initialized items will be notified
    disconnect(this, &SessionModel::rowsInserted, this, &RealDataModel::onRowsChange);

    SessionModel::readFrom(reader, messageService);

    connect(this, &SessionModel::rowsInserted, this, &RealDataModel::onRowsChange);

    bool containsOldRealData = false;
    for (auto item : realDataItems())
        if (item->dataLoader() == nullptr) {
            containsOldRealData = true;
            break;
        }

    // If there are realDataItems with no loader => old file version
    // In this case, all realData items are discarded. Project loading will still go on.
    // #baimport Improvement: Use legacy loader
    if (containsOldRealData) {
        messageService->send_warning(
            this, "You are loading an older project. The real data files from this project are not "
                  "supported any more. Please add them after loading the project.");

        clear();
    }

    if (!realDataItems().isEmpty())
        emit realDataAddedOrRemoved();
}

RealDataItem* RealDataModel::insertRealDataItem()
{
    return insertItem<RealDataItem>();
}

RealDataItem* RealDataModel::insertSpecularDataItem()
{
    auto r = insertRealDataItem();
    r->initAsSpecularItem();
    return r;
}

RealDataItem* RealDataModel::insertIntensityDataItem()
{
    auto r = insertRealDataItem();
    r->initAsIntensityItem();
    return r;
}

QVector<RealDataItem*> RealDataModel::realDataItems() const
{
    return topItems<RealDataItem>();
}

InstrumentModel* RealDataModel::instrumentModel() const
{
    return m_instrumentModel;
}

void RealDataModel::setInstrumentModel(InstrumentModel* instrumentModel)
{
    m_instrumentModel = instrumentModel;
}

void RealDataModel::onRowsChange(const QModelIndex& parent, int, int)
{
    // valid parent means not a data (which is top level item) but something below
    if (parent.isValid())
        return;

    emit realDataAddedOrRemoved();
}
