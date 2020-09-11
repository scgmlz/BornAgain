// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/OffSpecBeamEditor.cpp
//! @brief     Implements class OffSpecBeamEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/OffSpecBeamEditor.h"
#include "GUI/coregui/Models/BeamDistributionItem.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Views/CommonWidgets/ColumnResizer.h"
#include "GUI/coregui/Views/InfoWidgets/DistributionDialog.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include <QGridLayout>
#include <QGroupBox>

namespace
{
const QString wavelength_title("Wavelength [nm]");
const QString inclination_title("Inclination angle [deg]");
const QString azimuthal_title("Azimuthal angle [deg]");
const QString polarization_title("Polarization (Bloch vector)");
} // namespace

OffSpecBeamEditor::OffSpecBeamEditor(ColumnResizer* columnResizer, QWidget* parent)
    : SessionItemWidget(parent), m_columnResizer(columnResizer),
      m_intensityEditor(new ComponentEditor(ComponentEditor::PlainWidget)),
      m_wavelengthEditor(new ComponentEditor(ComponentEditor::InfoWidget, wavelength_title)),
      m_inclinationEditor(new ComponentEditor(ComponentEditor::GroupWidget, inclination_title)),
      m_azimuthalEditor(new ComponentEditor(ComponentEditor::InfoWidget, azimuthal_title)),
      m_gridLayout(new QGridLayout)
{
    m_gridLayout->addWidget(m_intensityEditor, 0, 0);
    m_gridLayout->addWidget(m_wavelengthEditor, 1, 0);
    m_gridLayout->addWidget(m_inclinationEditor, 1, 1);
    m_gridLayout->addWidget(m_azimuthalEditor, 1, 2);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(m_wavelengthEditor, &ComponentEditor::dialogRequest, this,
            &OffSpecBeamEditor::onDialogRequest);
    connect(m_inclinationEditor, &ComponentEditor::dialogRequest, this,
            &OffSpecBeamEditor::onDialogRequest);
    connect(m_azimuthalEditor, &ComponentEditor::dialogRequest, this,
            &OffSpecBeamEditor::onDialogRequest);

    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 0);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 1);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 2);
}

void OffSpecBeamEditor::subscribeToItem()
{
    m_intensityEditor->setItem(beamItem()->getItem(BeamItem::P_INTENSITY));

    auto wavelengthItem = beamItem()->getItem(BeamItem::P_WAVELENGTH);
    m_wavelengthEditor->setItem(wavelengthItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    auto inclinationItem = instrumentItem()->getItem(OffSpecInstrumentItem::P_ALPHA_AXIS);
    m_inclinationEditor->setItem(inclinationItem);

    auto azimuthalItem = beamItem()->getItem(BeamItem::P_AZIMUTHAL_ANGLE);
    m_azimuthalEditor->setItem(azimuthalItem->getItem(BeamDistributionItem::P_DISTRIBUTION));
}

void OffSpecBeamEditor::unsubscribeFromItem()
{
    m_intensityEditor->clearEditor();
    m_wavelengthEditor->clearEditor();
    m_inclinationEditor->clearEditor();
    m_azimuthalEditor->clearEditor();
}

OffSpecInstrumentItem* OffSpecBeamEditor::instrumentItem()
{
    auto result = dynamic_cast<OffSpecInstrumentItem*>(currentItem());
    ASSERT(result);
    return result;
}

BeamItem* OffSpecBeamEditor::beamItem()
{
    return instrumentItem()->beamItem();
}

void OffSpecBeamEditor::onDialogRequest(SessionItem* item, const QString& name)
{
    if (!item)
        return;

    auto dialog = new DistributionDialog(this);
    dialog->setItem(item);
    dialog->setNameOfEditor(name);
    dialog->show();
}
