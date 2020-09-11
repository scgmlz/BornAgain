// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/TestMinimizer.cpp
//! @brief     Implements class TrivialMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Minimizer/TestMinimizer.h"
#include "Fit/Kernel/Parameters.h"
#include <sstream>

using namespace Fit;

TestMinimizer::TestMinimizer() {}

TestMinimizer::~TestMinimizer() = default;

std::string TestMinimizer::minimizerName() const
{
    return "Test";
}

MinimizerResult TestMinimizer::minimize_scalar(fcn_scalar_t fcn, Fit::Parameters parameters)
{
    // calling user function once
    auto min_value = fcn(parameters);

    MinimizerResult result;
    result.setParameters(parameters);
    result.setMinValue(min_value);

    std::ostringstream report;
    report << "TestMinimizer::printOutcome() -> Done. Objective function value = " << min_value
           << std::endl;

    result.setReport(report.str());
    result.setNumberOfCalls(1);

    return result;
}
