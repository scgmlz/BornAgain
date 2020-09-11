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

#ifndef BORNAGAIN_CORE_SCATTERING_ROTATIONS_H
#define BORNAGAIN_CORE_SCATTERING_ROTATIONS_H

#include "Core/Basics/ICloneable.h"
#include "Core/Parametrization/INode.h"
#include "Core/Vector/Vectors3D.h"

class Transform3D;

//! Pure virtual interface for rotations.
//! @ingroup samples

class BA_CORE_API_ IRotation : public ICloneable, public INode
{
public:
    static IRotation* createRotation(const Transform3D& transform);
    static IRotation* createIdentity();

    IRotation(const NodeMeta& meta, const std::vector<double>& PValues);

    virtual IRotation* clone() const = 0;

    //! Returns a new IRotation object that is the current object's inverse
    virtual IRotation* createInverse() const = 0;

    //! Returns transformation.
    virtual Transform3D getTransform3D() const = 0;

    kvector_t transformed(const kvector_t& v) const;

    //! Returns true if rotation matrix is identity matrix (no rotations)
    virtual bool isIdentity() const;

    bool zInvariant() const;
};

BA_CORE_API_ IRotation* createProduct(const IRotation& left, const IRotation& right);

//! The identity rotation, which leaves everything in place.

class BA_CORE_API_ IdentityRotation : public IRotation // TODO get rid of this class
{
public:
    IdentityRotation();

    IdentityRotation* clone() const { return new IdentityRotation(); }
    IdentityRotation* createInverse() const { return new IdentityRotation(); }

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    Transform3D getTransform3D() const;

    bool isIdentity() const { return true; }
};

//! A rotation about the x axis.

class BA_CORE_API_ RotationX : public IRotation
{
public:
    RotationX(const std::vector<double> P);
    RotationX(double angle);

    RotationX* clone() const { return new RotationX(m_angle); }
    RotationX* createInverse() const { return new RotationX(-m_angle); }

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    double getAngle() const { return m_angle; }

    Transform3D getTransform3D() const;

protected:
    const double& m_angle;
};

//! A rotation about the y axis.

class BA_CORE_API_ RotationY : public IRotation
{
public:
    RotationY(const std::vector<double> P);
    RotationY(double angle);

    RotationY* clone() const { return new RotationY(m_angle); }
    RotationY* createInverse() const { return new RotationY(-m_angle); }

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    double getAngle() const { return m_angle; }

    Transform3D getTransform3D() const;

protected:
    const double& m_angle;
};

//! A rotation about the z axis.

class BA_CORE_API_ RotationZ : public IRotation
{
public:
    RotationZ(const std::vector<double> P);
    RotationZ(double angle);

    RotationZ* clone() const { return new RotationZ(m_angle); }
    RotationZ* createInverse() const { return new RotationZ(-m_angle); }

    void accept(INodeVisitor* visitor) const { visitor->visit(this); }

    double getAngle() const { return m_angle; }

    Transform3D getTransform3D() const;

protected:
    const double& m_angle;
};

//! A sequence of rotations about the z-x'-z'' axes.

class BA_CORE_API_ RotationEuler : public IRotation
{
public:
    RotationEuler(const std::vector<double> P);
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

#endif // BORNAGAIN_CORE_SCATTERING_ROTATIONS_H
