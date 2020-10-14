// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/projectdocument.cpp
//! @brief     Implements class ProjectDocument
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/projectdocument.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/mainwindow/OutputDataIOService.h"
#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/MessageService.h"
#include <QDir>
#include <QElapsedTimer>
#include <QXmlStreamReader>

namespace
{
const QString minimal_supported_version = "1.6.0";
}

ProjectDocument::ProjectDocument(const QString& projectFileName)
    : m_applicationModels(nullptr), m_modified(false), m_documentStatus(ProjectFlags::STATUS_OK),
      m_messageService(nullptr), m_dataService(new OutputDataIOService(this))
{
    setObjectName("ProjectDocument");
    if (!projectFileName.isEmpty())
        setProjectFileName(projectFileName);
}

QString ProjectDocument::projectName() const
{
    return m_project_name;
}

void ProjectDocument::setProjectName(const QString& text)
{
    if (m_project_name != text) {
        m_project_name = text;
        emit modified();
    }
}

QString ProjectDocument::projectDir() const
{
    return m_project_dir;
}

void ProjectDocument::setProjectDir(const QString& text)
{
    m_project_dir = text;
}

QString ProjectDocument::projectFileName() const
{
    if (!projectName().isEmpty())
        return projectDir() + "/" + projectName() + projectFileExtension();
    else
        return "";
}

void ProjectDocument::setProjectFileName(const QString& projectFileName)
{
    setProjectName(ProjectUtils::projectName(projectFileName));
    setProjectDir(ProjectUtils::projectDir(projectFileName));
}

QString ProjectDocument::projectFileExtension()
{
    return ".pro";
}

void ProjectDocument::setApplicationModels(ApplicationModels* applicationModels)
{
    if (applicationModels != m_applicationModels) {
        disconnectModels();
        m_applicationModels = applicationModels;
        m_dataService->setApplicationModels(m_applicationModels);
        connectModels();
    }
}

void ProjectDocument::save(const QString& project_file_name, bool autoSave)
{
    save_project_data(project_file_name);
    save_project_file(project_file_name, autoSave);
}

void ProjectDocument::save_project_file(const QString& project_file_name, bool autoSave)
{
    QElapsedTimer timer;
    timer.start();

    QFile file(project_file_name);
    if (!file.open(QFile::ReadWrite | QIODevice::Truncate | QFile::Text))
        throw GUIHelpers::Error("ProjectDocument::save_project_file() -> Error. Can't open "
                                "file '"
                                + project_file_name + "' for writing.");

    writeTo(&file);
    file.close();

    if (!autoSave) {
        setProjectFileName(project_file_name);
        m_modified = false;
        emit modified();
    }
}

void ProjectDocument::save_project_data(const QString& project_file_name)
{
    QElapsedTimer timer;
    timer.start();

    m_dataService->save(ProjectUtils::projectDir(project_file_name));
}

void ProjectDocument::load(const QString& project_file_name)
{
    QElapsedTimer timer1, timer2;
    timer1.start();

    m_documentStatus = ProjectFlags::STATUS_OK;
    setProjectFileName(project_file_name);

    QFile file(projectFileName());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString message = QString("Open file error '%1'").arg(file.errorString());
        m_messageService->send_error(this, message);
        ProjectFlags::setFlag(m_documentStatus, ProjectFlags::STATUS_FAILED);
        return;
    }

    try {
        disconnectModels();
        readFrom(&file);
        file.close();

        timer2.start();
        m_dataService->load(projectDir(), m_messageService);
        m_applicationModels->jobModel()->link_instruments();
        connectModels();

        if (m_messageService->warningCount())
            ProjectFlags::setFlag(m_documentStatus, ProjectFlags::STATUS_WARNING);

    } catch (const std::exception& ex) {
        QString message = QString("Exception thrown '%1'").arg(QString(ex.what()));
        m_messageService->send_error(this, message);
        ProjectFlags::setFlag(m_documentStatus, ProjectFlags::STATUS_FAILED);
    }
}

