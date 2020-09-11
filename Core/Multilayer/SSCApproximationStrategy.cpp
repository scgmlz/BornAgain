// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SSCApproximationStrategy.cpp
//! @brief     Implements class SSCApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SSCApproximationStrategy.h"
#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Multilayer/FormFactorCoherentSum.h"
#include "Core/Multilayer/InterferenceFunctionUtils.h"
#include "Core/SimulationElement/SimulationElement.h"

using InterferenceFunctionUtils::PrecomputePolarizedFormFactors;
using InterferenceFunctionUtils::PrecomputeScalarFormFactors;

SSCApproximationStrategy::SSCApproximationStrategy(SimulationOptions sim_params, double kappa,
                                                   bool polarized)
    : IInterferenceFunctionStrategy(sim_params, polarized), m_helper(kappa)
{
}

void SSCApproximationStrategy::strategy_specific_post_init()
{
    m_helper.init(m_formfactor_wrappers);
}

//! Returns the total scattering intensity for given kf and
//! for one particle layout (implied by the given particle form factors).
//! This is the scalar version
double SSCApproximationStrategy::scalarCalculation(const SimulationElement& sim_element) const
{
    double qp = sim_element.getMeanQ().magxy();
    double diffuse_intensity = 0.0;
    auto precomputed_ff = PrecomputeScalarFormFactors(sim_element, m_formfactor_wrappers);
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        complex_t ff = precomputed_ff[i];
        double fraction = m_formfactor_wrappers[i].relativeAbundance();
        diffuse_intensity += fraction * std::norm(ff);
    }
    complex_t mean_ff_norm =
        m_helper.getMeanFormfactorNorm(qp, precomputed_ff, m_formfactor_wrappers);
    complex_t p2kappa = m_helper.getCharacteristicSizeCoupling(qp, m_formfactor_wrappers);
    complex_t omega = m_helper.getCharacteristicDistribution(qp, mP_iff.get());
    double iff = 2.0 * (mean_ff_norm * omega / (1.0 - p2kappa * omega)).real();
    double dw_factor = mP_iff->DWfactor(sim_element.getMeanQ());
    return diffuse_intensity + dw_factor * iff;
}

//! This is the polarized version
double SSCApproximationStrategy::polarizedCalculation(const SimulationElement& sim_element) const
{
    double qp = sim_element.getMeanQ().magxy();
    Eigen::Matrix2cd diffuse_matrix = Eigen::Matrix2cd::Zero();
    auto precomputed_ff = PrecomputePolarizedFormFactors(sim_element, m_formfactor_wrappers);
    const auto& polarization_handler = sim_element.polarizationHandler();
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        Eigen::Matrix2cd ff = precomputed_ff[i];
        double fraction = m_formfactor_wrappers[i].relativeAbundance();
        diffuse_matrix += fraction * (ff * polarization_handler.getPolarization() * ff.adjoint());
    }
    Eigen::Matrix2cd mff_orig, mff_conj; // original and conjugated mean formfactor
    m_helper.getMeanFormfactors(qp, mff_orig, mff_conj, precomputed_ff, m_formfactor_wrappers);
    complex_t p2kappa = m_helper.getCharacteristicSizeCoupling(qp, m_formfactor_wrappers);
    complex_t omega = m_helper.getCharacteristicDistribution(qp, mP_iff.get());
    Eigen::Matrix2cd interference_matrix = (2.0 * omega / (1.0 - p2kappa * omega))
                                           * polarization_handler.getAnalyzerOperator() * mff_orig
                                           * polarization_handler.getPolarization() * mff_conj;
    Eigen::Matrix2cd diffuse_matrix2 = polarization_handler.getAnalyzerOperator() * diffuse_matrix;
    double interference_trace = std::abs(interference_matrix.trace());
    double diffuse_trace = std::abs(diffuse_matrix2.trace());
    double dw_factor = mP_iff->DWfactor(sim_element.getMeanQ());
    return diffuse_trace + dw_factor * interference_trace;
}
