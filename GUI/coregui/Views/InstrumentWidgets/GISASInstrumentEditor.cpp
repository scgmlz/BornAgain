// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASInstrumentEditor.cpp
//! @brief     Implements class GISASInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/GISASInstrumentEditor.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Views/CommonWidgets/ColumnResizer.h"
#include "GUI/coregui/Views/InstrumentWidgets/EnvironmentEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/GISASBeamEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/GISASDetectorEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/PolarizationAnalysisEditor.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QVBoxLayout>

GISASInstrumentEditor::GISASInstrumentEditor(QWidget* parent)
    : SessionItemWidget(parent), m_columnResizer(new ColumnResizer(this)),
      m_beamEditor(new GISASBeamEditor(m_columnResizer)), m_detectorEditor(new GISASDetectorEditor),
      m_environmentEditor(new EnvironmentEditor(m_columnResizer)),
      m_polarizationAnalysisEditor(new PolarizationAnalysisEditor(m_columnResizer))
{
    auto mainLayout = new QVBoxLayout;

    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_beamEditor, "Beam parameters"));
    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_detectorEditor, "Detector parameters"));
    mainLayout->addWidget(StyleUtils::createDetailsWidget(
        m_polarizationAnalysisEditor, "Polarization analysis", /*expanded*/ false));
    mainLayout->addWidget(
        StyleUtils::createDetailsWidget(m_environmentEditor, "Environment", /*expanded*/ false));
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void GISASInstrumentEditor::subscribeToItem()
{
    m_beamEditor->setItem(instrumentItem());
    m_detectorEditor->setItem(instrumentItem());
    m_environmentEditor->setItem(instrumentItem());
    m_polarizationAnalysisEditor->setItem(instrumentItem());
}

GISASInstrumentItem* GISASInstrumentEditor::instrumentItem()
{
    auto result = dynamic_cast<GISASInstrumentItem*>(currentItem());
    ASSERT(result);
    return result;
}
