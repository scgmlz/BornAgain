// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/RippleSawtooth.cpp
//! @brief     Implements class RippleSawtooth.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Shapes/RippleSawtooth.h"

RippleSawtooth::RippleSawtooth(double length, double width, double height, double asymmetry)
{
    double ymax = width / 2.0 - asymmetry;
    double ymin = -width / 2.0 - asymmetry;
    m_vertices.resize(6);
    m_vertices[0] = kvector_t(length / 2.0, ymax, 0.0);
    m_vertices[1] = kvector_t(length / 2.0, ymin, 0.0);
    m_vertices[2] = kvector_t(length / 2.0, 0.0, height);
    m_vertices[3] = kvector_t(-length / 2.0, ymax, 0.0);
    m_vertices[4] = kvector_t(-length / 2.0, ymin, 0.0);
    m_vertices[5] = kvector_t(-length / 2.0, 0.0, height);
}

RippleSawtooth::~RippleSawtooth() {}
