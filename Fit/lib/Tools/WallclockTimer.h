// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/WallclockTimer.h
//! @brief     Defines WallclockTimer class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef TIMEINTERVAL_H
#define TIMEINTERVAL_H

#include "WinDllMacros.h"
#include <memory>

struct WallclockTimerState;

//! A timer for measuring real (wall-clock) time spent between 'start' and 'stop' commands.

class BA_CORE_API_ WallclockTimer
{
public:
    WallclockTimer();
    ~WallclockTimer();

    void start();
    void stop();

    //! returns run time in sec.
    double runTime() const;

private:
    std::unique_ptr<WallclockTimerState> m_state;
};

#endif // TIMEINTERVAL_H
