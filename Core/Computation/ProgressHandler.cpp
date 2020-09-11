// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProgressHandler.cpp
//! @brief     Implements class ProgressHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/ProgressHandler.h"
#include <mutex>
#include <stdexcept>

void ProgressHandler::subscribe(ProgressHandler::Callback_t inform)
{
    if (m_inform)
        throw std::runtime_error("Invalid call of ProgressHandler::subscribe: "
                                 "currently, no more than one subscriber is allowed");
    m_inform = inform;
}

//! Increments number of completed computation steps (ticks).
//! Performs callback (method m_inform) to inform the subscriber about
//! the state of the computation and to obtain as return value a flag
//! that indicates whether to continue the computation.
void ProgressHandler::incrementDone(size_t ticks_done)
{
    static std::mutex single_mutex;
    std::unique_lock<std::mutex> single_lock(single_mutex);

    m_completed_nticks += ticks_done;
    if (m_completed_nticks > m_expected_nticks)
        m_expected_nticks = m_completed_nticks + 1;

    int percentage_done = (int)(100. * m_completed_nticks / m_expected_nticks);
    // fractional part is discarded, which is fine here:
    // the value 100 is only returned if everything is done

    m_continuation_flag = (!m_inform || m_inform(percentage_done)) && m_continuation_flag;
}
