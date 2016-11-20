// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/MinimizerResultsHelper.h
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
#include <sstream>
#include <iomanip>

class RootMinimizerAdapter;
class FitParameterSet;

//! Contains all logic to generate reports with the result of minimization.
//! @ingroup fitting_internal

class BA_CORE_API_ MinimizerResultsHelper {
public:
    MinimizerResultsHelper() {}

    //! Reports results of minimization in the form of multi-line string
    std::string reportResults(const RootMinimizerAdapter* minimizer) const;

    //! Reports fit parameters settings and final results
    std::string reportResults(const FitParameterSet* parameters) const;

private:
    std::string reportDescription(const RootMinimizerAdapter* minimizer) const;
    std::string reportOption(const RootMinimizerAdapter* minimizer) const;
    std::string reportStatus(const RootMinimizerAdapter* minimizer) const;
};

template <typename T>
std::string to_string_with_precision(const T a_value, int precision = 10, int width = 0)
{
    std::ostringstream out;
    if(width != 0)
        out << std::setw(14) << std::left;
    out << std::setprecision(precision) << a_value;
    return out.str();
}

template <typename T>
std::string to_string_scientific(const T a_value, int n = 10)
{
    std::ostringstream out;
    out << std::scientific << std::setprecision(n) << a_value;
    return out.str();
}

#endif // MINIMIZERRESULTSHELPER_H
