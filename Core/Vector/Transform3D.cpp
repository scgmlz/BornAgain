// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/Transform3D.cpp
//! @brief      Implements template class Transform3D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Vector/Transform3D.h"
#include <Eigen/LU>

Transform3D::Transform3D()
{
    m_matrix.setIdentity();
    m_inverse_matrix.setIdentity();
}

Transform3D::Transform3D(const Eigen::Matrix3d& matrix) : m_matrix(matrix)
{
    m_inverse_matrix = m_matrix.inverse();
}

Transform3D Transform3D::createIdentity()
{
    return Transform3D();
}

Transform3D Transform3D::createRotateX(double phi)
{
    double cosine = std::cos(phi);
    double sine = std::sin(phi);
    Eigen::Matrix3d matrix;
    matrix.setIdentity();
    matrix(1, 1) = cosine;
    matrix(1, 2) = -sine;
    matrix(2, 1) = sine;
    matrix(2, 2) = cosine;
    return Transform3D(matrix);
}

Transform3D Transform3D::createRotateY(double phi)
{
    double cosine = std::cos(phi);
    double sine = std::sin(phi);
    Eigen::Matrix3d matrix;
    matrix.setIdentity();
    matrix(0, 0) = cosine;
    matrix(0, 2) = sine;
    matrix(2, 0) = -sine;
    matrix(2, 2) = cosine;
    return Transform3D(matrix);
}

Transform3D Transform3D::createRotateZ(double phi)
{
    double cosine = std::cos(phi);
    double sine = std::sin(phi);
    Eigen::Matrix3d matrix;
    matrix.setIdentity();
    matrix(0, 0) = cosine;
    matrix(0, 1) = -sine;
    matrix(1, 0) = sine;
    matrix(1, 1) = cosine;
    return Transform3D(matrix);
}

Transform3D Transform3D::createRotateEuler(double alpha, double beta, double gamma)
{
    Transform3D zrot = createRotateZ(alpha);
    Transform3D xrot = createRotateX(beta);
    Transform3D zrot2 = createRotateZ(gamma);
    return zrot * xrot * zrot2;
}

void Transform3D::calculateEulerAngles(double* p_alpha, double* p_beta, double* p_gamma) const
{
    *p_beta = std::acos(m_matrix(2, 2));
    // First check if second angle is zero or pi
    if (std::abs(m_matrix(2, 2)) == 1.0) {
        *p_alpha = std::atan2(m_matrix(1, 0), m_matrix(0, 0));
        *p_gamma = 0.0;
    } else {
        *p_alpha = std::atan2(m_matrix(0, 2), -m_matrix(1, 2));
        *p_gamma = std::atan2(m_matrix(2, 0), m_matrix(2, 1));
    }
}

double Transform3D::calculateRotateXAngle() const
{
    return std::atan2(m_matrix(2, 1), m_matrix(1, 1));
}

double Transform3D::calculateRotateYAngle() const
{
    return std::atan2(m_matrix(0, 2), m_matrix(2, 2));
}

double Transform3D::calculateRotateZAngle() const
{
    return std::atan2(m_matrix(1, 0), m_matrix(0, 0));
}

Transform3D Transform3D::getInverse() const
{
    Transform3D result(m_inverse_matrix);
    return result;
}

template <class ivector_t> ivector_t Transform3D::transformed(const ivector_t& v) const
{
    auto x = m_matrix(0, 0) * v.x() + m_matrix(0, 1) * v.y() + m_matrix(0, 2) * v.z();
    auto y = m_matrix(1, 0) * v.x() + m_matrix(1, 1) * v.y() + m_matrix(1, 2) * v.z();
    auto z = m_matrix(2, 0) * v.x() + m_matrix(2, 1) * v.y() + m_matrix(2, 2) * v.z();
    return ivector_t(x, y, z);
}

template BA_CORE_API_ kvector_t Transform3D::transformed<kvector_t>(const kvector_t& v) const;
template BA_CORE_API_ cvector_t Transform3D::transformed<cvector_t>(const cvector_t& v) const;

template <class ivector_t> ivector_t Transform3D::transformedInverse(const ivector_t& v) const
{
    auto x = m_inverse_matrix(0, 0) * v.x() + m_inverse_matrix(0, 1) * v.y()
             + m_inverse_matrix(0, 2) * v.z();
    auto y = m_inverse_matrix(1, 0) * v.x() + m_inverse_matrix(1, 1) * v.y()
             + m_inverse_matrix(1, 2) * v.z();
    auto z = m_inverse_matrix(2, 0) * v.x() + m_inverse_matrix(2, 1) * v.y()
             + m_inverse_matrix(2, 2) * v.z();
    return ivector_t(x, y, z);
}

template BA_CORE_API_ kvector_t
Transform3D::transformedInverse<kvector_t>(const kvector_t& v) const;
template BA_CORE_API_ cvector_t
Transform3D::transformedInverse<cvector_t>(const cvector_t& v) const;

Transform3D* Transform3D::clone() const
{
    return new Transform3D(m_matrix);
}

Transform3D Transform3D::operator*(const Transform3D& other) const
{
    Eigen::Matrix3d product_matrix = this->m_matrix * other.m_matrix;
    return Transform3D(product_matrix);
}

bool Transform3D::operator==(const Transform3D& other) const
{
    return this->m_matrix == other.m_matrix;
}

Transform3D::ERotationType Transform3D::getRotationType() const
{
    if (isXRotation())
        return XAXIS;
    if (isYRotation())
        return YAXIS;
    if (isZRotation())
        return ZAXIS;
    return EULER;
}

bool Transform3D::isIdentity() const
{
    double alpha, beta, gamma;
    calculateEulerAngles(&alpha, &beta, &gamma);
    return (alpha == 0.0 && beta == 0.0 && gamma == 0.0);
}

void Transform3D::print(std::ostream& ostr) const
{
    ostr << "Transform3D: " << m_matrix;
}

bool Transform3D::isXRotation() const
{
    if (m_matrix(0, 0) != 1.0)
        return false;
    if (m_matrix(0, 1) != 0.0)
        return false;
    if (m_matrix(0, 2) != 0.0)
        return false;
    if (m_matrix(1, 0) != 0.0)
        return false;
    if (m_matrix(2, 0) != 0.0)
        return false;
    return true;
}

bool Transform3D::isYRotation() const
{
    if (m_matrix(1, 1) != 1.0)
        return false;
    if (m_matrix(0, 1) != 0.0)
        return false;
    if (m_matrix(1, 0) != 0.0)
        return false;
    if (m_matrix(1, 2) != 0.0)
        return false;
    if (m_matrix(2, 1) != 0.0)
        return false;
    return true;
}

bool Transform3D::isZRotation() const
{
    if (m_matrix(2, 2) != 1.0)
        return false;
    if (m_matrix(0, 2) != 0.0)
        return false;
    if (m_matrix(1, 2) != 0.0)
        return false;
    if (m_matrix(2, 0) != 0.0)
        return false;
    if (m_matrix(2, 1) != 0.0)
        return false;
    return true;
}
