//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file     Sample/RT/MatrixRTCoefficients.cpp
//! @brief    Implements class MatrixRTCoefficients.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/RT/MatrixRTCoefficients.h"
#include "Base/Utils/Assert.h"

namespace {
complex_t GetImExponential(complex_t exponent);
const auto eps = std::numeric_limits<double>::epsilon() * 10.;
} // namespace

MatrixRTCoefficients::MatrixRTCoefficients(double kz_sign, Eigen::Vector2cd eigenvalues,
                                           kvector_t b, double magnetic_SLD)
    : m_kz_sign(kz_sign)
    , m_lambda(std::move(eigenvalues))
    , m_b(std::move(b))
    , m_magnetic_SLD(magnetic_SLD) {
    ASSERT(std::abs(m_b.mag() - 1) < eps || (m_b.mag() < eps && magnetic_SLD < eps));

    m_T << 1, 0, 0, 1;
    m_R << -1, 0, 0, -1;
}

MatrixRTCoefficients::MatrixRTCoefficients(const MatrixRTCoefficients& other) = default;

MatrixRTCoefficients::~MatrixRTCoefficients() = default;

MatrixRTCoefficients* MatrixRTCoefficients::clone() const {
    return new MatrixRTCoefficients(*this);
}

Eigen::Matrix2cd MatrixRTCoefficients::TransformationMatrix(Eigen::Vector2d selection) const {
    const Eigen::Matrix2cd exp2 = Eigen::DiagonalMatrix<complex_t, 2>(selection);

    if (std::abs(m_b.mag() - 1.) < eps) {
        Eigen::Matrix2cd Q;
        const double factor1 = 2. * (1. + m_b.z());
        Q << (1. + m_b.z()), (I * m_b.y() - m_b.x()), (m_b.x() + I * m_b.y()), (m_b.z() + 1.);
        return Q * exp2 * Q.adjoint() / factor1;

    } else if (m_b.mag() < eps)
        return exp2;

    throw std::runtime_error("Broken magnetic field vector");
}

Eigen::Matrix2cd MatrixRTCoefficients::T1Matrix() const {
    return TransformationMatrix({0., 1.});
}

Eigen::Matrix2cd MatrixRTCoefficients::T2Matrix() const {
    return TransformationMatrix({1., 0.});
}

Eigen::Vector2cd MatrixRTCoefficients::T1plus() const {
    return T1Matrix() * m_T.col(0);
}

Eigen::Vector2cd MatrixRTCoefficients::R1plus() const {
    return T1Matrix() * m_R.col(0);
}

Eigen::Vector2cd MatrixRTCoefficients::T2plus() const {
    return T2Matrix() * m_T.col(0);
}

Eigen::Vector2cd MatrixRTCoefficients::R2plus() const {
    return T2Matrix() * m_R.col(0);
}

Eigen::Vector2cd MatrixRTCoefficients::T1min() const {
    return T1Matrix() * m_T.col(1);
}

Eigen::Vector2cd MatrixRTCoefficients::R1min() const {
    return T1Matrix() * m_R.col(1);
}

Eigen::Vector2cd MatrixRTCoefficients::T2min() const {
    return T2Matrix() * m_T.col(1);
}

Eigen::Vector2cd MatrixRTCoefficients::R2min() const {
    return T2Matrix() * m_R.col(1);
}

Eigen::Vector2cd MatrixRTCoefficients::getKz() const {
    return m_kz_sign * m_lambda;
}

Eigen::Matrix2cd MatrixRTCoefficients::pMatrixHelper(double sign) const {
    const complex_t alpha = m_lambda(1) + m_lambda(0);
    const complex_t beta = m_lambda(1) - m_lambda(0);

    Eigen::Matrix2cd result;

    kvector_t b = m_b;

    result << alpha + sign * beta * b.z(), sign * beta * (b.x() - I * b.y()),
        sign * beta * (b.x() + I * b.y()), alpha - sign * beta * b.z();

    return m_kz_sign * result;
}

Eigen::Matrix2cd MatrixRTCoefficients::computeP() const {
    Eigen::Matrix2cd result = pMatrixHelper(1.);
    result *= 0.5;

    return result;
}

Eigen::Matrix2cd MatrixRTCoefficients::computeInverseP() const {
    const complex_t alpha = m_lambda(1) + m_lambda(0);
    const complex_t beta = m_lambda(1) - m_lambda(0);

    if (std::abs(alpha * alpha - beta * beta) == 0.)
        return Eigen::Matrix2cd::Zero();

    Eigen::Matrix2cd result = pMatrixHelper(-1.);
    result *= 2. / (alpha * alpha - beta * beta);

    return result;
}

Eigen::Matrix2cd MatrixRTCoefficients::computeDeltaMatrix(double thickness) {
    Eigen::Matrix2cd result;
    const complex_t alpha = 0.5 * thickness * (m_lambda(1) + m_lambda(0));

    const Eigen::Matrix2cd exp2 = Eigen::DiagonalMatrix<complex_t, 2>(
        {GetImExponential(m_kz_sign * thickness * m_lambda(1)),
         GetImExponential(m_kz_sign * thickness * m_lambda(0))});

    // Compute resulting phase matrix according to exp(i p_m d_m) = exp1 * Q * exp2 * Q.adjoint();
    if (std::abs(m_b.mag() - 1.) < eps) {
        Eigen::Matrix2cd Q;
        const double factor1 = 2. * (1. + m_b.z());
        Q << (1. + m_b.z()), (I * m_b.y() - m_b.x()), (m_b.x() + I * m_b.y()), (m_b.z() + 1.);

        return Q * exp2 * Q.adjoint() / factor1;

    } else if (m_b.mag() < eps)
        return Eigen::Matrix2cd::Identity() * GetImExponential(m_kz_sign * alpha);

    throw std::runtime_error("Broken magnetic field vector");
}

namespace {
complex_t GetImExponential(complex_t exponent) {
    if (exponent.imag() > -std::log(std::numeric_limits<double>::min()))
        return 0.0;
    return std::exp(I * exponent);
}
} // namespace
