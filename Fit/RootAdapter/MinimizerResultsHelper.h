// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/MinimizerResultsHelper.h
//! @brief     Declares class MinimizerResultsHelper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERRESULTSHELPER_H
#define MINIMIZERRESULTSHELPER_H

#include "WinDllMacros.h"
#include <string>

class RootMinimizerAdapter;
class FitParameterSet;

//! Contains all logic to generate reports with the result of minimization.
//! @ingroup fitting_internal

class BA_CORE_API_ MinimizerResultsHelper {
public:
    MinimizerResultsHelper() {}

    //! Reports results of minimization in the form of multi-line string
    static std::string reportOutcome(const RootMinimizerAdapter* minimizer);

    //! Reports fit parameters settings and final results
    static std::string reportParameters(const FitParameterSet* parameters);

private:
    static std::string reportDescription(const RootMinimizerAdapter* minimizer);
    static std::string reportOption(const RootMinimizerAdapter* minimizer);
    static std::string reportStatus(const RootMinimizerAdapter* minimizer);
};

#endif // MINIMIZERRESULTSHELPER_H
