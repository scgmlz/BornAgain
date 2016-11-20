// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MainComputation.cpp
//! @brief     Implements class MainComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MainComputation.h"
#include "DecoratedLayerComputation.h"
#include "Layer.h"
#include "LayerSpecularInfo.h"
#include "Logger.h"
#include "MatrixSpecularInfoMap.h"
#include "MultiLayer.h"
#include "RoughMultiLayerComputation.h"
#include "SpecularComputation.h"
#include "ScalarSpecularInfoMap.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"
#include "SpecularMagnetic.h"
#include "SpecularMatrix.h"

MainComputation::MainComputation(
    const MultiLayer* p_multi_layer,
    const SimulationOptions& options,
    ProgressHandler& progress,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it)
    : m_sim_options(options)
    , m_progress(&progress)
    , mp_roughness_computation(nullptr)
{
    mp_multi_layer = p_multi_layer->clone();

    msglog(Logging::DEBUG2) << "MainComputation::init()";
    m_begin_it = begin_it;
    m_end_it = end_it;

    size_t nLayers = mp_multi_layer->getNumberOfLayers();
    m_layer_computation.resize( nLayers );
    for (size_t i=0; i<nLayers; ++i) {
        const Layer* layer = mp_multi_layer->getLayer(i);
        for (size_t j=0; j<layer->getNumberOfLayouts(); ++j)
            m_layer_computation[i].push_back( new DecoratedLayerComputation(layer, j) );
    }
    // scattering from rough surfaces in DWBA
    if (mp_multi_layer->hasRoughness())
        mp_roughness_computation = new RoughMultiLayerComputation(mp_multi_layer);
    mp_specular_computation = new SpecularComputation();
}

MainComputation::~MainComputation()
{
    delete mp_multi_layer;
    delete mp_roughness_computation;
    delete mp_specular_computation;
    for (auto& layer_comp: m_layer_computation)
        for (DecoratedLayerComputation* comp: layer_comp)
            delete comp;
}

void MainComputation::run()
{
    m_outcome.setRunning();
    try {
        runProtected();
        m_outcome.setCompleted();
    } catch(const std::exception &ex) {
        m_outcome.setRunMessage(std::string(ex.what()));
        m_outcome.setFailed();
    }
}

// The normalization of the calculated scattering intensities is:
// For nanoparticles: rho * (scattering cross-section/scattering particle)
// For roughness: (scattering cross-section of area S)/S
// For specular peak: |R|^2 * sin(alpha_i) / solid_angle
// This allows them to be added and normalized together to the beam afterwards
void MainComputation::runProtected()
{
    msglog(Logging::DEBUG2) << "MainComputation::runProtected()";

    if (mp_multi_layer->requiresMatrixRTCoefficients())
        collectRTCoefficientsMatrix();
    else
        collectRTCoefficientsScalar();

    // run through layers and run layer simulations
    std::vector<SimulationElement> layer_elements;
    std::copy(m_begin_it, m_end_it, std::back_inserter(layer_elements));
    bool polarized = mp_multi_layer->containsMagneticMaterial();
    for (auto& layer_comp: m_layer_computation) {
        for (const DecoratedLayerComputation* comp: layer_comp) {
            if (!m_progress->alive())
                return;
            comp->eval(m_sim_options, m_progress, polarized,
                       layer_elements.begin(), layer_elements.end());
            addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
        }
    }

    if (!mp_multi_layer->requiresMatrixRTCoefficients() && mp_roughness_computation) {
        msglog(Logging::DEBUG2) << "MainComputation::run() -> roughness";
        if (!m_progress->alive())
            return;
        mp_roughness_computation->eval(
            m_progress, layer_elements.begin(), layer_elements.end());
        addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
    }

    if (m_sim_options.includeSpecular())
        mp_specular_computation->eval(m_progress, polarized, m_begin_it, m_end_it);
}

void MainComputation::collectRTCoefficientsScalar()
{
    // run through layers and construct T,R functions
    for(size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        msglog(Logging::DEBUG2) << "MainComputation::run() -> Layer " << i;
        LayerSpecularInfo layer_coeff_map;
        layer_coeff_map.addRTCoefficients(new ScalarSpecularInfoMap(mp_multi_layer, i));

        // layer DWBA simulation
        for(DecoratedLayerComputation* comp: m_layer_computation[i])
            comp->setSpecularInfo(layer_coeff_map);

        // layer roughness DWBA
        if (mp_roughness_computation)
            mp_roughness_computation->setSpecularInfo(i, layer_coeff_map);

        if (i==0)
            mp_specular_computation->setSpecularInfo(layer_coeff_map);
    }
}

void MainComputation::collectRTCoefficientsMatrix()
{
    // run through layers and construct T,R functions
    for(size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        msglog(Logging::DEBUG2) << "MainComputation::runMagnetic() -> Layer " << i;
        LayerSpecularInfo layer_coeff_map;
        layer_coeff_map.addRTCoefficients(new MatrixSpecularInfoMap(mp_multi_layer, i));

        // layer DWBA simulation
        for(DecoratedLayerComputation* comp: m_layer_computation[i])
            comp->setSpecularInfo(layer_coeff_map);
    }
}
