// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/IShape.cpp
//! @brief     Implements default methods of interface IShape.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Shapes/IShape.h"

#include <cmath>

// Value of 24 ensures that real points stick out of the convex hull at most
// 1% of the radius
const size_t IShape::N_Circle = 24;

std::vector<kvector_t> IShape::vertices() const
{
    return m_vertices;
}

std::vector<kvector_t> RectangleVertices(double length, double width, double z)
{
    std::vector<kvector_t> result = {{length / 2.0, width / 2.0, z},
                                     {-length / 2.0, width / 2.0, z},
                                     {-length / 2.0, -width / 2.0, z},
                                     {length / 2.0, -width / 2.0, z}};
    return result;
}

std::vector<kvector_t> EllipseVertices(double r_x, double r_y, double z)
{
    static constexpr double delta_angle = 2.0 * M_PI / IShape::N_Circle;
    std::vector<kvector_t> result(IShape::N_Circle);
    for (size_t i = 0; i < IShape::N_Circle; ++i) {
        double angle = i * delta_angle;
        double x = r_x * std::cos(angle);
        double y = r_y * std::sin(angle);
        result[i] = kvector_t(x, y, z);
    }
    return result;
}
