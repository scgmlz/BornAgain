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

#include "DWBAComputation.h"
#include "GISASSpecularComputation.h"
#include "IComputationUtils.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MatrixFresnelMap.h"
#include "MultiLayer.h"
#include "ParticleLayoutComputation.h"
#include "ProgressHandler.h"
#include "RoughMultiLayerComputation.h"
#include "ScalarFresnelMap.h"
#include "SimulationElement.h"

static_assert(std::is_copy_constructible<DWBAComputation>::value == false,
    "DWBAComputation should not be copy constructable");
static_assert(std::is_copy_assignable<DWBAComputation>::value == false,
    "DWBAComputation should not be copy assignable");

DWBAComputation::DWBAComputation(const MultiLayer& multilayer, const SimulationOptions& options,
                                 ProgressHandler& progress,
                                 std::vector<SimulationElement>::iterator begin_it,
                                 std::vector<SimulationElement>::iterator end_it)
    : IComputation(options, progress, multilayer)
    , m_begin_it(begin_it)
    , m_end_it(end_it)
{
    mP_fresnel_map = IComputationUtils::CreateFresnelMap(multilayer, options);
    bool polarized = mP_multi_layer->containsMagneticMaterial();
    size_t nLayers = mP_multi_layer->numberOfLayers();
    for (size_t i=0; i<nLayers; ++i) {
        const Layer* layer = mP_multi_layer->layer(i);
        for (auto p_layout : layer->layouts())
            m_single_computation.addLayoutComputation(
                        new ParticleLayoutComputation(mP_multi_layer.get(), mP_fresnel_map.get(),
                                                      p_layout, i, m_sim_options, polarized));
    }
    // scattering from rough surfaces in DWBA
    if (mP_multi_layer->hasRoughness())
        m_single_computation.setRoughnessComputation(
                    new RoughMultiLayerComputation(mP_multi_layer.get(), mP_fresnel_map.get()));
    if (m_sim_options.includeSpecular())
        m_single_computation.setSpecularBinComputation(
                    new GISASSpecularComputation(mP_multi_layer.get(), mP_fresnel_map.get()));
    initFresnelMap();
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
    for (auto it=m_begin_it; it != m_end_it; ++it) {
        m_single_computation.compute(*it);
    }
}

void DWBAComputation::initFresnelMap()
{
    auto region_map = m_single_computation.regionMap();
    std::unique_ptr<MultiLayer> P_multilayer =
            m_sim_options.useAvgMaterials()
                 ? IComputationUtils::CreateAveragedMultilayer(*mP_multi_layer, region_map)
                 : std::unique_ptr<MultiLayer>(mP_multi_layer->clone());
    P_multilayer->initBFields();
    mP_fresnel_map->setMultilayer(*P_multilayer);
}
