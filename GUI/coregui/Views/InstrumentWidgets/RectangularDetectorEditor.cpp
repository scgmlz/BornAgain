// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/RectangularDetectorEditor.cpp
//! @brief     Implements class RectangularDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InstrumentWidgets/RectangularDetectorEditor.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/RectangularDetectorItem.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include <QGridLayout>

RectangularDetectorEditor::RectangularDetectorEditor(QWidget* parent)
    : SessionItemWidget(parent), m_xAxisEditor(nullptr), m_yAxisEditor(nullptr),
      m_resolutionFunctionEditor(nullptr), m_alignmentEditor(nullptr), m_positionsEditor(nullptr),
      m_normalEditor(nullptr), m_directionEditor(nullptr), m_gridLayout(new QGridLayout)
{
    create_editors();

    auto mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void RectangularDetectorEditor::onPropertyChanged(const QString& propertyName)
{
    if (propertyName == RectangularDetectorItem::P_ALIGNMENT)
        init_alignment_editors();
}

void RectangularDetectorEditor::subscribeToItem()
{
    detectorItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);

    init_editors();
}

void RectangularDetectorEditor::unsubscribeFromItem()
{
    m_xAxisEditor->clearEditor();
    m_yAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();
    m_alignmentEditor->clearEditor();
    m_positionsEditor->clearEditor();
    m_normalEditor->clearEditor();
    m_directionEditor->clearEditor();
}

RectangularDetectorItem* RectangularDetectorEditor::detectorItem()
{
    auto result = dynamic_cast<RectangularDetectorItem*>(currentItem());
    ASSERT(result);
    return result;
}

void RectangularDetectorEditor::create_editors()
{
    // axes and resolution function editors
    m_xAxisEditor = new ComponentEditor(ComponentEditor::GroupWidget, "X axis");
    m_gridLayout->addWidget(m_xAxisEditor, 1, 0);

    m_yAxisEditor = new ComponentEditor(ComponentEditor::GroupWidget, "Y axis");
    m_gridLayout->addWidget(m_yAxisEditor, 1, 1);

    m_resolutionFunctionEditor =
        new ComponentEditor(ComponentEditor::GroupWidget, "Resolution function");
    m_gridLayout->addWidget(m_resolutionFunctionEditor, 1, 2);

    // alignment selector editors
    m_alignmentEditor = new ComponentEditor(ComponentEditor::PlainWidget);
    m_gridLayout->addWidget(m_alignmentEditor, 2, 0);

    // editors for various positions
    m_positionsEditor = new ComponentEditor(ComponentEditor::GroupWidget, "Positions [mm]");
    m_gridLayout->addWidget(m_positionsEditor, 3, 0);

    m_normalEditor = new ComponentEditor(ComponentEditor::GroupWidget, "Normal vector");
    m_gridLayout->addWidget(m_normalEditor, 3, 1);

    m_directionEditor = new ComponentEditor(ComponentEditor::GroupWidget, "Direction vector");
    m_gridLayout->addWidget(m_directionEditor, 3, 2);
}

void RectangularDetectorEditor::init_editors()
{
    m_xAxisEditor->clearEditor();
    auto xAxisItem = detectorItem()->getItem(RectangularDetectorItem::P_X_AXIS);
    m_xAxisEditor->setItem(xAxisItem);

    m_yAxisEditor->clearEditor();
    auto yAxisItem = detectorItem()->getItem(RectangularDetectorItem::P_Y_AXIS);
    m_yAxisEditor->setItem(yAxisItem);

    m_resolutionFunctionEditor->clearEditor();
    auto resFuncGroup = detectorItem()->getItem(RectangularDetectorItem::P_RESOLUTION_FUNCTION);
    m_resolutionFunctionEditor->setItem(resFuncGroup);

    m_alignmentEditor->clearEditor();
    m_alignmentEditor->setItem(detectorItem()->getItem(RectangularDetectorItem::P_ALIGNMENT));

    init_alignment_editors();
}

void RectangularDetectorEditor::init_alignment_editors()
{
    m_positionsEditor->clearEditor();
    m_positionsEditor->hide();

    m_normalEditor->clearEditor();
    m_normalEditor->hide();

    m_directionEditor->clearEditor();
    m_directionEditor->hide();

    ComboProperty alignment =
        detectorItem()->getItemValue(RectangularDetectorItem::P_ALIGNMENT).value<ComboProperty>();

    if (alignment.getValue() == "Generic") {
        m_positionsEditor->show();
        m_normalEditor->show();
        m_directionEditor->show();

        m_positionsEditor->addItem(detectorItem()->getItem(RectangularDetectorItem::P_U0));
        m_positionsEditor->addItem(detectorItem()->getItem(RectangularDetectorItem::P_V0));

        auto normalVectorItem = detectorItem()->getItem(RectangularDetectorItem::P_NORMAL);
        m_normalEditor->setItem(normalVectorItem);

        auto directionVectorItem = detectorItem()->getItem(RectangularDetectorItem::P_DIRECTION);
        m_directionEditor->setItem(directionVectorItem);

    } else if (alignment.getValue() == "Perpendicular to direct beam"
               || alignment.getValue() == "Perpendicular to reflected beam (dpos)") {
        m_positionsEditor->show();
        m_positionsEditor->addItem(detectorItem()->getItem(RectangularDetectorItem::P_DBEAM_U0));
        m_positionsEditor->addItem(detectorItem()->getItem(RectangularDetectorItem::P_DBEAM_V0));
        m_positionsEditor->addItem(detectorItem()->getItem(RectangularDetectorItem::P_DISTANCE));

    } else if (alignment.getValue() == "Perpendicular to sample x-axis"
               || alignment.getValue() == "Perpendicular to reflected beam") {
        m_positionsEditor->show();

        m_positionsEditor->addItem(detectorItem()->getItem(RectangularDetectorItem::P_U0));
        m_positionsEditor->addItem(detectorItem()->getItem(RectangularDetectorItem::P_V0));
        m_positionsEditor->addItem(detectorItem()->getItem(RectangularDetectorItem::P_DISTANCE));
    }
}
