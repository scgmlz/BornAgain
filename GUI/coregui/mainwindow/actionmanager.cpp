// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/actionmanager.cpp
//! @brief     Implements class ActionManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "actionmanager.h"
#include "UpdateNotifier.h"
#include "hostosinfo.h"
#include "mainwindow.h"
#include "mainwindow_constants.h"
#include "projectmanager.h"
#include "qstringutils.h"
#include <QDebug>
#include <QDir>
#include <QMenuBar>
#include <QSettings>
#include <QShortcut>

ActionManager::ActionManager(MainWindow *parent)
    : QObject(parent)
    , m_mainWindow(parent)
    , m_newAction(0)
    , m_openAction(0)
    , m_saveAction(0)
    , m_saveAsAction(0)
    , m_menuBar(0)
    , m_fileMenu(0)
    , m_settingsMenu(0)
    , m_helpMenu(0)
    , m_runSimulationShortcut(0)
{
    setParent(parent);
    createActions();
    createMenus();
    createGlobalShortcuts();
}



void ActionManager::createActions()
{
    ProjectManager *projectManager = m_mainWindow->projectManager();
    Q_ASSERT(projectManager);

    // new project action
//    QIcon icon = QIcon::fromTheme(QLatin1String("document-new"), QIcon(QLatin1String(Constants::ICON_NEWFILE)));
    m_newAction = new QAction("&New Project", m_mainWindow);
    m_newAction->setShortcuts(QKeySequence::New);
    m_newAction->setStatusTip("Create a new project");
    connect(m_newAction, SIGNAL(triggered()), projectManager, SLOT(newProject()) );

    // open project action
//    icon = QIcon::fromTheme(QLatin1String("document-open"), QIcon(QLatin1String(Constants::ICON_OPENFILE)));
    m_openAction = new QAction("&Open Project", m_mainWindow);
    m_openAction->setShortcuts(QKeySequence::Open);
    m_openAction->setStatusTip("Open an existing project");
    connect(m_openAction, SIGNAL(triggered()), projectManager, SLOT(openProject()) );

    // save project action
//    icon = QIcon::fromTheme(QLatin1String("document-save"), QIcon(QLatin1String(Constants::ICON_SAVEFILE)));
    m_saveAction = new QAction("&Save Project", m_mainWindow);
    m_saveAction->setShortcuts(QKeySequence::Save);
    m_saveAction->setStatusTip("Save project");
    m_saveAction->setShortcutContext(Qt::ApplicationShortcut);
    connect(m_saveAction, SIGNAL(triggered()), projectManager, SLOT(saveProject()) );

    // save-as project action
//    icon = QIcon::fromTheme(QLatin1String("document-save-as"));
    m_saveAsAction = new QAction("Save &As...", m_mainWindow);
    m_saveAsAction->setShortcuts(QKeySequence::SaveAs);
    m_saveAsAction->setStatusTip("Save project under different name");
    connect(m_saveAsAction, SIGNAL(triggered()), projectManager, SLOT(saveProjectAs()) );

    // exit application action
//    icon = QIcon::fromTheme(QLatin1String("application-exit"));
    m_exitAction = new QAction("E&xit Application", this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    m_exitAction->setStatusTip("Exit the application");
    connect(m_exitAction, SIGNAL(triggered()), m_mainWindow, SLOT(close()));

    // about application action
//    icon = QIcon::fromTheme(QLatin1String("help-about"));
    m_aboutAction = new QAction("About &BornAgain", this);
    //m_aboutAction->setShortcuts(QKeySequence::HelpContents);
    m_aboutAction->setStatusTip("About the application");
    connect(m_aboutAction, SIGNAL(triggered()), m_mainWindow, SLOT(onAboutApplication()));

}


void ActionManager::createMenus()
{
    m_menuBar = new QMenuBar(0); // No parent (System menu bar on Mac OS X)

    if (!GUI_OS_Utils::HostOsInfo::isMacHost())
        m_mainWindow->setMenuBar(m_menuBar);

    // File Menu
    m_fileMenu = m_menuBar->addMenu("&File");
    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);
    connect(m_fileMenu, SIGNAL(aboutToShow()), this, SLOT(aboutToShowRecentProjects()));

    m_recentProjectsMenu = m_fileMenu->addMenu("Recent Projects");

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_saveAction);
    m_fileMenu->addAction(m_saveAsAction);

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    // Settings Menu
    m_settingsMenu = new QMenu("Settings", m_mainWindow);
    aboutToShowSettings(); // MacOS feature: action should exist already, otherwise menuBar will not add menu
    connect(m_settingsMenu, SIGNAL(aboutToShow()), this, SLOT(aboutToShowSettings()));
    m_menuBar->addMenu(m_settingsMenu);

    // Help Menu
    m_helpMenu = m_menuBar->addMenu("&Help");
    m_helpMenu->addAction(m_aboutAction);
}


