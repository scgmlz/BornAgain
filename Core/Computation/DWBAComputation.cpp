// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DWBAComputation.cpp
//! @brief     Implements class DWBAComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/DWBAComputation.h"
#include "Core/Computation/GISASSpecularComputation.h"
#include "Core/Computation/ParticleLayoutComputation.h"
#include "Core/Computation/ProcessedLayout.h"
#include "Core/Computation/ProcessedSample.h"
#include "Core/Computation/ProgressHandler.h"
#include "Core/Computation/RoughMultiLayerComputation.h"
#include "Core/Multilayer/IFresnelMap.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/SimulationElement/SimulationElement.h"

static_assert(std::is_copy_constructible<DWBAComputation>::value == false,
              "DWBAComputation should not be copy constructable");
static_assert(std::is_copy_assignable<DWBAComputation>::value == false,
              "DWBAComputation should not be copy assignable");

DWBAComputation::DWBAComputation(const MultiLayer& multilayer, const SimulationOptions& options,
                                 ProgressHandler& progress,
                                 std::vector<SimulationElement>::iterator begin_it,
                                 std::vector<SimulationElement>::iterator end_it)
    : IComputation(multilayer, options, progress), m_begin_it(begin_it), m_end_it(end_it)
{
    auto p_fresnel_map = mP_processed_sample->fresnelMap();
    bool polarized = mP_processed_sample->containsMagneticMaterial();
    for (const auto& layout : mP_processed_sample->layouts()) {
        m_single_computation.addLayoutComputation(
            new ParticleLayoutComputation(&layout, m_sim_options, polarized));
    }
    // scattering from rough surfaces in DWBA
    if (mP_processed_sample->hasRoughness())
        m_single_computation.setRoughnessComputation(
            new RoughMultiLayerComputation(mP_processed_sample.get()));
    if (m_sim_options.includeSpecular())
        m_single_computation.setSpecularBinComputation(new GISASSpecularComputation(p_fresnel_map));
}

DWBAComputation::~DWBAComputation() = default;

// The normalization of the calculated scattering intensities is:
// For nanoparticles: rho * (scattering cross-section/scattering particle)
// For roughness: (scattering cross-section of area S)/S
// For specular peak: |R|^2 * sin(alpha_i) / solid_angle
// This allows them to be added and normalized together to the beam afterwards
void DWBAComputation::runProtected()
{
    if (!mp_progress->alive())
        return;
    m_single_computation.setProgressHandler(mp_progress);
    for (auto it = m_begin_it; it != m_end_it; ++it) {
        if (!mp_progress->alive())
            break;
        m_single_computation.compute(*it);
    }
}
