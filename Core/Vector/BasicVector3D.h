// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/BasicVector3D.h
//! @brief      Declares template class BasicVector3D.
//!
//! Forked from CLHEP/Geometry by E. Chernyaev <Evgueni.Tcherniaev@cern.ch>,
//! then reworked beyond recongnition. Removed split of point and vector semantics.
//! Transforms are relegated to a separate class Transform3D.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BASICVECTOR3D_H
#define BASICVECTOR3D_H

#include "WinDllMacros.h"
#include <complex>

//! Three-dimensional vector template, for use with integer, double, or complex components.
//! @ingroup tools_internal

template<class T>
class BasicVector3D {
private:
    T v_[3];

public:
    // -------------------------------------------------------------------------
    // Constructors and other set functions
    // -------------------------------------------------------------------------

    //! Default constructor.
    BasicVector3D() { v_[0] = 0.0; v_[1] = 0.0; v_[2] = 0.0; }

    //! Constructor from cartesian components.
    BasicVector3D(const T x1, const T y1, const T z1) { v_[0] = x1; v_[1] = y1; v_[2] = z1; }

    // -------------------------------------------------------------------------
    // Component access
    // -------------------------------------------------------------------------

    //! Returns components by index.
    T operator[](int i) const { return v_[i]; }

    //! Sets components by index.
    T& operator[](int i) { return v_[i]; }

    //! Returns x-component in cartesian coordinate system.
    T x() const { return v_[0]; }
    //! Returns y-component in cartesian coordinate system.
    T y() const { return v_[1]; }
    //! Returns z-component in cartesian coordinate system.
    T z() const { return v_[2]; }

    //! Sets x-component in cartesian coordinate system.
    void setX(const T&a) { v_[0] = a; }
    //! Sets y-component in cartesian coordinate system.
    void setY(const T&a) { v_[1] = a; }
    //! Sets z-component in cartesian coordinate system.
    void setZ(const T&a) { v_[2] = a; }

    // -------------------------------------------------------------------------
    // In-place operations
    // -------------------------------------------------------------------------

    //! Adds other vector to this, and returns result.
    BasicVector3D<T>& operator+=(const BasicVector3D<T>& v) {
        v_[0] += v.v_[0]; v_[1] += v.v_[1]; v_[2] += v.v_[2]; return *this; }

    //! Subtracts other vector from this, and returns result.
    BasicVector3D<T>& operator-=(const BasicVector3D<T>& v) {
        v_[0] -= v.v_[0]; v_[1] -= v.v_[1]; v_[2] -= v.v_[2]; return *this; }


    //! Multiplies this with a scalar, and returns result.
#ifndef SWIG
    template<class U>
    auto operator*=(U a) -> BasicVector3D<decltype(this->x()*a)>& {
        v_[0] *= a; v_[1] *= a; v_[2] *= a; return *this; }
#endif // SWIG

    //! Divides this by a scalar, and returns result.
#ifndef SWIG
    template<class U>
    auto operator/=(U a) -> BasicVector3D<decltype(this->x()*a)>& {
        v_[0] /= a; v_[1] /= a; v_[2] /= a; return *this; }
#endif // SWIG

    // -------------------------------------------------------------------------
    // Functions of this (with no further argument)
    // -------------------------------------------------------------------------

    //! Returns complex conjugate vector
    BasicVector3D<T> conj() const;

    //! Returns squared magnitude squared of the vector.
    double mag2() const { return std::norm(v_[0]) + std::norm(v_[1]) + std::norm(v_[2]); }

    //! Returns magnitude of the vector.
    double mag() const { return sqrt(mag2()); }

    //! Returns squared distance from z axis.
    double magxy2() const { return std::norm(v_[0]) + std::norm(v_[1]); }

    //! Returns distance from z axis.
    double magxy() const { return sqrt(magxy2()); }

    //! Returns azimuth angle.
    double phi() const;

    //! Returns polar angle.
    double theta() const;

    //! Returns cosine of polar angle.
    double cosTheta() const;

    //! Returns squared sine of polar angle.
    double sin2Theta() const;

    //! Returns unit vector in direction of this. Throws for null vector.
    BasicVector3D<T> unit() const;

    //! Returns this, trivially converted to complex type.
    BasicVector3D<std::complex<double>> complex() const;

    //! Returns real parts.
    BasicVector3D<double> real() const;

    // -------------------------------------------------------------------------
    // Functions of this and another vector
    // -------------------------------------------------------------------------

    //! Returns dot product of vectors (antilinear in the first [=self] argument).
#ifndef SWIG
    template<class U>
    auto dot(const BasicVector3D<U>& v) const -> decltype(this->x()*v.x());
#endif // SWIG

    //! Returns cross product of vectors (linear in both arguments).
#ifndef SWIG
    template<class U>
    auto cross(const BasicVector3D<U>& v) const -> BasicVector3D<decltype(this->x()*v.x())>;
#endif // SWIG

    //! Returns angle with respect to another vector.
    double angle(const BasicVector3D<T>& v) const;

    //! Returns projection of this onto other vector: (this*v)*v/|v|^2.
    inline BasicVector3D<T> project(const BasicVector3D<T>& v) const {
        return dot(v)*v/v.mag2(); }

    // -------------------------------------------------------------------------
    // Rotations
    // -------------------------------------------------------------------------

    //! Returns result of rotation around x-axis.
    BasicVector3D<T> rotatedX(double a) const;
    //! Returns result of rotation around y-axis.
    BasicVector3D<T> rotatedY(double a) const;
    //! Returns result of rotation around z-axis.
    BasicVector3D<T> rotatedZ(double a) const {
        return BasicVector3D<T>( cos(a)*x()+sin(a)*y(), -sin(a)*x()+cos(a)*y(), z() );
    }
    //! Returns result of rotation around the axis specified by another vector.
    BasicVector3D<T> rotated(double a, const BasicVector3D<T>& v) const;
};

