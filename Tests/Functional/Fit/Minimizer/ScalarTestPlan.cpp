// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/ScalarTestPlan.cpp
//! @brief     Implements class ScalarTestPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Fit/Minimizer/ScalarTestPlan.h"
#include "Fit/Kernel/Minimizer.h"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace Fit;

ScalarTestPlan::ScalarTestPlan(const std::string& name, scalar_function_t func,
                               double expected_minimum, double tolerance)
    : MinimizerTestPlan(name), m_objective_function(func), m_expected_minimum(expected_minimum),
      m_tolerance_on_minimum(tolerance)
{
}

//! Returns true if found minimum of objective function coincide with expected.

bool ScalarTestPlan::minimumAsExpected(double found_minimum, double tolerance) const
{
    bool success(true);

    double diff = std::abs(found_minimum - m_expected_minimum);
    if (diff > tolerance)
        success = false;

    std::ostringstream text;
    text << "Found minimum:" << found_minimum << " Expected minimum:" << m_expected_minimum
         << " diff:" << diff << " " << (success ? "OK" : "FAILED");
    std::cout << text.str() << std::endl;

    return success;
}

bool ScalarTestPlan::checkMinimizer(Minimizer& minimizer)
{
    bool success(true);

    auto result = minimizer.minimize(scalarFunction(), parameters());
    std::cout << result.toString() << std::endl;

    std::cout << "ScalarTestPlan::checkResult() -> " << name() << std::endl;

    success &= valuesAsExpected(result.parameters().values());
    success &= minimumAsExpected(result.minValue(), m_tolerance_on_minimum);
    std::cout << std::endl;

    return success;
}

fcn_scalar_t ScalarTestPlan::scalarFunction() const
{
    fcn_scalar_t func = [&](const Parameters& params) {
        return m_objective_function(params.values());
    };
    return func;
}
