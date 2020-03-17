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

#include "MatrixFresnelMap.h"
#include "SimulationElement.h"
#include "Slice.h"
//#include "SpecularMagnetic.h"
//#include "SpecularMagnetic_v2.h"

#include <functional>

//namespace {
//template <class T> auto MatrixFresnelMap::computeRT(const std::vector<Slice>&, const kvector_t&) const
//{
//    constexpr bool value = std::is_same<T, MatrixRTCoefficients>::value
//                           || std::is_same<T, MatrixRTCoefficients_v2>::value;
//    static_assert(value, "Error in MatrixFresnelMap:computeRT: unknown coefficient type");
//};

//template <>
//auto MatrixFresnelMap::computeRT<MatrixRTCoefficients>(const std::vector<Slice>& slices, const kvector_t& k) const
//{
//    return m_Strategy.eval(slices, k);
//}

//template <>
std::vector<MatrixRTCoefficients_v2> MatrixFresnelMap::computeRT(const std::vector<Slice>& slices, const kvector_t& k) const
{
    return m_Strategy->eval(slices, k);
}
//}

MatrixFresnelMap::MatrixFresnelMap(std::unique_ptr<SpecularMagneticStrategy> strategy) : m_Strategy(std::move(strategy))
{}
//MatrixFresnelMap::MatrixFresnelMap(SpecularMagneticStrategy strategy) : m_Strategy(strategy) {}

MatrixFresnelMap::~MatrixFresnelMap() = default;

//! Returns hash value of a 3-vector, computed by exclusive-or of the component hash values.
size_t MatrixFresnelMap::HashKVector::operator()(const kvector_t& kvec) const noexcept
{
    return std::hash<double>{}(kvec.x())
         ^ std::hash<double>{}(kvec.y())
         ^ std::hash<double>{}(kvec.z());
}

std::unique_ptr<const ILayerRTCoefficients>
MatrixFresnelMap::getOutCoefficients(const SimulationElement& sim_element, size_t layer_index) const
{
    return getCoefficients(-sim_element.getMeanKf(), layer_index, m_inverted_slices,
                           m_hash_table_out);
}

void MatrixFresnelMap::setSlices(const std::vector<Slice> &slices)
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
                                  const std::vector<Slice>& slices, CoefficientHash& hash_table) const
{
    if (!m_use_cache) {
        auto coeffs = computeRT(slices, kvec);
        return std::make_unique<RTCoefficients>(coeffs[layer_index]);
    }
    const auto& coef_vector = getCoefficientsFromCache(kvec, slices, hash_table);
    return std::make_unique<RTCoefficients>(coef_vector[layer_index]);
}

const std::vector<MatrixFresnelMap::RTCoefficients>&
MatrixFresnelMap::getCoefficientsFromCache(kvector_t kvec, const std::vector<Slice>& slices,
                                           MatrixFresnelMap::CoefficientHash& hash_table) const
{
    auto it = hash_table.find(kvec);
    if (it == hash_table.end())
        it = hash_table.insert({kvec, computeRT(slices, kvec)}).first;
    return it->second;
}

SpecularMagneticStrategy* MatrixFresnelMap::getStrategy() const
{
    return this->m_Strategy.get();
}

