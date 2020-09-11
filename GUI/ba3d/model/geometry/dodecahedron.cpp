// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry/dodecahedron.cpp
//! @brief     Implements utility functions in ba3d namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "../geometry.h"
#include "Core/Basics/Assert.h"
#include <QQuaternion>
#include <qmath.h>

namespace RealSpace
{

Geometry::Mesh Geometry::meshDodecahedron()
{
    const float GR = GoldenRatio, G1 = 1 / GR;

    Vertices vs_;
    vs_.reserve(20);
    for (float x : {-1, +1})
        for (float y : {-1, +1})
            for (float z : {-1, +1})
                vs_.append(Vector3D(x, y, z));

    for (float g1 : {-G1, +G1})
        for (float g : {-GR, +GR}) {
            vs_.append(Vector3D(0, g1, g));
            vs_.append(Vector3D(g1, g, 0));
            vs_.append(Vector3D(g, 0, g1));
        }

    ASSERT(20 == vs_.count());

    // scale to circumscribed sphere
    float const F = .5f / vs_.at(0).length();
    for (auto& v : vs_)
        v = v * F;

    // face down
    auto q = QQuaternion::rotationTo(-Vector3D::_z,
                                     cross(vs_.at(8) - vs_.at(0), vs_.at(10) - vs_.at(0)));
    for (int i = 0; i < 20; ++i) {
        vs_[i] = q.rotatedVector(vs_.at(i));
        vs_[i].z += 0.5f * std::sqrt(G1); // shift the bottom of the dodecahedron to z=0 plane
    }

    Vertices vs;
    vs.reserve(180);

    auto add5 = [&](unsigned i1, unsigned i2, unsigned i3, unsigned i4, unsigned i5) {
        vs.addFan(vs_, {i1, i2, i3, i4, i5, i1});
    };

    add5(1, 11, 17, 3, 16); // bottom
    add5(1, 16, 10, 0, 9);
    add5(16, 3, 12, 2, 10);
    add5(3, 17, 7, 18, 12);
    add5(17, 11, 5, 19, 7);
    add5(11, 1, 9, 15, 5);

    add5(8, 4, 15, 9, 0);
    add5(14, 8, 0, 10, 2);
    add5(6, 14, 2, 12, 18);
    add5(13, 6, 18, 7, 19);
    add5(4, 13, 19, 5, 15);
    add5(4, 8, 14, 6, 13); // top

    ASSERT(144 == vs.count());

    return makeMesh(vs);
}

} // namespace RealSpace
