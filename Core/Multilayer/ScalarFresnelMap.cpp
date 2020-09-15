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

#include "Core/Multilayer/ScalarFresnelMap.h"
#include "Core/Multilayer/Slice.h"
#include "Core/RT/ScalarRTCoefficients.h"
#include "Core/SimulationElement/SimulationElement.h"
#include "Core/Vector/Vectors3D.h"
#include <functional>

ScalarFresnelMap::ScalarFresnelMap(std::unique_ptr<ISpecularStrategy> strategy)
    : IFresnelMap(std::move(strategy))
{
}

ScalarFresnelMap::~ScalarFresnelMap() = default;

//! Returns hash value of a pair of doubles, computed by exclusive-or of the component hash values.
size_t ScalarFresnelMap::Hash2Doubles::operator()(const std::pair<double, double>& doubles) const
    noexcept
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
        auto coeffs = m_Strategy->Execute(m_slices, kvec);
        return ISpecularStrategy::coefficient_pointer_type(coeffs[layer_index]->clone());
    }
    const auto& coef_vector = getCoefficientsFromCache(kvec);
    return ISpecularStrategy::coefficient_pointer_type(coef_vector[layer_index]->clone());
}

const ISpecularStrategy::coeffs_t& ScalarFresnelMap::getCoefficientsFromCache(kvector_t kvec) const
{
    std::pair<double, double> k2_theta(kvec.mag2(), kvec.theta());
    auto it = m_cache.find(k2_theta);
    if (it == m_cache.end()) {
        it = m_cache.emplace(k2_theta, m_Strategy->Execute(m_slices, kvec)).first;
    }
    return it->second;
}
