// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereGaussianRadius.cpp
//! @brief     Implements class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/SoftParticle/FormFactorSphereGaussianRadius.h"
#include "Core/Shapes/TruncatedEllipsoid.h"
#include "Core/Vector/SomeFormFactors.h"
#include "Fit/Tools/RealLimits.h"

FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius(const std::vector<double> P)
    : IFormFactorBorn({"FormFactorSphereGaussianRadius",
                       "class_tooltip",
                       {{"MeanRadius", "nm", "para_tooltip", 0, +INF, 0},
                        {"SigmaRadius", "nm", "para_tooltip", 0, +INF, 0}}},
                      P),
      m_mean(m_P[0]), m_sigma(m_P[1])
{
    m_mean_r3 = calculateMeanR3();
    onChange();
}

FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius(double mean, double sigma)
    : FormFactorSphereGaussianRadius(std::vector<double>{mean, sigma})
{
}

complex_t FormFactorSphereGaussianRadius::evaluate_for_q(cvector_t q) const
{
    double q2 = std::norm(q.x()) + std::norm(q.y()) + std::norm(q.z());
    double dw = std::exp(-q2 * m_sigma * m_sigma / 2.0);
    return dw * exp_I(q.z() * m_mean_r3) * someff::ffSphere(q, m_mean_r3);
    // TODO: don't center at bottom; revise mesocrystal1.py
}

void FormFactorSphereGaussianRadius::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_mean, m_mean, m_mean, 2.0 * m_mean, 0.0));
}

double FormFactorSphereGaussianRadius::calculateMeanR3() const
{
    return std::pow(m_mean * (m_mean * m_mean + 3.0 * m_sigma * m_sigma), 1.0 / 3.0);
}
