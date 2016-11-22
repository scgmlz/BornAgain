// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixRTCoefficients.cpp
//! @brief     Implements class MatrixRTCoefficients.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MatrixRTCoefficients.h"

MatrixRTCoefficients *MatrixRTCoefficients::clone() const
{
    return new MatrixRTCoefficients(*this);
}

void MatrixRTCoefficients::calculateTRMatrices()
{
    if (m_b_mag == 0.0) {
        calculateTRWithoutMagnetization();
        return;
    }

    if (lambda(0)==0.0) {
        complex_t ikt = mul_I( m_kt );
        // Lambda1 component contained only in T1m (R1m=0)
        // row 0:
        T1m(0,0) = (1.0 - m_bz/m_b_mag)/2.0;
        T1m(0,1) = - m_scatt_matrix(0,1)/2.0/m_b_mag;
        // row 1:
        T1m(1,0) = - m_scatt_matrix(1,0)/2.0/m_b_mag;
        T1m(1,1) = (1.0 + m_bz/m_b_mag)/2.0;
        // row 2:
        T1m(2,0) = ikt*(1.0 - m_bz/m_b_mag)/2.0;
        T1m(2,1) = -ikt*m_scatt_matrix(0,1)/2.0/m_b_mag;
        T1m(2,2) = T1m(0,0);
        T1m(2,3) = T1m(0,1);
        // row 3:
        T1m(3,0) = -ikt*m_scatt_matrix(1,0)/2.0/m_b_mag;
        T1m(3,1) = ikt*(1.0 + m_bz/m_b_mag)/2.0;
        T1m(3,2) = T1m(1,0);
        T1m(3,3) = T1m(1,1);
    }
    else {
        // T1m:
        // row 0:
        T1m(0,0) = (1.0 - m_bz/m_b_mag)/4.0;
        T1m(0,1) = - m_scatt_matrix(0,1)/4.0/m_b_mag;
        T1m(0,2) = lambda(0)*(m_bz/m_b_mag - 1.0)/4.0;
        T1m(0,3) = m_scatt_matrix(0,1)*lambda(0)/4.0/m_b_mag;
        // row 1:
        T1m(1,0) = - m_scatt_matrix(1,0)/4.0/m_b_mag;
        T1m(1,1) = (1.0 + m_bz/m_b_mag)/4.0;
        T1m(1,2) = m_scatt_matrix(1,0)*lambda(0)/4.0/m_b_mag;
        T1m(1,3) = - lambda(0)*(m_bz/m_b_mag + 1.0)/4.0;
        // row 2:
        T1m(2,0) = -(1.0 - m_bz/m_b_mag)/4.0/lambda(0);
        T1m(2,1) = m_scatt_matrix(0,1)/4.0/m_b_mag/lambda(0);
        T1m(2,2) = -(m_bz/m_b_mag - 1.0)/4.0;
        T1m(2,3) = - m_scatt_matrix(0,1)/4.0/m_b_mag;
        // row 3:
        T1m(3,0) = m_scatt_matrix(1,0)/4.0/m_b_mag/lambda(0);
        T1m(3,1) = -(1.0 + m_bz/m_b_mag)/4.0/lambda(0);
        T1m(3,2) = - m_scatt_matrix(1,0)/4.0/m_b_mag;
        T1m(3,3) = (m_bz/m_b_mag + 1.0)/4.0;

        // R1m:
        // row 0:
        R1m(0,0) = T1m(0,0);
        R1m(0,1) = T1m(0,1);
        R1m(0,2) = -T1m(0,2);
        R1m(0,3) = -T1m(0,3);
        // row 1:
        R1m(1,0) = T1m(1,0);
        R1m(1,1) = T1m(1,1);
        R1m(1,2) = -T1m(1,2);
        R1m(1,3) = -T1m(1,3);
        // row 2:
        R1m(2,0) = -T1m(2,0);
        R1m(2,1) = -T1m(2,1);
        R1m(2,2) = T1m(2,2);
        R1m(2,3) = T1m(2,3);
        // row 3:
        R1m(3,0) = -T1m(3,0);
        R1m(3,1) = -T1m(3,1);
        R1m(3,2) = T1m(3,2);
        R1m(3,3) = T1m(3,3);
    }

    if (lambda(1)==0.0) {
        complex_t ikt = mul_I(m_kt);
        // Lambda2 component contained only in T2m (R2m=0)
        // row 0:
        T2m(0,0) = (1.0 + m_bz/m_b_mag)/2.0;
        T2m(0,1) = m_scatt_matrix(0,1)/2.0/m_b_mag;
        // row 1:
        T2m(1,0) = m_scatt_matrix(1,0)/2.0/m_b_mag;
        T2m(1,1) = (1.0 - m_bz/m_b_mag)/2.0;
        // row 2:
        T2m(2,0) = ikt*(1.0 + m_bz/m_b_mag)/2.0;
        T2m(2,1) = ikt*m_scatt_matrix(0,1)/2.0/m_b_mag;
        T2m(2,2) = T2m(0,0);
        T2m(2,3) = T2m(0,1);
        // row 3:
        T2m(3,0) = ikt*m_scatt_matrix(1,0)/2.0/m_b_mag;
        T2m(3,1) = ikt*(1.0 - m_bz/m_b_mag)/2.0;
        T2m(3,2) = T2m(1,0);
        T2m(3,3) = T2m(1,1);
    }
    else {
        // T2m:
        // row 0:
        T2m(0,0) = (1.0 + m_bz/m_b_mag)/4.0;
        T2m(0,1) = m_scatt_matrix(0,1)/4.0/m_b_mag;
        T2m(0,2) = - lambda(1)*(m_bz/m_b_mag + 1.0)/4.0;
        T2m(0,3) = - m_scatt_matrix(0,1)*lambda(1)/4.0/m_b_mag;
        // row 1:
        T2m(1,0) = m_scatt_matrix(1,0)/4.0/m_b_mag;
        T2m(1,1) = (1.0 - m_bz/m_b_mag)/4.0;
        T2m(1,2) = - m_scatt_matrix(1,0)*lambda(1)/4.0/m_b_mag;
        T2m(1,3) = lambda(1)*(m_bz/m_b_mag - 1.0)/4.0;
        // row 2:
        T2m(2,0) = -(1.0 + m_bz/m_b_mag)/4.0/lambda(1);
        T2m(2,1) = - m_scatt_matrix(0,1)/4.0/m_b_mag/lambda(1);
        T2m(2,2) = (m_bz/m_b_mag + 1.0)/4.0;
        T2m(2,3) = m_scatt_matrix(0,1)/4.0/m_b_mag;
        // row 3:
        T2m(3,0) = - m_scatt_matrix(1,0)/4.0/m_b_mag/lambda(1);
        T2m(3,1) = -(1.0 - m_bz/m_b_mag)/4.0/lambda(1);
        T2m(3,2) = m_scatt_matrix(1,0)/4.0/m_b_mag;
        T2m(3,3) = (1.0 - m_bz/m_b_mag)/4.0;

        // R2m:
        // row 0:
        R2m(0,0) = T2m(0,0);
        R2m(0,1) = T2m(0,1);
        R2m(0,2) = -T2m(0,2);
        R2m(0,3) = -T2m(0,3);
        // row 1:
        R2m(1,0) = T2m(1,0);
        R2m(1,1) = T2m(1,1);
        R2m(1,2) = -T2m(1,2);
        R2m(1,3) = -T2m(1,3);
        // row 2:
        R2m(2,0) = -T2m(2,0);
        R2m(2,1) = -T2m(2,1);
        R2m(2,2) = T2m(2,2);
        R2m(2,3) = T2m(2,3);
        // row 3:
        R2m(3,0) = -T2m(3,0);
        R2m(3,1) = -T2m(3,1);
        R2m(3,2) = T2m(3,2);
        R2m(3,3) = T2m(3,3);
    }
}

