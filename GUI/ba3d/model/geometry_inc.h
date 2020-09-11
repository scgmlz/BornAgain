// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry_inc.h
//! @brief     Defines geometry namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_BA3D_MODEL_GEOMETRY_INC_H
#define BORNAGAIN_GUI_BA3D_MODEL_GEOMETRY_INC_H

#include "../def.h"
#include <memory>

// include to use geometry basics, without details

namespace RealSpace
{
//------------------------------------------------------------------------------

class Geometry;

typedef std::shared_ptr<Geometry> GeometryHandle;
typedef std::weak_ptr<Geometry> GeometryRef;

// some useful constants:
extern const float GoldenRatio;
extern const float IcosahedronL2R; // L/R conversion
extern const float DodecahedronL2R;

namespace GeometricID
{

// Enum id for basic shapes
enum class BaseShape {
    Plane,
    Box,
    Sphere,
    Column,
    Icosahedron,
    Dodecahedron,
    TruncatedBox,
    Cuboctahedron,
    Ripple
};

// Real shapes will be parameterized by BaseShape enum and possibly two floats
struct Key {
    Key(BaseShape, float = 0.0f, float = 0.0f, float = 0.0f);

    bool operator==(Key const&) const;

    BaseShape id;
    float p1, p2, p3;
};

// Hash functor for Key objects
struct KeyHash {
    std::size_t operator()(const Key& key) const noexcept;
};

} // namespace GeometricID
} // namespace RealSpace

#endif // BORNAGAIN_GUI_BA3D_MODEL_GEOMETRY_INC_H
