// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASBeamEditor.cpp
//! @brief     Implements class GISASBeamEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/GISASBeamEditor.h"
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

GISASBeamEditor::GISASBeamEditor(ColumnResizer* columnResizer, QWidget* parent)
    : SessionItemWidget(parent), m_columnResizer(columnResizer),
      m_intensityEditor(new ComponentEditor(ComponentEditor::PlainWidget)),
      m_wavelengthEditor(new ComponentEditor(ComponentEditor::InfoWidget, wavelength_title)),
      m_inclinationEditor(new ComponentEditor(ComponentEditor::InfoWidget, inclination_title)),
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
            &GISASBeamEditor::onDialogRequest);
    connect(m_inclinationEditor, &ComponentEditor::dialogRequest, this,
            &GISASBeamEditor::onDialogRequest);
    connect(m_azimuthalEditor, &ComponentEditor::dialogRequest, this,
            &GISASBeamEditor::onDialogRequest);

    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 0);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 1);
    m_columnResizer->addWidgetsFromGridLayout(m_gridLayout, 2);
}

void GISASBeamEditor::subscribeToItem()
{
    m_intensityEditor->setItem(beamItem()->getItem(BeamItem::P_INTENSITY));

    auto wavelengthItem = beamItem()->getItem(BeamItem::P_WAVELENGTH);
    m_wavelengthEditor->setItem(wavelengthItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    auto inclinationItem = beamItem()->getItem(BeamItem::P_INCLINATION_ANGLE);
    m_inclinationEditor->setItem(inclinationItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    auto azimuthalItem = beamItem()->getItem(BeamItem::P_AZIMUTHAL_ANGLE);
    m_azimuthalEditor->setItem(azimuthalItem->getItem(BeamDistributionItem::P_DISTRIBUTION));
}

void GISASBeamEditor::unsubscribeFromItem()
{
    m_intensityEditor->clearEditor();
    m_wavelengthEditor->clearEditor();
    m_inclinationEditor->clearEditor();
    m_azimuthalEditor->clearEditor();
}

GISASInstrumentItem* GISASBeamEditor::instrumentItem()
{
    auto result = dynamic_cast<GISASInstrumentItem*>(currentItem());
    ASSERT(result);
    return result;
}

BeamItem* GISASBeamEditor::beamItem()
{
    return instrumentItem()->beamItem();
}

void GISASBeamEditor::onDialogRequest(SessionItem* item, const QString& name)
{
    if (!item)
        return;

    auto dialog = new DistributionDialog(this);
    dialog->setItem(item);
    dialog->setNameOfEditor(name);
    dialog->show();
}
