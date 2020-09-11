// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/DoubleEllipse.cpp
//! @brief     Implements class DoubleEllipse.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Shapes/DoubleEllipse.h"

#include <algorithm>

DoubleEllipse::DoubleEllipse(double r0_x, double r0_y, double z, double rz_x, double rz_y)
{
    auto bottom_face = EllipseVertices(r0_x, r0_y, 0.0);
    size_t n_bottom = bottom_face.size();
    auto top_face = EllipseVertices(rz_x, rz_y, z);
    m_vertices.resize(n_bottom + top_face.size());
    std::move(bottom_face.begin(), bottom_face.end(), m_vertices.begin());
    std::move(top_face.begin(), top_face.end(), m_vertices.begin() + n_bottom);
}

DoubleEllipse::~DoubleEllipse() {}
