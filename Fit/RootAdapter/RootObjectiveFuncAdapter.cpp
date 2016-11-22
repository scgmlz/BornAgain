// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootObjectiveFuncAdapter.cpp
//! @brief     Implements class RootObjectiveFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RootObjectiveFuncAdapter.h"
#include "RootMinimizerFunctions.h"
#include "IMinimizer.h"
#include <stdexcept>

RootObjectiveFunctionAdapter::RootObjectiveFunctionAdapter()
    : m_nparameters(0)
    , m_ndatasize(0)
{}

//! Sets the function which will be used for finding objective function minimum value

void RootObjectiveFunctionAdapter::setObjectiveCallback(objective_function_t func)
{
    m_objective_callback = func;
}

//! Sets the function which will be used for gradient calculations.

void RootObjectiveFunctionAdapter::setGradientCallback(gradient_function_t func, int ndatasize)
{
    m_gradient_callback = func;
    m_ndatasize = ndatasize;
}

//! Sets number of fit parameters (needed to construct correct ROOT's functions).

void RootObjectiveFunctionAdapter::setNumberOfParameters(int nparameters)
{
    m_nparameters = nparameters;
}

//! Creates and returns objective function suitable for ROOT minimizers.

const RootObjectiveFunction*
    RootObjectiveFunctionAdapter::rootChiSquaredFunction()
{
    if(!m_objective_callback)
        throw std::runtime_error("RootObjectiveFunctionAdapter::rootChiSquaredFunction() -> Error. "
                                 "Objective function is not set.");

    if(m_nparameters <= 0)
        throw std::runtime_error("RootObjectiveFunctionAdapter::rootChiSquaredFunction() -> Error. "
                                 "Number of parameters must be >0");

    root_objective_t rootfun =
        [&] (const double* pars) {return evaluate(pars); };

    m_root_objective_function.reset(new RootObjectiveFunction(rootfun, m_nparameters));

    return m_root_objective_function.get();
}

//! Creates and returns gradient function suitable for ROOT minimizers.

const RootGradientFunction* RootObjectiveFunctionAdapter::rootGradientFunction()
{
    if(!m_gradient_callback)
        throw std::runtime_error("RootObjectiveFunctionAdapter::rootGradientFunction() -> Error. "
                                 "Objective function is not set.");

    if(m_nparameters <= 0)
        throw std::runtime_error("RootObjectiveFunctionAdapter::rootGradientFunction() -> Error. "
                                 "Number of parameters must be >0");

    if(m_ndatasize <= 0)
        throw std::runtime_error("RootObjectiveFunctionAdapter::rootGradientFunction() -> Error. "
                                 "Number of data elements is not defined.");

    root_gradient_t rootfun =
        [&] (const double* pars, unsigned int index, double* gradients)
        { return evaluate_gradient(pars, index, gradients); };

    m_root_gradient_function.reset(new RootGradientFunction(rootfun, m_nparameters,
                                                                     m_ndatasize));

    return m_root_gradient_function.get();
}

//! Transfers call of root's pointer based objective function to our callback

double RootObjectiveFunctionAdapter::evaluate(const double* pars)
{
    std::vector<double> vec;
    vec.resize(m_nparameters, 0.0);
    std::copy(pars, pars+m_nparameters, vec.begin());
    return m_objective_callback(vec);
}

//! Transfers call of root's pointer based gradient function to our callback

double RootObjectiveFunctionAdapter::evaluate_gradient(
    const double* pars, unsigned int index, double* gradients)
{
    std::vector<double> vec;
    vec.resize(m_nparameters, 0.0);
    std::copy(pars, pars+m_nparameters, vec.begin());

    std::vector<double> vec_gradients;

    if(gradients)
        vec_gradients.resize(m_nparameters);

    double result = m_gradient_callback(vec, index, vec_gradients);

    if(gradients)
        for(int i=0; i<(int)m_nparameters; ++i) gradients[i] = vec_gradients[i];

    return result;
}
