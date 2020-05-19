// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/ba3d/model/particles.h
//! @brief     Defines Particle class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_PARTICLES_H
#define BA3D_PARTICLES_H

#include "object.h"

namespace RealSpace
{
namespace Particles
{

enum class EShape {
    None,
    FullSphere,
    FullSpheroid,
    Cylinder,
    TruncatedSphere,
    TruncatedSpheroid,
    Cone,
    Icosahedron,
    Dodecahedron,
    TruncatedCube,
    Prism6,
    Cone6,
    Pyramid,
    Cuboctahedron,
    Prism3,
    Tetrahedron,
    EllipsoidalCylinder,
    Box,
    HemiEllipsoid,
    Dot,
    Ripple1Box,
    Ripple1Gauss,
    Ripple1Lorentz,
    Ripple2,
    AnisoPyramid,
};

QString const& name(EShape);

//------------------------------------------------------------------------------

class Particle : public Object
{
protected:
    Particle(GeometricID::Key);
    Vector3D turn;              // turn before scale
    Vector3D scale;             // geometries are of 1-size (box 1x1x1, sphere D=1), need scaling
    Vector3D offset;            // geometries centered around origin; particles stand on z=0 plane
    Vector3D rotate, translate; // remembered

    void set();

public:
    static EShape const firstKind = EShape::None;
    static EShape const lastKind = EShape::AnisoPyramid;

    void transform(Vector3D rotate, Vector3D translate);
    void fancy(Vector3D rotate, float r);

    void addTransform(Vector3D rotate, Vector3D translate);
    void addTranslation(Vector3D translate_);
    void addExtrinsicRotation(Vector3D rotateExtrinsic);
};

//------------------------------------------------------------------------------
// follow BornAgain manual, chapter 11, Particle form factors

class FullSphere : public Particle
{
public:
    FullSphere(float R);
};

class FullSpheroid : public Particle
{
public:
    FullSpheroid(float R, float H);
};

class Cylinder : public Particle
{
public:
    Cylinder(float R, float H);
};

class TruncatedSphere : public Particle
{
public:
    TruncatedSphere(float R, float H, float deltaH = 0.0f);
};

class TruncatedSpheroid : public Particle
{
public:
    TruncatedSpheroid(float R, float H, float fp, float deltaH = 0.0f);
};

class Cone : public Particle
{
public:
    Cone(float R, float H, float alpha);
};

class Icosahedron : public Particle
{
public:
    Icosahedron(float L);
};

class Dodecahedron : public Particle
{
public:
    Dodecahedron(float L);
};

class Dot : public Particle
{
public:
    Dot();
};

class TruncatedCube : public Particle
{
public:
    TruncatedCube(float L, float t);
};

class Prism6 : public Particle
{
public:
    Prism6(float R, float H);
};

class Cone6 : public Particle
{
public:
    Cone6(float R, float H, float alpha);
};

class Pyramid : public Particle
{
public:
    Pyramid(float L, float H, float alpha);
};

class Cuboctahedron : public Particle
{
public:
    Cuboctahedron(float L, float H, float rH, float alpha);
};

class Prism3 : public Particle
{
public:
    Prism3(float L, float H);
};

class Tetrahedron : public Particle
{
public:
    Tetrahedron(float L, float H, float alpha);
};

class EllipsoidalCylinder : public Particle
{
public:
    EllipsoidalCylinder(float Ra, float Rb, float H);
};

class Box : public Particle
{
public:
    Box(float L, float W, float H);
};

class HemiEllipsoid : public Particle
{
public:
    HemiEllipsoid(float Ra, float Rb, float H);
};

class Ripple1Box : public Particle
{
public:
    Ripple1Box(float L, float W, float H);
};

class Ripple1Gauss : public Particle
{
public:
    Ripple1Gauss(float L, float W, float H);
};

class Ripple1Lorentz : public Particle
{
public:
    Ripple1Lorentz(float L, float W, float H);
};

class Ripple2 : public Particle
{
public:
    Ripple2(float L, float W, float H, float asymmetry);
};

class AnisoPyramid : public Particle
{
public:
    AnisoPyramid(float L, float W, float H, float alpha);
};
} // namespace Particles
} // namespace RealSpace
#endif // BA3D_PARTICLES_H
