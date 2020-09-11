// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry_inc.cpp
//! @brief     Implements geometry namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/ba3d/model/geometry_inc.h"
#include <cmath>
#include <functional>

namespace RealSpace
{

// Useful constants:
const float GoldenRatio = (1.f + std::sqrt(5.f)) / 2.f;
const float IcosahedronL2R = 4.f / (10.f + 2.f * std::sqrt(5.f));
const float DodecahedronL2R = 4.f / std::sqrt(3.f) / (1.f + std::sqrt(5.f));

// Keys and hash:
GeometricID::Key::Key(BaseShape id_, float p1_, float p2_, float p3_)
    : id(id_), p1(p1_), p2(p2_), p3(p3_)
{
}

bool GeometricID::Key::operator==(Key const& other) const
{
    return id == other.id && p1 == other.p1 && p2 == other.p2;
}

std::size_t GeometricID::KeyHash::operator()(const GeometricID::Key& key) const noexcept
{
    {
        size_t h1 = std::hash<int>{}(static_cast<int>(key.id));
        size_t h2 = std::hash<float>{}(key.p1);
        size_t h3 = std::hash<float>{}(key.p2);
        size_t h4 = std::hash<float>{}(key.p3);
        return h1 ^ (h2 ^ (h3 ^ h4));
    }
}
} // namespace RealSpace
