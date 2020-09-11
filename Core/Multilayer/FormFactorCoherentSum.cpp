// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/FormFactorCoherentSum.cpp
//! @brief     Implements class FormFactorCoherentSum.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/FormFactorCoherentSum.h"
#include "Core/Basics/Exceptions.h"
#include "Core/SimulationElement/SimulationElement.h"

FormFactorCoherentSum::FormFactorCoherentSum(double abundance) : m_abundance(abundance) {}

void FormFactorCoherentSum::addCoherentPart(const FormFactorCoherentPart& part)
{
    m_parts.push_back(part);
}

complex_t FormFactorCoherentSum::evaluate(const SimulationElement& sim_element) const
{
    complex_t result{};
    for (auto& part : m_parts) {
        result += part.evaluate(sim_element);
    }
    return result;
}

Eigen::Matrix2cd FormFactorCoherentSum::evaluatePol(const SimulationElement& sim_element) const
{
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (auto& part : m_parts) {
        result += part.evaluatePol(sim_element);
    }
    return result;
}

void FormFactorCoherentSum::scaleRelativeAbundance(double total_abundance)
{
    if (total_abundance > 0.0) {
        m_abundance /= total_abundance;
        return;
    }
    throw Exceptions::LogicErrorException("FormFactorCoherentSum::scaleRelativeAbundance: "
                                          "Trying to scale with non strictly positive factor.");
}

double FormFactorCoherentSum::radialExtension() const
{
    return m_parts[0].radialExtension();
}

FormFactorCoherentSum::FormFactorCoherentSum(const std::vector<FormFactorCoherentPart>& parts,
                                             double abundance)
    : m_parts(parts), m_abundance(abundance)
{
}
