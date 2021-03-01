//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.cpp
//! @brief     Implements class LinkInstrumentManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h"
#include "GUI/coregui/Models/AxesItems.h"
#include "GUI/coregui/Models/DataItem.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include <QMessageBox>
#include <QPushButton>

namespace {
bool QuestionOnInstrumentReshaping(const QString& message);
} // namespace

LinkInstrumentManager::LinkInstrumentManager(QObject* parent)
    : QObject(parent), m_instrumentModel(nullptr), m_realDataModel(nullptr)
{
}

//! Sets models and builds initial links.

void LinkInstrumentManager::setModels(InstrumentModel* instrumentModel,
                                      RealDataModel* realDataModel)
{
    ASSERT(instrumentModel != nullptr);
    ASSERT(realDataModel != nullptr);

    if (m_instrumentModel)
        m_instrumentModel->disconnect(this);

    if (m_realDataModel)
        m_realDataModel->disconnect(this);

    m_instrumentModel = instrumentModel;
    m_realDataModel = realDataModel;

    connect(m_instrumentModel, &InstrumentModel::instrumentAddedOrRemoved, this,
            &LinkInstrumentManager::onInstrumentAddedOrRemoved);

    updateInstrumentSubscriptions();
}

//! Returns true if RealDataItem can be linked to the instrument (same number of bins).
//! Also offers dialog to adjust instrument to match shape of real data.

bool LinkInstrumentManager::canLinkDataToInstrument(const RealDataItem* realDataItem,
                                                    const QString& identifier,
                                                    bool quiet /*= false*/)
{
    auto instrumentItem = m_instrumentModel->findInstrumentById(identifier);

    // linking to null instrument is possible, it means unlinking from currently linked
    if (!instrumentItem)
        return true;

    const bool isCompatible = ImportDataUtils::Compatible(*instrumentItem, *realDataItem);
    if (!isCompatible) {
        if (!quiet)
            QMessageBox::warning(MainWindow::instance(), "Can't link to instrument",
                                 "Can't link, data is incompatible with the instrument.");
        return false;
    }

    if (realDataItem->isSpecularData() && !realDataItem->hasNativeData()) {
        if (!quiet)
            QMessageBox::warning(MainWindow::instance(), "Can't link to instrument",
                                 "Can't link, data is empty.");
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

//! Perform actions on instrument children change.

void LinkInstrumentManager::onInstrumentChildChange(InstrumentItem* instrument, SessionItem* child)
{
    if (child == nullptr)
        return;

    ASSERT(instrument != nullptr);

    // Run through all RealDataItem and refresh linking to match possible change in detector
    // axes definition.
    for (auto realDataItem : linkedRealDataItems(instrument))
        if (!instrument->alignedWith(realDataItem))
            realDataItem->clearInstrumentId();
        else
            realDataItem->updateToInstrument(instrument);
}

//! Updates map of instruments on insert/remove InstrumentItem event.

void LinkInstrumentManager::onInstrumentAddedOrRemoved()
{
    // remove links in realDataItems (in case of a linked instrument was removed)
    for (auto realDataItem : m_realDataModel->realDataItems()) {
        if (!m_instrumentModel->instrumentExists(realDataItem->instrumentId()))
            realDataItem->clearInstrumentId();
    }

    updateInstrumentSubscriptions();
}

//! Set up callbacks to all instrument items

void LinkInstrumentManager::updateInstrumentSubscriptions()
{
    for (auto instrumentItem : m_instrumentModel->instrumentItems()) {
        instrumentItem->mapper()->unsubscribe(this);

        instrumentItem->mapper()->setOnAnyChildChange(
            [this, instrumentItem](SessionItem* child) {
                onInstrumentChildChange(instrumentItem, child);
            },
            this);
    }
}

//! Returns list of RealDataItem's linked to given instrument.

QList<RealDataItem*> LinkInstrumentManager::linkedRealDataItems(InstrumentItem* instrumentItem)
{
    ASSERT(instrumentItem != nullptr);

    QList<RealDataItem*> result;
    for (auto realDataItem : m_realDataModel->realDataItems()) {
        const QString linkedIdentifier = realDataItem->instrumentId();
        const QString instrumentIdentifier = instrumentItem->id();

        if (linkedIdentifier == instrumentIdentifier)
            result.append(realDataItem);
    }
    return result;
}

namespace {
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
