// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditorActions.cpp
//! @brief     Implements class ProjectionsEditorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/ProjectionsEditorActions.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/IntensityDataWidgets/SaveProjectionsAssistant.h"
#include <QAction>
#include <QItemSelectionModel>
#include <QModelIndexList>

ProjectionsEditorActions::ProjectionsEditorActions(QWidget* parent)
    : QObject(parent), m_resetViewAction(new QAction(this)), m_togglePanelAction(new QAction(this)),
      m_deleteAction(new QAction("Remove selected", this)), m_model(nullptr),
      m_intensityDataItem(nullptr), m_selectionModel(nullptr), m_parent(parent)
{
    // Actions for top toolbar
    m_resetViewAction->setText("Center view");
    m_resetViewAction->setIcon(QIcon(":/images/camera-metering-center.svg"));
    m_resetViewAction->setToolTip("Reset view\n"
                                  "x,y,z axes range will be set to default");
    connect(m_resetViewAction, &QAction::triggered, this,
            &ProjectionsEditorActions::resetViewRequest);

    m_togglePanelAction->setText("Properties");
    m_togglePanelAction->setIcon(QIcon(":/images/dock-right.svg"));
    m_togglePanelAction->setToolTip("Toggle property panel");
    connect(m_togglePanelAction, &QAction::triggered, this,
            &ProjectionsEditorActions::propertyPanelRequest);

    m_deleteAction->setToolTip("Remove selected (Del)");
    m_deleteAction->setShortcuts(QKeySequence::Delete);
    connect(m_deleteAction, &QAction::triggered, this, &ProjectionsEditorActions::onDeleteAction);
}

void ProjectionsEditorActions::setContext(SessionModel* model, const QModelIndex& containerIndex,
                                          IntensityDataItem* intensityItem)
{
    m_model = model;
    m_containerIndex = containerIndex;
    m_intensityDataItem = intensityItem;
}

void ProjectionsEditorActions::setSelectionModel(QItemSelectionModel* selectionModel)
{
    m_selectionModel = selectionModel;
}

QList<QAction*> ProjectionsEditorActions::topToolBarActions()
{
    return QList<QAction*>() << m_resetViewAction << m_togglePanelAction;
}

void ProjectionsEditorActions::onDeleteAction()
{
    ASSERT(m_model);
    ASSERT(m_selectionModel);

    QModelIndexList indexes = m_selectionModel->selectedIndexes();
    while (indexes.size()) {
        m_model->removeRows(indexes.back().row(), 1, indexes.back().parent());
        indexes = m_selectionModel->selectedIndexes();
    }
}

//! Performs saving of projections in ascii file
void ProjectionsEditorActions::onSaveAction()
{
    if (!m_intensityDataItem)
        return;

    SaveProjectionsAssistant assistant;
    assistant.saveProjections(m_parent, m_intensityDataItem);
}
