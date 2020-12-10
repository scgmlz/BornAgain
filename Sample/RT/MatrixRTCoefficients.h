//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file     Sample/RT/MatrixRTCoefficients.h
//! @brief    Defines class MatrixRTCoefficients.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_RT_MATRIXRTCOEFFICIENTS_H
#define BORNAGAIN_SAMPLE_RT_MATRIXRTCOEFFICIENTS_H

#include "Base/Vector/Vectors3D.h"
#include "Sample/RT/ILayerRTCoefficients.h"
#include <vector>

//! Specular reflection and transmission coefficients in a layer in case
//! of magnetic interactions between the scattered particle and the layer.
//! @ingroup algorithms_internal

class MatrixRTCoefficients : public ILayerRTCoefficients {
public:
    friend class SpecularMagneticStrategy;
    friend class SpecularMagneticNCStrategy;
    friend class SpecularMagneticTanhStrategy;

    MatrixRTCoefficients(double kz_sign, Eigen::Vector2cd eigenvalues, kvector_t b,
                         double magnetic_SLD);
    MatrixRTCoefficients(const MatrixRTCoefficients& other);
    ~MatrixRTCoefficients() override;

    MatrixRTCoefficients* clone() const override;

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
    double magneticSLD() const { return m_magnetic_SLD; }

    Eigen::Matrix2cd computeP() const;
    Eigen::Matrix2cd computeInverseP() const;

    Eigen::Matrix2cd computeDeltaMatrix(double thickness);

    Eigen::Matrix2cd getReflectionMatrix() const override { return m_R; };

private:
    double m_kz_sign; //! wave propagation direction (-1 for direct one, 1 for time reverse)
    Eigen::Vector2cd m_lambda; //!< eigenvalues for wave propagation
    kvector_t m_b;             //!< unit magnetic field vector
    double m_magnetic_SLD;

    Eigen::Matrix2cd m_T;
    Eigen::Matrix2cd m_R;

    // helper functions to compute DWBA compatible amplitudes used in the T1plus() etc. functions
    Eigen::Matrix2cd TransformationMatrix(Eigen::Vector2d selection) const;
    Eigen::Matrix2cd T1Matrix() const;
    Eigen::Matrix2cd T2Matrix() const;

    Eigen::Matrix2cd pMatrixHelper(double sign) const;
};

#endif // BORNAGAIN_SAMPLE_RT_MATRIXRTCOEFFICIENTS_H
#endif // USER_API
