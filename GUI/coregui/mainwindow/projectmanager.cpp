// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/projectmanager.cpp
//! @brief     Implements class ProjectManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/projectmanager.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Views/InfoWidgets/ProjectLoadWarningDialog.h"
#include "GUI/coregui/mainwindow/AppSvc.h"
#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/mainwindow/SaveService.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include "GUI/coregui/mainwindow/newprojectdialog.h"
#include "GUI/coregui/mainwindow/projectdocument.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/MessageService.h"
#include <QApplication>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QStandardPaths>

namespace
{
const QString S_PROJECTMANAGER = "ProjectManager";
const QString S_AUTOSAVE = "EnableAutosave";
const QString S_DEFAULTPROJECTPATH = "DefaultProjectPath";
const QString S_RECENTPROJECTS = "RecentProjects";
const QString S_LASTUSEDIMPORTDIR = "LastUsedImportDir";
} // namespace

ProjectManager::ProjectManager(MainWindow* parent)
    : m_mainWindow(parent), m_project_document(nullptr), m_messageService(new MessageService),
      m_saveService(new SaveService(this))

{
    createNewProject();
    AppSvc::subscribe(this);
}

ProjectManager::~ProjectManager()
{
    AppSvc::unsubscribe(this);
    delete m_project_document;
    delete m_messageService;
}

//! Reads settings of ProjectManager from global settings.

void ProjectManager::readSettings()
{
    QSettings settings;
    m_workingDirectory = QDir::homePath();
    if (settings.childGroups().contains(S_PROJECTMANAGER)) {
        settings.beginGroup(S_PROJECTMANAGER);

        if (!settings.contains(S_AUTOSAVE))
            settings.setValue(S_AUTOSAVE, true);

        m_workingDirectory = settings.value(S_DEFAULTPROJECTPATH).toString();
        m_recentProjects = settings.value(S_RECENTPROJECTS).toStringList();

        if (settings.contains(S_LASTUSEDIMPORTDIR))
            m_importDirectory = settings.value(S_LASTUSEDIMPORTDIR, QString()).toString();

        setAutosaveEnabled(settings.value(S_AUTOSAVE).toBool());

        settings.endGroup();
    }
}

//! Saves settings of ProjectManager in global settings.

void ProjectManager::writeSettings()
{
    QSettings settings;
    settings.beginGroup(S_PROJECTMANAGER);
    settings.setValue(S_DEFAULTPROJECTPATH, m_workingDirectory);
    settings.setValue(S_RECENTPROJECTS, m_recentProjects);

    if (!m_importDirectory.isEmpty())
        settings.setValue(S_LASTUSEDIMPORTDIR, m_importDirectory);

    settings.endGroup();
}

ProjectDocument* ProjectManager::document()
{
    return m_project_document;
}

//! Returns list of recent projects, validates if projects still exists on disk.

QStringList ProjectManager::recentProjects()
{
    QStringList updatedList;
    for (QString fileName : m_recentProjects) {
        QFile fin(fileName);
        if (fin.exists())
            updatedList.append(fileName);
    }
    m_recentProjects = updatedList;
    return m_recentProjects;
}

//! Returns name of the current project directory.

QString ProjectManager::projectDir() const
{
    if (m_project_document && m_project_document->hasValidNameAndPath())
        return m_project_document->projectDir();

    return "";
}

//! Returns directory name suitable for saving plots.

QString ProjectManager::userExportDir() const
{
    QString result = projectDir();
    if (result.isEmpty())
        result = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    return result;
}

//! Returns directory name which was used by the user to import files.

QString ProjectManager::userImportDir() const
{
    return m_importDirectory.isEmpty() ? userExportDir() : m_importDirectory;
}

//! Sets user import directory in system settings.

void ProjectManager::setImportDir(const QString& dirname)
{
    m_importDirectory = dirname;
}

bool ProjectManager::isAutosaveEnabled() const
{
    return m_saveService->isAutosaveEnabled();
}

void ProjectManager::setAutosaveEnabled(bool value)
{
    m_saveService->setAutosaveEnabled(value);
    QSettings settings;
    settings.setValue(S_PROJECTMANAGER + "/" + S_AUTOSAVE, value);
}

//! Updates title of main window when the project was modified.

void ProjectManager::onDocumentModified()
{
    if (m_project_document->isModified()) {
        m_mainWindow->setWindowTitle("*" + m_project_document->projectName());
    } else {
        m_mainWindow->setWindowTitle(m_project_document->projectName());
    }
}

//! Clears list of recent projects.

void ProjectManager::clearRecentProjects()
{
    m_recentProjects.clear();
    modified();
}

//! Processes new project request (close old project, rise dialog for project name, create project).

void ProjectManager::newProject()
{
    if (!closeCurrentProject())
        return;

    QString projectFileName = acquireProjectFileName();

    if (!projectFileName.isEmpty()) {
        createNewProject();
        saveProject(projectFileName);
    }
}

//! Processes close current project request. Call save/discard/cancel dialog, if necessary.
//! Returns false if saving was canceled.

bool ProjectManager::closeCurrentProject()
{
    if (!m_project_document)
        return true;

    bool projectWasClosed(true);

    if (m_project_document && m_project_document->isModified()) {
        QMessageBox msgBox;
        msgBox.setText("The project has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Save:
            if (!saveProject())
                projectWasClosed = false;
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            projectWasClosed = false;
            break;
        default:
            break;
        }
    }

    if (projectWasClosed)
        deleteCurrentProject();

    return projectWasClosed;
}

//! Processes save project request.

