// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationDataSelectorWidget.cpp
//! @brief     Implements class SimulationDataSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SimulationWidgets/SimulationDataSelectorWidget.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/ModelUtils.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Models/SampleModel.h"
#include <QComboBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

namespace
{
const QString select_instrument_tooltip =
    "Select Instrument to simulate from those defined in Instrument View";
const QString select_sample_tooltip = "Select Sample to simulate from those defined in Sample View";
const QString select_realdata_tooltip = "Select real data to use during the fitting. \n"
                                        "If None is selected, the standard simulation will be run.";
} // namespace

SimulationDataSelectorWidget::SimulationDataSelectorWidget(QWidget* parent)
    : QWidget(parent), m_instrumentCombo(new QComboBox), m_sampleCombo(new QComboBox),
      m_realDataCombo(new QComboBox), m_applicationModels(0)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    // selection of input parameters
    QGroupBox* groupBox = new QGroupBox("Data selection");

    QLabel* instrumentSelectionLabel = new QLabel("Select Instrument:");
    instrumentSelectionLabel->setToolTip(select_instrument_tooltip);
    m_instrumentCombo->setToolTip(select_instrument_tooltip);
    m_instrumentCombo->setAttribute(Qt::WA_MacShowFocusRect, false);

    QLabel* sampleSelectionLabel = new QLabel("Select Sample:");
    sampleSelectionLabel->setToolTip(select_sample_tooltip);
    m_sampleCombo->setToolTip(select_sample_tooltip);

    QLabel* readDataSelectionLabel = new QLabel("Select Real Data:");
    readDataSelectionLabel->setToolTip(select_realdata_tooltip);
    m_realDataCombo->setToolTip(select_realdata_tooltip);

    // layout
    QGridLayout* dataSelectionLayout = new QGridLayout;
    dataSelectionLayout->setMargin(12); // to match margin in SimulationOptionsWidget

    dataSelectionLayout->addWidget(instrumentSelectionLabel, 0, 0);
    dataSelectionLayout->addWidget(m_instrumentCombo, 0, 1);
    dataSelectionLayout->addWidget(sampleSelectionLabel, 1, 0);
    dataSelectionLayout->addWidget(m_sampleCombo, 1, 1);
    dataSelectionLayout->addWidget(readDataSelectionLabel, 2, 0);
    dataSelectionLayout->addWidget(m_realDataCombo, 2, 1);
    groupBox->setLayout(dataSelectionLayout);

    mainLayout->addWidget(groupBox);
    setLayout(mainLayout);
}

void SimulationDataSelectorWidget::setApplicationModels(ApplicationModels* applicationModels)
{
    m_applicationModels = applicationModels;
    updateViewElements();
}

//! Returns selected MultiLayerItem taking into account that there might be several
//! multilayers with same name.

const MultiLayerItem* SimulationDataSelectorWidget::selectedMultiLayerItem() const
{
    auto items = m_applicationModels->sampleModel()->topItems<MultiLayerItem>();
    if (items.isEmpty())
        return nullptr;
    return dynamic_cast<const MultiLayerItem*>(items.at(selectedSampleIndex()));
}

//! Returns selected InstrumentItem taking into account that there might be several
//! instruments with same name.

const InstrumentItem* SimulationDataSelectorWidget::selectedInstrumentItem() const
{
    auto items = m_applicationModels->instrumentModel()->topItems<InstrumentItem>();
    return items.isEmpty() ? nullptr : items.at(selectedInstrumentIndex());
}

//! Returns selected InstrumentItem taking into account that there might be several
//! instruments with same name.

const RealDataItem* SimulationDataSelectorWidget::selectedRealDataItem() const
{
    auto items = m_applicationModels->realDataModel()->topItems();
    if (items.isEmpty())
        return nullptr;
    if (selectedRealDataIndex() >= 0 && selectedRealDataIndex() < items.size()) {
        return dynamic_cast<const RealDataItem*>(items.at(selectedRealDataIndex()));
    }
    return nullptr;
}

void SimulationDataSelectorWidget::updateViewElements()
{
    ASSERT(m_applicationModels);
    updateSelection(m_instrumentCombo,
                    ModelUtils::topItemNames(m_applicationModels->instrumentModel()));
    updateSelection(m_sampleCombo,
                    ModelUtils::topItemNames(m_applicationModels->sampleModel(), "MultiLayer"));
    updateSelection(m_realDataCombo, ModelUtils::topItemNames(m_applicationModels->realDataModel()),
                    true);
}

int SimulationDataSelectorWidget::selectedInstrumentIndex() const
{
    return m_instrumentCombo->currentIndex();
}

int SimulationDataSelectorWidget::selectedSampleIndex() const
{
    return m_sampleCombo->currentIndex();
}

int SimulationDataSelectorWidget::selectedRealDataIndex() const
{
    // -1 because m_realDataCombo always contains "None" as a first entry
    return m_realDataCombo->currentIndex() - 1;
}

//! Updates selection combo with string list while preserving previous selection.
//! If allow_none == true, additional "None" item will be added to the combo.

void SimulationDataSelectorWidget::updateSelection(QComboBox* comboBox, QStringList itemList,
                                                   bool allow_none)
{
    QString previousItem = comboBox->currentText();

    comboBox->clear();
    if (itemList.isEmpty()) {
        comboBox->setEnabled(false);
        comboBox->addItem("Not yet defined");
    } else {
        comboBox->setEnabled(true);
        // qSort(itemList.begin(), itemList.end()); // uncomment, if we want alphabetical order
        if (allow_none)
            itemList.insert(-1, "None");
        comboBox->addItems(itemList);
        if (itemList.contains(previousItem))
            comboBox->setCurrentIndex(itemList.indexOf(previousItem));
    }
}
