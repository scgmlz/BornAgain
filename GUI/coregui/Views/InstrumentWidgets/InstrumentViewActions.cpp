// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentViewActions.cpp
//! @brief     Implements class InstrumentViewActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/InstrumentViewActions.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/ModelUtils.h"
#include "GUI/coregui/Models/PointwiseAxisItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include <QAction>
#include <QDebug>
#include <QItemSelectionModel>
#include <QMenu>
#include <QModelIndex>
#include <QVariant>

InstrumentViewActions::InstrumentViewActions(QWidget* parent)
    : QObject(parent), m_addInstrumentMenu(nullptr), m_removeInstrumentAction(nullptr),
      m_cloneInstrumentAction(nullptr), m_model(nullptr), m_selectionModel(nullptr)
{
    initAddInstrumentMenu();

    m_removeInstrumentAction =
        new QAction(QIcon(":/images/delete.svg"), "Remove this instrument", this);

    m_cloneInstrumentAction =
        new QAction(QIcon(":/images/content-copy.svg"), "Clone this instrument", this);

    connect(m_removeInstrumentAction, &QAction::triggered, this,
            &InstrumentViewActions::onRemoveInstrument);
    connect(m_cloneInstrumentAction, &QAction::triggered, this,
            &InstrumentViewActions::onCloneInstrument);
}

InstrumentViewActions::~InstrumentViewActions()
{
    delete m_addInstrumentMenu;
}

void InstrumentViewActions::setModel(SessionModel* model)
{
    m_model = model;
}

void InstrumentViewActions::setSelectionModel(QItemSelectionModel* selectionModel)
{
    m_selectionModel = selectionModel;
}

//! Returns menu to create one of available instrument types.

QMenu* InstrumentViewActions::instrumentMenu()
{
    return m_addInstrumentMenu;
}

//! Adds instrument of certain type. Type of instrument is extracted from sender internal data.

void InstrumentViewActions::onAddInstrument()
{
    auto action = qobject_cast<QAction*>(sender());
    ASSERT(action && action->data().canConvert(QVariant::String));

    QString instrumentType = action->data().toString();

    if (instrumentType == "GISASInstrument") {
        auto instrument = m_model->insertNewItem(instrumentType);
        instrument->setItemName(suggestInstrumentName("GISAS"));
    } else if (instrumentType == "OffSpecInstrument") {
        auto instrument = m_model->insertNewItem(instrumentType);
        instrument->setItemName(suggestInstrumentName("OffSpec"));
    } else if (instrumentType == "SpecularInstrument") {
        auto instrument = m_model->insertNewItem(instrumentType);
        instrument->setItemName(suggestInstrumentName("Specular"));
    } else if (instrumentType == "DepthProbeInstrument") {
        auto instrument = m_model->insertNewItem(instrumentType);
        instrument->setItemName(suggestInstrumentName("DepthProbe"));
    } else {
        qInfo() << "InstrumentViewActions::onAddInstrument() -> Not supported instrument type"
                << instrumentType;
    }

    updateSelection();

    // Setting default action to the just triggered action
    m_addInstrumentMenu->setDefaultAction(action);
}

//! Removes currently selected instrument.

void InstrumentViewActions::onRemoveInstrument()
{
    QModelIndex currentIndex = m_selectionModel->currentIndex();

    if (currentIndex.isValid())
        m_model->removeRows(currentIndex.row(), 1, QModelIndex());

    updateSelection();
}

//! Clones currently selected instrument.

