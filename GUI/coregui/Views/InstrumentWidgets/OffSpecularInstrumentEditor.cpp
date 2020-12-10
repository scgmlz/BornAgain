//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/OffSpecularInstrumentEditor.cpp
//! @brief     Implements class OffSpecularInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/InstrumentWidgets/OffSpecularInstrumentEditor.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Views/CommonWidgets/ColumnResizer.h"
#include "GUI/coregui/Views/InstrumentWidgets/EnvironmentEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/GISASDetectorEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/OffSpecularBeamEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/PolarizationAnalysisEditor.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QVBoxLayout>

OffSpecularInstrumentEditor::OffSpecularInstrumentEditor(QWidget* parent)
    : SessionItemWidget(parent)
    , m_columnResizer(new ColumnResizer(this))
    , m_beamEditor(new OffSpecularBeamEditor(m_columnResizer))
    , m_detectorEditor(new GISASDetectorEditor)
    // temporary switched off to avoid memory leakage
    //, m_environmentEditor(new EnvironmentEditor(m_columnResizer))
    //, m_polarizationAnalysisEditor(new PolarizationAnalysisEditor(m_columnResizer))
    , m_environmentEditor(nullptr)
    , m_polarizationAnalysisEditor(nullptr) {
    auto mainLayout = new QVBoxLayout;

    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_beamEditor, "Beam parameters"));
    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_detectorEditor, "Detector parameters"));
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void OffSpecularInstrumentEditor::subscribeToItem() {
    m_beamEditor->setItem(instrumentItem());
    m_detectorEditor->setItem(instrumentItem());
    //    m_environmentEditor->setItem(instrumentItem());
    //    m_polarizationAnalysisEditor->setItem(instrumentItem());
}

OffSpecularInstrumentItem* OffSpecularInstrumentEditor::instrumentItem() {
    auto result = dynamic_cast<OffSpecularInstrumentItem*>(currentItem());
    ASSERT(result);
    return result;
}