// =============================================================================
// Non-member functions
// =============================================================================

//! Output to stream.
//! @relates BasicVector3D
template <class T>
std::ostream&
operator<<(std::ostream& os, const BasicVector3D<T>& a)
{ return os << "(" << a.x() << "," << a.y() << "," << a.z() << ")"; }

// -----------------------------------------------------------------------------
// Unary operators
// -----------------------------------------------------------------------------

//! Unary plus.
//! @relates BasicVector3D
template <class T>
inline BasicVector3D<T> operator+ (const BasicVector3D<T>& v)
{ return v; }

//! Unary minus.
//! @relates BasicVector3D
template <class T>
inline BasicVector3D<T> operator- (const BasicVector3D<T>& v)
{ return BasicVector3D<T>(-v.x(), -v.y(), -v.z()); }

// -----------------------------------------------------------------------------
// Binary operators
// -----------------------------------------------------------------------------

//! Addition of two vectors.
//! @relates BasicVector3D
template <class T>
inline BasicVector3D<T> operator+(const BasicVector3D<T>& a, const BasicVector3D<T>& b)
{ return BasicVector3D<T>(a.x()+b.x(), a.y()+b.y(), a.z()+b.z()); }

//! Subtraction of two vectors.
//! @relates BasicVector3D
template <class T>
inline BasicVector3D<T> operator-(const BasicVector3D<T>& a, const BasicVector3D<T>& b)
{ return BasicVector3D<T>(a.x()-b.x(), a.y()-b.y(), a.z()-b.z()); }

//! Multiplication vector by scalar.
//! @relates BasicVector3D
#ifndef SWIG
template <class T, class U>
inline auto operator* (const BasicVector3D<T>& v, const U a) -> BasicVector3D<decltype(v.x()*a)>
{ return BasicVector3D<decltype(v.x()*a)>(v.x()*a, v.y()*a, v.z()*a); }
#endif // SWIG

//! Multiplication scalar by vector.
//! @relates BasicVector3D
#ifndef SWIG
template <class T, class U>
inline auto operator* (const U a, const BasicVector3D<T>& v) -> BasicVector3D<decltype(a*v.x())>
{ return BasicVector3D<decltype(a*v.x())>(a*v.x(), a*v.y(), a*v.z()); }
#endif // SWIG

// vector*vector not supported
//    (We do not provide the operator form a*b of the dot product:
//     Though nice to write, and in some cases perfectly justified,
//     in general it tends to make expressions more difficult to read.)

//! Division vector by scalar.
//! @relates BasicVector3D
template <class T, class U>
inline BasicVector3D<T> operator/ (const BasicVector3D<T>& v, U a)
{ return BasicVector3D<T>(v.x()/a, v.y()/a, v.z()/a); }

//! Comparison of two vectors for equality.
//! @relates BasicVector3D
template <class T>
inline bool operator==(const BasicVector3D<T>& a, const BasicVector3D<T>& b)
{ return (a.x()==b.x()&& a.y()==b.y()&& a.z()==b.z()); }

//! Comparison of two vectors for inequality.
//! @relates BasicVector3D
template <class T>
inline bool operator!=(const BasicVector3D<T>& a, const BasicVector3D<T>& b)
{ return (a.x()!=b.x() || a.y()!=b.y() || a.z()!=b.z()); }

// -----------------------------------------------------------------------------
// Quasi constructor
// -----------------------------------------------------------------------------

//! Creates a vector<double> as a wavevector with given wavelength and angles.
//! Specifically needed for grazing-incidence scattering.
BA_CORE_API_ BasicVector3D<double> vecOfLambdaAlphaPhi(
    const double _lambda, const double _alpha, const double _phi);


// =============================================================================
// ?? for API generation ??
// =============================================================================

//! Returns dot product of (complex) vectors (antilinear in the first [=self] argument).
#ifndef SWIG
template<class T> template<class U>
inline auto BasicVector3D<T>::dot(const BasicVector3D<U> &v) const
-> decltype(this->x()*v.x())
{
    BasicVector3D<T> left_star = this->conj();
    return left_star.x()*v.x() + left_star.y()*v.y() + left_star.z()*v.z();
}
#endif // SWIG

//! Returns cross product of (complex) vectors.
#ifndef SWIG
template<class T> template<class U>
inline auto BasicVector3D<T>::cross(const BasicVector3D<U> &v) const
-> BasicVector3D<decltype(this->x()*v.x())>
{
    return BasicVector3D<decltype(this->x()*v.x())>(y()*v.z()-v.y()*z(),
                                                    z()*v.x()-v.z()*x(),
                                                    x()*v.y()-v.x()*y());
}
#endif // SWIG

template<> BA_CORE_API_ BasicVector3D<double> BasicVector3D<double>::conj() const;

template<> BA_CORE_API_ BasicVector3D<std::complex<double>>
    BasicVector3D<std::complex<double>>::conj() const;

template<> BA_CORE_API_ double BasicVector3D<double>::phi() const;

template<> BA_CORE_API_ double BasicVector3D<double>::theta() const;

template<> BA_CORE_API_ BasicVector3D<std::complex<double>> BasicVector3D<double>::complex() const;

template<> BA_CORE_API_ BasicVector3D<double> BasicVector3D<std::complex<double>>::real() const;

template<> BA_CORE_API_ BasicVector3D<std::complex<double>>
    BasicVector3D<std::complex<double>>::unit() const;

#endif // BASICVECTOR3D_H
