// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/Rotations.cpp
//! @brief     Implements IRotation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Scattering/Rotations.h"
#include "Core/Basics/Assert.h"
#include "Core/Vector/Transform3D.h"

// ************************************************************************** //
// interface IRotation
// ************************************************************************** //

IRotation::IRotation(const NodeMeta& meta, const std::vector<double>& PValues)
    : INode(meta, PValues)
{
}

IRotation* IRotation::createRotation(const Transform3D& transform)
{
    auto rot_type = transform.getRotationType();
    switch (rot_type) {
    case Transform3D::XAXIS: {
        double angle = transform.calculateRotateXAngle();
        return new RotationX(angle);
    }
    case Transform3D::YAXIS: {
        double angle = transform.calculateRotateYAngle();
        return new RotationY(angle);
    }
    case Transform3D::ZAXIS: {
        double angle = transform.calculateRotateZAngle();
        return new RotationZ(angle);
    }
    case Transform3D::EULER: {
        double alpha, beta, gamma;
        transform.calculateEulerAngles(&alpha, &beta, &gamma);
        return new RotationEuler(alpha, beta, gamma);
    }
    }
    ASSERT(0); // impossible case
}

IRotation* IRotation::createIdentity()
{
    return new RotationZ(0.0);
}

kvector_t IRotation::transformed(const kvector_t& v) const
{
    return getTransform3D().transformed(v);
}

bool IRotation::isIdentity() const
{
    return getTransform3D().isIdentity();
}

bool IRotation::zInvariant() const
{
    return getTransform3D().isZRotation();
}

//! Returns concatenated rotation (first right, then left).

IRotation* createProduct(const IRotation& left, const IRotation& right)
{
    Transform3D tr_left = left.getTransform3D();
    Transform3D tr_right = right.getTransform3D();
    IRotation* p_result = IRotation::createRotation(tr_left * tr_right);
    return p_result;
}

// ************************************************************************** //
// class IdentityRotation
// ************************************************************************** //

IdentityRotation::IdentityRotation()
    : IRotation({"IdentityRotation", "Identity rotation, does nothing", {}}, {})
{
}

Transform3D IdentityRotation::getTransform3D() const
{
    return Transform3D::createIdentity();
}

// ************************************************************************** //
// class RotationX
// ************************************************************************** //

//! Constructor of rotation around x-axis
//! @param angle: rotation angle around x-axis in radians
RotationX::RotationX(const std::vector<double> P)
    : IRotation(
        {"XRotation", "class_tooltip", {{"Angle", "rad", "Angle around x axis", -INF, +INF, 0}}},
        P),
      m_angle(m_P[0])
{
}

RotationX::RotationX(double angle) : RotationX(std::vector<double>{angle}) {}

Transform3D RotationX::getTransform3D() const
{
    return Transform3D::createRotateX(m_angle);
}

// ************************************************************************** //
// class RotationY
// ************************************************************************** //

//! Constructor of rotation around y-axis
//! @param angle: rotation angle around y-axis in radians
RotationY::RotationY(const std::vector<double> P)
    : IRotation(
        {"YRotation", "class_tooltip", {{"Angle", "rad", "Angle around y axis", -INF, +INF, 0}}},
        P),
      m_angle(m_P[0])
{
}

RotationY::RotationY(double angle) : RotationY(std::vector<double>{angle}) {}

Transform3D RotationY::getTransform3D() const
{
    return Transform3D::createRotateY(m_angle);
}

// ************************************************************************** //
// class RotationZ
// ************************************************************************** //

// --- RotationZ --------------------------------------------------------------

//! Constructor of rotation around z-axis
//! @param angle: rotation angle around z-axis in radians
RotationZ::RotationZ(const std::vector<double> P)
    : IRotation(
        {"ZRotation", "class_tooltip", {{"Angle", "rad", "Angle around z axis", -INF, +INF, 0}}},
        P),
      m_angle(m_P[0])
{
}

RotationZ::RotationZ(double angle) : RotationZ(std::vector<double>{angle}) {}

Transform3D RotationZ::getTransform3D() const
{
    return Transform3D::createRotateZ(m_angle);
}

// ************************************************************************** //
// class RotationEuler
// ************************************************************************** //

RotationEuler::RotationEuler(const std::vector<double> P)
    : IRotation({"EulerRotation",
                 "Sequence of three rotations around z-x'-z''",
                 {{"Alpha", "rad", "First Euler angle, rotation around z axis", -INF, +INF, 0},
                  {"Beta", "rad", "Second Euler angle, rotation around x' axis", -INF, +INF, 0},
                  {"Gamma", "rad", "Third Euler angle, rotation around z'' axis", -INF, +INF, 0}}},
                P),
      m_alpha(m_P[0]), m_beta(m_P[1]), m_gamma(m_P[2])
{
}

RotationEuler::RotationEuler(double alpha, double beta, double gamma)
    : RotationEuler(std::vector<double>{alpha, beta, gamma})
{
}

IRotation* RotationEuler::createInverse() const
{
    Transform3D inverse_transform(getTransform3D().getInverse());
    return createRotation(inverse_transform);
}

Transform3D RotationEuler::getTransform3D() const
{
    return Transform3D::createRotateEuler(m_alpha, m_beta, m_gamma);
}
