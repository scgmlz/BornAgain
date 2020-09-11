// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/ResidualFunctionAdapter.cpp
//! @brief     Implements class ResidualFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/RootAdapter/ResidualFunctionAdapter.h"
#include "Fit/RootAdapter/RootResidualFunction.h"
#include <cassert>
#include <sstream>

namespace
{
// step size of derivative calculations
const double kEps = 1.0E-9;
} // namespace

using namespace Fit;

ResidualFunctionAdapter::ResidualFunctionAdapter(fcn_residual_t func,
                                                 const Fit::Parameters& parameters)
    : m_datasize(0), m_fcn(func), m_parameters(parameters)
{
    // single call of user function to get dataset size
    auto residuals = m_fcn(parameters);
    m_datasize = residuals.size();
}

const RootResidualFunction* ResidualFunctionAdapter::rootResidualFunction()
{
    gradient_function_t gradient_fun = [&](const std::vector<double>& pars, unsigned int index,
                                           std::vector<double>& gradients) {
        return element_residual(pars, index, gradients);
    };

    scalar_function_t objective_fun = [&](const std::vector<double>& pars) { return chi2(pars); };

    m_root_objective.reset(
        new RootResidualFunction(objective_fun, gradient_fun, m_parameters.size(), m_datasize));

    return m_root_objective.get();
}

void ResidualFunctionAdapter::calculate_gradients(const std::vector<double>& pars)
{
    m_gradients.clear();
    m_gradients.resize(pars.size());
    for (size_t i_par = 0; i_par < pars.size(); ++i_par)
        m_gradients[i_par].resize(m_datasize, 0.0);

    auto residuals = get_residuals(pars);
    m_number_of_gradient_calls++;

    for (size_t i_par = 0; i_par < pars.size(); ++i_par) {
        std::vector<double> pars_deriv = pars; // values of parameters for derivative calculation
        pars_deriv[i_par] += kEps;

        auto residuals2 = get_residuals(pars_deriv);

        for (size_t i_data = 0; i_data < m_datasize; ++i_data)
            m_gradients[i_par][i_data] = (residuals2[i_data] - residuals[i_data]) / kEps;
    }
}

std::vector<double> ResidualFunctionAdapter::get_residuals(const std::vector<double>& pars)
{
    if (pars.size() != m_parameters.size()) {
        std::ostringstream ostr;
        ostr << "ResidualFunctionAdapter::residuals() -> Error. Number of fit parameters "
             << "has changed in the course of minimization. Initially was " << m_parameters.size()
             << " become " << pars.size() << "\n";
        throw std::runtime_error(ostr.str());
    }

    m_parameters.setValues(pars);
    auto result = m_fcn(m_parameters);

    if (result.size() != m_datasize) {
        std::ostringstream ostr;
        ostr << "ResidualFunctionAdapter::residuals() -> Error. Size of data "
             << "has changed in the course of minimization. Initial length " << m_datasize
             << " new length " << result.size() << "\n";
        throw std::runtime_error(ostr.str());
    }
    return result;
}

//! Returns residual for given data element index. If gradients vector size is not empty, also
//! calculates gradients. Actuall calculation is done for all data elements when index==0.
//! If index!=0 - cached value of residuals/gradients will be used.

double ResidualFunctionAdapter::element_residual(const std::vector<double>& pars,
                                                 unsigned int index, std::vector<double>& gradients)
{
    if (index == 0) {
        m_residuals = get_residuals(pars);
    }

    if (gradients.size()) {
        // Non zero size means that minimizer wants to know gradients.
        if (pars.size() != gradients.size())
            throw std::runtime_error("ResidualFunctionAdapter::element_residual() -> Error. "
                                     "Number of gradients doesn't match number of fit parameters.");
        if (index == 0)
            calculate_gradients(pars);
        for (size_t i_par = 0; i_par < pars.size(); ++i_par)
            gradients[i_par] = m_gradients[i_par][index];
    }

    return m_residuals[index];
}

double ResidualFunctionAdapter::chi2(const std::vector<double>& pars)
{
    ++m_number_of_calls;

    double result(0.0);
    for (auto x : get_residuals(pars))
        result += x * x;

    int fnorm = static_cast<int>(m_datasize) - static_cast<int>(m_parameters.freeParameterCount());
    if (fnorm <= 0)
        throw std::runtime_error("ResidualFunctionAdapter::chi2() -> Error. Normalization is 0");

    return result / fnorm;
}
