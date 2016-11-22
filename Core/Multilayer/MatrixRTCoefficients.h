// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MatrixRTCoefficients.h
//! @brief    Defines class MatrixRTCoefficients.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATRIXRTCOEFFICIENTS_H
#define MATRIXRTCOEFFICIENTS_H

#include "ILayerRTCoefficients.h"

//! Specular reflection and transmission coefficients in a layer in case
//! of 2x2 matrix interactions between the layers and the scattered particle.
//! @ingroup algorithms_internal

class BA_CORE_API_ MatrixRTCoefficients : public ILayerRTCoefficients
{
public:
    MatrixRTCoefficients() : m_kt(0.0) {}
    virtual ~MatrixRTCoefficients() {}

    virtual MatrixRTCoefficients* clone() const;

    //! The following functions return the transmitted and reflected amplitudes
    //! for different incoming beam polarizations and eigenmodes
    virtual Eigen::Vector2cd T1plus() const;
    virtual Eigen::Vector2cd R1plus() const;
    virtual Eigen::Vector2cd T2plus() const;
    virtual Eigen::Vector2cd R2plus() const;
    virtual Eigen::Vector2cd T1min() const;
    virtual Eigen::Vector2cd R1min() const;
    virtual Eigen::Vector2cd T2min() const;
    virtual Eigen::Vector2cd R2min() const;
    //! Returns z-part of the two wavevector eigenmodes
    virtual Eigen::Vector2cd getKz() const { return kz; }

    friend class SpecularMagnetic;

private:
    void calculateTRMatrices();
    void initializeBottomLayerPhiPsi();
    void initializeBottomLayerRT();
    void calculateTRWithoutMagnetization();

    // NOTE: exceptionally, this class has member variables without prefix m_

    Eigen::Vector2cd kz; //!< z-part of the two wavevector eigenmodes
    Eigen::Vector2cd lambda; // positive eigenvalues of transfer matrix
    Eigen::Vector4cd phi_psi_plus; //!< boundary values for up-polarization
    Eigen::Vector4cd phi_psi_min; //!< boundary values for down-polarization
//    Eigen::Vector2cd t1_plus;  //!< boundary value for up-polarization
//    Eigen::Vector2cd t2_plus;  //!< boundary value for up-polarization
//    Eigen::Vector2cd r1_plus;  //!< boundary value for up-polarization
//    Eigen::Vector2cd r2_plus;  //!< boundary value for up-polarization
//    Eigen::Vector2cd t1_min;  //!< boundary value for down-polarization
//    Eigen::Vector2cd t2_min;  //!< boundary value for down-polarization
//    Eigen::Vector2cd r1_min;  //!< boundary value for down-polarization
//    Eigen::Vector2cd r2_min;  //!< boundary value for down-polarization
    Eigen::Matrix4cd T1m; //!< matrix selecting the transmitted part of
                          //!< the first eigenmode
    Eigen::Matrix4cd R1m; //!< matrix selecting the reflected part of
                          //!< the first eigenmode
    Eigen::Matrix4cd T2m; //!< matrix selecting the transmitted part of
                          //!< the second eigenmode
    Eigen::Matrix4cd R2m; //!< matrix selecting the reflected part of
                          //!< the second eigenmode
    Eigen::Matrix2cd m_scatt_matrix; //!< scattering matrix
    complex_t m_a; //!< polarization independent part of scattering matrix
    complex_t m_b_mag; //!< magnitude of magnetic interaction term
    complex_t m_bz; //!< z-part of magnetic interaction term
    double m_kt; //!< wavevector length times thickness of layer for use when
                 //!< lambda=0
};

#endif // MATRIXRTCOEFFICIENTS_H
