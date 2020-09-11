// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/IMinimizer.cpp
//! @brief     Implements class IMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Minimizer/IMinimizer.h"

IMinimizer::IMinimizer() = default;

IMinimizer::~IMinimizer() = default;

Fit::MinimizerResult IMinimizer::minimize_scalar(fcn_scalar_t, Fit::Parameters)
{
    throw std::runtime_error("IMinimizer::minimize_scalar() -> Not implemented.");
}

Fit::MinimizerResult IMinimizer::minimize_residual(fcn_residual_t, Fit::Parameters)
{
    throw std::runtime_error("IMinimizer::minimize_residual() -> Not implemented.");
}

double IMinimizer::minValue() const
{
    throw std::runtime_error("IMinimizer::minValue() -> Not implemented.");
}

void IMinimizer::setOptions(const std::string&)
{
    throw std::runtime_error("IMinimizer::setOptions() -> Not implemented.");
}
