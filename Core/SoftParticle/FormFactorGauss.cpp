// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorGauss.cpp
//! @brief     Implements class FormFactorGaussSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/SoftParticle/FormFactorGauss.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Shapes/Box.h"
#include <limits>

FormFactorGaussSphere::FormFactorGaussSphere(const std::vector<double> P)
    : IFormFactorBorn({"FormFactorGaussSphere",
                       "class_tooltip",
                       {{"MeanRadius", "nm", "para_tooltip", 0, +INF, 0}}},
                      P),
      m_mean_radius(m_P[0])
{
    onChange();
}

FormFactorGaussSphere::FormFactorGaussSphere(double mean_radius)
    : FormFactorGaussSphere(std::vector<double>{mean_radius})
{
}

complex_t FormFactorGaussSphere::evaluate_for_q(cvector_t q) const
{
    const double max_ql = std::sqrt(-4 * M_PI * std::log(std::numeric_limits<double>::min()) / 3);

    double qzh = q.z().real() * m_mean_radius;
    if (std::abs(qzh) > max_ql)
        return 0.0;
    double qxr = q.x().real() * m_mean_radius;
    if (std::abs(qxr) > max_ql)
        return 0.0;
    double qyr = q.y().real() * m_mean_radius;
    if (std::abs(qyr) > max_ql)
        return 0.0;

    return pow(m_mean_radius, 3) * std::exp(-(qxr * qxr + qyr * qyr + qzh * qzh) / 4.0 / M_PI);
}
