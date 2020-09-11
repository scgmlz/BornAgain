// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/IInterferenceFunction.cpp
//! @brief     Implements the interface class IInterferenceFunction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Parametrization/RealParameter.h"
#include <algorithm>
#include <stdexcept>

IInterferenceFunction::IInterferenceFunction(const NodeMeta& meta,
                                             const std::vector<double>& PValues)
    : ISample(meta, PValues)
{
    registerParameter("PositionVariance", &m_position_var).setUnit("nm^2").setNonnegative();
}

IInterferenceFunction::IInterferenceFunction(double position_var) : m_position_var(position_var)
{
    registerParameter("PositionVariance", &m_position_var).setUnit("nm^2").setNonnegative();
}

// Default implementation of evaluate assumes no inner structure
// It is only to be overriden in case of the presence of such inner structure. See for example
// InterferenceFunction2DSuperLattice for such a case.
double IInterferenceFunction::evaluate(const kvector_t q, double outer_iff) const
{
    return iff_no_inner(q, outer_iff);
}

void IInterferenceFunction::setPositionVariance(double var)
{
    if (var < 0.0)
        throw std::runtime_error("IInterferenceFunction::setPositionVariance: "
                                 "variance should be positive.");
    m_position_var = var;
}

double IInterferenceFunction::DWfactor(kvector_t q) const
{
    // remove z component for two dimensional interference functions:
    if (supportsMultilayer())
        q.setZ(0.0);
    return std::exp(-q.mag2() * m_position_var);
}

double IInterferenceFunction::iff_no_inner(const kvector_t q, double outer_iff) const
{
    return DWfactor(q) * (iff_without_dw(q) * outer_iff - 1.0) + 1.0;
}
