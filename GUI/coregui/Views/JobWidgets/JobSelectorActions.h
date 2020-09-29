// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobSelectorActions.h
//! @brief     Defines class JobSelectorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBSELECTORACTIONS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBSELECTORACTIONS_H

#include <QModelIndex>
#include <QObject>

class QAction;
class JobModel;
class QItemSelectionModel;
class QModelIndex;
class QMenu;

//! The JobSelectorActions class contains actions to run/remove jobs. Actions are used by the
//! toolbar and JobSelectorList's context menu.

class JobSelectorActions : public QObject
{
    Q_OBJECT
public:
    JobSelectorActions(JobModel* jobModel, QObject* parent = 0);

    void setSelectionModel(QItemSelectionModel* selectionModel);

public slots:
    void onRunJob();
    void onRemoveJob();
    void onContextMenuRequest(const QPoint& point, const QModelIndex& indexAtPoint = {});
    void equalizeSelectedToJob(int selected_id);

private:
    void initItemContextMenu(QMenu& menu, const QModelIndex& indexAtPoint);
    void setupEqualizeMenu(QMenu& menu);
    void setAllActionsEnabled(bool value);
    bool canRunJob(const QModelIndex& index) const;
    bool canRemoveJob(const QModelIndex& index) const;

    QAction* m_runJobAction;
    QAction* m_removeJobAction;
    QItemSelectionModel* m_selectionModel;
    JobModel* m_jobModel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_JOBWIDGETS_JOBSELECTORACTIONS_H
