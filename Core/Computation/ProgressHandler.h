// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ProgressHandler.h
//! @brief     Defines class ProgressHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_PROGRESSHANDLER_H
#define BORNAGAIN_CORE_COMPUTATION_PROGRESSHANDLER_H

#include "Wrap/WinDllMacros.h"
#include <functional>

class MultiLayer;

//! Maintains information about progress of a computation.
//! Owner is the computation, which periodically calls the thread-safe function incrementDone(..).
//! An application (GUI or script) may subscribe(..) to be informed about progress.
//! It is then periodically called back by inform(..).
//! The return value of inform(..) can be used to request termination of the computation.
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ ProgressHandler
{
public:
    typedef std::function<bool(size_t)> Callback_t;

    ProgressHandler()
        : m_inform(nullptr), m_expected_nticks(0), m_completed_nticks(0), m_continuation_flag(true)
    {
    }
    ProgressHandler(const ProgressHandler& other)
        : m_inform(other.m_inform) // not clear whether we want multiple copies of this
          ,
          m_expected_nticks(other.m_expected_nticks), m_completed_nticks(other.m_completed_nticks)
    {
    }
    void subscribe(ProgressHandler::Callback_t callback);
    void reset()
    {
        m_completed_nticks = 0;
        m_continuation_flag = true;
    }
    void setExpectedNTicks(size_t n) { m_expected_nticks = n; }
    void incrementDone(size_t ticks_done);
    bool alive() { return m_continuation_flag; }

private:
    Callback_t m_inform;
    size_t m_expected_nticks;
    size_t m_completed_nticks;
    bool m_continuation_flag;
    bool defaultMonitorExec(int);
};

#endif // BORNAGAIN_CORE_COMPUTATION_PROGRESSHANDLER_H
