// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitWorker.cpp
//! @brief     Implements class FitWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/FitWorker.h"
#include "GUI/coregui/Views/FitWidgets/FitObjectiveBuilder.h"
#include <QDateTime>

void FitWorker::startFit()
{
    int duration(0);
    QDateTime beginTime = QDateTime::currentDateTime();

    emit started();
    try {
        m_fit_objective->runFit();
        duration = durationSince(beginTime);

    } catch (const std::exception& ex) {
        duration = durationSince(beginTime);
        emit error(QString::fromLatin1(ex.what()));
    }
    emit finished(duration);
}

void FitWorker::interruptFitting()
{
    if (m_fit_objective)
        m_fit_objective->interruptFitting();
}

int FitWorker::durationSince(const QDateTime& since)
{
    QDateTime endTime = QDateTime::currentDateTime();
    return int(since.msecsTo(endTime));
}
