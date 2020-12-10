//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Specular/SpecularScalarNCStrategy.cpp
//! @brief     Implements class SpecularScalarNCStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Specular/SpecularScalarNCStrategy.h"
#include <Eigen/Dense>

std::pair<complex_t, complex_t> SpecularScalarNCStrategy::transition(complex_t kzi, complex_t kzi1,
                                                                     double sigma) const {
    complex_t roughness_diff = 1;
    complex_t roughness_sum = 1;
    if (sigma > 0.0) {
        roughness_diff = std::exp(-(kzi1 - kzi) * (kzi1 - kzi) * sigma * sigma / 2.);
        roughness_sum = std::exp(-(kzi1 + kzi) * (kzi1 + kzi) * sigma * sigma / 2.);
    }
    const complex_t kz_ratio = kzi1 / kzi;

    const complex_t a00 = 0.5 * (1. + kz_ratio) * roughness_diff;
    const complex_t a01 = 0.5 * (1. - kz_ratio) * roughness_sum;

    return {a00, a01};
}
