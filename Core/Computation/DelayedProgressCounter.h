// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DelayedProgressCounter.h
//! @brief     Defines class DelayedProgressCounter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_DELAYEDPROGRESSCOUNTER_H
#define BORNAGAIN_CORE_COMPUTATION_DELAYEDPROGRESSCOUNTER_H

#include <cstddef>

class ProgressHandler;

//! Counter for reporting progress (with delay interval) in a threaded computation.

class DelayedProgressCounter
{
public:
    DelayedProgressCounter(ProgressHandler* p_progress, size_t interval);
    ~DelayedProgressCounter() {}

    //! Increments inner counter; at regular intervals updates progress handler.
    void stepProgress();

private:
    ProgressHandler* mp_progress;
    const size_t m_interval;
    size_t m_count;
};

#endif // BORNAGAIN_CORE_COMPUTATION_DELAYEDPROGRESSCOUNTER_H
