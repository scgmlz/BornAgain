// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitPrintService.h
//! @brief     Defines class FitPrintService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_FITTING_FITPRINTSERVICE_H
#define BORNAGAIN_CORE_FITTING_FITPRINTSERVICE_H

#include "Fit/Tools/WallclockTimer.h"
#include "Wrap/WinDllMacros.h"
#include <string>

class FitObjective;

//! Prints fit statistics to standard output during minimizer iterations.

class BA_CORE_API_ FitPrintService
{
public:
    FitPrintService();

    void print(const FitObjective& objective);

private:
    std::string iterationHeaderString(const FitObjective& objective);
    std::string wallTimeString();
    std::string parameterString(const FitObjective& objective);
    std::string fitResultString(const FitObjective& objective);

    WallclockTimer m_run_time;
    WallclockTimer m_last_call_time;
};

#endif // BORNAGAIN_CORE_FITTING_FITPRINTSERVICE_H
