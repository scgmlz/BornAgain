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

#include "Transform3D.h"
#include <Eigen/LU>


Transform3D::Transform3D()
{
    m_matrix.setIdentity();
    m_inverse_matrix.setIdentity();
}

Transform3D::Transform3D(const Transform3D& other)
: m_matrix(other.m_matrix)
, m_inverse_matrix(other.m_inverse_matrix)
{
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
    matrix(1,1) = cosine;
    matrix(1,2) = -sine;
    matrix(2,1) = sine;
    matrix(2,2) = cosine;
    return Transform3D(matrix);
}

Transform3D Transform3D::createRotateY(double phi)
{
    double cosine = std::cos(phi);
    double sine = std::sin(phi);
    Eigen::Matrix3d matrix;
    matrix.setIdentity();
    matrix(0,0) = cosine;
    matrix(0,2) = sine;
    matrix(2,0) = -sine;
    matrix(2,2) = cosine;
    return Transform3D(matrix);
}

Transform3D Transform3D::createRotateZ(double phi)
{
    double cosine = std::cos(phi);
    double sine = std::sin(phi);
    Eigen::Matrix3d matrix;
    matrix.setIdentity();
    matrix(0,0) = cosine;
    matrix(0,1) = -sine;
    matrix(1,0) = sine;
    matrix(1,1) = cosine;
    return Transform3D(matrix);
}

Transform3D Transform3D::createRotateEuler(
    double alpha, double beta, double gamma)
{
    Transform3D zrot = createRotateZ(alpha);
    Transform3D xrot = createRotateX(beta);
    Transform3D zrot2 = createRotateZ(gamma);
    return zrot2*xrot*zrot;
}

void Transform3D::calculateEulerAngles(
    double *p_alpha, double *p_beta, double *p_gamma) const
{
    // First check if second angle is zero or pi
    if (m_matrix(2,0)==0.0 && m_matrix(2,1)==0.0) {
        *p_alpha = std::atan2(-m_matrix(0,1), m_matrix(0,0));
        *p_beta = std::acos(m_matrix(2,2));
        *p_gamma = 0.0;
    } else {
        *p_alpha = std::atan2(m_matrix(2,0), m_matrix(2,1));
        *p_beta = std::acos(m_matrix(2,2));
        *p_gamma = std::atan2(m_matrix(0,2), -m_matrix(1,2));
    }
}

double Transform3D::calculateRotateXAngle() const
{
    return std::atan2(m_matrix(2,1), m_matrix(1,1));
}

double Transform3D::calculateRotateYAngle() const
{
    return std::atan2(m_matrix(0,2), m_matrix(2,2));
}

double Transform3D::calculateRotateZAngle() const
{
    return std::atan2(m_matrix(1,0), m_matrix(0,0));
}

Transform3D Transform3D::getInverse() const
{
    Transform3D result(m_inverse_matrix);
    return result;
}

kvector_t Transform3D::transformed(const kvector_t& v) const
{
    double x = m_matrix(0,0)*v.x() + m_matrix(0,1)*v.y() + m_matrix(0,2)*v.z();
    double y = m_matrix(1,0)*v.x() + m_matrix(1,1)*v.y() + m_matrix(1,2)*v.z();
    double z = m_matrix(2,0)*v.x() + m_matrix(2,1)*v.y() + m_matrix(2,2)*v.z();
    return kvector_t(x, y, z);
}

cvector_t Transform3D::transformed(const cvector_t& v) const
{
    complex_t x = m_matrix(0,0)*v.x() + m_matrix(0,1)*v.y() + m_matrix(0,2)*v.z();
    complex_t y = m_matrix(1,0)*v.x() + m_matrix(1,1)*v.y() + m_matrix(1,2)*v.z();
    complex_t z = m_matrix(2,0)*v.x() + m_matrix(2,1)*v.y() + m_matrix(2,2)*v.z();
    return cvector_t(x, y, z);
}

