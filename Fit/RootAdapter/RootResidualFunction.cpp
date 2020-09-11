// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootResidualFunction.cpp
//! @brief     Implements class RootResidualFunction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/RootAdapter/RootResidualFunction.h"

RootResidualFunction::RootResidualFunction(scalar_function_t objective_fun,
                                           gradient_function_t gradient_fun, size_t npars,
                                           size_t ndatasize)
    : ROOT::Math::FitMethodFunction(static_cast<int>(npars), static_cast<int>(ndatasize)),
      m_objective_fun(objective_fun), m_gradient_fun(gradient_fun), m_npars(npars),
      m_datasize(ndatasize)
{
}

RootResidualFunction::Type_t RootResidualFunction::Type() const
{
    return ROOT::Math::FitMethodFunction::kLeastSquare;
}

ROOT::Math::IMultiGenFunction* RootResidualFunction::Clone() const
{
    return new RootResidualFunction(m_objective_fun, m_gradient_fun, m_npars, m_datasize);
}

//! Returns residual value for given data element index. Transform call of ancient
//! pointer based function to safer gradient_function_t.
//! @param pars: array of fit parameter values from the minimizer
//! @param index: index of residual element
//! @param gradients: if not zero, then array where we have to put gradients
//! @return value of residual for given data element index

double RootResidualFunction::DataElement(const double* pars, unsigned int index,
                                         double* gradients) const
{
    std::vector<double> par_values;
    par_values.resize(m_npars, 0.0);
    std::copy(pars, pars + m_npars, par_values.begin());

    std::vector<double> par_gradients;

    if (gradients)
        par_gradients.resize(m_npars);

    // retrieving result from user function
    double result = m_gradient_fun(par_values, index, par_gradients);

    // packing result back to minimizer's array
    if (gradients)
        for (size_t i = 0; i < m_npars; ++i)
            gradients[i] = par_gradients[i];

    return result;
}

double RootResidualFunction::DoEval(const double* pars) const
{
    std::vector<double> par_values;
    par_values.resize(m_npars, 0.0);
    std::copy(pars, pars + m_npars, par_values.begin());
    return m_objective_fun(par_values);
}
