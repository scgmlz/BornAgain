// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/RippleCosine.cpp
//! @brief     Implements class RippleCosine.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Shapes/RippleCosine.h"

#include <cmath>

RippleCosine::RippleCosine(double length, double width, double height)
{
    size_t n_y = IShape::N_Circle + 1;
    double y_step = width / (IShape::N_Circle);
    m_vertices.resize(2 * n_y);
    for (size_t i = 0; i < n_y; ++i) {
        double y = i * y_step - width / 2.0;
        double z = height * (1.0 + std::cos(2.0 * M_PI * y / width)) / 2.0;
        m_vertices[i] = kvector_t(length / 2.0, y, z);
        m_vertices[n_y + i] = kvector_t(-length / 2.0, y, z);
    }
}

RippleCosine::~RippleCosine() {}
