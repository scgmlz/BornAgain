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

const size_t element_interval = 100;
ParticleLayoutComputation::ParticleLayoutComputation(
        const MultiLayer* p_multilayer, const IFresnelMap* p_fresnel_map, const ILayout* p_layout,
        size_t layer_index, const SimulationOptions& options, bool polarized, ProgressHandler& progress)
    : IComputationTerm(p_multilayer, p_fresnel_map)
    , m_progress(progress)
    , m_progress_counter(element_interval)
{
    LayoutStrategyBuilder builder(mp_multilayer, p_layout, mp_fresnel_map,
                                  polarized, options, layer_index);
    mP_strategy.reset(builder.releaseStrategy());
    m_region_map = builder.regionMap();
    m_surface_density = p_layout->totalParticleSurfaceDensity();
}

void ParticleLayoutComputation::evalSingle(SimulationElement& element) const
{
    if (!m_progress.alive())
        return;
    const double alpha_f = element.getAlphaMean();
    const size_t n_layers = mp_multilayer->numberOfLayers();
    if (n_layers > 1 && alpha_f < 0)
        return; // zero for transmission with multilayers (n>1)
    else
        element.addIntensity(mP_strategy->evaluate(element) * m_surface_density);
    m_progress_counter.stepProgress(m_progress);
}
