//  ************************************************************************************************
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
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_FIT_TOOLS_WALLCLOCKTIMER_H
#define BORNAGAIN_FIT_TOOLS_WALLCLOCKTIMER_H

#include <memory>

struct WallclockTimerState;

//! A timer for measuring real (wall-clock) time spent between 'start' and 'stop' commands.

class WallclockTimer {
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

#endif // BORNAGAIN_FIT_TOOLS_WALLCLOCKTIMER_H
#endif // USER_API
