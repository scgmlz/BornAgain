// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IInterferenceFunctionStrategy.cpp
//! @brief     Implements default behaviour of IInterferenceFunctionStrategy,
//!              IInterferenceFunctionStrategy1, IInterferenceFunctionStrategy2
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IInterferenceFunctionStrategy.h"
#include "FormFactorWrapper.h"
#include "IFormFactor.h"
#include "IInterferenceFunction.h"
#include "IntegratorMCMiser.h"
#include "LayerSpecularInfo.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include "ScalarRTCoefficients.h"
#include "SimulationElement.h"
#include "WavevectorInfo.h"

IInterferenceFunctionStrategy::IInterferenceFunctionStrategy()
{}

IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(const SimulationOptions& sim_params)
    : mP_iff {nullptr}
    , m_options {sim_params}
    , mP_integrator {make_integrator_miser(
        this, &IInterferenceFunctionStrategy::evaluate_for_fixed_angles, 2)}
{}

IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy()
{} // needs class definitions => don't move to .h

//! Initializes the object with form factors and interference functions
void IInterferenceFunctionStrategy::init(
    const SafePointerVector<FormFactorWrapper>& weighted_formfactors,
    const IInterferenceFunction& iff,
    const LayerSpecularInfo& specular_info)
{
    if (weighted_formfactors.size()==0)
        throw Exceptions::ClassInitializationException("Bug: Decorated layer has no formfactors.");
    m_formfactor_wrappers = weighted_formfactors;
    mP_iff.reset(iff.clone());

    m_total_abundance = 0;
    for (const auto ffw: m_formfactor_wrappers)
        m_total_abundance += ffw->m_abundance;

    if (&specular_info != mP_specular_info.get())
        mP_specular_info.reset(specular_info.clone());

    strategy_specific_post_init();
}

double IInterferenceFunctionStrategy::evaluate(const SimulationElement& sim_element) const
{
    if (m_options.isIntegrate() && (sim_element.getSolidAngle() > 0.0))
        return MCIntegratedEvaluate(sim_element);
    precomputeParticleFormfactors(sim_element);
    return evaluateForList(sim_element);
}

//! Performs a Monte Carlo integration over the bin for the evaluation of the intensity.
double IInterferenceFunctionStrategy::MCIntegratedEvaluate(
    const SimulationElement& sim_element) const
{
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    return mP_integrator->integrate(
        min_array, max_array, (void*)&sim_element, m_options.getMcPoints());
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles(
    double* fractions, size_t, void* params) const
{
    double par0 = fractions[0];
    double par1 = fractions[1];

    SimulationElement* pars = static_cast<SimulationElement*>(params);

    SimulationElement sim_element(*pars, par0, par1);
    precomputeParticleFormfactors(sim_element);
    return pars->getIntegrationFactor(par0, par1) * evaluateForList(sim_element);
}


//! Precomputes scalar form factors.
void IInterferenceFunctionStrategy1::precomputeParticleFormfactors(
    const SimulationElement& sim_element) const
{
    m_precomputed_ff1.clear();

    double wavevector_scattering_factor = sim_element.getKi().mag2() / 4 / M_PI;
    WavevectorInfo wavevectors(sim_element.getKi(), sim_element.getMeanKf());

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(sim_element));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(sim_element));
    for (auto ffw: m_formfactor_wrappers) {
        ffw->mp_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
        complex_t ff_mat = ffw->mp_ff->evaluate(wavevectors);
        m_precomputed_ff1.push_back(wavevector_scattering_factor*ff_mat);
    }
}

//! Precomputes matrix form factors.
void IInterferenceFunctionStrategy2::precomputeParticleFormfactors(
    const SimulationElement& sim_element) const
{
    m_precomputed_ff2.clear();

    double wavevector_scattering_factor = sim_element.getKi().mag2() / 4 / M_PI;
    WavevectorInfo wavevectors(sim_element.getKi(), sim_element.getMeanKf());

    const std::unique_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(sim_element));
    const std::unique_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(sim_element));
    for (auto ffw: m_formfactor_wrappers) {
        ffw->mp_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
        Eigen::Matrix2cd ff_mat = ffw->mp_ff->evaluatePol(wavevectors);
        m_precomputed_ff2.push_back(wavevector_scattering_factor*ff_mat);
    }
}
