// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.cpp
//! @brief     Implements class LinkInstrumentManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.h"
#include <QMessageBox>
#include <QPushButton>

namespace
{
const QString undefinedInstrumentName = "Undefined";

bool QuestionOnInstrumentReshaping(const QString& message);
} // namespace

LinkInstrumentManager::InstrumentInfo::InstrumentInfo()
    : m_name(undefinedInstrumentName), m_instrument(nullptr)
{
}

LinkInstrumentManager::LinkInstrumentManager(QObject* parent)
    : QObject(parent), m_instrumentModel(nullptr), m_realDataModel(nullptr)
{
}

//! Sets models and builds initial links.

void LinkInstrumentManager::setModels(InstrumentModel* instrumentModel,
                                      RealDataModel* realDataModel)
{
    setInstrumentModel(instrumentModel);
    setRealDataModel(realDataModel);
    updateInstrumentMap();
    updateRealDataMap();
    updateLinks();
}

//! Returns InstrumentItem for given identifier.

InstrumentItem* LinkInstrumentManager::getInstrument(const QString& identifier)
{
    for (int i = 0; i < m_instrumentVec.size(); ++i)
        if (m_instrumentVec[i].m_identifier == identifier)
            return m_instrumentVec[i].m_instrument;

    return nullptr;
}

//! Returns list of instrument names including artificial name "Undefined".

QStringList LinkInstrumentManager::instrumentNames() const
{
    QStringList result;
    for (int i = 0; i < m_instrumentVec.size(); ++i)
        result.append(m_instrumentVec[i].m_name);
    return result;
}

//! Returns combo index for instrument selector from given identifier.

int LinkInstrumentManager::instrumentComboIndex(const QString& identifier)
{
    for (int i = 0; i < m_instrumentVec.size(); ++i)
        if (m_instrumentVec[i].m_identifier == identifier)
            return i;

    return -1; // no such identifier exists
}

//! Returns instrument identifier from given index in combo instrument selector.

QString LinkInstrumentManager::instrumentIdentifier(int comboIndex)
{
    ASSERT(comboIndex >= 0 && comboIndex < m_instrumentVec.size());
    return m_instrumentVec[comboIndex].m_identifier;
}

//! Returns true if RealDataItem can be linked to the instrument (same number of bins).
//! Also offers dialog to adjust instrument to match shape of real data.

bool LinkInstrumentManager::canLinkDataToInstrument(const RealDataItem* realDataItem,
                                                    const QString& identifier)
{
    auto instrumentItem = getInstrument(identifier);

    // linking to null instrument is possible, it means unlinking from currently linked
    if (!instrumentItem)
        return true;

    if (!ImportDataUtils::Compatible(*instrumentItem, *realDataItem)) {
        QMessageBox::warning(nullptr, "Can't link to instrument",
                             "Can't link, data is incompatible with the instrument.");
        return false;
    }

    if (instrumentItem->alignedWith(realDataItem))
        return true;

    QString message =
        realDataItem->holdsDimensionalData()
            ? "Experimental data carries information on the range/points of measurement."
            : ImportDataUtils::printShapeMessage(instrumentItem->shape(), realDataItem->shape());
    if (!QuestionOnInstrumentReshaping(message))
        return false;

    instrumentItem->updateToRealData(realDataItem);
    return true;
}

//! Calls rebuild of instrument map if the name or identifier of the instrument have changed.

void LinkInstrumentManager::setOnInstrumentPropertyChange(SessionItem* instrument,
                                                          const QString& property)
{
    Q_UNUSED(instrument);
    if (property == SessionItem::P_NAME || property == InstrumentItem::P_IDENTIFIER)
        updateInstrumentMap();
}

//! Link or re-link RealDataItem to the instrument on identifier change.

void LinkInstrumentManager::setOnRealDataPropertyChange(SessionItem* dataItem,
                                                        const QString& property)
{
    if (property == RealDataItem::P_INSTRUMENT_ID) {
        RealDataItem* realDataItem = dynamic_cast<RealDataItem*>(dataItem);
        QString identifier = dataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        realDataItem->linkToInstrument(getInstrument(identifier));
    }
}

//! Perform actions on instrument children change.

void LinkInstrumentManager::onInstrumentChildChange(InstrumentItem* instrument, SessionItem* child)
{
    if (child == nullptr)
        return;

    onInstrumentLayoutChange(instrument);
}

//! Updates map of instruments on insert/remove InstrumentItem event.

void LinkInstrumentManager::onInstrumentRowsChange(const QModelIndex& parent, int, int)
{
    // valid parent means not an instrument (which is top level item) but something below
    if (parent.isValid())
        return;

    updateInstrumentMap();
    updateLinks();
}

//! Updates map of data on insert/remove RealDataItem event.

void LinkInstrumentManager::onRealDataRowsChange(const QModelIndex& parent, int, int)
{
    // valid parent means not a data (which is top level item) but something below
    if (parent.isValid())
        return;

    updateRealDataMap();
    updateLinks();
}

//! Runs through all RealDataItem and check all links.

