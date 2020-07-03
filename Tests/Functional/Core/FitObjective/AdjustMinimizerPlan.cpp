// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/FitObjective/AdjustMinimizerPlan.cpp
//! @brief     Implements collection of AdjustMinimizerPlan classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "AdjustMinimizerPlan.h"
#include "FitObjective.h"
#include "KernelTypes.h"
#include "Minimizer.h"
#include "Parameters.h"
#include "Units.h"
#include <iostream>

namespace
{
const double nm = Units::nanometer;
}

using namespace Fit;

AdjustMinimizerPlan::AdjustMinimizerPlan() : FitPlan("AdjustMinimizerPlan")
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISASFit");
    addParameter(Parameter("height", 2.0 * nm, AttLimits::limited(0.01, 30.0), 0.05), 5.0 * nm);
    addParameter(Parameter("radius", 10.0 * nm, AttLimits::limited(0.01, 30.0), 0.05), 5.0 * nm);
}

bool AdjustMinimizerPlan::checkMinimizer(Fit::Minimizer& minimizer)
{
    auto fit_objective = createFitObjective();

    fcn_scalar_t scalar_func = [&](const Fit::Parameters& params) {
        return fit_objective->evaluate(params);
    };

    // first fit using Genetic algorithm
    bool success(true);
    minimizer.setMinimizer("Genetic", "", "MaxIterations=2;RandomSeed=1");
    auto result = minimizer.minimize(scalar_func, parameters());
    fit_objective->finalize(result);

    auto best_params_so_far = result.parameters();

    // second fit with Minuit
    minimizer.setMinimizer("Minuit2", "Migrad");
    result = minimizer.minimize(scalar_func, best_params_so_far);
    fit_objective->finalize(result);

    std::cout << "FitPlan::checkResult() -> " << name() << std::endl;
    success &= valuesAsExpected(result.parameters().values());
    std::cout << std::endl;

    return success;
}
