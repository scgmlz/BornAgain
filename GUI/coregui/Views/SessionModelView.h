// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SessionModelView.h
//! @brief     Defines class SessionModelView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SESSIONMODELVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SESSIONMODELVIEW_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class MainWindow;
class QToolBar;
class QTabWidget;
class QToolButton;
class SessionModel;
class ModelTreeView;
class SessionModelDelegate;

//! The SessionModelView is a technical view which shows the content all current application
//! models. It appears as an additional view in the main navigation bar on the left, right
//! after the jobView (if corresponding setting of MainWindow is On).

class BA_CORE_API_ SessionModelView : public QWidget
{
    Q_OBJECT

public:
    SessionModelView(MainWindow* mainWindow = 0);

    void setViewActive(bool is_active);

private slots:
    void onExpandCollapseTree();

private:
    void init_tabs();
    QList<SessionModel*> modelsForTabs();
    void init_test_view();

    MainWindow* m_mainWindow;
    QToolBar* m_toolBar;
    QTabWidget* m_tabs;
    QToolButton* m_expandCollapseButton;
    SessionModelDelegate* m_delegate;
    QVector<ModelTreeView*> m_content;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SESSIONMODELVIEW_H
