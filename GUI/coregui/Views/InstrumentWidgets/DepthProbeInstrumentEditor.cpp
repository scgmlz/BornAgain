// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DepthProbeInstrumentEditor.cpp
//! @brief     Implements class DepthProbeInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/DepthProbeInstrumentEditor.h"
#include "GUI/coregui/Models/BeamDistributionItem.h"
#include "GUI/coregui/Models/BeamItems.h"
#include "GUI/coregui/Models/DepthProbeInstrumentItem.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Views/InfoWidgets/DistributionDialog.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include "GUI/coregui/utils/LayoutUtils.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QGridLayout>
#include <QVBoxLayout>

namespace
{
const QString wavelength_title("Wavelength [nm]");
const QString inclination_title("Inclination angles [deg]");
const QString depth_axis_title("Depth axis [nm]");
} // namespace

DepthProbeInstrumentEditor::DepthProbeInstrumentEditor(QWidget* parent)
    : SessionItemWidget(parent),
      m_wavelengthEditor(new ComponentEditor(ComponentEditor::InfoWidget, wavelength_title)),
      m_inclinationEditor(new ComponentEditor(ComponentEditor::InfoWidget, inclination_title)),
      m_depthAxisEditor(new ComponentEditor(ComponentEditor::InfoWidget, depth_axis_title)),
      m_gridLayout(new QGridLayout)
{
    m_gridLayout->addWidget(m_wavelengthEditor, 1, 0);
    m_gridLayout->addWidget(m_inclinationEditor, 1, 1);
    m_gridLayout->addWidget(m_depthAxisEditor, 1, 2);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(StyleUtils::createDetailsWidget(m_gridLayout, "Parameters"));
    mainLayout->addStretch();
    setLayout(mainLayout);

    connect(m_wavelengthEditor, &ComponentEditor::dialogRequest, this,
            &DepthProbeInstrumentEditor::onDialogRequest);
    connect(m_inclinationEditor, &ComponentEditor::dialogRequest, this,
            &DepthProbeInstrumentEditor::onDialogRequest);
}

void DepthProbeInstrumentEditor::subscribeToItem()
{
    const auto beam_item = instrumentItem()->getItem(DepthProbeInstrumentItem::P_BEAM);

    auto wavelengthItem = beam_item->getItem(SpecularBeamItem::P_WAVELENGTH);
    m_wavelengthEditor->setItem(wavelengthItem->getItem(BeamDistributionItem::P_DISTRIBUTION));

    auto inclinationItem = beam_item->getItem(SpecularBeamItem::P_INCLINATION_ANGLE);
    m_inclinationEditor->setItem(
        inclinationItem->getItem(SpecularBeamInclinationItem::P_DISTRIBUTION));
    m_inclinationEditor->addItem(
        inclinationItem->getItem(SpecularBeamInclinationItem::P_ALPHA_AXIS));
    m_depthAxisEditor->setItem(instrumentItem()->getItem(DepthProbeInstrumentItem::P_Z_AXIS));
}

void DepthProbeInstrumentEditor::unsubscribeFromItem()
{
    m_wavelengthEditor->clearEditor();
    m_inclinationEditor->clearEditor();
}

DepthProbeInstrumentItem* DepthProbeInstrumentEditor::instrumentItem()
{
    return dynamic_cast<DepthProbeInstrumentItem*>(currentItem());
}

void DepthProbeInstrumentEditor::onDialogRequest(SessionItem* item, const QString& name)
{
    if (!item)
        return;

    auto dialog = new DistributionDialog(this);
    dialog->setItem(item);
    dialog->setNameOfEditor(name);
    dialog->show();
}
