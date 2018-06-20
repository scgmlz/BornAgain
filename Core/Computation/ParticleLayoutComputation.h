// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ParticleLayoutComputation.h
//! @brief     Defines class ParticleLayoutComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTCOMPUTATION_H
#define PARTICLELAYOUTCOMPUTATION_H

#include "MultilayerInfo.h"
#include "SlicedParticle.h"
#include <map>
#include <memory>
#include <vector>

using std::size_t;

class ILayout;
class IInterferenceFunctionStrategy;
class SimulationElement;
class SimulationOptions;

//! Computes the scattering contribution from one particle layout.
//! Used by DWBAComputation.
//! @ingroup algorithms_internal

class ParticleLayoutComputation final
{
public:
    ParticleLayoutComputation(const MultiLayer* p_multilayer, const IFresnelMap* p_fresnel_map,
                              const ILayout* p_layout, size_t layer_index,
                              const SimulationOptions& options, bool polarized);
    ~ParticleLayoutComputation();

    void compute(SimulationElement& elem) const;

    //! Merges its region map into the given one (notice non-const reference parameter)
    void mergeRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map) const;

private:
    MultilayerInfo m_multilayer_info;
    std::unique_ptr<const IInterferenceFunctionStrategy> mP_strategy;
    double m_surface_density;
    std::map<size_t, std::vector<HomogeneousRegion>> m_region_map;
};

#endif // PARTICLELAYOUTCOMPUTATION_H
