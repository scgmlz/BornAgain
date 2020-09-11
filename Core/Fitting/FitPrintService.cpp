// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitPrintService.cpp
//! @brief     Defines class FitPrintService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Fitting/FitPrintService.h"
#include "Core/Fitting/FitObjective.h"
#include "Fit/Kernel/MinimizerResult.h"
#include "Fit/Tools/StringUtils.h"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace
{

size_t length_of_longest_name(const Fit::Parameters& params)
{
    size_t result(0);
    for (const auto& par : params) {
        if (par.name().size() > result)
            result = par.name().size();
    }
    return result;
}

} // namespace

FitPrintService::FitPrintService() = default;

void FitPrintService::print(const FitObjective& objective)
{
    std::ostringstream ostr;

    if (objective.isFirstIteration()) {
        m_run_time.start();
        m_last_call_time.start();
    }

    ostr << iterationHeaderString(objective);
    ostr << wallTimeString();
    ostr << parameterString(objective);

    if (objective.isCompleted())
        ostr << fitResultString(objective);

    std::cout << ostr.str() << "\n";
}

std::string FitPrintService::iterationHeaderString(const FitObjective& objective)
{
    std::ostringstream result;

    result << "FitPrintService::update() -> Info."
           << " NCall:" << objective.iterationInfo().iterationCount() << " Chi2:" << std::scientific
           << std::setprecision(8) << objective.iterationInfo().chi2() << "\n";

    return result.str();
}

std::string FitPrintService::wallTimeString()
{
    std::ostringstream result;

    m_last_call_time.stop();
    result << "Wall time since last call:" << std::fixed << std::setprecision(2)
           << m_last_call_time.runTime() << "\n";
    m_last_call_time.start();

    return result.str();
}

std::string FitPrintService::parameterString(const FitObjective& objective)
{
    std::ostringstream result;

    const auto params = objective.iterationInfo().parameters();
    const auto length = length_of_longest_name(params);

    for (const auto& par : params) {
        result << StringUtils::padRight(par.name(), length) << std::scientific
               << std::setprecision(6) << "  " << par.startValue() << " " << par.limits().toString()
               << "  " << par.value() << "\n";
    }

    return result.str();
}

std::string FitPrintService::fitResultString(const FitObjective& objective)
{
    std::ostringstream result;

    m_run_time.stop();

    result << "This was the last iteration." << std::endl;
    result << "Total time spend: " << std::fixed << std::setprecision(2) << m_run_time.runTime()
           << " sec."
           << "\n\n";

    result << objective.minimizerResult().toString();
    return result.str();
}