bool ProjectManager::saveProject(QString projectFileName)
{
    if (projectFileName.isEmpty()) {
        if (m_project_document->hasValidNameAndPath())
            projectFileName = m_project_document->projectFileName();
        else
            projectFileName = acquireProjectFileName();
    }

    if (projectFileName.isEmpty())
        return false;

    try {
        m_saveService->save(projectFileName);

    } catch (const std::exception& ex) {
        QString message = QString("Failed to save project under '%1'. \n\n").arg(projectFileName);
        message.append("Exception was thrown.\n\n");
        message.append(ex.what());

        QMessageBox::warning(m_mainWindow, "Error while saving project", message);
        return false;
    }

    addToRecentProjects();
    modified();

    return true;
}

//! Processes 'save project as' request.

bool ProjectManager::saveProjectAs()
{
    QString projectFileName = acquireProjectFileName();

    if (projectFileName.isEmpty())
        return false;

    return saveProject(projectFileName);
}

//! Opens existing project. If fileName is empty, will popup file selection dialog.

void ProjectManager::openProject(QString fileName)
{
    if (!closeCurrentProject())
        return;

    if (fileName.isEmpty()) {
        fileName =
            QFileDialog::getOpenFileName(m_mainWindow, "Open project file", workingDirectory(),
                                         "BornAgain project Files (*.pro)");
        if (fileName.isEmpty())
            return;
    }
    createNewProject();
    loadProject(fileName);

    if (m_project_document->isReady()) {
        addToRecentProjects();
    } else if (m_project_document->hasErrors()) {
        riseProjectLoadFailedDialog();
        deleteCurrentProject();
        createNewProject();
    } else if (m_project_document->hasWarnings()) {
        riseProjectLoadWarningDialog();
        addToRecentProjects();
    }
    emit modified();
}

//! Calls dialog window to define project path and name.

void ProjectManager::createNewProject()
{
    if (m_project_document)
        throw GUIHelpers::Error("ProjectManager::createNewProject() -> Project already exists");

    m_messageService->clear();

    m_project_document = new ProjectDocument();
    connect(m_project_document, SIGNAL(modified()), this, SLOT(onDocumentModified()));
    m_project_document->setProjectName("Untitled");
    m_project_document->setApplicationModels(m_mainWindow->models());
    m_project_document->setLogger(m_messageService);

    m_saveService->setDocument(m_project_document);
}

void ProjectManager::deleteCurrentProject()
{
    m_saveService->stopService();

    delete m_project_document;
    m_project_document = 0;
    m_mainWindow->models()->resetModels();
}

//! Load project data from file name. If autosave info exists, opens dialog for project restore.

void ProjectManager::loadProject(const QString& projectFileName)
{
    bool useAutosave = m_saveService && ProjectUtils::hasAutosavedData(projectFileName);

    if (useAutosave && restoreProjectDialog(projectFileName)) {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        m_project_document->load(ProjectUtils::autosaveName(projectFileName));
        m_project_document->setProjectFileName(projectFileName);
        m_project_document->setModified(true);
    } else {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        m_project_document->load(projectFileName);
    }
    QApplication::restoreOverrideCursor();
}

//! Returns project file name from dialog.

QString ProjectManager::acquireProjectFileName()
{
    NewProjectDialog dialog(m_mainWindow, workingDirectory(), untitledProjectName());

    if (dialog.exec() != QDialog::Accepted)
        return "";

    m_workingDirectory = dialog.getWorkingDirectory();

    return dialog.getProjectFileName();
}

//! Add name of the current project to the name of recent projects

void ProjectManager::addToRecentProjects()
{
    QString fileName = m_project_document->projectFileName();
    m_recentProjects.removeAll(fileName);
    m_recentProjects.prepend(fileName);
    while (m_recentProjects.size() > Constants::MAX_RECENT_PROJECTS)
        m_recentProjects.removeLast();
}

//! Returns default project path.

QString ProjectManager::workingDirectory()
{
    return m_workingDirectory;
}

//! Will return 'Untitled' if the directory with such name doesn't exist in project
//! path. Otherwise will return Untitled1, Untitled2 etc.

QString ProjectManager::untitledProjectName()
{
    QString result = "Untitled";
    QDir projectDir = workingDirectory() + "/" + result;
    if (projectDir.exists()) {
        for (size_t i = 1; i < 99; ++i) {
            result = QString("Untitled") + QString::number(i);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
            projectDir.setPath(workingDirectory() + "/" + result);
#else
            projectDir = workingDirectory() + "/" + result;
#endif
            if (!projectDir.exists())
                break;
        }
    }
    return result;
}

void ProjectManager::riseProjectLoadFailedDialog()
{
    QString message =
        QString("Failed to load the project '%1' \n\n").arg(m_project_document->projectFileName());

    for (auto details : m_messageService->errorDescriptionList(m_project_document))
        message.append(details + "\n");

    QMessageBox::warning(m_mainWindow, "Error while opening project file", message);
}

void ProjectManager::riseProjectLoadWarningDialog()
{
    ASSERT(m_project_document);
    ProjectLoadWarningDialog* warningDialog = new ProjectLoadWarningDialog(
        m_mainWindow, m_messageService, m_project_document->documentVersion());

    warningDialog->show();
    warningDialog->raise();
}

//! Rises dialog if the project should be restored from autosave. Returns true, if yes.

bool ProjectManager::restoreProjectDialog(const QString& projectFileName)
{
    QString title("Recover project");

    QString message =
        QString("Project '%1' contains autosaved data.\n\n"
                "Project saved at %2\nAutosave from %3")
            .arg(ProjectUtils::projectName(projectFileName))
            .arg(ProjectUtils::lastModified(projectFileName))
            .arg(ProjectUtils::lastModified(ProjectUtils::autosaveName(projectFileName)));

    return GUIHelpers::question(m_mainWindow, title, message,
                                "\nDo you want to restore from autosave?\n", "Yes, please restore.",
                                "No, keep loading original");
}
