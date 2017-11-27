// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DelayedProgressCounter.cpp
//! @brief     Implements class DelayedProgressCounter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ProgressHandler.h"
#include "DelayedProgressCounter.h"

void DelayedProgressCounter::stepProgress(ProgressHandler* progress)
{
    ++m_count;
    if( m_count==m_interval ) {
        progress->incrementDone(m_interval);
        m_count = 0;
    }
}
