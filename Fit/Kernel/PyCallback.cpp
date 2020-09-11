// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/PyCallback.cpp
//! @brief     Implements class PyCallback.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Kernel/PyCallback.h"

PyCallback::PyCallback(PyCallback::CallbackType callback_type) : m_callback_type(callback_type) {}

PyCallback::CallbackType PyCallback::callback_type() const
{
    return m_callback_type;
}

PyCallback::~PyCallback() = default;

double PyCallback::call_scalar(Fit::Parameters)
{
    throw std::runtime_error("PyCallback::call_scalar() -> Error. Not implemented");
}

std::vector<double> PyCallback::call_residuals(Fit::Parameters)
{
    throw std::runtime_error("PyCallback::call_residuals() -> Error. Not implemented");
}
