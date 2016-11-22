// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ThreadInfo.h
//! @brief     Defines struct ThreadInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef THREADINFO_H
#define THREADINFO_H

#include "WinDllMacros.h"

//! Information to run simulation with dedicated number of threads.
//! @ingroup simulation

struct BA_CORE_API_ ThreadInfo
{
    ThreadInfo();
    int n_threads;
    int current_thread;
    int n_batches;
    int current_batch;
};

inline ThreadInfo::ThreadInfo()
    : n_threads(0)
    , current_thread(0)
    , n_batches(1)
    , current_batch(0)
{
}

#endif // THREADINFO_H
