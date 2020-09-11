// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixFresnelMap.cpp
//! @brief     Implements class MatrixFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/MatrixFresnelMap.h"
#include "Core/Multilayer/Slice.h"
#include "Core/Multilayer/SpecularMagneticOldStrategy.h"
#include "Core/Multilayer/SpecularMagneticStrategy.h"
#include "Core/SimulationElement/SimulationElement.h"
#include <functional>

MatrixFresnelMap::MatrixFresnelMap(std::unique_ptr<ISpecularStrategy> strategy)
    : IFresnelMap(std::move(strategy)){};

MatrixFresnelMap::~MatrixFresnelMap() = default;

//! Returns hash value of a 3-vector, computed by exclusive-or of the component hash values.
size_t MatrixFresnelMap::HashKVector::operator()(const kvector_t& kvec) const noexcept
{
    return std::hash<double>{}(kvec.x()) ^ std::hash<double>{}(kvec.y())
           ^ std::hash<double>{}(kvec.z());
}

std::unique_ptr<const ILayerRTCoefficients>
MatrixFresnelMap::getOutCoefficients(const SimulationElement& sim_element, size_t layer_index) const
{
    return getCoefficients(-sim_element.getMeanKf(), layer_index, m_inverted_slices,
                           m_hash_table_out);
}

void MatrixFresnelMap::setSlices(const std::vector<Slice>& slices)
{
    IFresnelMap::setSlices(slices);
    m_inverted_slices.clear();
    for (auto slice : slices) {
        slice.invertBField();
        m_inverted_slices.push_back(slice);
    }
}

std::unique_ptr<const ILayerRTCoefficients>
MatrixFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index) const
{
    return getCoefficients(kvec, layer_index, m_slices, m_hash_table_in);
}

std::unique_ptr<const ILayerRTCoefficients>
MatrixFresnelMap::getCoefficients(const kvector_t& kvec, size_t layer_index,
                                  const std::vector<Slice>& slices,
                                  CoefficientHash& hash_table) const
{
    if (!m_use_cache) {
        auto coeffs = m_Strategy->Execute(slices, kvec);
        return ISpecularStrategy::single_coeff_t(coeffs[layer_index]->clone());
    }
    const auto& coef_vector = getCoefficientsFromCache(kvec, slices, hash_table);
    return ISpecularStrategy::single_coeff_t(coef_vector[layer_index]->clone());
}

const ISpecularStrategy::coeffs_t&
MatrixFresnelMap::getCoefficientsFromCache(kvector_t kvec, const std::vector<Slice>& slices,
                                           MatrixFresnelMap::CoefficientHash& hash_table) const
{
    auto it = hash_table.find(kvec);
    if (it == hash_table.end())
        it = hash_table.emplace(kvec, m_Strategy->Execute(slices, kvec)).first;
    return it->second;
}
