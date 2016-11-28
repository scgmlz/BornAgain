// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerStrategyBuilder.cpp
//! @brief     Implements class LayerStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerStrategyBuilder.h"
#include "Exceptions.h"
#include "FormFactorWrapper.h"
#include "FormFactorDWBA.h"
#include "FormFactorDWBAPol.h"
#include "ILayout.h"
#include "IParticle.h"
#include "InterferenceFunctionNone.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "LayerSpecularInfo.h"
#include "DecouplingApproximationStrategy.h"
#include "SSCApproximationStrategy.h"

LayerStrategyBuilder::LayerStrategyBuilder(
    const Layer& decorated_layer, bool polarized,
    const SimulationOptions& sim_params, size_t layout_index,
    const LayerSpecularInfo* specular_info)
    : m_sim_params {sim_params}
    , mP_specular_info {nullptr}
    , m_layout_index {layout_index}
    , m_polarized {polarized}
{
    mP_layer.reset(decorated_layer.clone());
    assert(mP_layer->getNumberOfLayouts() > 0);
    assert(specular_info);
    mP_specular_info.reset(specular_info->clone());
}

LayerStrategyBuilder::~LayerStrategyBuilder()
{} // needs class definitions => don't move to .h

//! Returns a new strategy object that is able to calculate the scattering for fixed k_f.
IInterferenceFunctionStrategy* LayerStrategyBuilder::createStrategy() const
{
    assert(mP_layer->getNumberOfLayouts()>0);
    SafePointerVector<class FormFactorWrapper> ff_wrappers = collectFormFactorWrappers();
    std::unique_ptr<class IInterferenceFunction> P_interference_function{
        mP_layer->getLayout(m_layout_index)->cloneInterferenceFunction()};

    IInterferenceFunctionStrategy* p_result = nullptr;
    switch (mP_layer->getLayout(m_layout_index)->getApproximation())
    {
    case ILayout::DA:
        if (m_polarized)
            p_result = new DecouplingApproximationStrategy2(m_sim_params);
        else
            p_result = new DecouplingApproximationStrategy1(m_sim_params);
        break;
    case ILayout::SSCA:
    {
        double kappa = P_interference_function->getKappa();
        if (kappa<=0.0)
            throw Exceptions::ClassInitializationException(
                "SSCA requires a nontrivial interference function "
                "with a strictly positive coupling coefficient kappa");
        if (m_polarized)
            p_result = new SSCApproximationStrategy2(m_sim_params, kappa);
        else
            p_result = new SSCApproximationStrategy1(m_sim_params, kappa);
        break;
    }
    default:
        throw Exceptions::ClassInitializationException(
            "Unknown interference function approximation");
    }
    if (!p_result)
        throw Exceptions::ClassInitializationException(
            "Could not create appropriate strategy");
    p_result->init(ff_wrappers, *P_interference_function);
    return p_result;
}

//! Sets m_formfactor_wrappers, the list of weighted form factors.
SafePointerVector<class FormFactorWrapper> LayerStrategyBuilder::collectFormFactorWrappers() const
{
    assert(mP_layer->getNumberOfLayouts()>0);
    SafePointerVector<class FormFactorWrapper> result;
    const ILayout* p_layout = mP_layer->getLayout(m_layout_index);
    const IMaterial* p_layer_material = mP_layer->getMaterial();
    double total_abundance = mP_layer->getTotalAbundance();
    if (total_abundance<=0.0) // TODO: why this can happen? why not throw error?
        total_abundance = 1.0;
    for (const IParticle* particle: p_layout->getParticles()) {
        FormFactorWrapper* p_weighted_ff;
        p_weighted_ff = createFormFactorWrapper(particle, p_layer_material);
        p_weighted_ff->scaleRelativeAbundance(total_abundance);
        p_weighted_ff->setSpecularInfo(*mP_specular_info);
        result.push_back(p_weighted_ff);
    }
    return result;
}

//! Returns a new formfactor wrapper for a given particle in given ambient material.
FormFactorWrapper* LayerStrategyBuilder::createFormFactorWrapper(
    const IParticle* particle, const IMaterial* p_ambient_material) const
{
    const std::unique_ptr<IParticle> P_particle_clone{ particle->clone() };
    P_particle_clone->setAmbientMaterial(*p_ambient_material);

    const std::unique_ptr<IFormFactor> P_ff_particle{ P_particle_clone->createFormFactor() };
    IFormFactor* p_ff_framework;
    if (mP_layer->getNumberOfLayers()>1) {
        if (m_polarized)
            p_ff_framework = new FormFactorDWBAPol(*P_ff_particle);
        else
            p_ff_framework = new FormFactorDWBA(*P_ff_particle);
    } else
        p_ff_framework = P_ff_particle->clone();

    return new FormFactorWrapper(p_ff_framework, particle->getAbundance());
}
