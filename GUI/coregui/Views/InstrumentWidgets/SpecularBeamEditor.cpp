// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SpecularBeamEditor.cpp
//! @brief     Defines class SpecularBeamEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/SpecularBeamEditor.h"
#include "GUI/coregui/Models/BeamDistributionItem.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Views/CommonWidgets/ColumnResizer.h"
#include "GUI/coregui/Views/InfoWidgets/DistributionDialog.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include "GUI/coregui/utils/LayoutUtils.h"
#include <QGridLayout>
#include <QGroupBox>

namespace
{
const QString wavelength_title("Wavelength [nm]");
const QString inclination_title("Inclination angles [deg]");
const QString footprint_title("Footprint correction");
const QString polarization_title("Polarization (Bloch vector)");
} // namespace

SpecularBeamEditor::SpecularBeamEditor(ColumnResizer* columnResizer, QWidget* parent)
    : SessionItemWidget(parent), m_columnResizer(columnResizer),
      m_intensityEditor(new ComponentEditor(ComponentEditor::PlainWidget)),
      m_wavelengthEditor(new ComponentEditor(ComponentEditor::InfoWidget, wavelength_title)),
      m_inclinationEditor(new ComponentEditor(ComponentEditor::InfoWidget, inclination_title)),
      m_footprint_editor(new ComponentEditor(ComponentEditor::GroupWidget, footprint_title)),
      m_gridLayout(new QGridLayout)
{
    m_gridLayout->addWidget(m_intensityEditor, 0, 0);
    m_gridLayout->addWidget(m_wavelengthEditor, 1, 0);
    m_gridLayout->addWidget(m_inclinationEditor, 1, 1);
    m_gridLayout->addWidget(LayoutUtils::placeHolder(), 1, 2);
    m_gridLayout->addWidget(m_footprint_editor, 2, 0);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(m_wavelengthEditor, &ComponentEditor::dialogRequest, this,
            &SpecularBeamEditor::onDialogRequest);
    connect(m_inclinationEditor, &ComponentEditor::dialogRequest, this,
            &SpecularBeamEditor::onDialogRequest);

    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 0);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 1);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 2);
}

void SpecularBeamEditor::subscribeToItem()
{
    const auto beam_item = instrumentItem()->beamItem();
    ASSERT(beam_item);

    m_intensityEditor->setItem(beam_item->getItem(SpecularBeamItem::P_INTENSITY));

    auto wavelengthItem = beam_item->getItem(SpecularBeamItem::P_WAVELENGTH);
    m_wavelengthEditor->setItem(wavelengthItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    auto inclinationItem = beam_item->getItem(SpecularBeamItem::P_INCLINATION_ANGLE);
    m_inclinationEditor->setItem(
        inclinationItem->getItem(SpecularBeamInclinationItem::P_DISTRIBUTION));
    m_inclinationEditor->addItem(
        inclinationItem->getItem(SpecularBeamInclinationItem::P_ALPHA_AXIS));

    m_footprint_editor->setItem(beam_item->getItem(SpecularBeamItem::P_FOOPTPRINT));
}

void SpecularBeamEditor::unsubscribeFromItem()
{
    m_intensityEditor->clearEditor();
    m_wavelengthEditor->clearEditor();
    m_inclinationEditor->clearEditor();
    m_footprint_editor->clearEditor();
}

SpecularInstrumentItem* SpecularBeamEditor::instrumentItem()
{
    auto result = dynamic_cast<SpecularInstrumentItem*>(currentItem());
    ASSERT(result);
    return result;
}

void SpecularBeamEditor::onDialogRequest(SessionItem* item, const QString& name)
{
    if (!item)
        return;

    auto dialog = new DistributionDialog(this);
    dialog->setItem(item);
    dialog->setNameOfEditor(name);
    dialog->show();
}
