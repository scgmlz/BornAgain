// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularScalarNCStrategy.cpp
//! @brief     Implements class SpecularScalarNCStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SpecularScalarNCStrategy.h"
#include <Eigen/Dense>

Eigen::Vector2cd SpecularScalarNCStrategy::transition(complex_t kzi, complex_t kzi1, double sigma,
                                                      double thickness,
                                                      const Eigen::Vector2cd& t_r1) const
{
    complex_t roughness_diff = 1;
    complex_t roughness_sum = 1;
    if (sigma > 0.0) {
        roughness_diff = exp(-(kzi1 - kzi) * (kzi1 - kzi) * sigma * sigma / 2.);
        roughness_sum = exp(-(kzi1 + kzi) * (kzi1 + kzi) * sigma * sigma / 2.);
    }
    const complex_t phase_shift = exp_I(kzi * thickness);
    const complex_t kz_ratio = kzi1 / kzi;

    const complex_t a00 = 0.5 * (1. + kz_ratio) * roughness_diff;
    const complex_t a01 = 0.5 * (1. - kz_ratio) * roughness_sum;

    Eigen::Vector2cd result;
    result << (a00 * t_r1(0) + a01 * t_r1(1)) / phase_shift,
        (a01 * t_r1(0) + a00 * t_r1(1)) * phase_shift;
    return result;
}
