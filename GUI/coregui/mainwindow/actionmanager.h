// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/actionmanager.h
//! @brief     Defines class ActionManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_ACTIONMANAGER_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_ACTIONMANAGER_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class QMenu;
class QAction;
class QMenuBar;
class MainWindow;
class QShortcut;

//! Class to handle MainWindow's menu and corresponding actions

class BA_CORE_API_ ActionManager : public QObject
{
    Q_OBJECT
public:
    ActionManager(MainWindow* parent);

private slots:
    void aboutToShowFileMenu();
    void aboutToShowSettings();
    void toggleCheckForUpdates(bool status);
    void setSessionModelViewActive(bool status);
    void onAboutApplication();
#ifdef BORNAGAIN_PYTHON
    void onImportFromPythonScript();
#endif // BORNAGAIN_PYTHON

private:
    MainWindow* m_mainWindow;

    QAction* m_newAction;
    QAction* m_openAction;
    QAction* m_saveAction;
    QAction* m_saveAsAction;
    QAction* m_exitAction;
    QAction* m_aboutAction;

    QMenuBar* m_menuBar;
    QMenu* m_fileMenu;
    QMenu* m_settingsMenu;
    QMenu* m_recentProjectsMenu;
    QMenu* m_helpMenu;
    QMenu* m_importMenu;

    QShortcut* m_runSimulationShortcut;

    void createActions();
    void createMenus();
    void createGlobalShortcuts();
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_ACTIONMANAGER_H
