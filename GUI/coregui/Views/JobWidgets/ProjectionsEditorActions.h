// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditorActions.h
//! @brief     Defines class ProjectionsEditorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSEDITORACTIONS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSEDITORACTIONS_H

#include "Wrap/WinDllMacros.h"
#include <QList>
#include <QModelIndex>
#include <QObject>

class SessionModel;
class QItemSelectionModel;
class QAction;
class IntensityDataItem;

//! Provides various actions for ProjectionsEditor.

class BA_CORE_API_ ProjectionsEditorActions : public QObject
{
    Q_OBJECT

public:
    ProjectionsEditorActions(QWidget* parent = 0);

    void setContext(SessionModel* model, const QModelIndex& shapeContainerIndex,
                    IntensityDataItem* intensityItem);

    void setSelectionModel(QItemSelectionModel* selectionModel);

    QList<QAction*> topToolBarActions();

public slots:
    void onDeleteAction();
    void onSaveAction();

signals:
    void resetViewRequest();
    void propertyPanelRequest();

private:
    QAction* m_resetViewAction;
    QAction* m_togglePanelAction;
    QAction* m_deleteAction;
    SessionModel* m_model;
    QModelIndex m_containerIndex; //!< Index of container with projections
    IntensityDataItem* m_intensityDataItem;
    QItemSelectionModel* m_selectionModel;
    QWidget* m_parent;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_PROJECTIONSEDITORACTIONS_H
