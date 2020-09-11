// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/WallclockTimer.cpp
//! @brief     Implements WallclockTimer class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Tools/WallclockTimer.h"
#include <chrono>

using clock_used = std::chrono::high_resolution_clock;
using duration_unit = std::chrono::seconds;

//! Internal state of a WallclockTimer object.

struct WallclockTimerState {
    std::chrono::time_point<clock_used> m_start_time;
    std::chrono::time_point<clock_used> m_end_time;
    bool m_is_running{false};
};

WallclockTimer::WallclockTimer() : m_state(new WallclockTimerState) {}
WallclockTimer::~WallclockTimer() = default;

void WallclockTimer::start()
{
    m_state->m_is_running = true;
    m_state->m_start_time = clock_used::now();
}

void WallclockTimer::stop()
{
    m_state->m_is_running = false;
    m_state->m_end_time = clock_used::now();
}

double WallclockTimer::runTime() const
{
    duration_unit diff =
        m_state->m_is_running
            ? std::chrono::duration_cast<duration_unit>(clock_used::now() - m_state->m_start_time)
            : std::chrono::duration_cast<duration_unit>(m_state->m_end_time
                                                        - m_state->m_start_time);

    return (double)diff.count();
}
