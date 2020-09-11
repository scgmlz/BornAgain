// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/BasicVector3D.cpp
//! @brief     Implements type-specific functions from template class BasicVector3D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Vector/BasicVector3D.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"

typedef std::complex<double> complex_t;

// -----------------------------------------------------------------------------
// Quasi constructor
// -----------------------------------------------------------------------------

BasicVector3D<double> vecOfLambdaAlphaPhi(double _lambda, double _alpha, double _phi)
{
    double k = M_TWOPI / _lambda;
    return BasicVector3D<double>(k * std::cos(_alpha) * std::cos(_phi),
                                 -k * std::cos(_alpha) * std::sin(_phi), k * std::sin(_alpha));
}

// -----------------------------------------------------------------------------
// Functions of this (with no further argument)
// -----------------------------------------------------------------------------

//! Returns complex conjugate vector
template <> BasicVector3D<double> BasicVector3D<double>::conj() const
{
    return *this;
}

template <> BasicVector3D<complex_t> BasicVector3D<complex_t>::conj() const
{
    return BasicVector3D<complex_t>(std::conj(v_[0]), std::conj(v_[1]), std::conj(v_[2]));
}

//! Returns azimuth angle.
template <> double BasicVector3D<double>::phi() const
{
    return x() == 0.0 && y() == 0.0 ? 0.0 : std::atan2(-y(), x());
}

//! Returns polar angle.
template <> double BasicVector3D<double>::theta() const
{
    return x() == 0.0 && y() == 0.0 && z() == 0.0 ? 0.0 : std::atan2(magxy(), z());
}

//! Returns cosine of polar angle.
template <> double BasicVector3D<double>::cosTheta() const
{
    return mag() == 0 ? 1 : z() / mag();
}

//! Returns squared sine of polar angle.
template <> double BasicVector3D<double>::sin2Theta() const
{
    return mag2() == 0 ? 0 : magxy2() / mag2();
}

//! Returns this, trivially converted to complex type.
template <> BasicVector3D<complex_t> BasicVector3D<double>::complex() const
{
    return BasicVector3D<complex_t>(v_[0], v_[1], v_[2]);
}

//! Returns real parts.
template <> BasicVector3D<double> BasicVector3D<double>::real() const
{
    return *this;
}

template <> BasicVector3D<double> BasicVector3D<complex_t>::real() const
{
    return BasicVector3D<double>(v_[0].real(), v_[1].real(), v_[2].real());
}

//! Returns unit vector in direction of this. Throws for null vector.
template <> BasicVector3D<double> BasicVector3D<double>::unit() const
{
    double len = mag();
    if (len == 0.0)
        throw Exceptions::DivisionByZeroException("Cannot normalize zero vector");
    return BasicVector3D<double>(x() / len, y() / len, z() / len);
}

template <> BasicVector3D<complex_t> BasicVector3D<complex_t>::unit() const
{
    double len = mag();
    if (len == 0.0)
        throw Exceptions::DivisionByZeroException("Cannot normalize zero vector");
    return BasicVector3D<complex_t>(x() / len, y() / len, z() / len);
}

// -----------------------------------------------------------------------------
// Combine two vectors
// -----------------------------------------------------------------------------

//! Returns angle with respect to another vector.
template <> double BasicVector3D<double>::angle(const BasicVector3D<double>& v) const
{
    double cosa = 0;
    double ptot = mag() * v.mag();
    if (ptot > 0) {
        cosa = dot(v) / ptot;
        if (cosa > 1)
            cosa = 1;
        if (cosa < -1)
            cosa = -1;
    }
    return std::acos(cosa);
}
