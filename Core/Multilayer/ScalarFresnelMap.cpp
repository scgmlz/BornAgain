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
#include "ScalarRTCoefficients.h"
#include "SimulationElement.h"
#include "Slice.h"
//#include "SpecularMatrix.h"
#include "Vectors3D.h"
#include <functional>

ScalarFresnelMap::ScalarFresnelMap(std::unique_ptr<SpecularScalarStrategy> strategy) : m_Strategy(std::move(strategy))
{}

ScalarFresnelMap::~ScalarFresnelMap() = default;

//! Returns hash value of a pair of doubles, computed by exclusive-or of the component hash values.
size_t ScalarFresnelMap::Hash2Doubles::operator()(std::pair<double, double> doubles) const noexcept
{
    return std::hash<double>{}(doubles.first) ^ std::hash<double>{}(doubles.second);
}

std::unique_ptr<const ILayerRTCoefficients>
ScalarFresnelMap::getOutCoefficients(const SimulationElement& sim_element, size_t layer_index) const
{
    return getCoefficients(-sim_element.getMeanKf(), layer_index);
}

std::unique_ptr<const ILayerRTCoefficients>
ScalarFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index) const
{
    if (!m_use_cache) {
        auto coeffs = m_Strategy->eval(m_slices, kvec);
        return std::make_unique<const ScalarRTCoefficients>(coeffs[layer_index]);
    }
    const auto& coef_vector = getCoefficientsFromCache(kvec);
    return std::make_unique<const ScalarRTCoefficients>(coef_vector[layer_index]);
}

const std::vector<ScalarRTCoefficients>&
ScalarFresnelMap::getCoefficientsFromCache(kvector_t kvec) const
{
    std::pair<double, double> k2_theta(kvec.mag2(), kvec.theta());
    auto it = m_cache.find(k2_theta);
    if (it == m_cache.end()) {
        it = m_cache.insert({k2_theta, m_Strategy->eval(m_slices, kvec)}).first;
    }
    return it->second;
}

SpecularScalarStrategy* ScalarFresnelMap::getStrategy() const
{
    return this->m_Strategy.get();

}
