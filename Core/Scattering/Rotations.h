// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/Rotations.h
//! @brief     Defines IRotation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ROTATIONS_H
#define ROTATIONS_H

#include "ISample.h"
#include "Transform3D.h"

//! Pure virtual interface for rotations.
//! @ingroup samples

class BA_CORE_API_ IRotation : public ISample
{
public:
    static IRotation* createRotation(const Transform3D& transform);
    static IRotation* createIdentity();
    virtual ~IRotation() {}

    virtual IRotation* clone() const=0;

    //! Returns a new IRotation object that is the current object's inverse
    virtual IRotation* createInverse() const=0;

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    //! Returns transformation.
    virtual Transform3D getTransform3D() const=0;

    //! Returns true if rotation matrix is identity matrix (no rotations)
    virtual bool isIdentity() const;
};

BA_CORE_API_ IRotation* createProduct(const IRotation& left, const IRotation& right);

bool IsZRotation(const IRotation& rot);

class BA_CORE_API_ IdentityRotation : public IRotation
{
public:
    IdentityRotation() =default;

    IdentityRotation* clone() const { return new IdentityRotation(); }
    IdentityRotation* createInverse() const { return new IdentityRotation(); }

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    Transform3D getTransform3D() const;

    bool isIdentity() const { return true; }
};

class BA_CORE_API_ RotationX : public IRotation
{
public:
    RotationX(double angle);

    RotationX* clone() const { return new RotationX(m_angle); }
    RotationX* createInverse() const { return new RotationX(-m_angle); }

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    double getAngle() const { return m_angle; }

    Transform3D getTransform3D() const;

protected:
    double m_angle;
};

class BA_CORE_API_ RotationY : public IRotation
{
public:
    RotationY(double angle);

    RotationY* clone() const { return new RotationY(m_angle); }
    RotationY* createInverse() const { return new RotationY(-m_angle); }

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    double getAngle() const { return m_angle; }

    Transform3D getTransform3D() const;

protected:
    double m_angle;
};

class BA_CORE_API_ RotationZ : public IRotation
{
public:
    RotationZ(double angle = 0.0);

    RotationZ* clone() const { return new RotationZ(m_angle); }
    RotationZ* createInverse() const { return new RotationZ(-m_angle); }

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    double getAngle() const { return m_angle; }

    Transform3D getTransform3D() const;

protected:
    double m_angle;
};

class BA_CORE_API_ RotationEuler : public IRotation
{
public:
    RotationEuler(double alpha, double beta, double gamma);

    RotationEuler* clone() const { return new RotationEuler(m_alpha, m_beta, m_gamma); }
    IRotation* createInverse() const;

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    double getAlpha() const { return m_alpha; }
    double getBeta() const { return m_beta; }
    double getGamma() const { return m_gamma; }

    Transform3D getTransform3D() const;

protected:
    double m_alpha, m_beta, m_gamma;
};

#endif // ROTATIONS_H
