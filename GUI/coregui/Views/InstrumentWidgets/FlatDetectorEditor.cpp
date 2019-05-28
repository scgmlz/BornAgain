// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/FlatDetectorEditor.cpp
//! @brief     Implements class FlatDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FlatDetectorEditor.h"
#include "FlatDetectorItem.h"
#include "ComponentEditor.h"
#include "ComboProperty.h"
#include <QGridLayout>

FlatDetectorEditor::FlatDetectorEditor(QWidget* parent)
    : SessionItemWidget(parent)
    , m_xAxisEditor(nullptr)
    , m_yAxisEditor(nullptr)
    , m_resolutionFunctionEditor(nullptr)
    , m_alignmentEditor(nullptr)
    , m_positionsEditor(nullptr)
    , m_normalEditor(nullptr)
    , m_directionEditor(nullptr)
    , m_gridLayout(new QGridLayout)
{
    create_editors();

    auto mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void FlatDetectorEditor::onPropertyChanged(const QString& propertyName)
{
    if (propertyName == FlatDetectorItem::P_ALIGNMENT)
        init_alignment_editors();
}

void FlatDetectorEditor::subscribeToItem()
{
    detectorItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onPropertyChanged(name); }, this);

    init_editors();
}

void FlatDetectorEditor::unsubscribeFromItem()
{
    m_xAxisEditor->clearEditor();
    m_yAxisEditor->clearEditor();
    m_resolutionFunctionEditor->clearEditor();
    m_alignmentEditor->clearEditor();
    m_positionsEditor->clearEditor();
    m_normalEditor->clearEditor();
    m_directionEditor->clearEditor();
}

FlatDetectorItem* FlatDetectorEditor::detectorItem()
{
    auto result = dynamic_cast<FlatDetectorItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

void FlatDetectorEditor::create_editors()
{
    // axes and resolution function editors
    m_xAxisEditor = new ComponentEditor(ComponentEditor::GroupWidget, "X axis");
    m_gridLayout->addWidget(m_xAxisEditor, 1, 0);

    m_yAxisEditor = new ComponentEditor(ComponentEditor::GroupWidget, "Y axis");
    m_gridLayout->addWidget(m_yAxisEditor, 1, 1);

    m_resolutionFunctionEditor = new ComponentEditor(ComponentEditor::GroupWidget, "Resolution function");
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

void FlatDetectorEditor::init_editors()
{
    m_xAxisEditor->clearEditor();
    auto xAxisItem = detectorItem()->getItem(FlatDetectorItem::P_X_AXIS);
    m_xAxisEditor->setItem(xAxisItem);

    m_yAxisEditor->clearEditor();
    auto yAxisItem = detectorItem()->getItem(FlatDetectorItem::P_Y_AXIS);
    m_yAxisEditor->setItem(yAxisItem);

    m_resolutionFunctionEditor->clearEditor();
    auto resFuncGroup = detectorItem()->getItem(FlatDetectorItem::P_RESOLUTION_FUNCTION);
    m_resolutionFunctionEditor->setItem(resFuncGroup);

    m_alignmentEditor->clearEditor();
    m_alignmentEditor->setItem(detectorItem()->getItem(FlatDetectorItem::P_ALIGNMENT));

    init_alignment_editors();
}

void FlatDetectorEditor::init_alignment_editors()
{
    m_positionsEditor->clearEditor();
    m_positionsEditor->hide();

    m_normalEditor->clearEditor();
    m_normalEditor->hide();

    m_directionEditor->clearEditor();
    m_directionEditor->hide();

    ComboProperty alignment
        = detectorItem()->getItemValue(FlatDetectorItem::P_ALIGNMENT).value<ComboProperty>();

    if (alignment.getValue() == Constants::ALIGNMENT_GENERIC) {
        m_positionsEditor->show();
        m_normalEditor->show();
        m_directionEditor->show();

        m_positionsEditor->addItem(detectorItem()->getItem(FlatDetectorItem::P_U0));
        m_positionsEditor->addItem(detectorItem()->getItem(FlatDetectorItem::P_V0));

        auto normalVectorItem = detectorItem()->getItem(FlatDetectorItem::P_NORMAL);
        m_normalEditor->setItem(normalVectorItem);

        auto directionVectorItem = detectorItem()->getItem(FlatDetectorItem::P_DIRECTION);
        m_directionEditor->setItem(directionVectorItem);

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_DIRECT_BEAM
               || alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM_DPOS) {
        m_positionsEditor->show();
        m_positionsEditor->addItem(detectorItem()->getItem(FlatDetectorItem::P_DBEAM_U0));
        m_positionsEditor->addItem(detectorItem()->getItem(FlatDetectorItem::P_DBEAM_V0));
        m_positionsEditor->addItem(detectorItem()->getItem(FlatDetectorItem::P_DISTANCE));

    } else if (alignment.getValue() == Constants::ALIGNMENT_TO_SAMPLE
               || alignment.getValue() == Constants::ALIGNMENT_TO_REFLECTED_BEAM) {
        m_positionsEditor->show();

        m_positionsEditor->addItem(detectorItem()->getItem(FlatDetectorItem::P_U0));
        m_positionsEditor->addItem(detectorItem()->getItem(FlatDetectorItem::P_V0));
        m_positionsEditor->addItem(detectorItem()->getItem(FlatDetectorItem::P_DISTANCE));
    }
}
