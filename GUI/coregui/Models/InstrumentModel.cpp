//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/InstrumentModel.cpp
//! @brief     Implements class InstrumentModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"

InstrumentModel::InstrumentModel(QObject* parent)
    : SessionModel(SessionXML::InstrumentModelTag, parent)
{
    setObjectName(SessionXML::InstrumentModelTag);

    connect(this, &SessionModel::rowsInserted, this, &InstrumentModel::onRowsChange);
    connect(this, &SessionModel::rowsRemoved, this, &InstrumentModel::onRowsChange);
}

InstrumentModel::~InstrumentModel() = default;

InstrumentModel* InstrumentModel::createCopy(SessionItem* parent)
{
    InstrumentModel* result = new InstrumentModel();
    result->initFrom(this, parent);
    return result;
}

QVector<SessionItem*> InstrumentModel::nonXMLItems() const
{
    QVector<SessionItem*> result;

    for (auto instrument_item : topItems<SpecularInstrumentItem>()) {
        auto axis_group = instrument_item->beamItem()
                              ->getItem(BeamItem::P_INCLINATION_ANGLE)
                              ->getItem(SpecularBeamInclinationItem::P_ALPHA_AXIS);

        if (auto pointwise_axis = axis_group->getChildOfType("PointwiseAxis"))
            result.push_back(pointwise_axis);
    }

    return result;
}

void InstrumentModel::readFrom(QXmlStreamReader* reader, MessageService* messageService /*= 0*/)
{
    // do not send added-notifications until completely read - otherwise partially
    // initialized items will be notified
    disconnect(this, &SessionModel::rowsInserted, this, &InstrumentModel::onRowsChange);

    SessionModel::readFrom(reader, messageService);

    connect(this, &SessionModel::rowsInserted, this, &InstrumentModel::onRowsChange);

    for (auto instrumentItem : instrumentItems()) {
        instrumentItem->mapper()->setOnPropertyChange(
            [this, instrumentItem](const QString& name) {
                onInstrumentPropertyChange(instrumentItem, name);
            },
            this);
    }

    if (!instrumentItems().isEmpty())
        emit instrumentAddedOrRemoved();
}

QVector<InstrumentItem*> InstrumentModel::instrumentItems() const
{
    return topItems<InstrumentItem>();
}

InstrumentItem* InstrumentModel::findInstrumentById(const QString& instrumentId) const
{
    for (auto instrument : instrumentItems())
        if (instrument->id() == instrumentId)
            return instrument;

    return nullptr;
}

void InstrumentModel::onRowsChange(const QModelIndex& parent, int, int)
{
    // valid parent means not an instrument (which is top level item) but something below
    if (parent.isValid())
        return;

    for (auto instrumentItem : instrumentItems()) {
        instrumentItem->mapper()->unsubscribe(this);

        instrumentItem->mapper()->setOnPropertyChange(
            [this, instrumentItem](const QString& name) {
                onInstrumentPropertyChange(instrumentItem, name);
            },
            this);
    }

    emit instrumentAddedOrRemoved();
}

void InstrumentModel::onInstrumentPropertyChange(const InstrumentItem* instrument,
                                                 const QString& propertyName)
{
    if (propertyName == SessionItem::P_NAME)
        emit instrumentNameChanged(instrument);
}