void ActionManager::createGlobalShortcuts()
{
    m_runSimulationShortcut =  new QShortcut(QKeySequence("Ctrl+r"), m_mainWindow);
    m_runSimulationShortcut->setContext((Qt::ApplicationShortcut));
    connect(m_runSimulationShortcut, SIGNAL(activated()),
            m_mainWindow, SLOT(onRunSimulationShortcut()));
}


void ActionManager::aboutToShowRecentProjects()
{
    qDebug() << "ActionManager::aboutToShowRecentProjects() ->"
             << m_mainWindow->projectManager()->getRecentProjects();
    m_recentProjectsMenu->clear();

    bool hasRecentProjects = false;
    foreach(QString file, m_mainWindow->projectManager()->getRecentProjects() ) {
        hasRecentProjects = true;
        qDebug() << file << QDir::toNativeSeparators(GUI_StringUtils::withTildeHomePath(file));
        QAction *action = m_recentProjectsMenu->addAction(
            QDir::toNativeSeparators(GUI_StringUtils::withTildeHomePath(file)));
        action->setData(qVariantFromValue(file));
        connect(action, SIGNAL(triggered()), m_mainWindow, SLOT(openRecentProject()));

    }

    m_recentProjectsMenu->setEnabled(hasRecentProjects);

    if (hasRecentProjects) {
        m_recentProjectsMenu->addSeparator();
        QAction *action = m_recentProjectsMenu->addAction("Clear Menu");
        connect(action, SIGNAL(triggered()),
                m_mainWindow->projectManager(), SLOT(clearRecentProjects()));
    }

}

void ActionManager::aboutToShowSettings()
{
    m_settingsMenu->clear();
    QSettings settings;

    settings.beginGroup(Constants::S_UPDATES);
    QAction *action = m_settingsMenu->addAction("Check for Updates");
    action->setCheckable(true);
    action->setChecked(settings.value(Constants::S_CHECKFORUPDATES, false).toBool());
    connect(action, SIGNAL(toggled(bool)), this, SLOT(toggleCheckForUpdates(bool)));
    settings.endGroup();

    settings.beginGroup(Constants::S_SESSIONMODELVIEW);
    action = m_settingsMenu->addAction("Model tech view");
    action->setToolTip("Additional developer's view will appear in left control tab bar");
    action->setCheckable(true);
    action->setChecked(settings.value(Constants::S_VIEWISACTIVE, false).toBool());
    connect(action, SIGNAL(toggled(bool)), this, SLOT(setSessionModelViewActive(bool)));
    settings.endGroup();
}

void ActionManager::toggleCheckForUpdates(bool status)
{
    QSettings settings;
    settings.beginGroup(Constants::S_UPDATES);
    settings.setValue(Constants::S_CHECKFORUPDATES, status);
    settings.endGroup();
    m_mainWindow->getUpdateNotifier()->checkForUpdates();
}

void ActionManager::setSessionModelViewActive(bool status)
{
    QSettings settings;
    settings.beginGroup(Constants::S_SESSIONMODELVIEW);
    settings.setValue(Constants::S_VIEWISACTIVE, status);
    settings.endGroup();
    m_mainWindow->onSessionModelViewActive(status);
}
