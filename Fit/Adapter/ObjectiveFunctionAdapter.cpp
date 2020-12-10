//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Adapter/ObjectiveFunctionAdapter.cpp
//! @brief     Implements class ObjectiveFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Fit/Adapter/ObjectiveFunctionAdapter.h"
#include "Fit/Adapter/ResidualFunctionAdapter.h"
#include "Fit/Adapter/RootResidualFunction.h"
#include "Fit/Adapter/RootScalarFunction.h"
#include "Fit/Adapter/ScalarFunctionAdapter.h"

using namespace mumufit;

ObjectiveFunctionAdapter::ObjectiveFunctionAdapter() = default;

ObjectiveFunctionAdapter::~ObjectiveFunctionAdapter() = default;

const RootScalarFunction*
ObjectiveFunctionAdapter::rootObjectiveFunction(fcn_scalar_t fcn, const Parameters& parameters) {
    std::unique_ptr<ScalarFunctionAdapter> tem_adapter(new ScalarFunctionAdapter(fcn, parameters));
    auto result = tem_adapter->rootObjectiveFunction();
    m_adapter.reset(tem_adapter.release());
    return result;
}

const RootResidualFunction*
ObjectiveFunctionAdapter::rootResidualFunction(fcn_residual_t fcn, const Parameters& parameters) {
    std::unique_ptr<ResidualFunctionAdapter> tem_adapter(
        new ResidualFunctionAdapter(fcn, parameters));
    auto result = tem_adapter->rootResidualFunction();
    m_adapter.reset(tem_adapter.release());
    return result;
}

int ObjectiveFunctionAdapter::numberOfCalls() const {
    return m_adapter ? m_adapter->numberOfCalls() : 0;
}

int ObjectiveFunctionAdapter::numberOfGradientCalls() const {
    return m_adapter ? m_adapter->numberOfGradientCalls() : 0;
}
