// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SSCApproximationStrategy.cpp
//! @brief     Implements classes SSCApproximationStrategy,
//!              SSCApproximationStrategy1, SSCApproximationStrategy2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SSCApproximationStrategy.h"
#include "Exceptions.h"
#include "FormFactorWrapper.h"
#include "IFormFactor.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "RealParameter.h"
#include "SimulationElement.h"

// ************************************************************************** //
//  class SSCApproximationStrategy
// ************************************************************************** //

SSCApproximationStrategy::SSCApproximationStrategy(double kappa)
    : m_mean_radius(0.0), m_kappa(kappa)
{}

void SSCApproximationStrategy::strategy_specific_post_init()
{
    // Set m_mean_radius to the weighted arithmetic average of the particle radii.
    m_mean_radius = 0.0;
    for (const auto ffw: m_formfactor_wrappers)
        m_mean_radius += ffw->relativeAbundance() * ffw->radialExtension();
    if (m_total_abundance > 0.0)
        m_mean_radius /= m_total_abundance;
}

complex_t SSCApproximationStrategy::getCharacteristicDistribution(double qp) const
{
    const InterferenceFunctionRadialParaCrystal *p_iff
        = dynamic_cast<const InterferenceFunctionRadialParaCrystal*>(mP_iff.get());
    if (p_iff == 0)
        throw Exceptions::ClassInitializationException("Wrong interference function for SSCA");
    return p_iff->FTPDF(qp);
}

complex_t SSCApproximationStrategy::getCharacteristicSizeCoupling(double qp, double kappa) const
{
    size_t n_frs = m_formfactor_wrappers.size();
    complex_t result = complex_t(0.0, 0.0);
    for (size_t i = 0; i < n_frs; ++i)
        result += m_formfactor_wrappers[i]->relativeAbundance() *
            calculatePositionOffsetPhase(qp, kappa, i);
    return result / m_total_abundance;
}

complex_t SSCApproximationStrategy::calculatePositionOffsetPhase(
    double qp, double kappa, size_t index) const
{
    return exp_I(kappa * qp *
                 (m_formfactor_wrappers[index]->radialExtension()
                  - m_mean_radius));
}

// ************************************************************************** //
//  class SSCApproximationStrategy1
// ************************************************************************** //

//! Returns the total scattering intensity for given kf and
//! for one layer (implied by the given particle form factors).
//! For each IParticle in the layer layout, the precomputed form factor must be provided.
double SSCApproximationStrategy1::evaluateForList(const SimulationElement& sim_element) const
{
    double qp = sim_element.getMeanQ().magxy();
    double diffuse_intensity = 0.0;
    if (m_total_abundance <= 0.0)
        return 0.0;
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        complex_t ff = m_precomputed_ff1[i];
        double fraction = m_formfactor_wrappers[i]->relativeAbundance() / m_total_abundance;
        diffuse_intensity += fraction * std::norm(ff);
    }
    complex_t mean_ff_norm  = getMeanFormfactorNorm(qp);
    complex_t p2kappa = getCharacteristicSizeCoupling(qp, 2.0 * m_kappa);
    complex_t omega = getCharacteristicDistribution(qp);
    double interference_intensity = 2.0 * (mean_ff_norm * omega / (1.0 - p2kappa * omega)).real();
    return m_total_abundance * (diffuse_intensity + interference_intensity);
}

complex_t SSCApproximationStrategy1::getMeanFormfactorNorm(double qp) const
{
    complex_t ff_orig=0., ff_conj=0.; // original and conjugated mean formfactor
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        complex_t prefac = m_formfactor_wrappers[i]->relativeAbundance()
            * calculatePositionOffsetPhase(qp, m_kappa, i);
        ff_orig += prefac * m_precomputed_ff1[i];
        ff_conj += prefac * std::conj(m_precomputed_ff1[i]);
    }
    return ff_orig * ff_conj / m_total_abundance / m_total_abundance;
}

// ************************************************************************** //
//  class SSCApproximationStrategy2
// ************************************************************************** //

//! Returns the total scattering intensity for given kf and
//! for one layer (implied by the given particle form factors).
//! For each IParticle in the layer layout, the precomputed form factor must be provided.
//! This is the polarized variant of evaluateForList. Each form factor must be
//! precomputed for polarized beam and detector.
double SSCApproximationStrategy2::evaluateForList(const SimulationElement& sim_element) const
{
    double qp = sim_element.getMeanQ().magxy();
    Eigen::Matrix2cd diffuse_matrix = Eigen::Matrix2cd::Zero();
    if (m_total_abundance <= 0.0)
        return 0.0;
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        Eigen::Matrix2cd ff = m_precomputed_ff2[i];
        double fraction = m_formfactor_wrappers[i]->relativeAbundance() / m_total_abundance;
        diffuse_matrix += fraction * (ff * sim_element.getPolarization() * ff.adjoint());
    }
    Eigen::Matrix2cd mff_orig, mff_conj; // original and conjugated mean formfactor
    getMeanFormfactors(qp, mff_orig, mff_conj);
    complex_t p2kappa = getCharacteristicSizeCoupling(qp, 2.0 * m_kappa);
    complex_t omega = getCharacteristicDistribution(qp);
    Eigen::Matrix2cd interference_matrix
        = (2.0 * omega / (1.0 - p2kappa * omega))
        * sim_element.getAnalyzerOperator() * mff_orig
        * sim_element.getPolarization() * mff_conj;
    Eigen::Matrix2cd diffuse_matrix2 = sim_element.getAnalyzerOperator() * diffuse_matrix;
    double interference_trace = std::abs(interference_matrix.trace());
    double diffuse_trace = std::abs(diffuse_matrix2.trace());
    return m_total_abundance * (diffuse_trace + interference_trace);
}

//! Computes ff_orig and ff_conj.
void SSCApproximationStrategy2::getMeanFormfactors(
    double qp, Eigen::Matrix2cd& ff_orig, Eigen::Matrix2cd& ff_conj) const
{
    ff_orig=Eigen::Matrix2cd::Zero();
    ff_conj=Eigen::Matrix2cd::Zero();
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        complex_t prefac = m_formfactor_wrappers[i]->relativeAbundance()
            * calculatePositionOffsetPhase(qp, m_kappa, i);
        ff_orig += prefac * m_precomputed_ff2[i];
        ff_conj += prefac * m_precomputed_ff2[i].adjoint();
    }
    ff_orig /= m_total_abundance;
    ff_conj /= m_total_abundance;
}
