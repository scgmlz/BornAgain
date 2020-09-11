// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/UpdateTimer.cpp
//! @brief     Implements class UpdateTimer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/CommonWidgets/UpdateTimer.h"
#include <QTimer>

UpdateTimer::UpdateTimer(int timerInterval, QObject* parent)
    : QObject(parent), m_update_request_count(0), m_timer_interval(timerInterval), m_is_busy(false),
      m_timer(new QTimer(this))
{
    m_timer->setInterval(m_timer_interval);
    m_timer->setSingleShot(true);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
}

void UpdateTimer::reset()
{
    m_update_request_count = 0;
    m_timer->stop();
    m_is_busy = false;
}

void UpdateTimer::setWallclockTimer(int timerInterval)
{
    m_timer_interval = timerInterval;
}

void UpdateTimer::scheduleUpdate()
{
    if (m_is_busy)
        return;

    ++m_update_request_count;

    if (!m_timer->isActive())
        m_timer->start(m_timer_interval);
}

void UpdateTimer::onTimerTimeout()
{
    m_is_busy = true;

    if (m_update_request_count > 0) {
        m_update_request_count = 0;
        emit timeToUpdate();
    }

    m_is_busy = false;
}
