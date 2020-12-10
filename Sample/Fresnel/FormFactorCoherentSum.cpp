//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Fresnel/FormFactorCoherentSum.cpp
//! @brief     Implements class FormFactorCoherentSum.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Fresnel/FormFactorCoherentSum.h"
#include "Base/Pixel/SimulationElement.h"

FormFactorCoherentSum::FormFactorCoherentSum(double abundance) : m_abundance(abundance) {}

void FormFactorCoherentSum::addCoherentPart(const FormFactorCoherentPart& part) {
    m_parts.push_back(part);
}

complex_t FormFactorCoherentSum::evaluate(const SimulationElement& sim_element) const {
    complex_t result{};
    for (const auto& part : m_parts)
        result += part.evaluate(sim_element);
    return result;
}

Eigen::Matrix2cd FormFactorCoherentSum::evaluatePol(const SimulationElement& sim_element) const {
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (const auto& part : m_parts)
        result += part.evaluatePol(sim_element);
    return result;
}

void FormFactorCoherentSum::scaleRelativeAbundance(double total_abundance) {
    if (total_abundance <= 0.0)
        throw std::runtime_error("FormFactorCoherentSum::scaleRelativeAbundance: "
                                 "Trying to scale with non strictly positive factor.");
    m_abundance /= total_abundance;
}

double FormFactorCoherentSum::radialExtension() const {
    return m_parts[0].radialExtension();
}

FormFactorCoherentSum::FormFactorCoherentSum(const std::vector<FormFactorCoherentPart>& parts,
                                             double abundance)
    : m_parts(parts), m_abundance(abundance) {}
