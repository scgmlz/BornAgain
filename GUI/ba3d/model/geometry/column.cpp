// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry/column.cpp
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
#include <qmath.h>

namespace RealSpace
{

Geometry::Mesh Geometry::meshColumn(float ratio_Rt_Rb, float numSides)
{
    int const sides = qRound(numSides);
    bool const smooth = (0 == sides); // sides = 0 implies smooth -> e.g. cylinder
    int const slices = smooth ? SLICES : sides;

    // Rt is the top radius, Rb is the bottom radius, H is the height
    // Values are chosen such that diameter and height are 1
    float const R = .5f;
    float Rb = R, Rt = Rb * ratio_Rt_Rb, H = 2 * R;

    // mesh of vertices (bottom and top) and normals
    Vertices vb(slices), vt(slices), nbt(slices);
    float const nz = (1 - Rt / Rb) * H;

    for (int s = 0; s < slices; ++s) {
        float th = float(2 * M_PI * s / slices), st = sinf(th), ct = cosf(th);

        Vector3D vb_(Rb * ct, Rb * st, 0), vt_(Rt * ct, Rt * st, H);
        vb[s] = vb_;
        vt[s] = vt_;
        if (smooth)
            nbt[s] = Vector3D(vb_.x, vb_.y, nz).normalized();
    }

    // make into triangles
    int const nv = 6 * 2 * slices;
    Vertices vs;
    vs.reserve(nv);
    Vertices ns;
    if (smooth)
        ns.reserve(nv);

    for (int s = 0; s < slices; ++s) {
        int s1 = s, s2 = (s + 1) % slices;

        vs.addTriangle(vb.at(s1), Vector3D(0, 0, 0), vb.at(s2)); // bottom
        if (smooth)
            ns.addVertex(-Vector3D::_z, 3);

        vs.addTriangle(Vector3D(0, 0, H), vt.at(s1), vt.at(s2)); // top
        if (smooth)
            ns.addVertex(+Vector3D::_z, 3);

        vs.addQuad(vb.at(s1), vb.at(s2), vt.at(s2), vt.at(s1)); // side
        if (smooth) {
            auto &n1 = nbt.at(s1), &n2 = nbt.at(s2);
            ns.addQuad(n1, n2, n2, n1);
        }
    }

    ASSERT(vs.count() == nv);
    ASSERT(!smooth || ns.count() == nv);

    return makeMesh(vs, smooth ? &ns : nullptr);
}

} // namespace RealSpace
