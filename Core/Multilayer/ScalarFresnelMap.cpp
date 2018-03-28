// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ScalarFresnelMap.cpp
//! @brief     Implements class ScalarFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ScalarFresnelMap.h"
#include "MultiLayer.h"
#include "ScalarRTCoefficients.h"
#include "SimulationElement.h"
#include "SpecularMatrix.h"
#include "SpecularSimulationElement.h"
#include "Vectors3D.h"

namespace {
std::vector<ScalarRTCoefficients> calculateCoefficients(const MultiLayer& multilayer,
                                                        kvector_t kvec);
}

ScalarFresnelMap::ScalarFresnelMap()
{}

ScalarFresnelMap::~ScalarFresnelMap()
{}

std::unique_ptr<const ILayerRTCoefficients>
ScalarFresnelMap::getOutCoefficients(const SimulationElement& sim_element, size_t layer_index) const
{
    return getCoefficients(-sim_element.getMeanKf(), layer_index);
}

void ScalarFresnelMap::fillSpecularData(SpecularSimulationElement& sim_element) const
{
    const auto& kvec = sim_element.getKi();
    if (m_use_cache)
        sim_element.setSpecular(SpecularData(getCoefficientsFromCache(kvec)));
    else
        sim_element.setSpecular(SpecularData(calculateCoefficients(*mP_multilayer, kvec)));
}

std::unique_ptr<const ILayerRTCoefficients>
ScalarFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index) const
{
    if (!m_use_cache) {
        auto coeffs = calculateCoefficients(*mP_multilayer, kvec);
        return std::make_unique<const ScalarRTCoefficients>(coeffs[layer_index]);
    }
    const auto& coef_vector = getCoefficientsFromCache(kvec);
    return std::make_unique<const ScalarRTCoefficients>(coef_vector[layer_index]);
}

const std::vector<ScalarRTCoefficients>&
ScalarFresnelMap::getCoefficientsFromCache(kvector_t kvec) const
{
    std::pair<double, double> k2_theta(kvec.mag2(), kvec.theta());
    auto it = m_hash_table.find(k2_theta);
    if (it == m_hash_table.end())
        it = m_hash_table.insert({k2_theta, calculateCoefficients(*mP_multilayer, kvec)}).first;
    return it->second;
}

namespace {
std::vector<ScalarRTCoefficients> calculateCoefficients(const MultiLayer& multilayer,
                                                        kvector_t kvec)
{
    std::vector<ScalarRTCoefficients> coeffs;
    SpecularMatrix::execute(multilayer, kvec, coeffs);
    return coeffs;
}
}
