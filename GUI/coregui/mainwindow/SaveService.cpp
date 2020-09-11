// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/SaveService.cpp
//! @brief     Implements class SaveService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/SaveService.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/Views/CommonWidgets/UpdateTimer.h"
#include "GUI/coregui/mainwindow/AutosaveController.h"
#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/mainwindow/SaveThread.h"
#include "GUI/coregui/mainwindow/projectdocument.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QApplication>
#include <QCoreApplication>
#include <QTime>

SaveService::SaveService(QObject* parent)
    : QObject(parent), m_is_saving(false), m_autosave(nullptr), m_document(nullptr)
{
}

void SaveService::setDocument(ProjectDocument* document)
{
    m_document = document;

    if (m_autosave)
        m_autosave->setDocument(document);

    m_save_queue.clear();
}

void SaveService::save(const QString& project_file_name)
{
    ASSERT(m_document);

    m_save_queue.enqueue(project_file_name);
    process_queue();
}

void SaveService::setAutosaveEnabled(bool value)
{
    if (value) {
        delete m_autosave;
        m_autosave = new AutosaveController(this);
        m_autosave->setDocument(m_document);
        connect(m_autosave, &AutosaveController::autosaveRequest, this,
                &SaveService::onAutosaveRequest);
    } else {
        delete m_autosave;
        m_autosave = 0;
    }
}

bool SaveService::isAutosaveEnabled() const
{
    return m_autosave ? true : false;
}

void SaveService::setAutosaveTime(int timerInterval)
{
    if (!m_autosave)
        setAutosaveEnabled(true);

    m_autosave->setAutosaveTime(timerInterval);
}

bool SaveService::isSaving() const
{
    return m_is_saving;
}

//!

void SaveService::stopService()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if (isSaving()) {
        QTime dieTime = QTime::currentTime().addSecs(60);
        while (QTime::currentTime() < dieTime) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            if (!isSaving())
                break;
        }
        if (isSaving())
            throw GUIHelpers::Error("SaveService::stopService() -> Error. Can't stop service. ");
    }

    if (m_autosave)
        m_autosave->removeAutosaveDir();

    setDocument(nullptr);
    QApplication::restoreOverrideCursor();
}

void SaveService::onAutosaveRequest()
{
    save(m_autosave->autosaveName());
}

void SaveService::onProjectSaved()
{
    ASSERT(m_document);
    ASSERT(m_is_saving);

    m_is_saving = false;
    emit projectSaved();

    // processing possible consequent saves
    process_queue();
}

void SaveService::process_queue()
{
    ASSERT(m_document);

    if (m_is_saving)
        return;

    if (!m_save_queue.isEmpty()) {
        m_is_saving = true;

        QString project_file_name = m_save_queue.dequeue();

        // saving project file in a main thread
        const bool isAutosave = project_file_name.contains(ProjectUtils::autosaveSubdir());
        m_document->save_project_file(project_file_name, isAutosave);

        if (m_document->hasData()) {
            // saving heavy data in separate thread
            SaveThread* saveThread = new SaveThread(this);
            saveThread->setSaveContext(m_document, project_file_name);

            connect(saveThread, &SaveThread::saveReady, this, &SaveService::onProjectSaved);
            connect(saveThread, &SaveThread::finished, saveThread, &QObject::deleteLater);
            saveThread->start();
        } else {
            onProjectSaved();
        }
    }
}
