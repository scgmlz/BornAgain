// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSphere.cpp
//! @brief     Implements class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/Basics/MathConstants.h"
#include "Core/HardParticle/FormFactorTruncatedSphere.h"
#include "Core/Particle/FormFactorWeighted.h"
#include "Core/Scattering/Rotations.h"
#include "Core/Vector/SomeFormFactors.h"

//! Constructor of a full sphere.
//! @param radius: radius of the sphere in nanometers
FormFactorFullSphere::FormFactorFullSphere(const std::vector<double> P, bool position_at_center)
    : IFormFactorBorn(
        {"FullSphere", "class_tooltip", {{"Radius", "nm", "para_tooltip", 0, +INF, 0}}}, P),
      m_radius(m_P[0]), m_position_at_center(position_at_center)
{
    onChange();
}

FormFactorFullSphere::FormFactorFullSphere(double radius, bool position_at_center)
    : FormFactorFullSphere(std::vector<double>{radius}, position_at_center)
{
}

double FormFactorFullSphere::bottomZ(const IRotation& rotation) const
{
    if (m_position_at_center)
        return -m_radius;
    kvector_t centre(0.0, 0.0, m_radius);
    kvector_t new_centre = rotation.transformed(centre);
    return new_centre.z() - m_radius;
}

double FormFactorFullSphere::topZ(const IRotation& rotation) const
{
    if (m_position_at_center)
        return m_radius;
    kvector_t centre(0.0, 0.0, m_radius);
    kvector_t new_centre = rotation.transformed(centre);
    return new_centre.z() + m_radius;
}

complex_t FormFactorFullSphere::evaluate_for_q(cvector_t q) const
{
    complex_t ret = someff::ffSphere(q, m_radius);
    if (!m_position_at_center)
        ret *= exp_I(q.z() * m_radius);
    return ret;
}

IFormFactor* FormFactorFullSphere::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                   kvector_t translation) const
{
    kvector_t center(0.0, 0.0, m_radius);
    kvector_t rotation_offset =
        m_position_at_center ? kvector_t(0.0, 0.0, 0.0) : rot.transformed(center) - center;
    kvector_t new_translation = translation + rotation_offset;
    std::unique_ptr<IRotation> P_identity(IRotation::createIdentity());
    double height = 2.0 * m_radius;
    auto effects = computeSlicingEffects(limits, new_translation, height);
    FormFactorTruncatedSphere slicedff(m_radius, height - effects.dz_bottom, effects.dz_top);
    return CreateTransformedFormFactor(slicedff, *P_identity, effects.position);
}

void FormFactorFullSphere::onChange() {}
