// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorToolBar.cpp
//! @brief     Implements class MaskEditorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/MaskEditorToolBar.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditorActions.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include <QButtonGroup>
#include <QLabel>
#include <QRadioButton>
#include <QStyle>
#include <QToolButton>
#include <QVariant>

MaskEditorToolBar::MaskEditorToolBar(MaskEditorActions* editorActions, QWidget* parent)
    : QToolBar(parent), m_editorActions(editorActions),
      m_activityButtonGroup(new QButtonGroup(this)), m_maskValueGroup(new QButtonGroup(this))
{
    setIconSize(QSize(Constants::toolbar_icon_size, Constants::toolbar_icon_size));
    setProperty("_q_custom_style_disabled", QVariant(true));

    setup_selection_group();
    //    setup_maskvalue_group();
    setup_shapes_group();
    setup_maskmodify_group();
    setup_extratools_group();

    connect(m_activityButtonGroup, SIGNAL(buttonClicked(int)), this,
            SLOT(onActivityGroupChange(int)));
    connect(m_maskValueGroup, SIGNAL(buttonClicked(int)), this, SLOT(onMaskValueGroupChange(int)));

    m_previousActivity = currentActivity();
}

//! Handles ZOOM requests from MaskGraphicsView while user press and holds
//! space bar. As soon as space bar is released, activity is returned to previous state.
void MaskEditorToolBar::onChangeActivityRequest(MaskEditorFlags::Activity value)
{
    if (value == MaskEditorFlags::PREVIOUS_MODE) {
        setCurrentActivity(m_previousActivity);
    } else {
        m_previousActivity = currentActivity();
        setCurrentActivity(value);
    }
    emit activityModeChanged(currentActivity());
}

void MaskEditorToolBar::onActivityGroupChange(int value)
{
    Q_UNUSED(value);
    emit activityModeChanged(currentActivity());
}

void MaskEditorToolBar::onMaskValueGroupChange(int value)
{
    Q_UNUSED(value);
    emit maskValueChanged(MaskEditorFlags::MaskValue(value));
}

void MaskEditorToolBar::onPresentationTypePressed()
{
    emit presentationTypeRequest(MaskEditorFlags::MASK_PRESENTER);
}

void MaskEditorToolBar::onPresentationTypeReleased()
{
    emit presentationTypeRequest(MaskEditorFlags::MASK_EDITOR);
}

void MaskEditorToolBar::setup_selection_group()
{
    QToolButton* panButton = new QToolButton(this);
    panButton->setIcon(QIcon(":/images/hand-right.svg"));
    panButton->setToolTip("Pan/zoom mode (space)");
    panButton->setCheckable(true);
    panButton->setChecked(true);
    addWidget(panButton);

    QToolButton* resetViewButton = new QToolButton(this);
    resetViewButton->setIcon(QIcon(":/images/camera-metering-center.svg"));
    resetViewButton->setToolTip("Reset pan/zoom to initial state");
    addWidget(resetViewButton);
    connect(resetViewButton, SIGNAL(clicked()), m_editorActions, SIGNAL(resetViewRequest()));

    add_separator();

    QToolButton* selectionButton = new QToolButton(this);
    selectionButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_arrow.svg"));
    selectionButton->setToolTip("Select/modify mask");
    selectionButton->setCheckable(true);
    addWidget(selectionButton);

    m_activityButtonGroup->addButton(panButton, MaskEditorFlags::PAN_ZOOM_MODE);
    m_activityButtonGroup->addButton(selectionButton, MaskEditorFlags::SELECTION_MODE);
}

void MaskEditorToolBar::setup_maskvalue_group()
{
    addWidget(new QLabel(" "));

    QRadioButton* maskTrueButton = new QRadioButton(this);
    maskTrueButton->setText("masked");
    maskTrueButton->setToolTip("Set mask to True (area is excluded from the simulation)");
    maskTrueButton->setCheckable(true);
    maskTrueButton->setChecked(true);
    addWidget(maskTrueButton);

    addWidget(new QLabel(" "));

    QRadioButton* maskFalseButton = new QRadioButton(this);
    maskFalseButton->setToolTip("Set mask to False (area stays in the simulation)");
    maskFalseButton->setCheckable(true);
    maskFalseButton->setText("active");
    addWidget(maskFalseButton);

    m_maskValueGroup->addButton(maskTrueButton, MaskEditorFlags::MASK_ON);
    m_maskValueGroup->addButton(maskFalseButton, MaskEditorFlags::MASK_OFF);
}

