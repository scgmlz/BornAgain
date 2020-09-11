// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/PolarizationAnalysisEditor.cpp
//! @brief     Implements class PolarizationAnalysisEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/PolarizationAnalysisEditor.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/DetectorItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Views/CommonWidgets/ColumnResizer.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include "GUI/coregui/utils/LayoutUtils.h"
#include <QGridLayout>
#include <QSpacerItem>

namespace
{
const QString beam_pol_title("Polarization (Bloch vector)");
const QString analyzer_orientation_title = "Analyzer orientation";
const QString analyzer_properties_title = "Analyzer properties";
} // namespace

PolarizationAnalysisEditor::PolarizationAnalysisEditor(ColumnResizer* columnResizer,
                                                       QWidget* parent)
    : SessionItemWidget(parent), m_columnResizer(columnResizer),
      m_polarizationEditor(new ComponentEditor(ComponentEditor::GroupWidget, beam_pol_title)),
      m_analyserDirectionEditor(
          new ComponentEditor(ComponentEditor::GroupWidget, analyzer_orientation_title)),
      m_analyserPropertiesEditor(
          new ComponentEditor(ComponentEditor::GroupWidget, analyzer_properties_title)),
      m_gridLayout(new QGridLayout)
{
    m_gridLayout->addWidget(m_polarizationEditor, 0, 0);
    m_gridLayout->addWidget(m_analyserDirectionEditor, 0, 1);
    m_gridLayout->addWidget(m_analyserPropertiesEditor, 0, 2);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 0);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 1);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 2);
}

void PolarizationAnalysisEditor::subscribeToItem()
{
    m_polarizationEditor->setItem(beamItem()->getItem(BeamItem::P_POLARIZATION));

    currentItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == Instrument2DItem::P_DETECTOR)
                updateAnalyserEditor();
        },
        this);

    updateAnalyserEditor();
}

void PolarizationAnalysisEditor::unsubscribeFromItem()
{
    m_polarizationEditor->clearEditor();
    m_analyserDirectionEditor->clearEditor();
    m_analyserPropertiesEditor->clearEditor();
}

GISASInstrumentItem* PolarizationAnalysisEditor::instrumentItem()
{
    auto result = dynamic_cast<GISASInstrumentItem*>(currentItem());
    ASSERT(result);
    return result;
}

BeamItem* PolarizationAnalysisEditor::beamItem()
{
    return instrumentItem()->beamItem();
}

DetectorItem* PolarizationAnalysisEditor::detectorItem()
{
    return instrumentItem()->detectorItem();
}

//! Updates analyser editor to display properties of currently selected detector
//! (spherical/rectangular).

void PolarizationAnalysisEditor::updateAnalyserEditor()
{
    m_analyserDirectionEditor->clearEditor();
    m_analyserPropertiesEditor->clearEditor();
    m_analyserDirectionEditor->addItem(detectorItem()->getItem(DetectorItem::P_ANALYZER_DIRECTION));
    m_analyserPropertiesEditor->addItem(
        detectorItem()->getItem(DetectorItem::P_ANALYZER_EFFICIENCY));
    m_analyserPropertiesEditor->addItem(
        detectorItem()->getItem(DetectorItem::P_ANALYZER_TOTAL_TRANSMISSION));
}
