// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/TruncatedEllipsoid.cpp
//! @brief     Implements class TruncatedEllipsoid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Shapes/TruncatedEllipsoid.h"

#include <algorithm>
#include <cmath>

TruncatedEllipsoid::TruncatedEllipsoid(double r_x, double r_y, double r_z, double height, double dh)
{
    static const int n_heights =
        std::max(2, static_cast<int>(std::round(
                        static_cast<double>(IShape::N_Circle) * height / 2.0 / r_z + 0.5)));
    double h_step = (height - dh) / (n_heights - 1);
    m_vertices.resize(n_heights * IShape::N_Circle);
    auto it = m_vertices.begin();
    for (int i = 0; i < n_heights; ++i) {
        double z = i * h_step;
        double radius_factor = std::sqrt(1.0 - std::pow((z + r_z - height) / r_z, 2));
        auto ellipse = EllipseVertices(radius_factor * r_x, radius_factor * r_y, i * h_step);
        std::move(ellipse.begin(), ellipse.end(), it);
        it = it + ellipse.size();
    }
}

TruncatedEllipsoid::~TruncatedEllipsoid() {}
