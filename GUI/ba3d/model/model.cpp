//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/model.cpp
//! @brief     Implements Model class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/ba3d/model/model.h"
#include "Base/Utils/Assert.h"
#include "GUI/ba3d/model/geometry.h"

namespace RealSpace {

Model::Model() : defCamPos(Vector3D::_1, Vector3D::_0, Vector3D::_z) {}

Model::~Model() {
    for (auto o : objects) {
        o->model = nullptr;
        delete o;
    }

    for (auto o : objectsBlend) {
        o->model = nullptr;
        delete o;
    }
}

void Model::clearOpaque() {
    while (!objects.isEmpty())
        delete objects.first();
    emit updated(false);
}

void Model::clearBlend() {
    while (!objectsBlend.isEmpty())
        delete objectsBlend.first();
    emit updated(false);
}

Particles::Particle* Model::newParticle(Particles::EShape k, float R) {
    using namespace Particles;

    float D = 2 * R;

    switch (k) {
    case EShape::None:
        return nullptr;
    case EShape::BarGauss:
        return new BarGauss(D, D, 5 * D);
    case EShape::BarLorentz:
        return new BarLorentz(D, D, 5 * D);
    case EShape::Box:
        return new Box(D, D, D);
    case EShape::FullSphere:
        return new FullSphere(R);
    case EShape::FullSpheroid:
        return new FullSpheroid(R / 2, D);
    case EShape::Cylinder:
        return new Cylinder(R, D);
    case EShape::TruncatedSphere:
        return new TruncatedSphere(R, D / 3);
    case EShape::TruncatedSpheroid:
        return new TruncatedSpheroid(R, 2 * R, 1.5);
    case EShape::Cone:
        return new Cone(R, D, 1.3f);
    case EShape::Icosahedron:
        return new Icosahedron(R * IcosahedronL2R);
    case EShape::Dodecahedron:
        return new Dodecahedron(R * DodecahedronL2R);
    case EShape::TruncatedCube:
        return new TruncatedCube(D, D / 3);
    case EShape::Prism6:
        return new Prism6(R, D);
    case EShape::Cone6:
        return new Cone6(R, D, 1.3f);
    case EShape::Pyramid:
        return new Pyramid(D, D, 1.3f);
    case EShape::Cuboctahedron:
        return new Cuboctahedron(D, R * 3 / 2, 2.f / 3, 2);
    case EShape::Prism3:
        return new Prism3(R, D);
    case EShape::Tetrahedron:
        return new Tetrahedron(R, D, 1.3f);
    case EShape::EllipsoidalCylinder:
        return new EllipsoidalCylinder(R, R / 2, D);
    case EShape::HemiEllipsoid:
        return new HemiEllipsoid(R, R, D);
    case EShape::Dot:
        return new Dot();
    case EShape::CosineRippleBox:
        return new CosineRippleBox(D, D, D); // TODO ripples should be elongated
    case EShape::CosineRippleGauss:
        return new CosineRippleGauss(D, D, D); // TODO ripples should be elongated
    case EShape::CosineRippleLorentz:
        return new CosineRippleLorentz(D, D, D); // TODO ripples should be elongated
    case EShape::SawtoothRippleBox:
        return new SawtoothRippleBox(D, D, D); // TODO ripples should be elongated
    case EShape::SawtoothRippleGauss:
        return new SawtoothRippleGauss(D, D, D); // TODO ripples should be elongated
    case EShape::SawtoothRippleLorentz:
        return new SawtoothRippleLorentz(D, D, D); // TODO ripples should be elongated
    case EShape::AnisoPyramid:
        return new AnisoPyramid(R, D, D, 1.3f);
    }
    return nullptr;
}

void Model::add(Object* o) {
    ASSERT(o);
    ASSERT(!o->model);
    o->model = this;
    objects.append(o);
}

void Model::addBlend(Object* o) {
    ASSERT(o);
    ASSERT(!o->model);
    o->model = this;
    objectsBlend.append(o);
}

void Model::rem(Object* o) {
    int i;
    if ((i = objects.indexOf(o)) >= 0)
        objects.remove(i);
    else if ((i = objectsBlend.indexOf(o)) >= 0)
        objectsBlend.remove(i);
    else
        ASSERT(false); // object not found, should not happen, bad caller!

    o->releaseGeometry();
    o->model = nullptr;
}

void Model::releaseGeometries() {
    for (auto o : objects)
        o->releaseGeometry();
    for (auto o : objectsBlend)
        o->releaseGeometry();
}

bool Model::modelIsEmpty() {
    if (objects.isEmpty() && objectsBlend.isEmpty())
        return true;
    else
        return false;
}

void Model::draw(Canvas& canvas) const {
    for (auto o : objects)
        o->draw(canvas);
}

void Model::drawBlend(Canvas& canvas) const {
    for (auto o : objectsBlend)
        o->draw(canvas);
}

} // namespace RealSpace
