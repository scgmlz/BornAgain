//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorFullSphere.cpp
//! @brief     Implements class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/HardParticle/FormFactorFullSphere.h"
#include "Base/Math/Constants.h"
#include "Sample/HardParticle/FormFactorTruncatedSphere.h"
#include "Sample/LibFF/SomeFormFactors.h"
#include "Sample/Scattering/Rotations.h"

FormFactorFullSphere::FormFactorFullSphere(const std::vector<double> P, bool position_at_center)
    : IBornFF({"FullSphere", "sphere", {{"Radius", "nm", "radius", 0, +INF, 0}}}, P)
    , m_radius(m_P[0])
    , m_position_at_center(position_at_center) {
    onChange();
}

FormFactorFullSphere::FormFactorFullSphere(double radius, bool position_at_center)
    : FormFactorFullSphere(std::vector<double>{radius}, position_at_center) {}

double FormFactorFullSphere::bottomZ(const IRotation& rotation) const {
    if (m_position_at_center)
        return -m_radius;
    kvector_t centre(0.0, 0.0, m_radius);
    kvector_t new_centre = rotation.transformed(centre);
    return new_centre.z() - m_radius;
}

double FormFactorFullSphere::topZ(const IRotation& rotation) const {
    if (m_position_at_center)
        return m_radius;
    kvector_t centre(0.0, 0.0, m_radius);
    kvector_t new_centre = rotation.transformed(centre);
    return new_centre.z() + m_radius;
}

complex_t FormFactorFullSphere::evaluate_for_q(cvector_t q) const {
    complex_t ret = someff::ffSphere(q, m_radius);
    if (!m_position_at_center)
        ret *= exp_I(q.z() * m_radius);
    return ret;
}

IFormFactor* FormFactorFullSphere::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                   kvector_t translation) const {
    kvector_t center(0.0, 0.0, m_radius);
    kvector_t rotation_offset =
        m_position_at_center ? kvector_t(0.0, 0.0, 0.0) : rot.transformed(center) - center;
    kvector_t new_translation = translation + rotation_offset;
    double height = 2.0 * m_radius;
    auto effects = computeSlicingEffects(limits, new_translation, height);
    FormFactorTruncatedSphere slicedff(m_radius, height - effects.dz_bottom, effects.dz_top);
    return createTransformedFormFactor(slicedff, IdentityRotation(), effects.position);
}

void FormFactorFullSphere::onChange() {}
