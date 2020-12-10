//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Interference/SSCApproximationStrategy.cpp
//! @brief     Implements class SSCApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Interference/SSCApproximationStrategy.h"
#include "Base/Pixel/SimulationElement.h"
#include "Sample/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Sample/Fresnel/FormFactorCoherentSum.h"

SSCApproximationStrategy::SSCApproximationStrategy(
    const std::vector<FormFactorCoherentSum>& weighted_formfactors,
    const InterferenceFunctionRadialParaCrystal* iff, SimulationOptions sim_params, bool polarized,
    double kappa)
    : IInterferenceFunctionStrategy(weighted_formfactors, sim_params, polarized)
    , m_iff(iff->clone())
    , m_kappa(kappa) {
    m_mean_radius = 0.0;
    for (const auto& ffw : m_weighted_formfactors)
        m_mean_radius += ffw.relativeAbundance() * ffw.radialExtension();
}

//! Returns the total scattering intensity for given kf and
//! for one particle layout (implied by the given particle form factors).
//! This is the scalar version
double SSCApproximationStrategy::scalarCalculation(const SimulationElement& sim_element) const {
    const double qp = sim_element.meanQ().magxy();
    double diffuse_intensity = 0.0;
    complex_t ff_orig = 0., ff_conj = 0.; // original and conjugated mean formfactor
    for (const auto& ffw : m_weighted_formfactors) {
        complex_t ff = ffw.evaluate(sim_element);
        double fraction = ffw.relativeAbundance();
        diffuse_intensity += fraction * std::norm(ff);
        double radial_extension = ffw.radialExtension();
        complex_t prefac =
            ffw.relativeAbundance() * calculatePositionOffsetPhase(qp, radial_extension);
        ff_orig += prefac * ff;
        ff_conj += prefac * std::conj(ff);
    }
    const complex_t mean_ff_norm = ff_orig * ff_conj;
    const complex_t p2kappa = getCharacteristicSizeCoupling(qp, m_weighted_formfactors);
    const complex_t omega = m_iff->FTPDF(qp);
    const double iff = 2.0 * (mean_ff_norm * omega / (1.0 - p2kappa * omega)).real();
    const double dw_factor = m_iff->DWfactor(sim_element.meanQ());
    return diffuse_intensity + dw_factor * iff;
}

//! This is the polarized version
double SSCApproximationStrategy::polarizedCalculation(const SimulationElement& sim_element) const {
    const double qp = sim_element.meanQ().magxy();
    Eigen::Matrix2cd diffuse_matrix = Eigen::Matrix2cd::Zero();
    const auto& polarization_handler = sim_element.polarizationHandler();
    Eigen::Matrix2cd ff_orig = Eigen::Matrix2cd::Zero();
    Eigen::Matrix2cd ff_conj = Eigen::Matrix2cd::Zero();
    for (const auto& ffw : m_weighted_formfactors) {
        const Eigen::Matrix2cd ff = ffw.evaluatePol(sim_element);
        const double fraction = ffw.relativeAbundance();
        diffuse_matrix += fraction * (ff * polarization_handler.getPolarization() * ff.adjoint());
        const double radial_extension = ffw.radialExtension();
        const complex_t prefac =
            ffw.relativeAbundance() * calculatePositionOffsetPhase(qp, radial_extension);
        ff_orig += prefac * ff;
        ff_conj += prefac * ff.adjoint();
    }
    const complex_t p2kappa = getCharacteristicSizeCoupling(qp, m_weighted_formfactors);
    const complex_t omega = m_iff->FTPDF(qp);
    const Eigen::Matrix2cd interference_matrix =
        (2.0 * omega / (1.0 - p2kappa * omega)) * polarization_handler.getAnalyzerOperator()
        * ff_orig * polarization_handler.getPolarization() * ff_conj;
    const Eigen::Matrix2cd diffuse_matrix2 =
        polarization_handler.getAnalyzerOperator() * diffuse_matrix;
    const double interference_trace = std::abs(interference_matrix.trace());
    const double diffuse_trace = std::abs(diffuse_matrix2.trace());
    const double dw_factor = m_iff->DWfactor(sim_element.meanQ());
    return diffuse_trace + dw_factor * interference_trace;
}

complex_t SSCApproximationStrategy::getCharacteristicSizeCoupling(
    double qp, const std::vector<FormFactorCoherentSum>& ff_wrappers) const {
    complex_t result = 0;
    for (const auto& ffw : ff_wrappers)
        result +=
            ffw.relativeAbundance() * calculatePositionOffsetPhase(2.0 * qp, ffw.radialExtension());
    return result;
}

complex_t SSCApproximationStrategy::calculatePositionOffsetPhase(double qp,
                                                                 double radial_extension) const {
    return exp_I(m_kappa * qp * (radial_extension - m_mean_radius));
}