void InstrumentViewActions::onCloneInstrument()
{
    QModelIndex currentIndex = m_selectionModel->currentIndex();

    if (currentIndex.isValid()) {
        SessionItem* item = m_model->itemForIndex(currentIndex);
        QString nameOfClone = suggestInstrumentName(item->itemName());
        SessionItem* clone = m_model->insertNewItem(item->modelType());
        for (auto child : item->children()) {
            if (child->displayName() == InstrumentItem::P_IDENTIFIER)
                continue;
            auto tag = item->tagFromItem(child);
            m_model->copyItem(child, clone, tag);
        }
        clone->setItemName(nameOfClone);

        // copying non-uniform axis data
        if (auto instrument = dynamic_cast<SpecularInstrumentItem*>(item)) {
            auto axis_group = instrument->beamItem()->inclinationAxisGroup();

            auto donor_axis =
                dynamic_cast<PointwiseAxisItem*>(axis_group->getItemOfType("PointwiseAxis"));
            if (!donor_axis->containsNonXMLData())
                return;

            auto acceptor_axis =
                dynamic_cast<PointwiseAxisItem*>(dynamic_cast<SpecularInstrumentItem*>(clone)
                                                     ->beamItem()
                                                     ->inclinationAxisGroup()
                                                     ->getItemOfType("PointwiseAxis"));
            acceptor_axis->init(*donor_axis->getAxis(), donor_axis->getUnitsLabel());
        }
    }
}

void InstrumentViewActions::onContextMenuRequest(const QPoint& point,
                                                 const QModelIndex& indexAtPoint)
{
    QMenu menu;

    setAllActionsEnabled(indexAtPoint.isValid());

    menu.addAction(m_cloneInstrumentAction);
    menu.addAction(m_removeInstrumentAction);
    menu.addSeparator();
    menu.addMenu(m_addInstrumentMenu);
    menu.exec(point);
}

void InstrumentViewActions::setAllActionsEnabled(bool value)
{
    m_removeInstrumentAction->setEnabled(value);
    m_cloneInstrumentAction->setEnabled(value);
}

void InstrumentViewActions::updateSelection()
{
    if (!m_selectionModel->hasSelection()) {
        // select last item
        QModelIndex itemIndex =
            m_model->index(m_model->rowCount(QModelIndex()) - 1, 0, QModelIndex());
        m_selectionModel->select(itemIndex, QItemSelectionModel::ClearAndSelect);
    }
}

QString InstrumentViewActions::suggestInstrumentName(const QString& currentName)
{
    auto map_of_names = mapOfNames();

    int ncopies = map_of_names[currentName];
    if (ncopies == 0) {
        map_of_names[currentName] = 1;
        return currentName;
    } else {
        map_of_names[currentName]++;
        return QString("%1 (%2)").arg(currentName).arg(map_of_names[currentName]);
    }
}

QMap<QString, int> InstrumentViewActions::mapOfNames()
{
    QMap<QString, int> result;

    for (auto& name : ModelUtils::topItemNames(m_model)) {
        int ncopy(1);
        QRegExp regexp("\\((.*)\\)");
        if (regexp.indexIn(name) >= 0)
            ncopy = regexp.cap(1).toInt();
        name.replace(regexp.cap(0), "");
        name = name.trimmed();
        result[name] = ncopy;
    }

    return result;
}

//! Constructs menu to add instruments of various types. The type of instrument
//! is encoded in QAction internal data.

void InstrumentViewActions::initAddInstrumentMenu()
{
    m_addInstrumentMenu = new QMenu("Add new instrument");
    m_addInstrumentMenu->setToolTipsVisible(true);

    auto action = m_addInstrumentMenu->addAction("GISAS");
    action->setData(QVariant::fromValue(QString{"GISASInstrument"}));
    action->setToolTip("Add GISAS instrument with default settings");
    connect(action, &QAction::triggered, this, &InstrumentViewActions::onAddInstrument);
    m_addInstrumentMenu->setDefaultAction(action);

    action = m_addInstrumentMenu->addAction("OffSpec");
    action->setData(QVariant::fromValue(QString{"OffSpecInstrument"}));
    action->setToolTip("Add OffSpec instrument with default settings");
    connect(action, &QAction::triggered, this, &InstrumentViewActions::onAddInstrument);

    action = m_addInstrumentMenu->addAction("Specular");
    action->setData(QVariant::fromValue(QString{"SpecularInstrument"}));
    action->setToolTip("Add Specular instrument with default settings");
    connect(action, &QAction::triggered, this, &InstrumentViewActions::onAddInstrument);

    action = m_addInstrumentMenu->addAction("DepthProbe");
    action->setData(QVariant::fromValue(QString{"DepthProbeInstrument"}));
    action->setToolTip("Add DepthProbe instrument with default settings");
    connect(action, &QAction::triggered, this, &InstrumentViewActions::onAddInstrument);
}
