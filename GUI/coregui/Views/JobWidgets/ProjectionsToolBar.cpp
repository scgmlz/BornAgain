// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsToolBar.cpp
//! @brief     Implements class ProjectionsToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/ProjectionsToolBar.h"
#include "GUI/coregui/Views/JobWidgets/ProjectionsEditorActions.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include <QButtonGroup>
#include <QLabel>
#include <QToolButton>

namespace
{
const QString pan_zoom_tooltip = "Pan/zoom mode (space)\n"
                                 "Drag axes with the mouse, use mouse wheel to zoom in/out";

const QString reset_view_tooltip = "Reset view\nx,y,z axes range will be set to default";

const QString selection_mode_tooltip =
    "Selection mode\nYou can select existing projections and move them around";

const QString horizontal_mode_tooltip =
    "Horizontal projections mode\nCreate projection along x-axis by clicking on color map";

const QString vertical_mode_tooltip =
    "Vertical projections mode\nCreate projection along y-axis by clicking on color map";

} // namespace

ProjectionsToolBar::ProjectionsToolBar(ProjectionsEditorActions* editorActions, QWidget* parent)
    : QToolBar(parent), m_editorActions(editorActions),
      m_activityButtonGroup(new QButtonGroup(this))
{
    setIconSize(QSize(Constants::toolbar_icon_size, Constants::toolbar_icon_size));
    setProperty("_q_custom_style_disabled", QVariant(true));

    setup_selection_group();
    setup_shapes_group();
    setup_extratools_group();

    connect(m_activityButtonGroup, SIGNAL(buttonClicked(int)), this,
            SLOT(onActivityGroupChange(int)));

    m_previousActivity = currentActivity();
}

void ProjectionsToolBar::onChangeActivityRequest(MaskEditorFlags::Activity value)
{
    if (value == MaskEditorFlags::PREVIOUS_MODE) {
        setCurrentActivity(m_previousActivity);
    } else {
        m_previousActivity = currentActivity();
        setCurrentActivity(value);
    }
    emit activityModeChanged(currentActivity());
}

//! Change activity only if current activity is one of drawing mode (horizontal, vertical
//! projections drawing).
void ProjectionsToolBar::onProjectionTabChange(MaskEditorFlags::Activity value)
{
    if (currentActivity() == MaskEditorFlags::HORIZONTAL_LINE_MODE
        || currentActivity() == MaskEditorFlags::VERTICAL_LINE_MODE)
        onChangeActivityRequest(value);
}

void ProjectionsToolBar::onActivityGroupChange(int)
{
    emit activityModeChanged(currentActivity());
}

void ProjectionsToolBar::setup_selection_group()
{
    auto panButton = new QToolButton(this);
    panButton->setIcon(QIcon(":/images/hand-right.svg"));
    panButton->setToolTip(pan_zoom_tooltip);
    panButton->setCheckable(true);
    panButton->setChecked(true);
    addWidget(panButton);

    auto resetViewButton = new QToolButton(this);
    resetViewButton->setIcon(QIcon(":/images/camera-metering-center.svg"));
    resetViewButton->setToolTip(reset_view_tooltip);
    addWidget(resetViewButton);
    connect(resetViewButton, &QToolButton::clicked, m_editorActions,
            &ProjectionsEditorActions::resetViewRequest);

    add_separator();

    QToolButton* selectionButton = new QToolButton(this);
    selectionButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_arrow.svg"));
    selectionButton->setToolTip(selection_mode_tooltip);
    selectionButton->setCheckable(true);
    addWidget(selectionButton);

    m_activityButtonGroup->addButton(panButton, MaskEditorFlags::PAN_ZOOM_MODE);
    m_activityButtonGroup->addButton(selectionButton, MaskEditorFlags::SELECTION_MODE);
}

void ProjectionsToolBar::setup_shapes_group()
{
    auto horizontalLineButton = new QToolButton(this);
    horizontalLineButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_horizontalline.svg"));
    horizontalLineButton->setToolTip(horizontal_mode_tooltip);
    horizontalLineButton->setCheckable(true);
    addWidget(horizontalLineButton);

    auto verticalLineButton = new QToolButton(this);
    verticalLineButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_verticalline.svg"));
    verticalLineButton->setToolTip(vertical_mode_tooltip);
    verticalLineButton->setCheckable(true);
    addWidget(verticalLineButton);

    m_activityButtonGroup->addButton(verticalLineButton, MaskEditorFlags::VERTICAL_LINE_MODE);
    m_activityButtonGroup->addButton(horizontalLineButton, MaskEditorFlags::HORIZONTAL_LINE_MODE);

    add_separator();
}

void ProjectionsToolBar::setup_extratools_group()
{
    auto saveButton = new QToolButton(this);
    saveButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_save.svg"));
    saveButton->setToolTip("Save created projections in multi-column ASCII file.");
    addWidget(saveButton);
    connect(saveButton, &QToolButton::clicked, m_editorActions,
            &ProjectionsEditorActions::onSaveAction);
}

void ProjectionsToolBar::add_separator()
{
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

MaskEditorFlags::Activity ProjectionsToolBar::currentActivity() const
{
    return MaskEditorFlags::EActivityType(m_activityButtonGroup->checkedId());
}

void ProjectionsToolBar::setCurrentActivity(MaskEditorFlags::Activity value)
{
    int button_index = static_cast<int>(value);
    m_activityButtonGroup->button(button_index)->setChecked(true);
}