void MaskEditorToolBar::setup_shapes_group()
{
    QToolButton* roiButton = new QToolButton(this);
    roiButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_roi.svg"));
    roiButton->setToolTip("Create region of interest");
    roiButton->setCheckable(true);
    addWidget(roiButton);

    QToolButton* rectangleButton = new QToolButton(this);
    rectangleButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_rectangle.svg"));
    rectangleButton->setToolTip("Create rectangle mask");
    rectangleButton->setCheckable(true);
    addWidget(rectangleButton);

    QToolButton* polygonButton = new QToolButton(this);
    polygonButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_polygon.svg"));
    polygonButton->setToolTip("Create polygon mask");
    polygonButton->setCheckable(true);
    addWidget(polygonButton);

    QToolButton* verticalLineButton = new QToolButton(this);
    verticalLineButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_verticalline.svg"));
    verticalLineButton->setToolTip("Create vertical line mask");
    verticalLineButton->setCheckable(true);
    addWidget(verticalLineButton);

    QToolButton* horizontalLineButton = new QToolButton(this);
    horizontalLineButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_horizontalline.svg"));
    horizontalLineButton->setToolTip("Create horizontal line mask");
    horizontalLineButton->setCheckable(true);
    addWidget(horizontalLineButton);

    QToolButton* ellipseButton = new QToolButton(this);
    ellipseButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_ellipse.svg"));
    ellipseButton->setToolTip("Create ellipse mask");
    ellipseButton->setCheckable(true);
    addWidget(ellipseButton);

    //    QToolButton *maskAllButton = new QToolButton(this);
    //    maskAllButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_maskall.svg"));
    //    maskAllButton->setToolTip("Create masked area covering whole detector plane\n"
    //                              "Will be placed beneath all masks. Only one instance is
    //                              allowed.");
    //    maskAllButton->setCheckable(true);
    //    addWidget(maskAllButton);

    m_activityButtonGroup->addButton(roiButton, MaskEditorFlags::ROI_MODE);
    m_activityButtonGroup->addButton(rectangleButton, MaskEditorFlags::RECTANGLE_MODE);
    m_activityButtonGroup->addButton(polygonButton, MaskEditorFlags::POLYGON_MODE);
    m_activityButtonGroup->addButton(verticalLineButton, MaskEditorFlags::VERTICAL_LINE_MODE);
    m_activityButtonGroup->addButton(horizontalLineButton, MaskEditorFlags::HORIZONTAL_LINE_MODE);
    m_activityButtonGroup->addButton(ellipseButton, MaskEditorFlags::ELLIPSE_MODE);
    //    m_activityButtonGroup->addButton(maskAllButton, MaskEditorFlags::MASKALL_MODE);
    add_separator();
}

void MaskEditorToolBar::setup_maskmodify_group()
{
    ASSERT(m_editorActions);
    addAction(m_editorActions->bringToFrontAction());
    addAction(m_editorActions->sendToBackAction());
    add_separator();
}

void MaskEditorToolBar::setup_extratools_group()
{
    QToolButton* presentationButton = new QToolButton(this);
    presentationButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_lightbulb.svg"));
    presentationButton->setToolTip("Press and hold to see mask results.");
    addWidget(presentationButton);

    connect(presentationButton, SIGNAL(pressed()), this, SLOT(onPresentationTypePressed()));
    connect(presentationButton, SIGNAL(released()), this, SLOT(onPresentationTypeReleased()));

    QToolButton* propertyPanelButton = new QToolButton(this);
    propertyPanelButton->setIcon(QIcon(":/MaskWidgets/images/maskeditor_toolpanel.svg"));
    propertyPanelButton->setToolTip("Open panel with additional properties");
    addWidget(propertyPanelButton);

    connect(propertyPanelButton, SIGNAL(clicked()), m_editorActions,
            SIGNAL(propertyPanelRequest()));
    add_separator();
}

void MaskEditorToolBar::add_separator()
{
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

MaskEditorFlags::Activity MaskEditorToolBar::currentActivity() const
{
    return MaskEditorFlags::EActivityType(m_activityButtonGroup->checkedId());
}

void MaskEditorToolBar::setCurrentActivity(MaskEditorFlags::Activity value)
{
    m_activityButtonGroup->button(value)->setChecked(true);
}
