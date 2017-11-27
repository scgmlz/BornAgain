// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DWBAComputation.cpp
//! @brief     Implements class DWBAComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DWBAComputation.h"
#include "ParticleLayoutComputation.h"
#include "Layer.h"
#include "IFresnelMap.h"
#include "MatrixFresnelMap.h"
#include "MultiLayer.h"
#include "RoughMultiLayerComputation.h"
#include "SpecularComputation.h"
#include "ScalarFresnelMap.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"
#include "MaterialFactoryFuncs.h"

DWBAComputation::DWBAComputation(
    const MultiLayer& multilayer,
    const SimulationOptions& options,
    ProgressHandler& progress,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it)
    : IComputation (progress, begin_it, end_it)
    , mP_multi_layer(multilayer.cloneSliced(options.useAvgMaterials()))
    , m_sim_options(options)
{
    mP_fresnel_map.reset(createFresnelMap());
    bool polarized = mP_multi_layer->containsMagneticMaterial();
    size_t nLayers = mP_multi_layer->numberOfLayers();
    for (size_t i=0; i<nLayers; ++i) {
        const Layer* layer = mP_multi_layer->layer(i);
        for (auto p_layout : layer->layouts())
            m_computation_terms.emplace_back(
                        new ParticleLayoutComputation(
                            mP_multi_layer.get(), mP_fresnel_map.get(), p_layout, i,
                            m_sim_options, polarized));
    }
    // scattering from rough surfaces in DWBA
    if (mP_multi_layer->hasRoughness())
        m_computation_terms.emplace_back(new RoughMultiLayerComputation(mP_multi_layer.get(),
                                                                     mP_fresnel_map.get()));
    if (m_sim_options.includeSpecular())
        m_computation_terms.emplace_back(new SpecularComputation(mP_multi_layer.get(),
                                                              mP_fresnel_map.get()));
    initFresnelMap();
}

DWBAComputation::~DWBAComputation() {}

void DWBAComputation::run()
{
    m_status.setRunning();
    try {
        runProtected();
        m_status.setCompleted();
    } catch(const std::exception &ex) {
        m_status.setErrorMessage(std::string(ex.what()));
        m_status.setFailed();
    }
}

// The normalization of the calculated scattering intensities is:
// For nanoparticles: rho * (scattering cross-section/scattering particle)
// For roughness: (scattering cross-section of area S)/S
// For specular peak: |R|^2 * sin(alpha_i) / solid_angle
// This allows them to be added and normalized together to the beam afterwards
void DWBAComputation::runProtected()
{
    // add intensity of all IComputationTerms:
    for (auto& comp: m_computation_terms) {
        if (!m_progress->alive())
            return;
        comp->eval(m_progress, m_begin_it, m_end_it );
    }
}

IFresnelMap* DWBAComputation::createFresnelMap()
{
    std::unique_ptr<IFresnelMap> P_result;
    if (!mP_multi_layer->requiresMatrixRTCoefficients())
        P_result.reset(new ScalarFresnelMap());
    else
        P_result.reset(new MatrixFresnelMap());
    // Disable caching of R,T coefficients when using Monte Carlo integration
    if (P_result && m_sim_options.isIntegrate()) {
        P_result->disableCaching();
    }
    return P_result.release();
}

std::unique_ptr<MultiLayer> DWBAComputation::getAveragedMultilayer() const
{
    std::map<size_t, std::vector<HomogeneousRegion>> region_map;
    for (auto& comp: m_computation_terms) {
        comp->mergeRegionMap(region_map);
    }
    std::unique_ptr<MultiLayer> P_result(mP_multi_layer->clone());
    auto last_layer_index = P_result->numberOfLayers()-1;
    for (auto& entry : region_map)
    {
        auto i_layer = entry.first;
        if (i_layer==0 || i_layer==last_layer_index)
            continue;  // skip semi-infinite layers
        auto layer_mat = P_result->layerMaterial(i_layer);
        if (!checkRegions(entry.second))
            throw std::runtime_error("DWBAComputation::getAveragedMultilayer: "
                                     "total volumetric fraction of particles exceeds 1!");
        auto new_mat = createAveragedMaterial(layer_mat, entry.second);
        P_result->setLayerMaterial(i_layer, new_mat);
    }
    return P_result;
}

std::unique_ptr<MultiLayer> DWBAComputation::getMultilayerForFresnel() const
{
    std::unique_ptr<MultiLayer> P_result = m_sim_options.useAvgMaterials()
                                           ? getAveragedMultilayer()
                                           : std::unique_ptr<MultiLayer>(mP_multi_layer->clone());
    P_result->initBFields();
    return P_result;
}

void DWBAComputation::initFresnelMap()
{
    auto multilayer = getMultilayerForFresnel();
    mP_fresnel_map->setMultilayer(*multilayer);
}

bool DWBAComputation::checkRegions(const std::vector<HomogeneousRegion>& regions) const
{
    double total_fraction = 0;
    for (auto& region : regions)
        total_fraction += region.m_volume;
    return (total_fraction >= 0 && total_fraction <= 1);
}
