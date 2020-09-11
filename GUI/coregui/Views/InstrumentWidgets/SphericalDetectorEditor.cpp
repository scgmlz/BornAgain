// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SphericalDetectorEditor.cpp
//! @brief     Implement class SphericalDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/SphericalDetectorEditor.h"
#include "GUI/coregui/Models/SphericalDetectorItem.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include <QGridLayout>

namespace
{
const QString phi_axis_title = "Phi axis";
const QString alpha_axis_title = "Alpha axis";
const QString resolution_title = "Resolution function";
const QString polarization_title = "Analyzer orientation";
} // namespace

SphericalDetectorEditor::SphericalDetectorEditor(QWidget* parent)
    : SessionItemWidget(parent),
      m_phiAxisEditor(new ComponentEditor(ComponentEditor::GroupWidget, phi_axis_title)),
      m_alphaAxisEditor(new ComponentEditor(ComponentEditor::GroupWidget, alpha_axis_title)),
      m_resolutionFunctionEditor(
          new ComponentEditor(ComponentEditor::GroupWidget, resolution_title)),
      m_gridLayout(new QGridLayout)
{
    m_gridLayout->addWidget(m_phiAxisEditor, 1, 0);
    m_gridLayout->addWidget(m_alphaAxisEditor, 1, 1);
    m_gridLayout->addWidget(m_resolutionFunctionEditor, 1, 2);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void SphericalDetectorEditor::subscribeToItem()
{
    auto phiAxisItem = detectorItem()->getItem(SphericalDetectorItem::P_PHI_AXIS);
    m_phiAxisEditor->setItem(phiAxisItem);

    auto alphaAxisItem = detectorItem()->getItem(SphericalDetectorItem::P_ALPHA_AXIS);
    m_alphaAxisEditor->setItem(alphaAxisItem);

    auto resFuncGroup = detectorItem()->getItem(SphericalDetectorItem::P_RESOLUTION_FUNCTION);
    m_resolutionFunctionEditor->setItem(resFuncGroup);
}

void SphericalDetectorEditor::unsubscribeFromItem()
{
    m_phiAxisEditor->clearEditor();
    m_alphaAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();
}

SphericalDetectorItem* SphericalDetectorEditor::detectorItem()
{
    auto result = dynamic_cast<SphericalDetectorItem*>(currentItem());
    ASSERT(result);
    return result;
}