bool ProjectDocument::hasValidNameAndPath()
{
    return (!m_project_name.isEmpty() && !m_project_dir.isEmpty());
}

bool ProjectDocument::isModified()
{
    return m_modified;
}

void ProjectDocument::setModified(bool flag)
{
    m_modified = flag;
    if (m_modified)
        emit modified();
}

void ProjectDocument::setLogger(MessageService* messageService)
{
    m_messageService = messageService;
}

ProjectFlags::DocumentStatus ProjectDocument::documentStatus() const
{
    return m_documentStatus;
}

bool ProjectDocument::isReady() const
{
    return (m_documentStatus == ProjectFlags::STATUS_OK);
}

bool ProjectDocument::hasWarnings() const
{
    return m_documentStatus.testFlag(ProjectFlags::STATUS_WARNING);
}

bool ProjectDocument::hasErrors() const
{
    return m_documentStatus.testFlag(ProjectFlags::STATUS_FAILED);
}

bool ProjectDocument::hasData() const
{
    return !m_dataService->nonXMLItems().isEmpty();
}

QString ProjectDocument::documentVersion() const
{
    QString result(m_currentVersion);
    if (result.isEmpty())
        result = GUIHelpers::getBornAgainVersionString();
    return result;
}

void ProjectDocument::onModelChanged()
{
    m_modified = true;
    emit modified();
}

void ProjectDocument::readFrom(QIODevice* device)
{
    ASSERT(m_messageService);
    QXmlStreamReader reader(device);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == ProjectDocumentXML::BornAgainTag) {
                m_currentVersion = reader.attributes()
                                       .value(ProjectDocumentXML::BornAgainVersionAttribute)
                                       .toString();
                if (!GUIHelpers::isVersionMatchMinimal(m_currentVersion,
                                                       minimal_supported_version)) {
                    ProjectFlags::setFlag(m_documentStatus, ProjectFlags::STATUS_FAILED);
                    QString message = QString("Can't open document version '%1', "
                                              "minimal supported version '%2'")
                                          .arg(m_currentVersion)
                                          .arg(minimal_supported_version);
                    m_messageService->send_error(this, message);
                    return;
                }

            }

            else if (reader.name() == ProjectDocumentXML::InfoTag) {
                //
            } else {
                m_applicationModels->readFrom(&reader, m_messageService);
                if (m_messageService->messageCount(m_applicationModels) > 0) {
                    ProjectFlags::setFlag(m_documentStatus, ProjectFlags::STATUS_WARNING);
                }
            }
        }
    }

    if (reader.hasError()) {
        ProjectFlags::setFlag(m_documentStatus, ProjectFlags::STATUS_FAILED);
        QString message = QString("Format error '%1'").arg(reader.errorString());
        m_messageService->send_error(this, message);
        return;
    }
}

void ProjectDocument::writeTo(QIODevice* device)
{
    QXmlStreamWriter writer(device);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("BornAgain");
    QString version_string = GUIHelpers::getBornAgainVersionString();
    writer.writeAttribute("Version", version_string);

    writer.writeStartElement(ProjectDocumentXML::InfoTag);
    writer.writeAttribute(ProjectDocumentXML::InfoNameAttribute, projectName());
    writer.writeEndElement(); // InfoTag

    m_applicationModels->writeTo(&writer);

    writer.writeEndElement(); // BornAgain tag
    writer.writeEndDocument();
}

void ProjectDocument::disconnectModels()
{
    if (m_applicationModels)
        disconnect(m_applicationModels, SIGNAL(modelChanged()), this, SLOT(onModelChanged()));
}

void ProjectDocument::connectModels()
{
    if (m_applicationModels)
        connect(m_applicationModels, SIGNAL(modelChanged()), this, SLOT(onModelChanged()),
                Qt::UniqueConnection);
}