void LinkInstrumentManager::updateLinks()
{
    for (auto realDataItem : m_realDataModel->topItems<RealDataItem>()) {
        QString identifier = realDataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        auto instrumentItem = getInstrument(identifier);

        if (!instrumentItem) {
            // if no instrument with P_INSTRUMENT_ID exists, break the link
            realDataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());
        } else {
            // refresh the link to update axes
            realDataItem->linkToInstrument(instrumentItem);
        }
    }
}

//! Builds the map of existing instruments, their names, identifiers and sets up callbacks.

void LinkInstrumentManager::updateInstrumentMap()
{
    m_instrumentVec.clear();
    m_instrumentVec.append(InstrumentInfo()); // undefined instrument
    for (auto instrumentItem : m_instrumentModel->topItems<InstrumentItem>()) {
        instrumentItem->mapper()->unsubscribe(this);

        instrumentItem->mapper()->setOnPropertyChange(
            [this, instrumentItem](const QString& name) {
                setOnInstrumentPropertyChange(instrumentItem, name);
            },
            this);

        instrumentItem->mapper()->setOnAnyChildChange(
            [this, instrumentItem](SessionItem* child) {
                onInstrumentChildChange(instrumentItem, child);
            },
            this);

        InstrumentInfo info;
        info.m_name = instrumentItem->itemName();
        info.m_identifier = instrumentItem->getItemValue(InstrumentItem::P_IDENTIFIER).toString();
        info.m_instrument = instrumentItem;
        m_instrumentVec.append(info);
    }

    emit instrumentMapUpdated();
}

//! Sets callbacks for all RealDataItem.

void LinkInstrumentManager::updateRealDataMap()
{
    for (auto dataItem : m_realDataModel->topItems<RealDataItem>()) {
        dataItem->mapper()->unsubscribe(this);

        dataItem->mapper()->setOnPropertyChange(
            [this, dataItem](const QString& name) { setOnRealDataPropertyChange(dataItem, name); },
            this);
    }
}

//! Runs through all RealDataItem and refresh linking to match possible change in detector
//! axes definition.

void LinkInstrumentManager::onInstrumentLayoutChange(InstrumentItem* changedInstrument)
{
    for (auto realDataItem : linkedItems(changedInstrument))
        if (!changedInstrument->alignedWith(realDataItem))
            realDataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());
        else
            realDataItem->linkToInstrument(changedInstrument);
}

//! Returns list of RealDataItem's linked to given instrument.

QList<RealDataItem*> LinkInstrumentManager::linkedItems(InstrumentItem* instrumentItem)
{
    QList<RealDataItem*> result;
    for (auto realDataItem : m_realDataModel->topItems<RealDataItem>()) {
        QString linkedIdentifier =
            realDataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
        QString instrumentIdentifier =
            instrumentItem->getItemValue(InstrumentItem::P_IDENTIFIER).toString();

        if (linkedIdentifier == instrumentIdentifier)
            result.append(realDataItem);
    }
    return result;
}

//! Sets connections for instrument model.

void LinkInstrumentManager::setInstrumentModel(InstrumentModel* model)
{
    if (m_instrumentModel) {
        disconnect(m_instrumentModel, &InstrumentModel::rowsInserted, this,
                   &LinkInstrumentManager::onInstrumentRowsChange);
        disconnect(m_instrumentModel, &InstrumentModel::rowsRemoved, this,
                   &LinkInstrumentManager::onInstrumentRowsChange);
    }

    m_instrumentModel = model;

    if (m_instrumentModel) {
        connect(m_instrumentModel, &InstrumentModel::rowsInserted, this,
                &LinkInstrumentManager::onInstrumentRowsChange);
        connect(m_instrumentModel, &InstrumentModel::rowsRemoved, this,
                &LinkInstrumentManager::onInstrumentRowsChange);
    }
}

//! Sets connections for real data model.

void LinkInstrumentManager::setRealDataModel(RealDataModel* model)
{
    if (m_realDataModel) {
        disconnect(m_realDataModel, &RealDataModel::rowsInserted, this,
                   &LinkInstrumentManager::onRealDataRowsChange);
        disconnect(m_realDataModel, &RealDataModel::rowsRemoved, this,
                   &LinkInstrumentManager::onRealDataRowsChange);
    }

    m_realDataModel = model;

    if (m_realDataModel) {
        connect(m_realDataModel, &RealDataModel::rowsInserted, this,
                &LinkInstrumentManager::onRealDataRowsChange);
        connect(m_realDataModel, &RealDataModel::rowsRemoved, this,
                &LinkInstrumentManager::onRealDataRowsChange);
    }
}

namespace
{
bool QuestionOnInstrumentReshaping(const QString& message)
{
    QMessageBox msgBox;
    msgBox.setText("Instrument description conflicts with the experimental data.");

    QString informative;
    informative.append(message);
    informative.append("\n\nDo you want to adjust the instrument to the experimental data?\n\n");
    msgBox.setInformativeText(informative);

    QPushButton* modifyInstrumentButton =
        msgBox.addButton("Yes, please modify instrument", QMessageBox::YesRole);
    msgBox.addButton("No, leave as it is", QMessageBox::NoRole);

    msgBox.exec();

    return msgBox.clickedButton() == modifyInstrumentButton;
}
} // namespace
