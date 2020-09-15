// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file     Core/RT/MatrixRTCoefficients_v2.h
//! @brief    Defines class MatrixRTCoefficients_v2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_RT_MATRIXRTCOEFFICIENTS_V2_H
#define BORNAGAIN_CORE_RT_MATRIXRTCOEFFICIENTS_V2_H

#include "Core/RT/ILayerRTCoefficients.h"
#include "Core/Vector/Vectors3D.h"
#include <vector>

//! Specular reflection and transmission coefficients in a layer in case
//! of magnetic interactions between the scattered particle and the layer.
//! @ingroup algorithms_internal

class BA_CORE_API_ MatrixRTCoefficients_v2 : public ILayerRTCoefficients
{
public:
    friend class SpecularMagneticStrategy;

    MatrixRTCoefficients_v2(double kz_sign, Eigen::Vector2cd eigenvalues, kvector_t b);
    MatrixRTCoefficients_v2(const MatrixRTCoefficients_v2& other);
    ~MatrixRTCoefficients_v2() override;

    MatrixRTCoefficients_v2* clone() const override;

    //! The following functions return the transmitted and reflected amplitudes
    //! for different incoming beam polarizations and eigenmodes
    Eigen::Vector2cd T1plus() const override;
    Eigen::Vector2cd R1plus() const override;
    Eigen::Vector2cd T2plus() const override;
    Eigen::Vector2cd R2plus() const override;
    Eigen::Vector2cd T1min() const override;
    Eigen::Vector2cd R1min() const override;
    Eigen::Vector2cd T2min() const override;
    Eigen::Vector2cd R2min() const override;
    //! Returns z-part of the two wavevector eigenmodes
    Eigen::Vector2cd getKz() const override;

    Eigen::Matrix2cd getReflectionMatrix() const override;

private:
    double m_kz_sign; //! wave propagation direction (-1 for direct one, 1 for time reverse)
    Eigen::Vector2cd m_lambda; //!< eigenvalues for wave propagation
    kvector_t m_b; //!< normalized magnetic field impact (with correction for external mag. field)

    Eigen::Vector4cd m_w_plus; //!< boundary values for up-polarization
    Eigen::Vector4cd m_w_min;  //!< boundary values for down-polarization

    Eigen::Matrix4cd T1; //!< matrix selecting the transmitted part of
                         //!< the first eigenmode
    Eigen::Matrix4cd R1; //!< matrix selecting the reflected part of
                         //!< the first eigenmode
    Eigen::Matrix4cd T2; //!< matrix selecting the transmitted part of
                         //!< the second eigenmode
    Eigen::Matrix4cd R2; //!< matrix selecting the reflected part of
                         //!< the second eigenmode
};

#endif // BORNAGAIN_CORE_RT_MATRIXRTCOEFFICIENTS_V2_H
