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

#include "Core/Computation/ParticleLayoutComputation.h"
#include "Core/Computation/LayoutStrategyBuilder.h"
#include "Core/Computation/ProcessedLayout.h"
#include "Core/Multilayer/IInterferenceFunctionStrategy.h"
#include "Core/SimulationElement/SimulationElement.h"

ParticleLayoutComputation::ParticleLayoutComputation(const ProcessedLayout* p_layout,
                                                     const SimulationOptions& options,
                                                     bool polarized)
    : mp_layout(p_layout)
{
    LayoutStrategyBuilder builder(p_layout, options, polarized);
    mP_strategy.reset(builder.releaseStrategy());
    m_region_map = p_layout->regionMap();
    m_surface_density = p_layout->surfaceDensity();
}

ParticleLayoutComputation::~ParticleLayoutComputation() = default;

void ParticleLayoutComputation::compute(SimulationElement& elem) const
{
    double alpha_f = elem.getAlphaMean();
    size_t n_layers = mp_layout->numberOfSlices();
    if (n_layers > 1 && alpha_f < 0) {
        return; // zero for transmission with multilayers (n>1)
    } else {
        elem.addIntensity(mP_strategy->evaluate(elem) * m_surface_density);
    }
}

void ParticleLayoutComputation::mergeRegionMap(
    std::map<size_t, std::vector<HomogeneousRegion>>& region_map) const
{
    for (auto& entry : m_region_map) {
        size_t i = entry.first;
        auto& regions = entry.second;
        region_map[i].insert(region_map[i].begin(), regions.begin(), regions.end());
    }
}
