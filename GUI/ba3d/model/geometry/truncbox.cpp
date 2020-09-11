// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry/truncbox.cpp
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

namespace RealSpace
{

Geometry::Mesh Geometry::meshTruncBox(float tD)
{ // t/D
    if (tD <= 0)
        return meshBox();

    float const D = .5f, t = D * (1 - qMin(tD, 1.f));
    Vertices vs;
    vs.reserve(150);

    QVector<float> as({+D, +t, -t, -D, -D, -t, +t, +D});
    QVector<float> bs({+t, +D, +D, +t, -t, -D, -D, -t});

    auto side = [&](int ax, int ay, int az, int bx, int by, int bz, const Vector3D& d, bool rev) {
        Vertices vs_(8);
        for (int i = 0; i < 8; ++i)
            vs_[rev ? 7 - i : i] =
                Vector3D(ax * as.at(i) + bx * bs.at(i), ay * as.at(i) + by * bs.at(i),
                         az * as.at(i) + bz * bs.at(i))
                + d;
        vs.addFan(vs_, {0, 1, 2, 3, 4, 5, 6, 7, 0});
    };

    // +0.5f is required to shift the bottom of the Truncated Box to the z=0 plane

    auto corner = [&](int x, int y, int z) {
        Vertices vs_({{D * x, D * y, t * z + 0.5f},
                      {D * x, t * y, D * z + 0.5f},
                      {t * x, D * y, D * z + 0.5f}});
        if (x * y * z > 0)
            vs.addTriangle(vs_.at(0), vs_.at(2), vs_.at(1));
        else
            vs.addTriangle(vs_.at(0), vs_.at(1), vs_.at(2));
    };

    side(0, 1, 0, 0, 0, 1, Vector3D(+D, 0, +0.5f), false);
    side(0, 1, 0, 0, 0, 1, Vector3D(-D, 0, +0.5f), true);
    side(1, 0, 0, 0, 0, 1, Vector3D(0, +D, +0.5f), true);
    side(1, 0, 0, 0, 0, 1, Vector3D(0, -D, +0.5f), false);
    side(1, 0, 0, 0, 1, 0, Vector3D(0, 0, +D + 0.5f), false);
    side(1, 0, 0, 0, 1, 0, Vector3D(0, 0, -D + 0.5f), true);

    for (int x : {-1, +1})
        for (int y : {-1, +1})
            for (int z : {-1, +1})
                corner(x, y, z);

    ASSERT(150 == vs.count());

    return makeMesh(vs);
}

} // namespace RealSpace
