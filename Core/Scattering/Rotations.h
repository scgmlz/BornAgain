// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/Rotations.h
//! @brief     Defines IRotation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROTATIONS_H
#define ROTATIONS_H

#include "ISample.h"
#include "Transform3D.h"

//! Pure virtual interface for rotations.
//! Must be subclass of sample, because it can be registered as a child in ICompositeSample.
//! @ingroup samples

class BA_CORE_API_ IRotation : public ISample
{
public:
    static IRotation* createRotation(const Transform3D& transform);
    virtual ~IRotation() {}

    virtual IRotation* clone() const=0;
    IRotation* cloneInvertB() const final { return clone(); }

    //! Returns a new IRotation object that is the current object's inverse
    virtual IRotation* createInverse() const=0;

    //! Calls the ISampleVisitor's visit method
    void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    //! Returns transformation.
    virtual Transform3D getTransform3D() const=0;

    //! Returns true if roation matrix is identity matrix (no rotations)
    virtual bool isIdentity() const;
};

BA_CORE_API_ IRotation* CreateProduct(const IRotation& left, const IRotation& right);

class BA_CORE_API_ RotationX : public IRotation
{
public:
    RotationX(double angle);

    RotationX* clone() const { return new RotationX(m_angle); }
    RotationX* createInverse() const { return new RotationX(-m_angle); }

    void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

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

    void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

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

    void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

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

    void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    double getAlpha() const { return m_alpha; }
    double getBeta() const { return m_beta; }
    double getGamma() const { return m_gamma; }

    Transform3D getTransform3D() const;

protected:
    double m_alpha, m_beta, m_gamma;
};

#endif // ROTATIONS_H
