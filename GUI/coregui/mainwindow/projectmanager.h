// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/projectmanager.h
//! @brief     Defines class ProjectManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTMANAGER_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTMANAGER_H

#include "Wrap/WinDllMacros.h"
#include <QObject>
#include <QStringList>

class MainWindow;
class ProjectDocument;
class MessageService;
class SaveService;

//! Handles activity related to opening/save projects.

class BA_CORE_API_ ProjectManager : public QObject
{
    Q_OBJECT
public:
    ProjectManager(MainWindow* parent);
    virtual ~ProjectManager();

    void readSettings();
    void writeSettings();

    ProjectDocument* document();

    QStringList recentProjects();
    QString projectDir() const;
    QString userExportDir() const;
    QString userImportDir() const;
    void setImportDir(const QString& dirname);

    bool isAutosaveEnabled() const;

signals:
    void modified();

public slots:
    void setAutosaveEnabled(bool value);
    void onDocumentModified();
    void clearRecentProjects();
    void newProject();
    bool closeCurrentProject();
    bool saveProject(QString projectFileName = "");
    bool saveProjectAs();
    void openProject(QString fileName = "");

private:
    void createNewProject();
    void deleteCurrentProject();
    void loadProject(const QString& projectFileName);
    QString acquireProjectFileName();
    void addToRecentProjects();

    QString workingDirectory();
    QString untitledProjectName();

    void riseProjectLoadFailedDialog();
    void riseProjectLoadWarningDialog();
    bool restoreProjectDialog(const QString& projectFileName);

    MainWindow* m_mainWindow;
    ProjectDocument* m_project_document;

    //!< Name of directory where project directory was created.
    QString m_workingDirectory;

    //!< Name of directory from there user prefer to import files
    QString m_importDirectory;

    QStringList m_recentProjects;
    MessageService* m_messageService;
    SaveService* m_saveService;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTMANAGER_H
