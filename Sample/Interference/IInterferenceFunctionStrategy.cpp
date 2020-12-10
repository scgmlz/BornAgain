//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Interference/IInterferenceFunctionStrategy.cpp
//! @brief     Implements default behaviour of IInterferenceFunctionStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Interference/IInterferenceFunctionStrategy.h"
#include "Base/Math/IntegratorMCMiser.h"
#include "Base/Pixel/SimulationElement.h"
#include "Base/Utils/Assert.h"
#include "Sample/Fresnel/FormFactorCoherentSum.h"

IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(
    const std::vector<FormFactorCoherentSum>& weighted_formfactors,
    const SimulationOptions& sim_params, bool polarized)
    : m_weighted_formfactors(weighted_formfactors)
    , m_options(sim_params)
    , m_polarized(polarized)
    , m_integrator(make_integrator_miser(
          this, &IInterferenceFunctionStrategy::evaluate_for_fixed_angles, 2)) {
    ASSERT(!m_weighted_formfactors.empty());
}

IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy() = default;

double IInterferenceFunctionStrategy::evaluate(const SimulationElement& sim_element) const {
    if (m_options.isIntegrate() && (sim_element.solidAngle() > 0.0))
        return MCIntegratedEvaluate(sim_element);
    return evaluateSinglePoint(sim_element);
}

double
IInterferenceFunctionStrategy::evaluateSinglePoint(const SimulationElement& sim_element) const {
    if (!m_polarized)
        return scalarCalculation(sim_element);
    return polarizedCalculation(sim_element);
}

//! Performs a Monte Carlo integration over the bin for the evaluation of the intensity.
double
IInterferenceFunctionStrategy::MCIntegratedEvaluate(const SimulationElement& sim_element) const {
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    return m_integrator->integrate(min_array, max_array, (void*)&sim_element,
                                   m_options.getMcPoints());
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles(double* fractions, size_t,
                                                                void* params) const {
    double par0 = fractions[0];
    double par1 = fractions[1];

    SimulationElement* pars = static_cast<SimulationElement*>(params);

    SimulationElement sim_element = pars->pointElement(par0, par1);
    return pars->integrationFactor(par0, par1) * evaluateSinglePoint(sim_element);
}
