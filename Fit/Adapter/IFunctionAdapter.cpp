//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Adapter/IFunctionAdapter.cpp
//! @brief     Implements interface IFunctionAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Fit/Adapter/IFunctionAdapter.h"

using namespace mumufit;

IFunctionAdapter::IFunctionAdapter() : m_number_of_calls(0), m_number_of_gradient_calls(0) {}

IFunctionAdapter::~IFunctionAdapter() = default;

int IFunctionAdapter::numberOfCalls() const {
    return m_number_of_calls;
}

int IFunctionAdapter::numberOfGradientCalls() const {
    return m_number_of_gradient_calls;
}
