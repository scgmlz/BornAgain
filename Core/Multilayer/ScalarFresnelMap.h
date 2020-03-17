// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ScalarFresnelMap.h
//! @brief     Defines class ScalarFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SCALARFRESNELMAP_H
#define SCALARFRESNELMAP_H

#include "IFresnelMap.h"
#include "ScalarRTCoefficients.h"
#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>
#include "SpecularScalarStrategy.h"

class ILayerRTCoefficients;
class SimulationElement;
class Slice;

//! Implementation of IFresnelMap for scalar valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ ScalarFresnelMap : public IFresnelMap
{
public:
    ScalarFresnelMap(std::unique_ptr<SpecularScalarStrategy> strategy);
    ~ScalarFresnelMap() final;

    std::unique_ptr<const ILayerRTCoefficients>
    getOutCoefficients(const SimulationElement& sim_element, size_t layer_index) const override;

    SpecularScalarStrategy* getStrategy() const override;

private:
    //! Provides a hash function for a pair of doubles.
    class Hash2Doubles
    {
    public:
        size_t operator()(std::pair<double, double> doubles) const noexcept;
    };

    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index) const override;
    const std::vector<ScalarRTCoefficients>& getCoefficientsFromCache(kvector_t kvec) const;
    mutable std::unordered_map<std::pair<double, double>, std::vector<ScalarRTCoefficients>,
                               Hash2Doubles> m_cache;

    std::unique_ptr<SpecularScalarStrategy> m_Strategy;

};

#endif // SCALARFRESNELMAP_H
