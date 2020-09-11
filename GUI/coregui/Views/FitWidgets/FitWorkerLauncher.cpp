// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitWorkerLauncher.cpp
//! @brief     Implements class FitWorkerLauncher
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/FitWorkerLauncher.h"
#include "GUI/coregui/Views/FitWidgets/FitWorker.h"
#include <QThread>

FitWorkerLauncher::FitWorkerLauncher(QObject* parent)
    : QObject(parent), m_is_fit_running(false), m_duration(0)
{
}

void FitWorkerLauncher::runFitting(std::shared_ptr<FitObjectiveBuilder> suite)
{
    if (!suite || m_is_fit_running)
        return;

    auto thread = new QThread();
    auto fw = new FitWorker(suite);
    fw->moveToThread(thread);

    // start fitting when thread starts
    connect(thread, &QThread::started, fw, &FitWorker::startFit);
    connect(fw, &FitWorker::started, this, &FitWorkerLauncher::intern_workerStarted);

    connect(this, &FitWorkerLauncher::intern_interruptFittingWorker, fw,
            &FitWorker::interruptFitting, Qt::DirectConnection);

    connect(fw, &FitWorker::error, this, &FitWorkerLauncher::intern_error);
    connect(fw, &FitWorker::finished, this, &FitWorkerLauncher::intern_workerFinished);

    // delete fitting worker and thread when done
    connect(fw, SIGNAL(finished(int)), fw, SLOT(deleteLater()));
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    m_is_fit_running = true;
    thread->start();
}

//! Returns duration of fit in msec.

int FitWorkerLauncher::getDuration()
{
    return m_duration;
}

void FitWorkerLauncher::interruptFitting()
{
    if (m_is_fit_running)
        emit intern_interruptFittingWorker();
}

void FitWorkerLauncher::intern_workerFinished(int duration)
{
    m_is_fit_running = false;
    m_duration = duration;
    emit fittingFinished();
}

void FitWorkerLauncher::intern_workerStarted()
{
    emit fittingStarted();
}

void FitWorkerLauncher::intern_error(const QString& mesg)
{
    emit fittingError(mesg);
}
