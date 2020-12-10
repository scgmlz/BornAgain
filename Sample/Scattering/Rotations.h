//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Scattering/Rotations.h
//! @brief     Defines IRotation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_SCATTERING_ROTATIONS_H
#define BORNAGAIN_SAMPLE_SCATTERING_ROTATIONS_H

#include "Base/Types/ICloneable.h"
#include "Param/Node/INode.h"

class Transform3D;

//! Abstract base class for rotations.
//! @ingroup samples

class IRotation : public ICloneable, public INode {
public:
    static IRotation* createRotation(const Transform3D& transform);

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

IRotation* createProduct(const IRotation& left, const IRotation& right);

//! The identity rotation, which leaves everything in place.

class IdentityRotation : public IRotation // TODO RECONSIDER: merge with class IRotation
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

class RotationX : public IRotation {
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

class RotationY : public IRotation {
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

class RotationZ : public IRotation {
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

class RotationEuler : public IRotation {
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

#endif // BORNAGAIN_SAMPLE_SCATTERING_ROTATIONS_H
