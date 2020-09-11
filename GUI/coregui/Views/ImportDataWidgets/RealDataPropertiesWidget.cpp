// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataPropertiesWidget.cpp
//! @brief     Implements class RealDataPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/ImportDataWidgets/RealDataPropertiesWidget.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h"
#include <QComboBox>
#include <QDataWidgetMapper>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

namespace
{
const QString instrumentNameTooltip = "Name of real data";
const QString selectorTooltip = "Select instrument to link with real data";
} // namespace

RealDataPropertiesWidget::RealDataPropertiesWidget(QWidget* parent)
    : QWidget(parent), m_linkManager(new LinkInstrumentManager(this)),
      m_dataNameMapper(new QDataWidgetMapper(this)), m_dataNameLabel(new QLabel("Dataset")),
      m_dataNameEdit(new QLineEdit), m_instrumentLabel(new QLabel("Linked instrument")),
      m_instrumentCombo(new QComboBox), m_currentDataItem(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle("RealDataPropertiesWidget");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setMargin(5);
    mainLayout->setSpacing(2);

    m_dataNameLabel->setToolTip(instrumentNameTooltip);
    m_dataNameEdit->setToolTip(instrumentNameTooltip);
    m_instrumentLabel->setToolTip(selectorTooltip);
    m_instrumentCombo->setToolTip(selectorTooltip);

    mainLayout->addWidget(m_dataNameLabel);
    mainLayout->addWidget(m_dataNameEdit);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(m_instrumentLabel);
    mainLayout->addWidget(m_instrumentCombo);

    mainLayout->addStretch();
    setLayout(mainLayout);

    setComboConnected(true);
    connect(m_linkManager, SIGNAL(instrumentMapUpdated()), this, SLOT(onInstrumentMapUpdate()));

    setPropertiesEnabled(false);
}

//! Sets models to underlying link manager.

void RealDataPropertiesWidget::setModels(InstrumentModel* instrumentModel,
                                         RealDataModel* realDataModel)
{
    m_linkManager->setModels(instrumentModel, realDataModel);
}

//! Set current RealDataItem to display in instrument selector.

void RealDataPropertiesWidget::setItem(SessionItem* item)
{
    m_dataNameMapper->clearMapping();

    if (item == m_currentDataItem)
        return;

    if (m_currentDataItem)
        m_currentDataItem->mapper()->unsubscribe(this);

    m_currentDataItem = dynamic_cast<RealDataItem*>(item);

    if (!m_currentDataItem) {
        setPropertiesEnabled(false);
        return;
    }

    setPropertiesEnabled(true);

    m_currentDataItem->mapper()->setOnPropertyChange(
        [this](const QString& name) { onRealDataPropertyChanged(name); }, this);

    m_currentDataItem->mapper()->setOnItemDestroy([this](SessionItem*) { m_currentDataItem = 0; },
                                                  this);

    // Initialize QLineEdit to edit itemName directly in the model
    m_dataNameMapper->setModel(item->model());
    m_dataNameMapper->setRootIndex(item->index());
    m_dataNameMapper->setCurrentModelIndex(item->getItem(SessionItem::P_NAME)->index());
    m_dataNameMapper->addMapping(m_dataNameEdit, 1);
    m_dataNameMapper->toFirst();

    // Set combo selector to show linked instrument
    setComboToIdentifier(item->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString());
}

//! Processes user interaction with instrument selector combo. If there is realDataItem,
//! it will be linked with selected instrument.

void RealDataPropertiesWidget::onInstrumentComboIndexChanged(int index)
{
    m_current_id = m_linkManager->instrumentIdentifier(index);

    if (!m_currentDataItem)
        return;

    QString dataLink = m_currentDataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString();
    if (m_current_id == dataLink)
        return;

    if (m_linkManager->canLinkDataToInstrument(m_currentDataItem, m_current_id)) {
        m_currentDataItem->setItemValue(RealDataItem::P_INSTRUMENT_ID, m_current_id);

    } else {
        // LinkManager doesn't allow to link data to instrument.
        setComboToIdentifier(dataLink); // Returning Combo selector to previous state
    }
}

//! Updates instrument selector for new instruments and their names.
//! Current selection will be preserved.

void RealDataPropertiesWidget::onInstrumentMapUpdate()
{
    setComboConnected(false);
    m_instrumentCombo->clear();
    m_instrumentCombo->addItems(m_linkManager->instrumentNames());
    int index = m_linkManager->instrumentComboIndex(m_current_id);
    if (index >= 0) {
        m_instrumentCombo->setCurrentIndex(index);
    } else {
        // instrument corresponding to m_current_id was deleted
        m_current_id = "";
        m_instrumentCombo->setCurrentIndex(0);
    }
    setComboConnected(true);
}

//! Updates instrument combo on link change of current RealDataItem.

void RealDataPropertiesWidget::onRealDataPropertyChanged(const QString& name)
{
    if (name == RealDataItem::P_INSTRUMENT_ID) {
        setComboToIdentifier(
            m_currentDataItem->getItemValue(RealDataItem::P_INSTRUMENT_ID).toString());
    }
}

//! Sets instrument combo selector to the state corresponding to given instrument identifier.

void RealDataPropertiesWidget::setComboToIdentifier(const QString& identifier)
{
    setComboConnected(false);
    m_current_id = identifier;
    int index = m_linkManager->instrumentComboIndex(identifier);
    ASSERT(index >= 0);
    m_instrumentCombo->setCurrentIndex(index);
    setComboConnected(true);
}

//! Sets connected/disconnected for instrument combo selector.

void RealDataPropertiesWidget::setComboConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_instrumentCombo, SIGNAL(currentIndexChanged(int)), this,
                SLOT(onInstrumentComboIndexChanged(int)));
    } else {
        disconnect(m_instrumentCombo, SIGNAL(currentIndexChanged(int)), this,
                   SLOT(onInstrumentComboIndexChanged(int)));
    }
}

//! Sets all widget's children enabled/disabled. When no RealDataItem selected all
//! will appear in gray.

void RealDataPropertiesWidget::setPropertiesEnabled(bool enabled)
{
    m_dataNameLabel->setEnabled(enabled);
    m_dataNameEdit->setEnabled(enabled);
    m_instrumentLabel->setEnabled(enabled);
    m_instrumentCombo->setEnabled(enabled);
    if (enabled == false) {
        m_dataNameEdit->clear();
        m_instrumentCombo->setCurrentIndex(0);
    }
}
