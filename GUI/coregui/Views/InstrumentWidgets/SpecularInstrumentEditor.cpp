// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SpecularInstrumentEditor.cpp
//! @brief     Implements class SpecularInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/SpecularInstrumentEditor.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Views/CommonWidgets/ColumnResizer.h"
#include "GUI/coregui/Views/InstrumentWidgets/EnvironmentEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/PolarizationAnalysisEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/SpecularBeamEditor.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QVBoxLayout>

SpecularInstrumentEditor::SpecularInstrumentEditor(QWidget* parent)
    : SessionItemWidget(parent), m_columnResizer(new ColumnResizer(this)),
      m_beamEditor(new SpecularBeamEditor(m_columnResizer)),
      m_environmentEditor(new EnvironmentEditor(m_columnResizer)),
      m_polarizationAnalysisEditor(nullptr)
{
    auto mainLayout = new QVBoxLayout;

    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_beamEditor, "Beam parameters"));
    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_environmentEditor, "Environment",
                                                          /*expanded*/ false));
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void SpecularInstrumentEditor::subscribeToItem()
{
    m_beamEditor->setItem(instrumentItem());
    m_environmentEditor->setItem(instrumentItem());
    //    m_polarizationAnalysisEditor->setItem(instrumentItem());
}

SpecularInstrumentItem* SpecularInstrumentEditor::instrumentItem()
{
    auto result = dynamic_cast<SpecularInstrumentItem*>(currentItem());
    ASSERT(result);
    return result;
}