void MatrixRTCoefficients::initializeBottomLayerPhiPsi()
{
    if (m_b_mag == 0.0) {
        phi_psi_min << 0.0, -std::sqrt(m_a), 0.0, 1.0;
        phi_psi_plus << -std::sqrt(m_a), 0.0, 1.0, 0.0;
        return;
    }
    // First basis vector that has no upward going wave amplitude
    phi_psi_min(0) = m_scatt_matrix(0,1) * ( lambda(0)-lambda(1) ) /
            2.0/m_b_mag;
    phi_psi_min(1) = ( m_bz  * (lambda(1) - lambda(0)) / m_b_mag -
            lambda(1) - lambda(0) )/2.0;
    phi_psi_min(2) = 0.0;
    phi_psi_min(3) = 1.0;

    // Second basis vector that has no upward going wave amplitude
    phi_psi_plus(0) = - (m_scatt_matrix(0,0) + lambda(0) * lambda(1) ) /
            ( lambda(0) + lambda(1) );
    phi_psi_plus(1) = m_scatt_matrix(1,0) * ( lambda(0) - lambda(1) ) /
            2.0/m_b_mag;
    phi_psi_plus(2) = 1.0;
    phi_psi_plus(3) = 0.0;
}

void MatrixRTCoefficients::initializeBottomLayerRT()
{
    // first treat case where both eigenmodes are the same (no B-field in layer)
    if (m_b_mag == 0.0) {
        phi_psi_min << 0.0, -std::sqrt(m_a), 0.0, 1.0;
        phi_psi_plus << -std::sqrt(m_a), 0.0, 1.0, 0.0;
        return;
    }
    // non-zero B-field
    return;
}

