// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobWorker.cpp
//! @brief     Implements class JobWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/JobWorker.h"
#include "Core/Simulation/GISASSimulation.h"
#include <QDateTime>
#include <memory>

JobWorker::JobWorker(const QString& identifier, Simulation* simulation)
    : m_identifier(identifier), m_simulation(simulation), m_percentage_done(0),
      m_job_status("Idle"), m_terminate_request_flag(false), m_simulation_duration(0)
{
}

QString JobWorker::identifier() const
{
    return m_identifier;
}

int JobWorker::progress() const
{
    return m_percentage_done;
}

void JobWorker::start()
{
    m_terminate_request_flag = false;
    m_simulation_duration = 0;
    emit started();

    if (m_simulation) {
        m_simulation->subscribe([this](size_t percentage_done) {
            return updateProgress(static_cast<int>(percentage_done));
        });

        m_job_status = "Running";

        try {
            QDateTime beginTime = QDateTime::currentDateTime();
            m_simulation->runSimulation();
            if (m_job_status != "Canceled")
                m_job_status = "Completed";

            QDateTime endTime = QDateTime::currentDateTime();
            m_simulation_duration = static_cast<int>(beginTime.msecsTo(endTime));

        } catch (const std::exception& ex) {
            m_job_status = "Failed";
            m_percentage_done = 100;
            m_failure_message = "JobRunner::start() -> Simulation failed with exception throw:\n\n";

            m_failure_message.append(QString(ex.what()));
        }

    } else {
        m_job_status = "Failed";
        m_percentage_done = 100;
        m_failure_message = "JobRunner::start() -> Error. Simulation doesn't exist.";
    }

    emit progressUpdate();
    emit finished();
}

QString JobWorker::status() const
{
    return m_job_status;
}

QString JobWorker::failureMessage() const
{
    return m_failure_message;
}

int JobWorker::simulationDuration() const
{
    return m_simulation_duration;
}

//! Sets request for JobRunner to terminate underlying domain simulation.

void JobWorker::terminate()
{
    m_terminate_request_flag = true;
    m_job_status = "Canceled";
}

//! Sets current progress. Returns true if we want to continue the simulation.

bool JobWorker::updateProgress(int percentage_done)
{
    if (percentage_done > m_percentage_done) {
        m_percentage_done = percentage_done;
        emit progressUpdate();
    }
    return !m_terminate_request_flag;
}
