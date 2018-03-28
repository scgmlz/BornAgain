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

#include "Hash2Doubles.h"
#include "IFresnelMap.h"
#include <unordered_map>
#include <utility>
#include <vector>

class ILayerRTCoefficients;
class MultiLayer;
class ScalarRTCoefficients;
class SimulationElement;

//! Implementation of IFresnelMap for scalar valued reflection/transmission coefficients.
//! @ingroup algorithms_internal

class BA_CORE_API_ ScalarFresnelMap : public IFresnelMap
{
public:
    ScalarFresnelMap();
    ~ScalarFresnelMap() final;

    std::unique_ptr<const ILayerRTCoefficients>
    getOutCoefficients(const SimulationElement& sim_element,
                       size_t layer_index) const override;

    //! Fills simulation element specular data
    void fillSpecularData(SpecularSimulationElement& sim_element) const override;

private:
    std::unique_ptr<const ILayerRTCoefficients> getCoefficients(const kvector_t& kvec,
                                                                size_t layer_index) const override;
    const std::vector<ScalarRTCoefficients>& getCoefficientsFromCache(kvector_t kvec) const;

    mutable std::unordered_map<std::pair<double, double>, std::vector<ScalarRTCoefficients>,
                               Hash2Doubles> m_hash_table;
};

#endif // SCALARFRESNELMAP_H
