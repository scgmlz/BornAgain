// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IInterferenceFunctionStrategy.cpp
//! @brief     Implements default behaviour of IInterferenceFunctionStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/IInterferenceFunctionStrategy.h"
#include "Core/Aggregate/InterferenceFunctionNone.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Multilayer/FormFactorCoherentSum.h"
#include "Core/SimulationElement/SimulationElement.h"
#include "Core/Tools/IntegratorMCMiser.h"

IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(const SimulationOptions& sim_params,
                                                             bool polarized)
    : mP_iff(nullptr), m_options(sim_params), m_polarized(polarized),
      mP_integrator(
          make_integrator_miser(this, &IInterferenceFunctionStrategy::evaluate_for_fixed_angles, 2))
{
}

IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy() = default;

void IInterferenceFunctionStrategy::init(
    const std::vector<FormFactorCoherentSum>& weighted_formfactors,
    const IInterferenceFunction* p_iff)
{
    if (weighted_formfactors.size() == 0)
        throw Exceptions::ClassInitializationException(
            "IInterferenceFunctionStrategy::init: strategy gets no form factors.");
    m_formfactor_wrappers = weighted_formfactors;
    if (p_iff)
        mP_iff.reset(p_iff->clone());
    else
        mP_iff.reset(new InterferenceFunctionNone());

    strategy_specific_post_init();
}

double IInterferenceFunctionStrategy::evaluate(const SimulationElement& sim_element) const
{
    if (m_options.isIntegrate() && (sim_element.getSolidAngle() > 0.0))
        return MCIntegratedEvaluate(sim_element);
    return evaluateSinglePoint(sim_element);
}

double
IInterferenceFunctionStrategy::evaluateSinglePoint(const SimulationElement& sim_element) const
{
    if (!m_polarized)
        return scalarCalculation(sim_element);
    else
        return polarizedCalculation(sim_element);
}

//! Performs a Monte Carlo integration over the bin for the evaluation of the intensity.
double
IInterferenceFunctionStrategy::MCIntegratedEvaluate(const SimulationElement& sim_element) const
{
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    return mP_integrator->integrate(min_array, max_array, (void*)&sim_element,
                                    m_options.getMcPoints());
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles(double* fractions, size_t,
                                                                void* params) const
{
    double par0 = fractions[0];
    double par1 = fractions[1];

    SimulationElement* pars = static_cast<SimulationElement*>(params);

    SimulationElement sim_element(*pars, par0, par1);
    return pars->getIntegrationFactor(par0, par1) * evaluateSinglePoint(sim_element);
}

void IInterferenceFunctionStrategy::strategy_specific_post_init() {}
