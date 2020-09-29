// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMagneticNewTanhStrategy.cpp
//! @brief     Implements class SpecularMagneticNewTanhStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SpecularMagneticNewTanhStrategy.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/MathFunctions.h"

namespace
{
const double pi2_15 = std::pow(M_PI_2, 1.5);
} // namespace

Eigen::Matrix2cd
SpecularMagneticNewTanhStrategy::computeRoughnessMatrix(const MatrixRTCoefficients_v3& coeff,
                                                        double sigma, bool inverse) const
{
    if (sigma < 10 * std::numeric_limits<double>::epsilon())
        return Eigen::Matrix2cd{Eigen::Matrix2cd::Identity()};

    const double sigeff = pi2_15 * sigma;
    const auto b = coeff.m_b;

    if (std::abs(b.mag() - 1.) < std::numeric_limits<double>::epsilon() * 10.) {
        Eigen::Matrix2cd Q;
        const double factor1 = 2. * (1. + b.z());
        Q << (1. + b.z()), (I * b.y() - b.x()), (b.x() + I * b.y()), (b.z() + 1.);

        complex_t l1 = std::sqrt(MathFunctions::tanhc(sigeff * coeff.m_lambda(1)));
        complex_t l2 = std::sqrt(MathFunctions::tanhc(sigeff * coeff.m_lambda(0)));

        if (inverse) {
            l1 = 1. / l1;
            l2 = 1. / l2;
        }

        const Eigen::Matrix2cd lambda = Eigen::DiagonalMatrix<complex_t, 2>({l1, l2});

        return Q * lambda * Q.adjoint() / factor1;

    } else if (b.mag() < 10 * std::numeric_limits<double>::epsilon()) {
        complex_t alpha =
            std::sqrt(MathFunctions::tanhc(0.5 * sigeff * (coeff.m_lambda(1) + coeff.m_lambda(0))));
        if (inverse)
            alpha = 1. / alpha;
        const Eigen::Matrix2cd lambda = Eigen::DiagonalMatrix<complex_t, 2>({alpha, alpha});

        return lambda;
    }

    throw std::runtime_error("Broken magnetic field vector");
}

std::pair<Eigen::Matrix2cd, Eigen::Matrix2cd>
SpecularMagneticNewTanhStrategy::computeBackwardsSubmatrices(
    const MatrixRTCoefficients_v3& coeff_i, const MatrixRTCoefficients_v3& coeff_i1,
    double sigma) const
{
    Eigen::Matrix2cd R{Eigen::Matrix2cd::Identity()};
    Eigen::Matrix2cd RInv{Eigen::Matrix2cd::Identity()};

    if (sigma != 0.) {
        R = computeRoughnessMatrix(coeff_i1, sigma, false)
            * computeRoughnessMatrix(coeff_i, sigma, true);

        RInv = computeRoughnessMatrix(coeff_i, sigma, false)
               * computeRoughnessMatrix(coeff_i1, sigma, true);
    }

    const Eigen::Matrix2cd mproduct = coeff_i.computeInverseP() * coeff_i1.computeP();
    const Eigen::Matrix2cd mp = 0.5 * (RInv + mproduct * R);
    const Eigen::Matrix2cd mm = 0.5 * (RInv - mproduct * R);

    return {mp, mm};
}
