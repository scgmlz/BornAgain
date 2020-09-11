// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/object.cpp
//! @brief     Implements Object class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/ba3d/model/object.h"
#include "../view/canvas.h"
#include "GUI/ba3d/model/geometry.h"
#include "GUI/ba3d/model/model.h"
#include <cmath>

namespace
{
QQuaternion EulerToQuaternion(const RealSpace::Vector3D& euler);

RealSpace::Vector3D QuaternionToEuler(const QQuaternion& q);
} // namespace

namespace RealSpace
{

#ifdef Q_OS_LINUX
QColor const clrObject = Qt::lightGray;
#else
QColor const clrObject = Qt::black;
#endif

Object::Object(GeometricID::Key gky_) : color(clrObject), isNull(false), model(nullptr), gky(gky_)
{
}

Object::~Object()
{
    releaseGeometry();
    if (model)
        model->rem(this);
}

void Object::transform(float scale, Vector3D rotate, Vector3D translate)
{
    transform(Vector3D(scale, scale, scale), rotate, translate);
}

void Object::transform(Vector3D scale, Vector3D rotate, Vector3D translate)
{
    mat.setToIdentity();
    mat.translate(translate);
    mat.rotate(EulerToQuaternion(rotate));
    mat.scale(scale);
}

void Object::transform(Vector3D turn, Vector3D scale, Vector3D rotate, Vector3D translate)
{
    // 1. turn to align with x/y/z as needed
    // 2. scale to desired x/y/z size
    // 3. rotate as needed by the scene
    // 4. move to the position
    mat.setToIdentity();
    mat.translate(translate);
    mat.rotate(EulerToQuaternion(rotate));
    mat.scale(scale);
    mat.rotate(EulerToQuaternion(turn));
}

// This method allows the addition of an extrinsic global rotation to an object i.e.
// it rotates the object about the global origin of the coordinate system
void Object::addExtrinsicRotation(Vector3D turn, Vector3D scale, Vector3D& rotate,
                                  Vector3D rotateExtrinsic, Vector3D& translate)
{
    mat.setToIdentity();
    mat.rotate(EulerToQuaternion(rotateExtrinsic));
    mat.translate(translate);
    mat.rotate(EulerToQuaternion(rotate));
    mat.scale(scale);
    mat.rotate(EulerToQuaternion(turn));

    // first apply the particle's intrinsic and then extrinsic rotations
    QQuaternion q = EulerToQuaternion(rotateExtrinsic) * EulerToQuaternion(rotate);
    rotate = QuaternionToEuler(q);

    // translate the object to the extrinsically rotated translation vector
    translate = EulerToQuaternion(rotateExtrinsic).rotatedVector(translate);
}

void Object::releaseGeometry()
{
    geo.reset();
}

void Object::draw(Canvas& canvas)
{
    if (isNull)
        return;

    if (!geo)
        geo = geometryStore().getGeometry(gky);
    canvas.draw(color, mat, *geo);
}

} // namespace RealSpace

namespace
{
QQuaternion EulerToQuaternion(const RealSpace::Vector3D& euler)
{
    float cpsi2 = std::cos(euler.x / 2.0f);
    float spsi2 = std::sin(euler.x / 2.0f);
    float cth2 = std::cos(euler.y / 2.0f);
    float sth2 = std::sin(euler.y / 2.0f);
    float cphi2 = std::cos(euler.z / 2.0f);
    float sphi2 = std::sin(euler.z / 2.0f);
    auto a = cphi2 * cth2 * cpsi2 - sphi2 * cth2 * spsi2;
    auto b = cphi2 * cpsi2 * sth2 + sphi2 * sth2 * spsi2;
    auto c = cphi2 * sth2 * spsi2 - sphi2 * cpsi2 * sth2;
    auto d = cphi2 * cth2 * spsi2 + cth2 * cpsi2 * sphi2;
    return QQuaternion{a, b, c, d};
}

RealSpace::Vector3D QuaternionToEuler(const QQuaternion& q)
{
    auto qvec = q.toVector4D();

    float a = qvec.w(); // scalar part of quaternion
    float b = qvec.x();
    float c = qvec.y();
    float d = qvec.z();

    float term1 = std::atan(d / a);
    float term2 = 0;

    if (b == 0)
        term2 = static_cast<float>(M_PI_2);
    else
        term2 = std::atan(c / b);

    float x = term1 + term2;
    float y = 2 * std::atan(std::sqrt((b * b + c * c) / (a * a + d * d)));
    float z = term1 - term2;

    return RealSpace::Vector3D(x, y, z);
}
} // namespace
