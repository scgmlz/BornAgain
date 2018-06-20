// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ParticleLayoutComputation.cpp
//! @brief     Implements class ParticleLayoutComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ParticleLayoutComputation.h"
#include "DelayedProgressCounter.h"
#include "Exceptions.h"
#include "IInterferenceFunctionStrategy.h"
#include "IFresnelMap.h"
#include "ILayout.h"
#include "LayoutStrategyBuilder.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"

ParticleLayoutComputation::ParticleLayoutComputation(
        const MultiLayer* p_multilayer, const IFresnelMap* p_fresnel_map, const ILayout* p_layout,
        size_t layer_index, const SimulationOptions& options, bool polarized)
    : m_multilayer_info(p_multilayer, p_fresnel_map)
{
    LayoutStrategyBuilder builder(p_multilayer, p_layout, p_fresnel_map,
                                  polarized, options, layer_index);
    mP_strategy.reset(builder.releaseStrategy());
    m_region_map = builder.regionMap();
    m_surface_density = p_layout->totalParticleSurfaceDensity();
}

ParticleLayoutComputation::~ParticleLayoutComputation() =default;

void ParticleLayoutComputation::compute(SimulationElement& elem) const
{
    auto p_multilayer = m_multilayer_info.mp_multilayer;
    double alpha_f = elem.getAlphaMean();
    size_t n_layers = p_multilayer->numberOfLayers();
    if (n_layers > 1 && alpha_f < 0) {
        return; // zero for transmission with multilayers (n>1)
    } else {
        elem.addIntensity(mP_strategy->evaluate(elem) * m_surface_density);
    }
}

void ParticleLayoutComputation::mergeRegionMap(
        std::map<size_t, std::vector<HomogeneousRegion> >& region_map) const
{
    for (auto& entry : m_region_map)
    {
        size_t i = entry.first;
        auto& regions = entry.second;
        region_map[i].insert(region_map[i].begin(), regions.begin(), regions.end());
    }
}
