// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/VarianceFunctions.cpp
//! @brief     Implements IVarianceFunction classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/VarianceFunctions.h"
#include <algorithm>

IVarianceFunction::IVarianceFunction() = default;
IVarianceFunction::~IVarianceFunction() = default;

VarianceConstantFunction* VarianceConstantFunction::clone() const
{
    return new VarianceConstantFunction();
}

double VarianceConstantFunction::variance(double, double) const
{
    return 1.0;
}

VarianceSimFunction::VarianceSimFunction(double epsilon) : m_epsilon(epsilon) {}

VarianceSimFunction* VarianceSimFunction::clone() const
{
    return new VarianceSimFunction(m_epsilon);
}

double VarianceSimFunction::variance(double /*exp*/, double sim) const
{
    return std::max(sim, m_epsilon);
}
