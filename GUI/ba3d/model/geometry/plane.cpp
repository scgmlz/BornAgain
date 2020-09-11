// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry/plane.cpp
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

Geometry::Mesh Geometry::meshPlane()
{
    float const D = .5f;

    Vertices vs;
    vs.reserve(4);
    vs.addQuad({+D, +D, 0}, {-D, +D, 0}, {-D, -D, 0}, {+D, -D, 0});

    ASSERT(4 == vs.count());

    return makeMesh(vs);
}

} // namespace RealSpace
