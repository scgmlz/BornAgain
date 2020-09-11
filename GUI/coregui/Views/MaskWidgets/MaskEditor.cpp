// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditor.cpp
//! @brief     Implements class MaskEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/MaskEditor.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditorActions.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditorCanvas.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditorPropertyPanel.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditorToolBar.h"
#include "GUI/coregui/Views/MaskWidgets/MaskGraphicsScene.h"
#include "minisplitter.h"
#include <QBoxLayout>
#include <QContextMenuEvent>

MaskEditor::MaskEditor(QWidget* parent)
    : QMainWindow(parent), m_editorActions(new MaskEditorActions(this)),
      m_toolBar(new MaskEditorToolBar(m_editorActions)),
      m_editorPropertyPanel(new MaskEditorPropertyPanel), m_editorCanvas(new MaskEditorCanvas),
      m_splitter(new Manhattan::MiniSplitter)
{
    setObjectName("MaskEditor");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_splitter->addWidget(m_editorCanvas);
    m_splitter->addWidget(m_editorPropertyPanel);
    m_splitter->setCollapsible(1, true);

    addToolBar(Qt::RightToolBarArea, m_toolBar);

    setCentralWidget(m_splitter);

    setup_connections();

    m_editorPropertyPanel->setPanelHidden(true);
}

void MaskEditor::setMaskContext(SessionModel* model, const QModelIndex& maskContainerIndex,
                                IntensityDataItem* intensityItem)
{
    m_editorPropertyPanel->setMaskContext(model, maskContainerIndex, intensityItem);

    ASSERT(intensityItem);
    ASSERT(maskContainerIndex.isValid());
    ASSERT(model->itemForIndex(maskContainerIndex)->modelType() == "MaskContainer");

    m_editorCanvas->setSelectionModel(m_editorPropertyPanel->selectionModel());
    m_editorCanvas->setMaskContext(model, maskContainerIndex, intensityItem);

    m_editorActions->setModel(model, maskContainerIndex);
    m_editorActions->setSelectionModel(m_editorPropertyPanel->selectionModel());
}

void MaskEditor::resetContext()
{
    m_editorPropertyPanel->resetContext();
    m_editorCanvas->resetContext();
}

//! shows/hides right panel with properties
void MaskEditor::onPropertyPanelRequest()
{
    m_editorPropertyPanel->setPanelHidden(!m_editorPropertyPanel->isHidden());
}

//! Context menu reimplemented to supress default menu
void MaskEditor::contextMenuEvent(QContextMenuEvent* event)
{
    Q_UNUSED(event);
}

//! Returns list of actions intended for styled toolbar (on the top).

QList<QAction*> MaskEditor::topToolBarActions()
{
    return m_editorActions->topToolBarActions();
}

void MaskEditor::setup_connections()
{
    // reset view request is propagated from editorActions to graphics view
    connect(m_editorActions, &MaskEditorActions::resetViewRequest, m_editorCanvas,
            &MaskEditorCanvas::onResetViewRequest);

    // tool panel request is propagated from editorActions to this MaskEditor
    connect(m_editorActions, &MaskEditorActions::propertyPanelRequest, this,
            &MaskEditor::onPropertyPanelRequest);

    // save plot request is propagated from editorActions to graphics scene
    connect(m_editorActions, &MaskEditorActions::savePlotRequest, m_editorCanvas,
            &MaskEditorCanvas::onSavePlotRequest);

    // selection/drawing activity is propagated from ToolBar to graphics scene
    connect(m_toolBar, &MaskEditorToolBar::activityModeChanged, m_editorCanvas->getScene(),
            &MaskGraphicsScene::onActivityModeChanged);

    // mask value is propagated from ToolBar to graphics scene
    connect(m_toolBar, &MaskEditorToolBar::maskValueChanged, m_editorCanvas->getScene(),
            &MaskGraphicsScene::onMaskValueChanged);

    // show results request is propagated from ToolBar to Canvas
    connect(m_toolBar, &MaskEditorToolBar::presentationTypeRequest, m_editorCanvas,
            &MaskEditorCanvas::onPresentationTypeRequest);

    // space bar push (request for zoom mode) is propagated from graphics view to ToolBar
    connect(m_editorCanvas, &MaskEditorCanvas::changeActivityRequest, m_toolBar,
            &MaskEditorToolBar::onChangeActivityRequest);

    // Delete request is propagated from canvas to actions
    connect(m_editorCanvas, &MaskEditorCanvas::deleteSelectedRequest, m_editorActions,
            &MaskEditorActions::onDeleteMaskAction);

    // context menu request is propagated from graphics scene to MaskEditorActions
    connect(m_editorCanvas->getScene(), &MaskGraphicsScene::itemContextMenuRequest, m_editorActions,
            &MaskEditorActions::onItemContextMenuRequest);

    // context menu request is propagated from PropertyPanel to MaskEditorActions
    connect(m_editorPropertyPanel, &MaskEditorPropertyPanel::itemContextMenuRequest,
            m_editorActions, &MaskEditorActions::onItemContextMenuRequest);
}
