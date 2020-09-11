// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry/icosahedron.cpp
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

Geometry::Mesh Geometry::meshIcosahedron()
{
    Vertices vs_(12); // 12 vertices of the icosahedron retrieved from Icosahedron.cpp

    const float E = 1.0; // edge

    vs_[0] = Vector3D(-0.57735026918962573f * E, 0.0f * E, 0.0f);
    vs_[1] = Vector3D(0.28867513459481281f * E, 0.5f * E, 0.0f);
    vs_[2] = Vector3D(0.28867513459481281f * E, -0.5f * E, 0.0f);
    vs_[3] = Vector3D(0.93417235896271578f * E, 0.0f * E, 0.57735026918962562f * E);
    vs_[4] =
        Vector3D(-0.46708617948135783f * E, 0.80901699437494756f * E, 0.57735026918962562f * E);
    vs_[5] =
        Vector3D(-0.46708617948135783f * E, -0.80901699437494756f * E, 0.57735026918962562f * E);
    vs_[6] = Vector3D(-0.93417235896271578f * E, 0.0f * E, 0.93417235896271589f * E);
    vs_[7] = Vector3D(0.46708617948135783f * E, 0.80901699437494756f * E, 0.93417235896271589f * E);
    vs_[8] =
        Vector3D(0.46708617948135783f * E, -0.80901699437494756f * E, 0.93417235896271589f * E);
    vs_[9] = Vector3D(0.57735026918962573f * E, 0.0f * E, 1.5115226281523415f * E);
    vs_[10] = Vector3D(-0.28867513459481281f * E, 0.5f * E, 1.5115226281523415f * E);
    vs_[11] = Vector3D(-0.28867513459481281f * E, -0.5f * E, 1.5115226281523415f * E);

    ASSERT(12 == vs_.count());

    Vertices vs;
    vs.reserve(60);

    // lower half of the icosahedron (clockwise ordering of vertices)
    vs.addTriangle(vs_[0], vs_[1], vs_[2]);
    vs.addTriangle(vs_[0], vs_[4], vs_[1]);
    vs.addTriangle(vs_[1], vs_[3], vs_[2]);
    vs.addTriangle(vs_[2], vs_[5], vs_[0]);

    vs.addTriangle(vs_[0], vs_[6], vs_[4]);
    vs.addTriangle(vs_[4], vs_[7], vs_[1]);
    vs.addTriangle(vs_[1], vs_[7], vs_[3]);
    vs.addTriangle(vs_[3], vs_[8], vs_[2]);
    vs.addTriangle(vs_[8], vs_[5], vs_[2]);
    vs.addTriangle(vs_[5], vs_[6], vs_[0]);

    // upper half of the icosahedron (couter clockwise ordering of vertices)
    vs.addTriangle(vs_[11], vs_[6], vs_[5]);
    vs.addTriangle(vs_[8], vs_[11], vs_[5]);
    vs.addTriangle(vs_[9], vs_[8], vs_[3]);
    vs.addTriangle(vs_[9], vs_[3], vs_[7]);
    vs.addTriangle(vs_[10], vs_[7], vs_[4]);
    vs.addTriangle(vs_[6], vs_[10], vs_[4]);

    vs.addTriangle(vs_[10], vs_[6], vs_[11]);
    vs.addTriangle(vs_[9], vs_[11], vs_[8]);
    vs.addTriangle(vs_[9], vs_[7], vs_[10]);
    vs.addTriangle(vs_[9], vs_[10], vs_[11]);

    ASSERT(60 == vs.count());

    return makeMesh(vs);
}

} // namespace RealSpace
