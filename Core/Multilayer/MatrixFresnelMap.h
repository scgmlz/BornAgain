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

#ifndef BORNAGAIN_CORE_MULTILAYER_MATRIXFRESNELMAP_H
#define BORNAGAIN_CORE_MULTILAYER_MATRIXFRESNELMAP_H

#include "Core/Multilayer/IFresnelMap.h"
#include "Core/Multilayer/SpecularMagneticStrategy.h"
#include "Core/RT/MatrixRTCoefficients.h"
#include "Core/RT/MatrixRTCoefficients_v2.h"
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

class ILayerRTCoefficients;
class Slice;
class SimulationElement;

//! Implementation of IFresnelMap for matrix valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class MatrixFresnelMap : public IFresnelMap
{
public:
    MatrixFresnelMap(std::unique_ptr<ISpecularStrategy> strategy);
    ~MatrixFresnelMap() override;

    MatrixFresnelMap(const MatrixFresnelMap& other) = delete;
    MatrixFresnelMap& operator=(const MatrixFresnelMap& other) = delete;

    std::unique_ptr<const ILayerRTCoefficients>
    getOutCoefficients(const SimulationElement& sim_element,
                       size_t layer_index) const final override;

    void setSlices(const std::vector<Slice>& slices) final override;

private:
    //! Provides a hash function for a 3-vector of doubles, for use in MatrixFresnelMap.
    class HashKVector
    {
    public:
        size_t operator()(const kvector_t& kvec) const noexcept;
    };

    using CoefficientHash = std::unordered_map<kvector_t, ISpecularStrategy::coeffs_t, HashKVector>;

    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index) const override;
    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index,
                                                                const std::vector<Slice>& slices,
                                                                CoefficientHash& hash_table) const;
    std::vector<Slice> m_inverted_slices;
    mutable CoefficientHash m_hash_table_out;
    mutable CoefficientHash m_hash_table_in;

    const ISpecularStrategy::coeffs_t& getCoefficientsFromCache(kvector_t kvec,
                                                                const std::vector<Slice>& slices,
                                                                CoefficientHash& hash_table) const;
};

#endif // BORNAGAIN_CORE_MULTILAYER_MATRIXFRESNELMAP_H
