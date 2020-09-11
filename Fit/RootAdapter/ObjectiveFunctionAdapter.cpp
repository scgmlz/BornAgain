// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/ObjectiveFunctionAdapter.cpp
//! @brief     Implements class ObjectiveFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/RootAdapter/ObjectiveFunctionAdapter.h"
#include "Fit/RootAdapter/ResidualFunctionAdapter.h"
#include "Fit/RootAdapter/RootResidualFunction.h"
#include "Fit/RootAdapter/RootScalarFunction.h"
#include "Fit/RootAdapter/ScalarFunctionAdapter.h"

using namespace Fit;

ObjectiveFunctionAdapter::ObjectiveFunctionAdapter() = default;

ObjectiveFunctionAdapter::~ObjectiveFunctionAdapter() = default;

const RootScalarFunction*
ObjectiveFunctionAdapter::rootObjectiveFunction(fcn_scalar_t fcn, const Parameters& parameters)
{
    std::unique_ptr<ScalarFunctionAdapter> temp_adapter(new ScalarFunctionAdapter(fcn, parameters));
    auto result = temp_adapter->rootObjectiveFunction();
    m_adapter.reset(temp_adapter.release());
    return result;
}

const RootResidualFunction*
ObjectiveFunctionAdapter::rootResidualFunction(fcn_residual_t fcn, const Parameters& parameters)
{
    std::unique_ptr<ResidualFunctionAdapter> temp_adapter(
        new ResidualFunctionAdapter(fcn, parameters));
    auto result = temp_adapter->rootResidualFunction();
    m_adapter.reset(temp_adapter.release());
    return result;
}

int ObjectiveFunctionAdapter::numberOfCalls() const
{
    return m_adapter ? m_adapter->numberOfCalls() : 0;
}

int ObjectiveFunctionAdapter::numberOfGradientCalls() const
{
    return m_adapter ? m_adapter->numberOfGradientCalls() : 0;
}
