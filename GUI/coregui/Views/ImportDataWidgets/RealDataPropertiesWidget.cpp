//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataPropertiesWidget.cpp
//! @brief     Implements class RealDataPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/ImportDataWidgets/RealDataPropertiesWidget.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/ImportDataWidgets/LinkInstrumentManager.h"
#include <QComboBox>
#include <QDataWidgetMapper>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

RealDataPropertiesWidget::RealDataPropertiesWidget(QWidget* parent)
    : QWidget(parent)
    , m_linkManager(new LinkInstrumentManager(this))
    , m_instrumentModel(nullptr)
    , m_instrumentLabel(new QLabel("Linked instrument"))
    , m_instrumentCombo(new QComboBox)
    , m_currentDataItem(nullptr)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle("RealDataPropertiesWidget");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setMargin(5);
    mainLayout->setSpacing(2);

    m_instrumentCombo->setToolTip("Select instrument to link with real data");

    mainLayout->addWidget(m_instrumentLabel);
    mainLayout->addWidget(m_instrumentCombo);

    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(m_instrumentCombo,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
            &RealDataPropertiesWidget::onInstrumentComboIndexChanged);

    connect(m_linkManager, &LinkInstrumentManager::instrumentMapUpdated, this,
            &RealDataPropertiesWidget::updateInstrumentCombo);

    setPropertiesEnabled(false);
}

//! Sets models to underlying link manager.

void RealDataPropertiesWidget::setModels(InstrumentModel* instrumentModel,
                                         RealDataModel* realDataModel)
{
    m_instrumentModel = instrumentModel;
    m_linkManager->setModels(instrumentModel, realDataModel);
    updateInstrumentCombo();
}

//! Set current RealDataItem to display in instrument selector.

void RealDataPropertiesWidget::setItem(SessionItem* item)
{
    if (item == m_currentDataItem)
        return;

    if (m_currentDataItem)
        m_currentDataItem->mapper()->unsubscribe(this);

    m_currentDataItem = dynamic_cast<RealDataItem*>(item);

    setPropertiesEnabled(m_currentDataItem != nullptr);

    if (!m_currentDataItem)
        return;

    m_currentDataItem->mapper()->setOnPropertyChange(
        [this](const QString& name) { onRealDataPropertyChanged(name); }, this);

    m_currentDataItem->mapper()->setOnItemDestroy(
        [this](SessionItem*) { m_currentDataItem = nullptr; }, this);

    // Set combo selector to show linked instrument
    setComboToIdentifier(m_currentDataItem->instrumentId());
}

//! Processes user interaction with instrument selector combo. If there is realDataItem,
//! it will be linked with selected instrument.

void RealDataPropertiesWidget::onInstrumentComboIndexChanged(int index)
{
    if (!m_currentDataItem)
        return;

    const QString newSelectedInstrumentId = m_instrumentCombo->currentData().toString();

    if (newSelectedInstrumentId == m_currentDataItem->instrumentId())
        return;

    if (m_linkManager->canLinkDataToInstrument(m_currentDataItem, newSelectedInstrumentId))
        m_currentDataItem->setInstrumentId(newSelectedInstrumentId);
    else
        // Linking was impossible or denied. Set combo to previous state
        setComboToIdentifier(m_currentDataItem->instrumentId());
}

//! Updates instrument selector for new instruments and their names.
//! Current selection will be preserved.

void RealDataPropertiesWidget::updateInstrumentCombo()
{
    QString currentId = m_currentDataItem != nullptr ? m_currentDataItem->instrumentId() : "";

    QSignalBlocker b(m_instrumentCombo);

    m_instrumentCombo->clear();

    // fill the combo. Userdata contains instrument's uid
    m_instrumentCombo->addItem("Undefined", ""); // undefined instrument
    for (auto instrumentItem : m_instrumentModel->instrumentItems())
        m_instrumentCombo->addItem(instrumentItem->itemName(), instrumentItem->id());

    const int index = m_instrumentCombo->findData(currentId);
    if (index >= 0)
        m_instrumentCombo->setCurrentIndex(index);
    else
        // instrument selected in data item was deleted
        m_instrumentCombo->setCurrentIndex(0);
}

//! Updates instrument combo on link change of current RealDataItem.

void RealDataPropertiesWidget::onRealDataPropertyChanged(const QString& name)
{
    if (name == RealDataItem::P_INSTRUMENT_ID)
        setComboToIdentifier(m_currentDataItem->instrumentId());
}

//! Sets instrument combo selector to the state corresponding to given instrument identifier.

void RealDataPropertiesWidget::setComboToIdentifier(const QString& instrumentId)
{
    const int index = m_instrumentCombo->findData(instrumentId);
    ASSERT(index >= 0);

    QSignalBlocker b(m_instrumentCombo);
    m_instrumentCombo->setCurrentIndex(index);
}

//! Sets all widget's children enabled/disabled. When no RealDataItem selected all
//! will appear in gray.

void RealDataPropertiesWidget::setPropertiesEnabled(bool enabled)
{
    m_instrumentLabel->setEnabled(enabled);
    m_instrumentCombo->setEnabled(enabled);
    if (!enabled)
        m_instrumentCombo->setCurrentIndex(0);
}
