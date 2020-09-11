// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/Minimizer.cpp
//! @brief     Implements class Minimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Kernel/Minimizer.h"
#include "Fit/Kernel/Kernel.h"
#include "Fit/Kernel/PyCallback.h"

using namespace Fit;

Minimizer::Minimizer() : m_kernel(new Kernel) {}

void Minimizer::setMinimizer(const std::string& minimizerName, const std::string& algorithmName,
                             const std::string& options)
{
    m_kernel->setMinimizer(minimizerName, algorithmName, options);
}

void Minimizer::setMinimizer(IMinimizer* minimizer)
{
    m_kernel->setMinimizer(minimizer);
}

Minimizer::~Minimizer() = default;

MinimizerResult Minimizer::minimize(fcn_scalar_t fcn, const Parameters& parameters)
{
    return m_kernel->minimize(fcn, parameters);
}

MinimizerResult Minimizer::minimize(fcn_residual_t fcn, const Parameters& parameters)
{
    return m_kernel->minimize(fcn, parameters);
}

MinimizerResult Minimizer::minimize(PyCallback& callback, const Parameters& parameters)
{
    if (callback.callback_type() == PyCallback::SCALAR) {
        fcn_scalar_t fcn = [&](const Parameters& pars) { return callback.call_scalar(pars); };
        return minimize(fcn, parameters);

    } else if (callback.callback_type() == PyCallback::RESIDUAL) {
        fcn_residual_t fcn = [&](const Parameters& pars) { return callback.call_residuals(pars); };
        return minimize(fcn, parameters);
    }

    throw std::runtime_error("Minimizer::minimize() -> Error. Unexpected user function");
}
