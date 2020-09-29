// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagneticNewNCStrategy.cpp
//! @brief     Implements class SpecularMagneticNewNCStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SpecularMagneticNewNCStrategy.h"

namespace
{
complex_t checkForUnderflow(complex_t val);
}

std::pair<Eigen::Matrix2cd, Eigen::Matrix2cd>
SpecularMagneticNewNCStrategy::computeRoughnessMatrices(const MatrixRTCoefficients_v3& coeff_i,
                                                        const MatrixRTCoefficients_v3& coeff_i1,
                                                        double sigma) const
{
    complex_t beta_i = coeff_i.m_lambda(1) - coeff_i.m_lambda(0);
    complex_t beta_i1 = coeff_i1.m_lambda(1) - coeff_i1.m_lambda(0);

    auto roughness_matrix = [sigma, &coeff_i, &coeff_i1, beta_i, beta_i1](double sign) {
        const complex_t alpha_p = coeff_i1.m_lambda(0) + coeff_i1.m_lambda(1)
                                  + sign * (coeff_i.m_lambda(0) + coeff_i.m_lambda(1));
        auto b_p_vec = beta_i1 * coeff_i1.m_b + sign * beta_i * coeff_i.m_b;

        auto square = [](auto& v) { return v.x() * v.x() + v.y() * v.y() + v.z() * v.z(); };
        complex_t beta_p = std::sqrt(checkForUnderflow(square(b_p_vec)));
        b_p_vec /= beta_p;

        const complex_t alpha_pp = -(alpha_p * alpha_p + beta_p * beta_p) * sigma * sigma / 8.;
        const complex_t beta_pp = -alpha_p * beta_p * sigma * sigma / 4.;

        Eigen::Matrix2cd QL, QR;

        const complex_t factor1 = std::sqrt(2. * (1. + b_p_vec.z()));
        const complex_t factor2 = std::sqrt(2. * (1. - b_p_vec.z()));
        QL << (b_p_vec.z() + 1.) / factor1, (b_p_vec.z() - 1.) / factor2,
            (b_p_vec.x() + I * b_p_vec.y()) / factor1, (b_p_vec.x() + I * b_p_vec.y()) / factor2;
        QR << (b_p_vec.z() + 1.) / factor1, (b_p_vec.x() - I * b_p_vec.y()) / factor1,
            (b_p_vec.z() - 1.) / factor2, (b_p_vec.x() - I * b_p_vec.y()) / factor2;

        const Eigen::Matrix2cd exp1 =
            Eigen::DiagonalMatrix<complex_t, 2>({std::exp(alpha_pp), std::exp(alpha_pp)});

        if (std::abs(beta_p) > std::numeric_limits<double>::epsilon() * 10.) {
            Eigen::Matrix2cd exp2 = Eigen::Matrix2cd(
                Eigen::DiagonalMatrix<complex_t, 2>({std::exp(beta_pp), std::exp(-beta_pp)}));
            return Eigen::Matrix2cd{exp1 * QL * exp2 * QR};
        }

        return exp1;
    };

    const Eigen::Matrix2cd roughness_sum = roughness_matrix(1.);
    const Eigen::Matrix2cd roughness_diff = roughness_matrix(-1.);

    return {roughness_sum, roughness_diff};
}

std::pair<Eigen::Matrix2cd, Eigen::Matrix2cd>
SpecularMagneticNewNCStrategy::computeBackwardsSubmatrices(const MatrixRTCoefficients_v3& coeff_i,
                                                           const MatrixRTCoefficients_v3& coeff_i1,
                                                           double sigma) const
{
    Eigen::Matrix2cd roughness_sum{Eigen::Matrix2cd::Identity()};
    Eigen::Matrix2cd roughness_diff{Eigen::Matrix2cd::Identity()};
    if (sigma != 0.) {
        const auto ret = computeRoughnessMatrices(coeff_i, coeff_i1, sigma);
        roughness_sum = std::get<0>(ret);
        roughness_diff = std::get<1>(ret);
    }

    const auto P = Eigen::Matrix2cd(coeff_i.computeInverseP() * coeff_i1.computeP());
    const auto mp = 0.5 * (Eigen::Matrix2cd::Identity() + P) * roughness_diff;
    const auto mm = 0.5 * (Eigen::Matrix2cd::Identity() - P) * roughness_sum;

    return {mp, mm};
}

namespace
{
complex_t checkForUnderflow(complex_t val)
{
    return std::abs(val.imag()) < 1e-80 && val.real() < 0 ? complex_t(val.real(), 1e-40) : val;
}
} // namespace
