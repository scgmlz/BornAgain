// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobQueueData.cpp
//! @brief     Implements class JobQueueData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/JobQueueData.h"
#include "Core/Simulation/GISASSimulation.h"
#include "GUI/coregui/Models/DomainSimulationBuilder.h"
#include "GUI/coregui/Models/InstrumentItems.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/JobWorker.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QThread>

namespace
{

}

JobQueueData::JobQueueData(JobModel* jobModel) : m_jobModel(jobModel) {}

bool JobQueueData::hasUnfinishedJobs()
{
    return m_simulations.size();
}

//! Submits job and run it in a thread.

void JobQueueData::runJob(JobItem* jobItem)
{
    QString identifier = jobItem->getIdentifier();
    if (getThread(identifier))
        return;

    if (getSimulation(identifier))
        throw GUIHelpers::Error("JobQueueData::runJob() -> Error. Simulation is already existing.");

    try {
        auto simulation = DomainSimulationBuilder::createSimulation(
            jobItem->multiLayerItem(), jobItem->instrumentItem(), jobItem->simulationOptionsItem());
        m_simulations[identifier] = simulation.release();
    } catch (const std::exception& ex) {
        QString message("JobQueueData::runJob() -> Error. "
                        "Attempt to create sample/instrument object from user description "
                        "has failed with following error message.\n\n");
        message += QString::fromStdString(std::string(ex.what()));
        jobItem->setComments(message);
        jobItem->setProgress(100);
        jobItem->setStatus("Failed");
        emit focusRequest(jobItem);
        return;
    }

    auto worker = new JobWorker(identifier, m_simulations[identifier]);
    m_workers[identifier] = worker;

    auto thread = new QThread;
    worker->moveToThread(thread);
    m_threads[identifier] = thread;

    // thread will start the worker
    connect(thread, &QThread::started, worker, &JobWorker::start);

    // finished thread will be removed from the list
    connect(thread, &QThread::finished, this, &JobQueueData::onFinishedThread);

    // connecting the worker to started/progress slots
    connect(worker, &JobWorker::started, this, &JobQueueData::onStartedJob);
    connect(worker, &JobWorker::progressUpdate, this, &JobQueueData::onProgressUpdate);

    // finished job will do all cleanup
    connect(worker, &JobWorker::finished, this, &JobQueueData::onFinishedJob);

    thread->start();
}

//! Cancels running job.

void JobQueueData::cancelJob(const QString& identifier)
{
    if (getThread(identifier))
        getWorker(identifier)->terminate();
}

//! Remove job from list completely.

void JobQueueData::removeJob(const QString& identifier)
{
    cancelJob(identifier);
    clearSimulation(identifier);
}

//! Sets JobItem properties when the job is going to start.

void JobQueueData::onStartedJob()
{
    auto worker = qobject_cast<JobWorker*>(sender());

    auto jobItem = m_jobModel->getJobItemForIdentifier(worker->identifier());
    jobItem->setProgress(0);
    jobItem->setStatus("Running");
    jobItem->setBeginTime(GUIHelpers::currentDateTime());
    jobItem->setEndTime(QString());
}

//! Performs necessary actions when job is finished.

void JobQueueData::onFinishedJob()
{
    auto worker = qobject_cast<JobWorker*>(sender());

    auto jobItem = m_jobModel->getJobItemForIdentifier(worker->identifier());
    processFinishedJob(worker, jobItem);

    // I tell to the thread to exit here (instead of connecting JobRunner::finished
    // to the QThread::quit because of strange behaviour)
    getThread(worker->identifier())->quit();

    emit focusRequest(jobItem);

    clearSimulation(worker->identifier());
    assignForDeletion(worker);

    if (!hasUnfinishedJobs())
        emit globalProgress(100);
}

void JobQueueData::onFinishedThread()
{
    auto thread = qobject_cast<QThread*>(sender());
    assignForDeletion(thread);
}

void JobQueueData::onProgressUpdate()
{
    auto worker = qobject_cast<JobWorker*>(sender());
    auto jobItem = m_jobModel->getJobItemForIdentifier(worker->identifier());
    jobItem->setProgress(worker->progress());
    updateGlobalProgress();
}

//! Estimates global progress from the progress of multiple running jobs and
//! emmits appropriate signal.

void JobQueueData::updateGlobalProgress()
{
    int global_progress(0);
    int nRunningJobs(0);
    QModelIndex parentIndex;
    for (int i_row = 0; i_row < m_jobModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_jobModel->index(i_row, 0, parentIndex);
        JobItem* jobItem = m_jobModel->getJobItemForIndex(itemIndex);
        if (jobItem->isRunning()) {
            global_progress += jobItem->getProgress();
            nRunningJobs++;
        }
    }

    if (nRunningJobs)
        global_progress /= nRunningJobs;
    else
        global_progress = -1;

    emit globalProgress(global_progress);
}

//! Cancels all running jobs.

void JobQueueData::onCancelAllJobs()
{
    for (const auto& key : m_threads.keys())
        cancelJob(key);
}

//! Removes QThread from the map of known threads, assigns it for deletion.

void JobQueueData::assignForDeletion(QThread* thread)
{
    for (auto it = m_threads.begin(); it != m_threads.end(); ++it) {
        if (it.value() == thread) {
            thread->deleteLater();
            m_threads.erase(it);
            return;
        }
    }

    throw GUIHelpers::Error("JobQueueData::assignForDeletion() -> Error! Can't find thread.");
}

//! Removes JobRunner from the map of known runners, assigns it for deletion.

void JobQueueData::assignForDeletion(JobWorker* worker)
{
    ASSERT(worker);
    worker->disconnect();
    for (auto it = m_workers.begin(); it != m_workers.end(); ++it) {
        if (it.value() == worker) {
            m_workers.erase(it);
            delete worker;
            return;
        }
    }

    throw GUIHelpers::Error("JobQueueData::assignForDeletion() -> Error! Can't find the runner.");
}

void JobQueueData::clearSimulation(const QString& identifier)
{
    auto simulation = getSimulation(identifier);
    m_simulations.remove(identifier);
    delete simulation;
}

//! Set all data of finished job

void JobQueueData::processFinishedJob(JobWorker* worker, JobItem* jobItem)
{
    jobItem->setEndTime(GUIHelpers::currentDateTime());
    jobItem->setDuration(worker->simulationDuration());

    // propagating status of runner
    if (worker->status() == "Failed") {
        jobItem->setComments(worker->failureMessage());
    } else {
        // propagating simulation results
        auto simulation = getSimulation(worker->identifier());
        jobItem->setResults(simulation);
    }
    jobItem->setStatus(worker->status());

    // fixing job progress (if job was successfull, but due to wrong estimation, progress not 100%)
    if (jobItem->isCompleted())
        jobItem->setProgress(100);
}

//! Returns the thread for given identifier.

QThread* JobQueueData::getThread(const QString& identifier)
{
    auto it = m_threads.find(identifier);
    return it != m_threads.end() ? it.value() : nullptr;
}

//! Returns job runner for given identifier.

JobWorker* JobQueueData::getWorker(const QString& identifier)
{
    auto it = m_workers.find(identifier);
    return it != m_workers.end() ? it.value() : nullptr;
}

//! Returns the simulation (if exists) for given identifier.

Simulation* JobQueueData::getSimulation(const QString& identifier)
{
    auto it = m_simulations.find(identifier);
    return it != m_simulations.end() ? it.value() : nullptr;
}
