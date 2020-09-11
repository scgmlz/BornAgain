// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/IterationInfo.cpp
//! @brief     Implements class IterationInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Fitting/IterationInfo.h"

IterationInfo::IterationInfo() : m_chi2(0.0), m_iteration_count(0) {}

void IterationInfo::update(const Fit::Parameters& params, double chi2)
{
    m_current_parameters = params;
    m_chi2 = chi2;
    m_iteration_count++;
}

unsigned IterationInfo::iterationCount() const
{
    return m_iteration_count;
}

double IterationInfo::chi2() const
{
    return m_chi2;
}

Fit::Parameters IterationInfo::parameters() const
{
    return m_current_parameters;
}

std::map<std::string, double> IterationInfo::parameterMap() const
{
    std::map<std::string, double> result;

    for (const auto& par : m_current_parameters)
        result.insert(std::make_pair(par.name(), par.value()));

    return result;
}
