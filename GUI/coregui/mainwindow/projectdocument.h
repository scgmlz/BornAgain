// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/projectdocument.h
//! @brief     Defines class ProjectDocument
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTDOCUMENT_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTDOCUMENT_H

#include "GUI/coregui/mainwindow/ProjectFlags.h"
#include "Wrap/WinDllMacros.h"
#include <QObject>

class QIODevice;
class ApplicationModels;
class MessageService;
class OutputDataIOService;

namespace ProjectDocumentXML
{
const QString BornAgainTag("BornAgain");
const QString BornAgainVersionAttribute("Version");
const QString InfoTag("DocumentInfo");
const QString InfoNameAttribute("ProjectName");
} // namespace ProjectDocumentXML

//! Project document class handles all data related to the opened project
//! (sample, jobModel, project specific windows settings)
//!
//! e.g. if project file is /home/users/development/Untitled/Untitled.pro
//! projectName()     - 'Untitled'
//! projectDir()      - '/home/users/development/Untitled
//! projectFileName() - '/home/users/development/Untitled/Untitled.pro'
class BA_CORE_API_ ProjectDocument : public QObject
{
    Q_OBJECT

public:
    ProjectDocument(const QString& projectFileName = "");

    QString projectName() const;
    void setProjectName(const QString& text);

    QString projectDir() const;
    void setProjectDir(const QString& text);

    QString projectFileName() const;
    void setProjectFileName(const QString& text);

    static QString projectFileExtension();

    void setApplicationModels(ApplicationModels* applicationModels);

    void save(const QString& project_file_name, bool autoSave = false);

    void save_project_file(const QString& project_file_name, bool autoSave = false);
    void save_project_data(const QString& project_file_name);

    void load(const QString& project_file_name);

    bool hasValidNameAndPath();

    bool isModified();
    void setModified(bool flag);

    void setLogger(MessageService* messageService);

    ProjectFlags::DocumentStatus documentStatus() const;

    bool isReady() const;

    bool hasWarnings() const;

    bool hasErrors() const;

    bool hasData() const;

    QString documentVersion() const;

signals:
    void modified();

public slots:
    void onModelChanged();

private:
    void readFrom(QIODevice* device);
    void writeTo(QIODevice* device);

    void disconnectModels();
    void connectModels();

    QString m_project_dir;
    QString m_project_name;
    ApplicationModels* m_applicationModels;
    bool m_modified;
    ProjectFlags::DocumentStatus m_documentStatus;
    MessageService* m_messageService;
    QString m_currentVersion;
    OutputDataIOService* m_dataService;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_PROJECTDOCUMENT_H
