// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorHollowSphere.cpp
//! @brief     Implements class FormFactorHollowSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorHollowSphere.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Shapes/TruncatedEllipsoid.h"
#include <limits>

FormFactorHollowSphere::FormFactorHollowSphere(const std::vector<double> P)
    : IFormFactorBorn({"FormFactorHollowSphere",
                       "class_tooltip",
                       {{"MeanRadius", "nm", "para_tooltip", 0, +INF, 0},
                        {"FullWidth", "nm", "para_tooltip", 0, +INF, 0}}},
                      P),
      m_mean(m_P[0]), m_full_width(m_P[1])
{
    if (!checkParameters())
        throw Exceptions::ClassInitializationException(
            "FormFactorHollowSphere::FormFactorHollowSphere:"
            " mean radius must be bigger than the half width");
    onChange();
}

FormFactorHollowSphere::FormFactorHollowSphere(double mean, double full_width)
    : FormFactorHollowSphere(std::vector<double>{mean, full_width})
{
}

complex_t FormFactorHollowSphere::evaluate_for_q(cvector_t q) const
{
    double R = m_mean;
    double W = m_full_width;
    double q2 = std::norm(q.x()) + std::norm(q.y()) + std::norm(q.z());
    double q_r = std::sqrt(q2);
    if (q_r * R < std::numeric_limits<double>::epsilon())
        return (4.0 * M_PI * R * R * R + M_PI * R * W * W) / 3.0;
    double qR = q_r * R;
    double qW = q_r * W;
    double nominator =
        4 * M_PI
        * (4 * std::sin(qR) * std::sin(qW / 2.0) - qW * std::cos(qW / 2.0) * std::sin(qR)
           - 2.0 * qR * std::cos(qR) * std::sin(qW / 2.0));
    return nominator / (q2 * q2 * W);
}

void FormFactorHollowSphere::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_mean, m_mean, m_mean, 2.0 * m_mean, 0.0));
}

bool FormFactorHollowSphere::checkParameters() const
{
    if (m_full_width <= 0.0)
        return false;
    if (2.0 * m_mean < m_full_width)
        return false;
    return true;
}
