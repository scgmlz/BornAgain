// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/def.h
//! @brief     Definitions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_BA3D_DEF_H
#define BORNAGAIN_GUI_BA3D_DEF_H

#if defined(__GNUC__) && !defined(__APPLE__)
#pragma GCC diagnostic ignored "-Wswitch-enum"
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

//------------------------------------------------------------------------------
// coordinates

#include <QVector3D>

namespace RealSpace
{
//------------------------------------------------------------------------------

struct Vector3D {
    float x, y, z;

    Vector3D();
    Vector3D(float);
    Vector3D(float, float, float);

    Vector3D(const Vector3D&) = default;

    Vector3D(QVector3D const&);
    operator QVector3D() const;

    float length() const;
    Vector3D normalized() const;

    Vector3D interpolateTo(const Vector3D&, float) const;

    static Vector3D const _0, _1, _x, _y, _z;
};

// products
Vector3D cross(const Vector3D&, const Vector3D&);
float dot(const Vector3D&, const Vector3D&);

Vector3D operator+(const Vector3D&);
Vector3D operator-(const Vector3D&);
Vector3D operator*(const Vector3D&, float);

Vector3D operator+(const Vector3D&, const Vector3D&);
Vector3D operator-(const Vector3D&, const Vector3D&);

//------------------------------------------------------------------------------

// range of float
struct Range {
    float min, max;
    Range(float, float);

    float size() const;
    float mid() const;
};

// range of coordinates
struct VectorRange {
    Range x, y, z;
    VectorRange(Range, Range, Range);
    VectorRange(Vector3D, Vector3D);

    Vector3D size() const;
    Vector3D mid() const;

    float length() const;
};

//------------------------------------------------------------------------------
} // namespace RealSpace
#endif // BORNAGAIN_GUI_BA3D_DEF_H
