// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/Rotations.cpp
//! @brief     Implements IRotation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Rotations.h"
#include "BornAgainNamespace.h"
#include "ISampleVisitor.h"
#include "RealParameter.h"

IRotation* IRotation::createRotation(const Transform3D& transform)
{
    double alpha, beta, gamma;
    transform.calculateEulerAngles(&alpha, &beta, &gamma);
    Transform3D::ERotationType rot_type = transform.getRotationType();
    switch (rot_type) {
    case Transform3D::XAXIS:
        if (alpha>0.0) beta = -beta;
        return new RotationX(beta);
    case Transform3D::YAXIS:
        if (alpha>0.0 && alpha<3.14) beta = -beta;
        return new RotationY(beta);
    case Transform3D::ZAXIS:
        return new RotationZ(alpha);
    default:
        return new RotationEuler(alpha, beta, gamma);
    }
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

// --- RotationX --------------------------------------------------------------

RotationX::RotationX(double angle)
    : m_angle(angle)
{
    setName(BornAgain::XRotationType);
    registerParameter(BornAgain::Angle, &m_angle).setUnit("rad");
}

Transform3D RotationX::getTransform3D() const
{
    return Transform3D::createRotateX(m_angle);
}

// --- RotationY --------------------------------------------------------------

RotationY::RotationY(double angle)
    : m_angle(angle)
{
    setName(BornAgain::YRotationType);
    registerParameter(BornAgain::Angle, &m_angle).setUnit("rad");
}

Transform3D RotationY::getTransform3D() const
{
    return Transform3D::createRotateY(m_angle);
}

// --- RotationZ --------------------------------------------------------------

RotationZ::RotationZ(double angle)
    : m_angle(angle)
{
    setName(BornAgain::ZRotationType);
    registerParameter(BornAgain::Angle, &m_angle).setUnit("rad");
}

Transform3D RotationZ::getTransform3D() const
{
    return Transform3D::createRotateZ(m_angle);
}

// --- RotationEuler ----------------------------------------------------------

RotationEuler::RotationEuler(double alpha, double beta, double gamma)
    : m_alpha(alpha), m_beta(beta), m_gamma(gamma)
{
    setName(BornAgain::EulerRotationType);
    registerParameter(BornAgain::Alpha, &m_alpha).setUnit("rad");
    registerParameter(BornAgain::Beta, &m_beta  ).setUnit("rad");
    registerParameter(BornAgain::Gamma, &m_gamma).setUnit("rad");
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
