// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorDot.cpp
//! @brief     Implements class FormFactorDot.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorDot.h"

FormFactorDot::FormFactorDot(const std::vector<double> P)
    : IFormFactorBorn(
          {"Dot",
           "dot, with scattering power of a sphere of given radius",
           {{"Radius", "nm", "radius of sphere that defines scattering power", 0, +INF, 0}}},
          P),
      m_radius(m_P[0])
{
    onChange();
}

FormFactorDot::FormFactorDot(double radius) : FormFactorDot(std::vector<double>{radius}) {}

complex_t FormFactorDot::evaluate_for_q(cvector_t) const
{
    return 4 * M_PI / 3 * pow(m_radius, 3);
}