kvector_t Transform3D::transformedInverse(const kvector_t& v) const
{
    double x = m_inverse_matrix(0,0)*v.x() + m_inverse_matrix(0,1)*v.y()
            + m_inverse_matrix(0,2)*v.z();
    double y = m_inverse_matrix(1,0)*v.x() + m_inverse_matrix(1,1)*v.y()
            + m_inverse_matrix(1,2)*v.z();
    double z = m_inverse_matrix(2,0)*v.x() + m_inverse_matrix(2,1)*v.y()
            + m_inverse_matrix(2,2)*v.z();
    return kvector_t(x, y, z);
}

cvector_t Transform3D::transformedInverse(const cvector_t& v) const
{
    complex_t x = m_inverse_matrix(0,0)*v.x() + m_inverse_matrix(0,1)*v.y()
            + m_inverse_matrix(0,2)*v.z();
    complex_t y = m_inverse_matrix(1,0)*v.x() + m_inverse_matrix(1,1)*v.y()
            + m_inverse_matrix(1,2)*v.z();
    complex_t z = m_inverse_matrix(2,0)*v.x() + m_inverse_matrix(2,1)*v.y()
            + m_inverse_matrix(2,2)*v.z();
    return cvector_t(x, y, z);
}

Transform3D* Transform3D::clone() const
{
    return new Transform3D(m_matrix);
}

Transform3D Transform3D::operator*(const Transform3D& other) const
{
    Eigen::Matrix3d product_matrix = this->m_matrix * other.m_matrix;
    return Transform3D(product_matrix);
}

bool Transform3D::operator==(const Transform3D &other) const
{
    return this->m_matrix == other.m_matrix;
}

Transform3D::ERotationType Transform3D::getRotationType() const
{
    if (isXRotation()) return XAXIS;
    if (isYRotation()) return YAXIS;
    if (isZRotation()) return ZAXIS;
    return EULER;
}

bool Transform3D::isIdentity() const
{
    double alpha, beta, gamma;
    calculateEulerAngles(&alpha, &beta, &gamma);
    return (alpha==0.0 && beta==0.0 && gamma==0.0);
}

void Transform3D::print(std::ostream& ostr) const
{
    ostr << "Transform3D: " << m_matrix;
}

bool Transform3D::isXRotation() const
{
    if (m_matrix(0,0) != 1.0) return false;
    if (m_matrix(0,1) != 0.0) return false;
    if (m_matrix(0,2) != 0.0) return false;
    if (m_matrix(1,0) != 0.0) return false;
    if (m_matrix(2,0) != 0.0) return false;
    return true;
}

bool Transform3D::isYRotation() const
{
    if (m_matrix(1,1) != 1.0) return false;
    if (m_matrix(0,1) != 0.0) return false;
    if (m_matrix(1,0) != 0.0) return false;
    if (m_matrix(1,2) != 0.0) return false;
    if (m_matrix(2,1) != 0.0) return false;
    return true;
}

bool Transform3D::isZRotation() const
{
    if (m_matrix(2,2) != 1.0) return false;
    if (m_matrix(0,2) != 0.0) return false;
    if (m_matrix(1,2) != 0.0) return false;
    if (m_matrix(2,0) != 0.0) return false;
    if (m_matrix(2,1) != 0.0) return false;
    return true;
}

Transform3D::Transform3D(const Eigen::Matrix3d& matrix)
    : m_matrix(matrix)
{
    m_inverse_matrix = m_matrix.inverse();
}

double BottomZ(const std::vector<kvector_t>& vertices, const Transform3D& rotation)
{
    if (vertices.size()==0)
        throw std::runtime_error("BottomZ() error: no vertices passed!");
    kvector_t vertex_rot = rotation.transformed(vertices[0]);
    double zmin = vertex_rot.z();
    for (size_t index=1; index<vertices.size(); ++index) {
        vertex_rot = rotation.transformed(vertices[index]);
        zmin = std::min(zmin, vertex_rot.z());
    }
    return zmin;
}

double TopZ(const std::vector<kvector_t>& vertices, const Transform3D& rotation)
{
    if (vertices.size()==0)
        throw std::runtime_error("TopZ() error: no vertices passed!");
    kvector_t vertex_rot = rotation.transformed(vertices[0]);
    double zmax = vertex_rot.z();
    for (size_t index=1; index<vertices.size(); ++index) {
        vertex_rot = rotation.transformed(vertices[index]);
        zmax = std::max(zmax, vertex_rot.z());
    }
    return zmax;
}
