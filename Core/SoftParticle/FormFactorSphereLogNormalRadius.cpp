// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereLogNormalRadius.cpp
//! @brief     Implements class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/SoftParticle/FormFactorSphereLogNormalRadius.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Shapes/TruncatedEllipsoid.h"
#include "Core/Vector/SomeFormFactors.h"

FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius(const std::vector<double> P,
                                                                 size_t n_samples)
    : IFormFactorBorn({"FormFactorSphereLogNormalRadius",
                       "class_tooltip",
                       {{"MeanRadius", "nm", "para_tooltip", 0, +INF, 0},
                        {"ScaleParameter", "", "para_tooltip", -INF, +INF, 0}}},
                      P),
      m_mean(m_P[0]), m_scale_param(m_P[1]), m_n_samples(n_samples)
{

    DistributionLogNormal distri(m_mean, m_scale_param);
    m_radii.clear();
    m_probabilities.clear();
    for (ParameterSample& sample : distri.equidistantSamples(m_n_samples)) {
        m_radii.push_back(sample.value);
        m_probabilities.push_back(sample.weight);
    }

    onChange();
}

FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius(double mean, double scale_param,
                                                                 size_t n_samples)
    : FormFactorSphereLogNormalRadius(std::vector<double>{mean, scale_param}, n_samples)
{
}

FormFactorSphereLogNormalRadius* FormFactorSphereLogNormalRadius::clone() const
{
    return new FormFactorSphereLogNormalRadius(m_mean, m_scale_param, m_n_samples);
}

complex_t FormFactorSphereLogNormalRadius::evaluate_for_q(cvector_t q) const
{
    complex_t result = 0;
    for (size_t i = 0; i < m_radii.size(); ++i)
        result += someff::ffSphere(q, m_radii[i]) * m_probabilities[i];
    return result;
}

void FormFactorSphereLogNormalRadius::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_mean, m_mean, m_mean, 2.0 * m_mean, 0.0));
}
