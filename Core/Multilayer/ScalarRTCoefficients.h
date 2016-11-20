// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ScalarRTCoefficients.h
//! @brief     Defines class ScalarRTCoefficients.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SCALARRTCOEFFICIENTS_H
#define SCALARRTCOEFFICIENTS_H

#include "ILayerRTCoefficients.h"
#include "Complex.h"
#include "EigenCore.h"

//! Specular reflection and transmission coefficients in a layer in case
//! of scalar interactions between the layers and the scattered particle.
//! @ingroup algorithms_internal

class BA_CORE_API_ ScalarRTCoefficients : public ILayerRTCoefficients
{
public:
    ScalarRTCoefficients();
    virtual ~ScalarRTCoefficients() {}

    virtual ScalarRTCoefficients* clone() const;

    // The following functions return the transmitted and reflected amplitudes
    // for different incoming beam polarizations and eigenmodes
    virtual Eigen::Vector2cd T1plus() const;
    virtual Eigen::Vector2cd R1plus() const;
    virtual Eigen::Vector2cd T2plus() const;
    virtual Eigen::Vector2cd R2plus() const;
    virtual Eigen::Vector2cd T1min() const;
    virtual Eigen::Vector2cd R1min() const;
    virtual Eigen::Vector2cd T2min() const;
    virtual Eigen::Vector2cd R2min() const;
    //! Returns z-part of the two wavevector eigenmodes
    virtual Eigen::Vector2cd getKz() const;

    // Scalar value getters; these throw errors by default as they should only
    // be used when the derived object is really scalar
    virtual complex_t getScalarT() const;
    virtual complex_t getScalarR() const;
    virtual complex_t getScalarKz() const { return kz; }

    //! Relative unsigned vertical wavevector component +-k_z/K

    //! In the manual called f_l.
    //! Computed as sqrt(n^2 - (k_parallel/K)^2).
    //! The real part is always positive, hence it is propagating upwards.

    complex_t lambda;

    //! Signed vertical wavevector component k_z
    complex_t kz;

    //! Transmission and reflection coefficient

    //! In the manual called A^{-} = t_r(0) and A^{+} = t_r(1).
    //! Values of the transmitted/reflected (=down/up propagating) wavefunction
    //! at top boundary of the layer (resp. at the bottom of the top air/vacuum layer).

    Eigen::Vector2cd t_r;

private:
    Eigen::Vector2cd m_plus;
    Eigen::Vector2cd m_min;
};

// ************************************************************************** //
// implementation
// ************************************************************************** //

inline ScalarRTCoefficients::ScalarRTCoefficients()
    : lambda(0), kz(0)
{
    m_plus(0) = 1.0;
    m_plus(1) = 0.0;
    m_min(0) = 0.0;
    m_min(1) = 1.0;
    t_r << complex_t(1.0, 0.0), complex_t(0.0, 0.0);
}

inline ScalarRTCoefficients* ScalarRTCoefficients::clone() const
{
    return new ScalarRTCoefficients(*this);
}

inline Eigen::Vector2cd ScalarRTCoefficients::T1plus() const
{
    return Eigen::Vector2cd::Zero();
}

inline Eigen::Vector2cd ScalarRTCoefficients::R1plus() const
{
    return Eigen::Vector2cd::Zero();
}

inline Eigen::Vector2cd ScalarRTCoefficients::T2plus() const
{
    return m_plus * getScalarT();
}

inline Eigen::Vector2cd ScalarRTCoefficients::R2plus() const
{
    return m_plus * getScalarR();
}

inline Eigen::Vector2cd ScalarRTCoefficients::T1min() const
{
    return m_min * getScalarT();
}

inline Eigen::Vector2cd ScalarRTCoefficients::R1min() const
{
    return m_min * getScalarR();
}

inline Eigen::Vector2cd ScalarRTCoefficients::T2min() const
{
    return Eigen::Vector2cd::Zero();
}

inline Eigen::Vector2cd ScalarRTCoefficients::R2min() const
{
    return Eigen::Vector2cd::Zero();
}

inline Eigen::Vector2cd ScalarRTCoefficients::getKz() const
{
    return (m_plus+m_min) * kz;
}

inline complex_t ScalarRTCoefficients::getScalarR() const
{
    return t_r(1);
}

inline complex_t ScalarRTCoefficients::getScalarT() const
{
    return t_r(0);
}

#endif // SCALARRTCOEFFICIENTS_H
