// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/LayoutStrategyBuilder.cpp
//! @brief     Implements class LayoutStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/LayoutStrategyBuilder.h"
#include "Core/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Computation/ProcessedLayout.h"
#include "Core/Multilayer/DecouplingApproximationStrategy.h"
#include "Core/Multilayer/SSCApproximationStrategy.h"

LayoutStrategyBuilder::LayoutStrategyBuilder(const ProcessedLayout* p_layout,
                                             const SimulationOptions& sim_params, bool polarized)
    : mp_layout(p_layout), m_sim_params(sim_params), m_polarized(polarized)
{
    createStrategy();
}

// needs class definitions => don't move to .h
LayoutStrategyBuilder::~LayoutStrategyBuilder() {}

IInterferenceFunctionStrategy* LayoutStrategyBuilder::releaseStrategy()
{
    return mP_strategy.release();
}

//! Returns a new strategy object that is able to calculate the scattering for fixed k_f.
void LayoutStrategyBuilder::createStrategy()
{
    const IInterferenceFunction* p_iff = mp_layout->interferenceFunction();
    checkInterferenceFunction(p_iff);

    auto p_radial_para = dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(p_iff);
    if (p_radial_para && p_radial_para->kappa() > 0.0) {
        double kappa = p_radial_para->kappa();
        mP_strategy.reset(new SSCApproximationStrategy(m_sim_params, kappa, m_polarized));
    } else {
        mP_strategy.reset(new DecouplingApproximationStrategy(m_sim_params, m_polarized));
    }
    if (!mP_strategy)
        throw Exceptions::ClassInitializationException("Could not create appropriate strategy");
    mP_strategy->init(mp_layout->formFactorList(), p_iff);
    return;
}

void LayoutStrategyBuilder::checkInterferenceFunction(const IInterferenceFunction* p_iff)
{
    auto n_slices = mp_layout->numberOfSlices();
    if (p_iff && n_slices > 1 && !p_iff->supportsMultilayer())
        throw std::runtime_error("LayoutStrategyBuilder::checkInterferenceFunction: "
                                 "interference function does not support multiple layers");
}
