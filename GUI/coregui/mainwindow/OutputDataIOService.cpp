// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/OutputDataIOService.cpp
//! @brief     Implements class OutputDataIOService
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/OutputDataIOService.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "GUI/coregui/Models/ApplicationModels.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/mainwindow/ProjectUtils.h"
#include "GUI/coregui/mainwindow/SaveLoadInterface.h"
#include "GUI/coregui/utils/MessageService.h"

namespace
{
JobItem* parentJobItem(SaveLoadInterface* item);
} // namespace

OutputDataIOService::OutputDataIOService(QObject* parent)
    : QObject(parent), m_applicationModels(nullptr)
{
    setObjectName("OutputDataIOService");
}

OutputDataIOService::OutputDataIOService(ApplicationModels* models, QObject* parent)
    : QObject(parent), m_applicationModels(nullptr)
{
    setObjectName("OutputDataIOService");
    setApplicationModels(models);
}

void OutputDataIOService::setApplicationModels(ApplicationModels* models)
{
    m_applicationModels = models;
}

void OutputDataIOService::save(const QString& projectDir)
{
    if (!m_history.hasHistory(projectDir))
        m_history.setHistory(projectDir, OutputDataDirHistory());

    OutputDataDirHistory newHistory;

    for (auto item : nonXMLItems()) {
        if (m_history.wasModifiedSinceLastSave(projectDir, item))
            item->save(projectDir);
        newHistory.markAsSaved(item);
    }

    // dealing with files
    QStringList oldFiles = m_history.savedFileNames(projectDir);
    QStringList newFiles = newHistory.savedFileNames();
    cleanOldFiles(projectDir, oldFiles, newFiles);

    // if oldHistory contained some deleted items, that info will be dropped here
    m_history.setHistory(projectDir, newHistory);
}

void OutputDataIOService::load(const QString& projectDir, MessageService* messageService)
{
    OutputDataDirHistory newHistory;

    for (auto item : nonXMLItems()) {
        try {
            item->load(projectDir);
            newHistory.markAsSaved(item);
            // handling crash of GUI during job run and non-existing file
            if (auto jobItem = parentJobItem(item)) {
                if (jobItem->isRunning()) {
                    jobItem->setComments("Possible GUI crash while job was running");
                    jobItem->setStatus("Failed");
                }
            }

        } catch (const std::exception& ex) {
            if (auto jobItem = parentJobItem(item)) {
                // Handling corrupted file on disk
                jobItem->setComments(
                    QString("Load of the data from disk failed with '%1'").arg(QString(ex.what())));
                jobItem->setStatus("Failed");
            }
            if (messageService)
                messageService->send_warning(this, QString(ex.what()));
            else
                throw ex;
        }
    }
    m_history.setHistory(projectDir, newHistory);
}

//! Returns all non-XML items available for save/load.

QVector<SaveLoadInterface*> OutputDataIOService::nonXMLItems() const
{
    QVector<SaveLoadInterface*> result;

    if (!m_applicationModels)
        return result;

    for (auto item : m_applicationModels->nonXMLData())
        if (auto non_xml_item = dynamic_cast<SaveLoadInterface*>(item))
            result.push_back(non_xml_item);

    return result;
}

//! Clean old saved files.
//! All files in oldSaves list, which are not in newSaves list, will be removed.

void OutputDataIOService::cleanOldFiles(const QString& projectDir, const QStringList& oldSaves,
                                        const QStringList& newSaves)
{
    QStringList to_remove = ProjectUtils::substract(oldSaves, newSaves);
    ProjectUtils::removeFiles(projectDir, to_remove);
}

namespace
{
JobItem* parentJobItem(SaveLoadInterface* item)
{
    auto session_item = dynamic_cast<SessionItem*>(item); // sidecast
    auto jobItem = dynamic_cast<const JobItem*>(ModelPath::ancestor(session_item, "JobItem"));
    return const_cast<JobItem*>(jobItem);
}
} // namespace
