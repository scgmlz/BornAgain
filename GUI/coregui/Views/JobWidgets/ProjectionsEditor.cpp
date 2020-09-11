// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditor.cpp
//! @brief     Implements class ProjectionsEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/ProjectionsEditor.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/JobWidgets/ProjectionsEditorActions.h"
#include "GUI/coregui/Views/JobWidgets/ProjectionsEditorCanvas.h"
#include "GUI/coregui/Views/JobWidgets/ProjectionsPropertyPanel.h"
#include "GUI/coregui/Views/JobWidgets/ProjectionsToolBar.h"
#include "GUI/coregui/Views/JobWidgets/ProjectionsWidget.h"
#include "minisplitter.h"
#include <QItemSelectionModel>
#include <QSplitter>

ProjectionsEditor::ProjectionsEditor(QWidget* parent)
    : QMainWindow(parent), m_editorActions(new ProjectionsEditorActions(this)),
      m_toolBar(new ProjectionsToolBar(m_editorActions)),
      m_projectionsCanvas(new ProjectionsEditorCanvas), m_projectionsWidget(new ProjectionsWidget),
      m_propertyPanel(new ProjectionsPropertyPanel), m_selectionModel(nullptr),
      m_rightSplitter(new Manhattan::MiniSplitter), m_bottomSplitter(new QSplitter)
{
    addToolBar(Qt::RightToolBarArea, m_toolBar);

    m_bottomSplitter->setOrientation(Qt::Vertical);
    m_bottomSplitter->addWidget(m_projectionsCanvas);
    m_bottomSplitter->addWidget(m_projectionsWidget);
    m_bottomSplitter->setStyleSheet("background-color:white;");

    m_rightSplitter->addWidget(m_bottomSplitter);
    m_rightSplitter->addWidget(m_propertyPanel);

    setCentralWidget(m_rightSplitter);

    m_propertyPanel->setHidden(true);
    setup_connections();
}

void ProjectionsEditor::setContext(SessionModel* model, const QModelIndex& shapeContainerIndex,
                                   IntensityDataItem* intensityItem)
{
    Q_UNUSED(model);
    Q_UNUSED(shapeContainerIndex);

    delete m_selectionModel;
    m_selectionModel = new QItemSelectionModel(model, this);

    m_propertyPanel->setItem(intensityItem);
    m_projectionsCanvas->setSelectionModel(m_selectionModel);
    m_projectionsCanvas->setContext(model, shapeContainerIndex, intensityItem);
    m_projectionsWidget->setItem(intensityItem);

    m_editorActions->setContext(model, shapeContainerIndex, intensityItem);
    m_editorActions->setSelectionModel(m_selectionModel);
}

void ProjectionsEditor::resetContext()
{
    m_propertyPanel->setItem(nullptr);
    m_projectionsCanvas->resetContext();
    m_projectionsWidget->setItem(nullptr);
}

QList<QAction*> ProjectionsEditor::topToolBarActions()
{
    return m_editorActions->topToolBarActions();
}

void ProjectionsEditor::setup_connections()
{
    // tool panel request is propagated from editorActions to this MaskEditor
    connect(m_editorActions, &ProjectionsEditorActions::resetViewRequest, m_projectionsCanvas,
            &ProjectionsEditorCanvas::onResetViewRequest);

    // tool panel request is propagated from editorActions to this MaskEditor
    connect(m_editorActions, &ProjectionsEditorActions::propertyPanelRequest,
            [=]() { m_propertyPanel->setHidden(!m_propertyPanel->isHidden()); });

    // selection/drawing activity is propagated from ToolBar to graphics scene
    connect(m_toolBar, &ProjectionsToolBar::activityModeChanged, m_projectionsCanvas,
            &ProjectionsEditorCanvas::onActivityModeChanged);

    // selection/drawing activity is propagated from ToolBar to Projections Widget
    connect(m_toolBar, &ProjectionsToolBar::activityModeChanged, m_projectionsWidget,
            &ProjectionsWidget::onActivityModeChanged);

    // click on projections tab is propagated to tool bar
    connect(m_projectionsWidget, &ProjectionsWidget::changeActivityRequest, m_toolBar,
            &ProjectionsToolBar::onProjectionTabChange);

    // Delete request is propagated from canvas to actions
    connect(m_projectionsCanvas, &ProjectionsEditorCanvas::deleteSelectedRequest, m_editorActions,
            &ProjectionsEditorActions::onDeleteAction);

    // space bar push (request for zoom mode) is propagated from graphics view to ToolBar
    connect(m_projectionsCanvas, &ProjectionsEditorCanvas::changeActivityRequest, m_toolBar,
            &ProjectionsToolBar::onChangeActivityRequest);

    // ColorMap margins changed, canvas -> projection widget
    connect(m_projectionsCanvas, &ProjectionsEditorCanvas::marginsChanged, m_projectionsWidget,
            &ProjectionsWidget::onMarginsChanged);

    m_toolBar->onChangeActivityRequest(MaskEditorFlags::HORIZONTAL_LINE_MODE);
}
