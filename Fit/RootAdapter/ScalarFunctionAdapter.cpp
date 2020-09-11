// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/ScalarFunctionAdapter.cpp
//! @brief     Defines class ScalarFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/RootAdapter/ScalarFunctionAdapter.h"
#include "Fit/Kernel/KernelTypes.h"
#include "Fit/RootAdapter/RootScalarFunction.h"

using namespace Fit;

ScalarFunctionAdapter::ScalarFunctionAdapter(fcn_scalar_t func, const Parameters& parameters)
    : m_fcn(func), m_parameters(parameters)
{
}

const RootScalarFunction* ScalarFunctionAdapter::rootObjectiveFunction()
{
    root_scalar_t rootfun = [&](const double* pars) {
        std::vector<double> vec;
        vec.resize(m_parameters.size(), 0.0);
        std::copy(pars, pars + m_parameters.size(), vec.begin());
        m_parameters.setValues(vec);
        ++m_number_of_calls;
        return m_fcn(m_parameters);
    };

    m_root_objective.reset(new RootScalarFunction(rootfun, static_cast<int>(m_parameters.size())));
    return m_root_objective.get();
}
