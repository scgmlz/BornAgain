//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Fresnel/ScalarFresnelMap.h
//! @brief     Defines class ScalarFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_FRESNEL_SCALARFRESNELMAP_H
#define BORNAGAIN_SAMPLE_FRESNEL_SCALARFRESNELMAP_H

#include "Sample/Fresnel/IFresnelMap.h"
#include "Sample/RT/ScalarRTCoefficients.h"
#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>

class ILayerRTCoefficients;
class SimulationElement;
class Slice;

//! Implementation of IFresnelMap for scalar valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class ScalarFresnelMap : public IFresnelMap {
public:
    ScalarFresnelMap(std::unique_ptr<ISpecularStrategy> strategy);
    ~ScalarFresnelMap() override;

    ScalarFresnelMap(const ScalarFresnelMap& other) = delete;
    ScalarFresnelMap& operator=(const ScalarFresnelMap& other) = delete;

    std::unique_ptr<const ILayerRTCoefficients>
    getOutCoefficients(const SimulationElement& sim_element, size_t layer_index) const override;

private:
    //! Provides a hash function for a pair of doubles.
    class Hash2Doubles {
    public:
        size_t operator()(const std::pair<double, double>& doubles) const noexcept;
    };

    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index) const override;
    const ISpecularStrategy::coeffs_t& getCoefficientsFromCache(kvector_t kvec) const;
    mutable std::unordered_map<std::pair<double, double>, ISpecularStrategy::coeffs_t, Hash2Doubles>
        m_cache;
};

#endif // BORNAGAIN_SAMPLE_FRESNEL_SCALARFRESNELMAP_H
#endif // USER_API
