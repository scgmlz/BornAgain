// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularScalarTanhStrategy.cpp
//! @brief     Implements class SpecularScalarTanhStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SpecularScalarTanhStrategy.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/MathFunctions.h"
#include <Eigen/Dense>

namespace
{
const double pi2_15 = std::pow(M_PI_2, 1.5);
}

Eigen::Vector2cd SpecularScalarTanhStrategy::transition(complex_t kzi, complex_t kzi1, double sigma,
                                                        double thickness,
                                                        const Eigen::Vector2cd& t_r1) const
{
    complex_t roughness = 1;
    if (sigma > 0.0) {
        const double sigeff = pi2_15 * sigma;
        roughness =
            std::sqrt(MathFunctions::tanhc(sigeff * kzi1) / MathFunctions::tanhc(sigeff * kzi));
    }
    const complex_t inv_roughness = 1.0 / roughness;
    const complex_t phase_shift = exp_I(kzi * thickness);
    const complex_t kz_ratio = kzi1 / kzi * roughness;

    const complex_t a00 = 0.5 * (inv_roughness + kz_ratio);
    const complex_t a01 = 0.5 * (inv_roughness - kz_ratio);

    Eigen::Vector2cd result;
    result << (a00 * t_r1(0) + a01 * t_r1(1)) / phase_shift,
        (a01 * t_r1(0) + a00 * t_r1(1)) * phase_shift;
    return result;
}
