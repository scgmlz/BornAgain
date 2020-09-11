// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/ResidualTestPlan.cpp
//! @brief     Implements class ResidualTestPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Fit/Minimizer/ResidualTestPlan.h"
#include "Fit/Kernel/Minimizer.h"
#include "Fit/Kernel/Parameters.h"
#include "Fit/TestEngine/Numeric.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace Fit;

ResidualTestPlan::ResidualTestPlan(const std::string& name, test_funct_t func)
    : MinimizerTestPlan(name), m_test_func(func)
{
    m_xvalues.resize(101);
    for (int i = 0; i <= 100; ++i)
        m_xvalues[i] = i * 0.1;
}

fcn_residual_t ResidualTestPlan::residualFunction()
{
    fcn_residual_t func = [&](Fit::Parameters pars) -> std::vector<double> {
        return evaluate(pars.values());
    };

    return func;
}

bool ResidualTestPlan::checkMinimizer(Minimizer& minimizer)
{
    bool success(true);

    auto result = minimizer.minimize(residualFunction(), parameters());
    std::cout << result.toString() << std::endl;

    std::cout << "ScalarTestPlan::checkResult() -> " << name() << std::endl;
    success &= valuesAsExpected(result.parameters().values());
    std::cout << std::endl;

    return success;
}

void ResidualTestPlan::init_data_values()
{
    std::vector<double> pars;
    for (const auto& plan : m_parameter_plan)
        pars.push_back(plan.expectedValue());

    for (auto x : m_xvalues)
        m_data_values.push_back(m_test_func(x, pars));
}

std::vector<double> ResidualTestPlan::evaluate(const std::vector<double>& pars)
{
    if (m_data_values.empty())
        init_data_values();

    std::vector<double> result;

    size_t index(0);
    for (auto x : m_xvalues) {
        result.push_back(m_test_func(x, pars) - m_data_values[index]);
        ++index;
    }

    return result;
}