void MatrixRTCoefficients::calculateTRWithoutMagnetization()
{
    T1m.setZero();
    R1m.setZero();
    T2m.setZero();
    R2m.setZero();

    if (m_a==0.0) {
        // Spin down component contained only in T1 (R1=0)
        T1m(1,1) = 1.0;
        T1m(3,1) = mul_I(m_kt);
        T1m(3,3) = 1.0;

        // Spin up component contained only in T2 (R2=0)
        T2m(0,0) = 1.0;
        T2m(2,0) = mul_I(m_kt);
        T2m(2,2) = 1.0;
        return;
    }

    // T1m:
    T1m(1,1) = 0.5;
    T1m(1,3) = -std::sqrt(m_a)/2.0;
    T1m(3,1) = -1.0/(2.0*std::sqrt(m_a));
    T1m(3,3) = 0.5;

    // R1m:
    R1m(1,1) = 0.5;
    R1m(1,3) = std::sqrt(m_a)/2.0;
    R1m(3,1) = 1.0/(2.0*std::sqrt(m_a));
    R1m(3,3) = 0.5;

    // T2m:
    T2m(0,0) = 0.5;
    T2m(0,2) = -std::sqrt(m_a)/2.0;
    T2m(2,0) = -1.0/(2.0*std::sqrt(m_a));
    T2m(2,2) = 0.5;

    // R2m:
    R2m(0,0) = 0.5;
    R2m(0,2) = std::sqrt(m_a)/2.0;
    R2m(2,0) = 1.0/(2.0*std::sqrt(m_a));
    R2m(2,2) = 0.5;
}

Eigen::Vector2cd MatrixRTCoefficients::T1plus() const
{
    Eigen::Vector2cd result;
    result(0) = T1m.row(2).dot(phi_psi_plus);
    result(1) = T1m.row(3).dot(phi_psi_plus);
    if (lambda(0)==0.0 && result==Eigen::Vector2cd::Zero()) {
        result(0) = 0.5;
    }
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients::R1plus() const
{
    Eigen::Vector2cd result;
    result(0) = R1m.row(2).dot(phi_psi_plus);
    result(1) = R1m.row(3).dot(phi_psi_plus);
    if (lambda(0)==0.0) {
        if (T1m.row(2).dot(phi_psi_plus)==0.0
                && T1m.row(3).dot(phi_psi_plus)==0.0) {
            result(0) = -0.5;
        }
    }
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients::T2plus() const
{
    Eigen::Vector2cd result;
    result(0) = T2m.row(2).dot(phi_psi_plus);
    result(1) = T2m.row(3).dot(phi_psi_plus);
    if (lambda(1)==0.0 && result==Eigen::Vector2cd::Zero()) {
        result(0) = 0.5;
    }
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients::R2plus() const
{
    Eigen::Vector2cd result;
    result(0) = R2m.row(2).dot(phi_psi_plus);
    result(1) = R2m.row(3).dot(phi_psi_plus);
    if (lambda(1)==0.0) {
        if (T2m.row(2).dot(phi_psi_plus)==0.0
                && T2m.row(3).dot(phi_psi_plus)==0.0) {
            result(0) = -0.5;
        }
    }
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients::T1min() const
{
    Eigen::Vector2cd result;
    result(0) = T1m.row(2).dot(phi_psi_min);
    result(1) = T1m.row(3).dot(phi_psi_min);
    if (lambda(0)==0.0 && result==Eigen::Vector2cd::Zero()) {
        result(1) = 0.5;
    }
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients::R1min() const
{
    Eigen::Vector2cd result;
    result(0) = R1m.row(2).dot(phi_psi_min);
    result(1) = R1m.row(3).dot(phi_psi_min);
    if (lambda(0)==0.0) {
        if (T1m.row(2).dot(phi_psi_min)==0.0
                && T1m.row(3).dot(phi_psi_min)==0.0) {
            result(1) = -0.5;
        }
    }
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients::T2min() const
{
    Eigen::Vector2cd result;
    result(0) = T2m.row(2).dot(phi_psi_min);
    result(1) = T2m.row(3).dot(phi_psi_min);
    if (lambda(1)==0.0 && result==Eigen::Vector2cd::Zero()) {
        result(1) = 0.5;
    }
    return result;
}

Eigen::Vector2cd MatrixRTCoefficients::R2min() const
{
    Eigen::Vector2cd result;
    result(0) = R2m.row(2).dot(phi_psi_min);
    result(1) = R2m.row(3).dot(phi_psi_min);
    if (lambda(1)==0.0) {
        if (T2m.row(2).dot(phi_psi_min)==0.0
                && T2m.row(3).dot(phi_psi_min)==0.0) {
            result(1) = -0.5;
        }
    }
    return result;
}
