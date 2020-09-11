// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file     Core/RT/MatrixRTCoefficients_v2.cpp
//! @brief    Implements class MatrixRTCoefficients_v2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/RT/MatrixRTCoefficients_v2.h"

namespace
{
Eigen::Vector2cd waveVector(const Eigen::Matrix4cd& frob_matrix,
                            const Eigen::Vector4cd& boundary_cond);

constexpr complex_t I = complex_t(0.0, 1.0);
} // namespace

MatrixRTCoefficients_v2::MatrixRTCoefficients_v2(double kz_sign, Eigen::Vector2cd eigenvalues,
                                                 kvector_t b)
    : m_kz_sign(kz_sign), m_lambda(std::move(eigenvalues)), m_b(std::move(b))
{
}

MatrixRTCoefficients_v2::MatrixRTCoefficients_v2(const MatrixRTCoefficients_v2& other) = default;

MatrixRTCoefficients_v2::~MatrixRTCoefficients_v2() = default;

MatrixRTCoefficients_v2* MatrixRTCoefficients_v2::clone() const
{
    return new MatrixRTCoefficients_v2(*this);
}

Eigen::Vector2cd MatrixRTCoefficients_v2::T1plus() const
{
    const Eigen::Vector2cd result = waveVector(T1, m_w_plus);
    if (m_lambda(0) == 0.0 && result == Eigen::Vector2cd::Zero())
        return {0.5, 0.0};
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients_v2::R1plus() const
{
    if (m_lambda(0) == 0.0 && waveVector(T1, m_w_plus) == Eigen::Vector2cd::Zero())
        return {-0.5, 0.0};
    return waveVector(R1, m_w_plus);
}

Eigen::Vector2cd MatrixRTCoefficients_v2::T2plus() const
{
    const Eigen::Vector2cd result = waveVector(T2, m_w_plus);
    if (m_lambda(1) == 0.0 && result == Eigen::Vector2cd::Zero())
        return {0.5, 0.0};
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients_v2::R2plus() const
{
    if (m_lambda(1) == 0.0 && waveVector(T2, m_w_plus) == Eigen::Vector2cd::Zero())
        return {-0.5, 0.0};
    return waveVector(R2, m_w_plus);
}

Eigen::Vector2cd MatrixRTCoefficients_v2::T1min() const
{
    const Eigen::Vector2cd result = waveVector(T1, m_w_min);
    if (m_lambda(0) == 0.0 && result == Eigen::Vector2cd::Zero())
        return {0.0, 0.5};
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients_v2::R1min() const
{
    if (m_lambda(0) == 0.0 && waveVector(T1, m_w_min) == Eigen::Vector2cd::Zero())
        return {0.0, -0.5};
    return waveVector(R1, m_w_min);
}

Eigen::Vector2cd MatrixRTCoefficients_v2::T2min() const
{
    const Eigen::Vector2cd result = waveVector(T2, m_w_min);
    if (m_lambda(1) == 0.0 && result == Eigen::Vector2cd::Zero())
        return {0.0, 0.5};
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients_v2::R2min() const
{
    if (m_lambda(1) == 0.0 && waveVector(T2, m_w_min) == Eigen::Vector2cd::Zero())
        return {0.0, -0.5};
    return waveVector(R2, m_w_min);
}

Eigen::Vector2cd MatrixRTCoefficients_v2::getKz() const
{
    return -I * m_kz_sign * m_lambda;
}

namespace
{
Eigen::Vector2cd waveVector(const Eigen::Matrix4cd& frob_matrix,
                            const Eigen::Vector4cd& boundary_cond)
{
    Eigen::Matrix<complex_t, 4, 1> m = frob_matrix * boundary_cond;
    return {m(2), m(3)};
}
} // namespace
