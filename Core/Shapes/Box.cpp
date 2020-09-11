// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/Box.cpp
//! @brief     Implements class Box.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Shapes/Box.h"

#include <algorithm>

Box::Box(double length, double width, double height)
{
    m_vertices.resize(8);
    auto bottom_face = RectangleVertices(length, width, 0.0);
    auto top_face = RectangleVertices(length, width, height);
    std::move(bottom_face.begin(), bottom_face.end(), m_vertices.begin());
    std::move(top_face.begin(), top_face.end(), m_vertices.begin() + 4);
}

Box::~Box() {}
