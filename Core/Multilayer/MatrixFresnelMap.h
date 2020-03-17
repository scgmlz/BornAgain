// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixFresnelMap.h
//! @brief     Defines class MatrixFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATRIXFRESNELMAP_H
#define MATRIXFRESNELMAP_H

#include "IFresnelMap.h"
//#include "MatrixRTCoefficients.h"
#include "MatrixRTCoefficients_v2.h"
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include "SpecularMagneticStrategy.h"

class ILayerRTCoefficients;
class Slice;
class SimulationElement;

//! Implementation of IFresnelMap for matrix valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ MatrixFresnelMap : public IFresnelMap
{
public:
    using RTCoefficients = MatrixRTCoefficients_v2;

    MatrixFresnelMap(std::unique_ptr<SpecularMagneticStrategy> strategy);
    ~MatrixFresnelMap() override;

    std::unique_ptr<const ILayerRTCoefficients>
    getOutCoefficients(const SimulationElement& sim_element,
                       size_t layer_index) const final override;

    void setSlices(const std::vector<Slice>& slices) final override;

    SpecularMagneticStrategy* getStrategy() const override;

private:

//    template <class T> auto computeRT(const std::vector<Slice>&, const kvector_t&) const;

//    template <>
//    auto computeRT<MatrixRTCoefficients>(const std::vector<Slice>& slices, const kvector_t& k) const;

//    template <>
    std::vector<MatrixRTCoefficients_v2> computeRT(const std::vector<Slice>& slices, const kvector_t& k) const;

    //! Provides a hash function for a 3-vector of doubles, for use in MatrixFresnelMap.
    class HashKVector
    {
    public:
        size_t operator()(const kvector_t& kvec) const noexcept;
    };

    using CoefficientHash = std::unordered_map<kvector_t, std::vector<RTCoefficients>, HashKVector>;

    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index) const override;
    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index,
                                                                const std::vector<Slice>& slices,
                                                                CoefficientHash& hash_table) const;
    std::vector<Slice> m_inverted_slices;
    mutable CoefficientHash m_hash_table_out;
    mutable CoefficientHash m_hash_table_in;

    const std::vector<RTCoefficients>&
    getCoefficientsFromCache(kvector_t kvec, const std::vector<Slice>& slices,
                             CoefficientHash& hash_table) const;

    std::unique_ptr<SpecularMagneticStrategy> m_Strategy;
};

#endif // MATRIXFRESNELMAP_H
