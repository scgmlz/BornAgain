// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/ba3d/model/geometry/ripple.cpp
//! @brief     Implements utility functions in ba3d namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "../geometry.h"
#include <qmath.h>

namespace RealSpace
{

Geometry::Mesh Geometry::meshRipple(float numSides, float ratio_asymmetry_W)
{
    int const sides = qRound(numSides);
    bool const smooth = (0 == sides); // sides = 0 implies smooth -> e.g. cosine ripple
    int const slices = smooth ? 4 * SLICES : sides;

    // Values are chosen such that length, width and height are 1
    float const R = .5f;
    float const H = 2 * R;                             // L = W = H = 2*R
    float const asymmetry = ratio_asymmetry_W * 2 * R; // for Ripple1 asymmetry is inherently 0

    Vertices vfront(slices), vback(slices);

    if (numSides == 3) {
        // Ripple2: saw-tooth (3 rectangular sides and 2 triangular front and back)
        vfront[0] = Vector3D(-R, -R, 0);
        vfront[1] = Vector3D(-R, asymmetry, H);
        vfront[2] = Vector3D(-R, R, 0);

        vback[0] = Vector3D(R, -R, 0);
        vback[1] = Vector3D(R, asymmetry, H);
        vback[2] = Vector3D(R, R, 0);
    } else if (numSides == 0) {
        // Ripple1: cosine ripple
        for (int s = 0; s < slices; ++s) {
            float th = static_cast<float>(M_PI * s / (slices + 1));
            float y = -R * cosf(th);
            float z = R * (1.0f + cosf(2 * static_cast<float>(M_PI) * y / (2 * R)));
            vfront[s] = Vector3D(-R, y, z);
            vback[s] = Vector3D(R, y, z);
        }
    }

    int const nv = (3 + 3 + 6) * slices; // 3 for part of front face, 3 for part of back face
                                         // 6 for side face

    Vertices vs;
    vs.reserve(nv);

    for (int s = 0; s < slices; ++s) {
        int s1 = s, s2 = (s + 1) % slices;

        // clockwise ordering of vertices
        vs.addTriangle(vfront.at(s1), vfront.at(s2), Vector3D(-R, asymmetry, H / 2)); // front

        // counter-clockwise ordering of vertices
        vs.addTriangle(vback.at(s1), Vector3D(R, asymmetry, H / 2), vback.at(s2)); // back

        // counter-clockwise ordering of vertices
        vs.addQuad(vfront.at(s2), vfront.at(s1), vback.at(s1), vback.at(s2)); // side
    }

    Q_ASSERT(vs.count() == nv);

    return makeMesh(vs, nullptr); // normals not calculated here and left for makeMesh to calculate
}

} // namespace RealSpace
