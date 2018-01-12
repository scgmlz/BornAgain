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

#include "Rotations.h"
#include "BornAgainNamespace.h"
#include "RealParameter.h"

IRotation* IRotation::createRotation(const Transform3D& transform)
{
    double alpha, beta, gamma;
    transform.calculateEulerAngles(&alpha, &beta, &gamma);
    auto rot_type = transform.getRotationType();
    switch (rot_type) {
    case Transform3D::XAXIS:
        if (alpha>0.0) beta = -beta;
        return new RotationX(beta);
    case Transform3D::YAXIS:
        if (alpha>0.0 && alpha<3.14) beta = -beta;
        return new RotationY(beta);
    case Transform3D::ZAXIS:
        return new RotationZ(alpha);
    case Transform3D::EULER:
        return new RotationEuler(alpha, beta, gamma);
    }
    throw std::runtime_error("IRotation::createRotation error: unknown rotation type.");
}

IRotation* IRotation::createIdentity()
{
    return new RotationZ(0.0);
}

bool IRotation::isIdentity() const
{
    return getTransform3D().isIdentity();
}

//! Returns concatenated rotation (first right, then left).

IRotation* createProduct(const IRotation& left, const IRotation& right)
{
    Transform3D tr_left = left.getTransform3D();
    Transform3D tr_right = right.getTransform3D();
    IRotation *p_result = IRotation::createRotation(tr_left*tr_right);
    return p_result;
}

bool IsZRotation(const IRotation& rot)
{
    auto transform = rot.getTransform3D();
    return transform.isZRotation();
}

// --- IdentityRotation -------------------------------------------------------

Transform3D IdentityRotation::getTransform3D() const
{
    return Transform3D::createIdentity();
}

// --- RotationX --------------------------------------------------------------

//! Constructor of rotation around x-axis
//! @param angle: rotation angle around x-axis in radians
RotationX::RotationX(double angle)
    : m_angle(angle)
{
    setName(BornAgain::XRotationType);
    registerParameter(BornAgain::Angle, &m_angle).setUnit(BornAgain::UnitsRad);
}

Transform3D RotationX::getTransform3D() const
{
    return Transform3D::createRotateX(m_angle);
}

// --- RotationY --------------------------------------------------------------

//! Constructor of rotation around y-axis
//! @param angle: rotation angle around y-axis in radians
RotationY::RotationY(double angle)
    : m_angle(angle)
{
    setName(BornAgain::YRotationType);
    registerParameter(BornAgain::Angle, &m_angle).setUnit(BornAgain::UnitsRad);
}

Transform3D RotationY::getTransform3D() const
{
    return Transform3D::createRotateY(m_angle);
}

// --- RotationZ --------------------------------------------------------------

//! Constructor of rotation around z-axis
//! @param angle: rotation angle around z-axis in radians
RotationZ::RotationZ(double angle)
    : m_angle(angle)
{
    setName(BornAgain::ZRotationType);
    registerParameter(BornAgain::Angle, &m_angle).setUnit(BornAgain::UnitsRad);
}

Transform3D RotationZ::getTransform3D() const
{
    return Transform3D::createRotateZ(m_angle);
}

// --- RotationEuler ----------------------------------------------------------

//! Constructor of Euler rotation (sequence of three rotations following Euler angles
//! notation z-x'-z').
//! @param alpha: first Euler angle in radians
//! @param beta: second Euler angle in radians
//! @param gamma: third Euler angle in radians
RotationEuler::RotationEuler(double alpha, double beta, double gamma)
    : m_alpha(alpha), m_beta(beta), m_gamma(gamma)
{
    setName(BornAgain::EulerRotationType);
    registerParameter(BornAgain::Alpha, &m_alpha).setUnit(BornAgain::UnitsRad);
    registerParameter(BornAgain::Beta, &m_beta  ).setUnit(BornAgain::UnitsRad);
    registerParameter(BornAgain::Gamma, &m_gamma).setUnit(BornAgain::UnitsRad);
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
