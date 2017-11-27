// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DelayedProgressCounter.h
//! @brief     Defines class DelayedProgressCounter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DELAYEDPROGRESSCOUNTER_H
#define DELAYEDPROGRESSCOUNTER_H

#include <cstddef>

class ProgressHandler;

//! Counter for reporting progress (with delay interval) in a threaded computation.

class DelayedProgressCounter
{
public:
    DelayedProgressCounter(size_t interval) : m_interval(interval), m_count(0) {}
    ~DelayedProgressCounter() {}

    //! Increments inner counter; at regular intervals updates progress handler.
    void stepProgress(ProgressHandler* progress);
private:
    const size_t m_interval;
    size_t m_count;
};

#endif // DELAYEDPROGRESSCOUNTER_H
