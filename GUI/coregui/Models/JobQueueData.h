// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobQueueData.h
//! @brief     Defines class JobQueueData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_JOBQUEUEDATA_H
#define BORNAGAIN_GUI_COREGUI_MODELS_JOBQUEUEDATA_H

#include "Wrap/WinDllMacros.h"
#include <QMap>
#include <QObject>

class JobItem;
class JobModel;
class Simulation;
class JobWorker;

//! The JobQueueData class holds all objects/logic to run simulation in a thread.

class BA_CORE_API_ JobQueueData : public QObject
{
    Q_OBJECT
public:
    JobQueueData(JobModel* jobModel);

    bool hasUnfinishedJobs();

signals:
    void globalProgress(int);
    void focusRequest(JobItem* jobItem);

public slots:
    void onStartedJob();
    void onProgressUpdate();
    void onFinishedJob();

    void onFinishedThread();
    void onCancelAllJobs();

    void runJob(JobItem* jobItem);
    void cancelJob(const QString& identifier);
    void removeJob(const QString& identifier);

private:
    void assignForDeletion(QThread* thread);
    void assignForDeletion(JobWorker* worker);
    void clearSimulation(const QString& identifier);
    void processFinishedJob(JobWorker* worker, JobItem* jobItem);

    void updateGlobalProgress();

    QThread* getThread(const QString& identifier);
    JobWorker* getWorker(const QString& identifier);
    Simulation* getSimulation(const QString& identifier);

    QMap<QString, QThread*> m_threads;        //! job identifier to the thread
    QMap<QString, JobWorker*> m_workers;      //! job identifier to jobWorker
    QMap<QString, Simulation*> m_simulations; //! job identifier to simulation

    JobModel* m_jobModel;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_JOBQUEUEDATA_H
