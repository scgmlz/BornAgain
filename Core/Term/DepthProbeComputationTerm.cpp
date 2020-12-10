//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Term/DepthProbeComputationTerm.cpp
//! @brief     Implements functor DepthProbeComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Term/DepthProbeComputationTerm.h"
#include "Base/Axis/IAxis.h"
#include "Base/Progress/DelayedProgressCounter.h"
#include "Core/Element/DepthProbeElement.h"
#include "Sample/Fresnel/IFresnelMap.h"
#include "Sample/Processed/ProcessedSample.h"
#include "Sample/RT/ILayerRTCoefficients.h"

DepthProbeComputationTerm::DepthProbeComputationTerm(const ProcessedSample* p_sample)
    : m_sample{p_sample} {}

DepthProbeComputationTerm::~DepthProbeComputationTerm() = default;

void DepthProbeComputationTerm::setProgressHandler(ProgressHandler* p_progress) {
    m_progress_counter = std::make_unique<DelayedProgressCounter>(p_progress, 100);
}

void DepthProbeComputationTerm::compute(DepthProbeElement& elem) const {
    if (elem.isCalculated()) {
        const IAxis& z_positions = *elem.getZPositions();
        const size_t n_z = z_positions.size();
        const size_t n_layers = m_sample->numberOfSlices();
        size_t start_z_ind = n_z;
        std::valarray<double> intensities(0.0, n_z);

        double z_layer_bottom(0.0);
        double z_layer_top(0.0);
        for (size_t i_layer = 0; i_layer < n_layers && start_z_ind != 0; ++i_layer) {
            z_layer_bottom = m_sample->sliceBottomZ(i_layer);
            z_layer_top = m_sample->sliceTopZ(i_layer);

            // get R & T coefficients for current layer
            const auto p_coefficients = m_sample->fresnelMap()->getInCoefficients(elem, i_layer);
            const complex_t R = p_coefficients->getScalarR();
            const complex_t T = p_coefficients->getScalarT();
            const complex_t kz_out = p_coefficients->getScalarKz();
            const complex_t kz_in = -kz_out;

            // Compute intensity for z's of the layer
            size_t ip1_z = start_z_ind;
            for (; ip1_z > 0; --ip1_z) {
                const size_t i_z = ip1_z - 1;
                if (i_layer + 1 != n_layers && z_positions[i_z] <= z_layer_bottom)
                    break;
                const double local_position = z_positions[i_z] - z_layer_top;
                intensities[i_z] = std::norm(R * exp_I(kz_out * local_position)
                                             + T * exp_I(kz_in * local_position));
            }
            start_z_ind = ip1_z;
        }
        elem.setIntensities(std::move(intensities));
    }
    if (m_progress_counter) {
        m_progress_counter->stepProgress();
    }
}
