// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSpheroid.cpp
//! @brief     Implements class FormFactorFullSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorFullSpheroid.h"
#include "Core/Basics/MathConstants.h"
#include "Core/HardParticle/FormFactorTruncatedSpheroid.h"
#include "Core/Shapes/TruncatedEllipsoid.h"
#include "Core/Tools/MathFunctions.h"
#include <limits>

//! Constructor of full spheroid.
//! @param radius: radius of the circular cross section in nanometers
//! @param height: height of the full spheroid in nanometers
FormFactorFullSpheroid::FormFactorFullSpheroid(const std::vector<double> P)
    : IFormFactorBorn({"FullSpheroid",
                       "class_tooltip",
                       {{"Radius", "nm", "para_tooltip", 0, +INF, 0},
                        {"Height", "nm", "para_tooltip", 0, +INF, 0}}},
                      P),
      m_radius(m_P[0]), m_height(m_P[1])
{
    onChange();
}

FormFactorFullSpheroid::FormFactorFullSpheroid(double radius, double height)
    : FormFactorFullSpheroid(std::vector<double>{radius, height})
{
}

complex_t FormFactorFullSpheroid::evaluate_for_q(cvector_t q) const
{
    double h = m_height / 2;
    double R = m_radius;

    // complex length of q (not a sesquilinear dot product!),
    // xy components multiplied with R, z component multiplied with h
    complex_t qR = sqrt(R * R * (q.x() * q.x() + q.y() * q.y()) + h * h * q.z() * q.z());

    complex_t zFactor = exp_I(h * q.z());

    if (std::abs(qR) < 1e-4)
        // expand sin(qR)-qR*cos(qR) up to qR^5
        return 4 * M_PI / 3 * R * R * h * (1. - 0.1 * pow(qR, 2)) * zFactor;

    return 4 * M_PI / pow(qR, 3) * R * R * h * (sin(qR) - qR * cos(qR)) * zFactor;
}

IFormFactor* FormFactorFullSpheroid::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                     kvector_t translation) const
{
    double flattening = m_height / (2.0 * m_radius);
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorTruncatedSpheroid slicedff(m_radius, m_height - effects.dz_bottom, flattening,
                                         effects.dz_top);
    return createTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorFullSpheroid::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_radius, m_radius, m_height / 2.0, m_height, 0.0));
}
