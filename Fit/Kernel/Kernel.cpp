// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/Kernel.cpp
//! @brief     Implements class Kernel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Kernel/Kernel.h"
#include "Fit/Minimizer/IMinimizer.h"
#include "Fit/Minimizer/MinimizerFactory.h"

using namespace Fit;

namespace
{
const std::string default_minimizer = "Minuit2";
const std::string default_algorithm = "Migrad";
} // namespace

Kernel::Kernel()
{
    setMinimizer(default_minimizer, default_algorithm);
}

Kernel::~Kernel() = default;

void Kernel::setMinimizer(const std::string& minimizerName, const std::string& algorithmName,
                          const std::string& options)
{
    m_minimizer.reset(MinimizerFactory::createMinimizer(minimizerName, algorithmName, options));
}

void Kernel::setMinimizer(IMinimizer* minimizer)
{
    m_minimizer.reset(minimizer);
}

MinimizerResult Kernel::minimize(fcn_scalar_t fcn, const Parameters& parameters)
{
    setParameters(parameters);

    m_timer.start();
    if (m_minimizer->requiresResiduals())
        throw std::runtime_error(
            "Error in Kernel::minimize: the chosen minimizer requires residuals computation. "
            "Please use FitObjective::evaluate_residuals with this minimizer.");
    auto result = m_minimizer->minimize_scalar(fcn, parameters);
    m_timer.stop();

    result.setDuration(m_timer.runTime());
    return result;
}

MinimizerResult Kernel::minimize(fcn_residual_t fcn, const Parameters& parameters)
{
    setParameters(parameters);

    m_timer.start();
    auto result = m_minimizer->minimize_residual(fcn, parameters);
    m_timer.stop();

    result.setDuration(m_timer.runTime());
    return result;
}

void Kernel::setParameters(const Parameters& parameters)
{
    m_parameters = parameters;
}
