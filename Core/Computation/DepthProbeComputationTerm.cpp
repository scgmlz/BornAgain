// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DepthProbeComputationTerm.cpp
//! @brief     Implements functor DepthProbeComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DepthProbeComputationTerm.h"
#include "DelayedProgressCounter.h"
#include "DepthProbeElement.h"
#include "IAxis.h"
#include "IFresnelMap.h"
#include "ILayerRTCoefficients.h"
#include "MultiLayer.h"

DepthProbeComputationTerm::DepthProbeComputationTerm(const MultiLayer* p_multi_layer,
                                                     const IFresnelMap* p_fresnel_map)
    : mp_multilayer(p_multi_layer), mp_fresnel_map(p_fresnel_map)
{}

DepthProbeComputationTerm::~DepthProbeComputationTerm() =default;

void DepthProbeComputationTerm::setProgressHandler(ProgressHandler* p_progress)
{
    mP_progress_counter.reset(new DelayedProgressCounter(p_progress, 100));
}

void DepthProbeComputationTerm::compute(DepthProbeElement& elem) const
{
    if (elem.isCalculated()) {
        const IAxis& z_positions = *elem.getZPositions();
        const size_t n_z = z_positions.size();
        const size_t n_layers = mp_multilayer->numberOfLayers();
        size_t start_z_ind = n_z;
        std::valarray<double> intensities(0.0, n_z);

        double z_layer_bottom(0.0);
        double z_layer_top(0.0);
        for (size_t i_layer = 0; i_layer < n_layers && start_z_ind != 0; ++i_layer) {
            z_layer_bottom = mp_multilayer->layerBottomZ(i_layer);
            z_layer_top = mp_multilayer->layerTopZ(i_layer);

            // get R & T coefficients for current layer
            const auto p_coefficients = mp_fresnel_map->getInCoefficients(elem, i_layer);
            const complex_t R = p_coefficients->getScalarR();
            const complex_t T = p_coefficients->getScalarT();
            const complex_t kz_out = p_coefficients->getScalarKz();
            const complex_t kz_in = -kz_out;

            // Compute intensity for z's of the layer
            size_t ip1_z = start_z_ind;
            for (; ip1_z > 0; --ip1_z)
            {
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
    if (mP_progress_counter) {
        mP_progress_counter->stepProgress();
    }
}
