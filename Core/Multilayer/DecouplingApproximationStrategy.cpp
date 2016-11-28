// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/DecouplingApproximationStrategy.cpp
//! @brief     Implements classes DecouplingApproximationStrategy1,
//!              DecouplingApproximationStrategy2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DecouplingApproximationStrategy.h"
#include "Exceptions.h"
#include "FormFactorWrapper.h"
#include "IInterferenceFunction.h"
#include "MathFunctions.h"
#include "RealParameter.h"
#include "SimulationElement.h"

//! Returns the total incoherent and coherent scattering intensity for given kf and
//! for one layer (implied by the given particle form factors).
//! For each IParticle in the layer layout, the precomputed form factor must be provided.
double DecouplingApproximationStrategy1::evaluateForList(
    const SimulationElement& sim_element) const
{
    double intensity = 0.0;
    complex_t amplitude = complex_t(0.0, 0.0);
    if (m_total_abundance <= 0.0)
        return 0.0;
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        complex_t ff = m_precomputed_ff1[i];
        if (std::isnan(ff.real()))
            throw Exceptions::RuntimeErrorException(
                "DecouplingApproximationStrategy::evaluateForList() -> Error! Amplitude is NaN");
        double fraction = m_formfactor_wrappers[i]->relativeAbundance() / m_total_abundance;
        amplitude += fraction * ff;
        intensity += fraction * std::norm(ff);
    }
    double amplitude_norm = std::norm(amplitude);
    double itf_function = mP_iff->evaluate(sim_element.getMeanQ());
    return m_total_abundance * (intensity + amplitude_norm * (itf_function - 1.0));
}

//! Returns the total incoherent and coherent scattering intensity for given kf and
//! for one layer (implied by the given particle form factors).
//! For each IParticle in the layer layout, the precomputed form factor must be provided.
//! This is the polarized variant of evaluateForList. Each form factor must be
//! precomputed for polarized beam and detector.
double DecouplingApproximationStrategy2::evaluateForList(
    const SimulationElement& sim_element) const
{
    Eigen::Matrix2cd mean_intensity = Eigen::Matrix2cd::Zero();
    Eigen::Matrix2cd mean_amplitude = Eigen::Matrix2cd::Zero();

    if (m_total_abundance <= 0.0)
        return 0.0;
    for (size_t i = 0; i < m_formfactor_wrappers.size(); ++i) {
        Eigen::Matrix2cd ff = m_precomputed_ff2[i];
        if (!ff.allFinite())
            throw Exceptions::RuntimeErrorException(
                "DecouplingApproximationStrategy::evaluateForList() -> "
                "Error! Form factor contains NaN or infinite");
        double fraction = m_formfactor_wrappers[i]->relativeAbundance() / m_total_abundance;
        mean_amplitude += fraction * ff;
        mean_intensity += fraction * (ff * sim_element.getPolarization() * ff.adjoint());
    }
    Eigen::Matrix2cd amplitude_matrix = sim_element.getAnalyzerOperator() * mean_amplitude
            * sim_element.getPolarization() * mean_amplitude.adjoint();
    Eigen::Matrix2cd intensity_matrix = sim_element.getAnalyzerOperator() * mean_intensity;
    double amplitude_trace = std::abs(amplitude_matrix.trace());
    double intensity_trace = std::abs(intensity_matrix.trace());
    double itf_function = mP_iff->evaluate(sim_element.getMeanQ());
    return m_total_abundance * (intensity_trace + amplitude_trace * (itf_function - 1.0));
}
