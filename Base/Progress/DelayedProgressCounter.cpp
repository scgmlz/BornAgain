//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Progress/DelayedProgressCounter.cpp
//! @brief     Implements class DelayedProgressCounter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Base/Progress/DelayedProgressCounter.h"
#include "Base/Progress/ProgressHandler.h"

DelayedProgressCounter::DelayedProgressCounter(ProgressHandler* p_progress, size_t interval)
    : m_progress(p_progress), m_interval(interval), m_count(0) {}

void DelayedProgressCounter::stepProgress() {
    ++m_count;
    if (m_count == m_interval) {
        m_progress->incrementDone(m_interval);
        m_count = 0;
    }
}
