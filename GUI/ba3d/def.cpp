// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/def.cpp
//! @brief     Definitions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/ba3d/def.h"

static_assert(QT_VERSION >= QT_VERSION_CHECK(5, 5, 1),
              "requires Qt >= 5.5.1, have " QT_VERSION_STR);

namespace RealSpace
{
//------------------------------------------------------------------------------

Vector3D::Vector3D() : Vector3D(0, 0, 0) {}

Vector3D::Vector3D(float v) : Vector3D(v, v, v) {}

Vector3D::Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

Vector3D::Vector3D(QVector3D const& v) : Vector3D(v.x(), v.y(), v.z()) {}

float Vector3D::length() const
{
    return QVector3D(*this).length();
}

Vector3D Vector3D::normalized() const
{
    return QVector3D(*this).normalized();
}

Vector3D Vector3D::interpolateTo(const Vector3D& to, float rat) const
{
    return *this * (1 - rat) + to * rat;
}

RealSpace::Vector3D::operator QVector3D() const
{
    return QVector3D(x, y, z);
}

Vector3D const Vector3D::_0(0, 0, 0), Vector3D::_1(1, 1, 1), Vector3D::_x(1, 0, 0),
    Vector3D::_y(0, 1, 0), Vector3D::_z(0, 0, 1);

Vector3D cross(const Vector3D& v1, const Vector3D& v2)
{
    return QVector3D::crossProduct(v1, v2);
}

float dot(const Vector3D& v1, const Vector3D& v2)
{
    return QVector3D::dotProduct(v1, v2);
}

Vector3D operator+(const Vector3D& v)
{
    return v;
}

Vector3D operator-(const Vector3D& v)
{
    return Vector3D::_0 - v;
}

Vector3D operator*(const Vector3D& v, float f)
{
    return Vector3D(v.x * f, v.y * f, v.z * f);
}

Vector3D operator+(const Vector3D& _1, const Vector3D& _2)
{
    return Vector3D(_1.x + _2.x, _1.y + _2.y, _1.z + _2.z);
}

Vector3D operator-(const Vector3D& _1, const Vector3D& _2)
{
    return Vector3D(_1.x - _2.x, _1.y - _2.y, _1.z - _2.z);
}

//------------------------------------------------------------------------------

Range::Range(float r1, float r2) : min(qMin(r1, r2)), max(qMax(r1, r2)) {}

float Range::size() const
{
    return max - min;
}

float Range::mid() const
{
    return (min + max) / 2;
}

//------------------------------------------------------------------------------

VectorRange::VectorRange(Range x_, Range y_, Range z_) : x(x_), y(y_), z(z_) {}

VectorRange::VectorRange(Vector3D _1, Vector3D _2)
    : x(Range(_1.x, _2.x)), y(Range(_1.y, _2.y)), z(Range(_1.z, _2.z))
{
}

Vector3D VectorRange::size() const
{
    return Vector3D(x.size(), y.size(), z.size());
}

Vector3D VectorRange::mid() const
{
    return Vector3D(x.mid(), y.mid(), z.mid());
}

float VectorRange::length() const
{
    return Vector3D(x.size(), y.size(), z.size()).length();
}

//------------------------------------------------------------------------------
} // namespace RealSpace
