// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSphere.cpp
//! @brief     Implements class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorFullSphere.h"
#include "BornAgainNamespace.h"
#include "MathConstants.h"
#include "RealParameter.h"

FormFactorFullSphere::FormFactorFullSphere(double radius) : m_radius(radius)
{
    setName(BornAgain::FFFullSphereType);
    registerParameter(BornAgain::Radius, &m_radius).setUnit("nm").setNonnegative();
}

complex_t FormFactorFullSphere::evaluate_for_q(const cvector_t q) const
{
    double R = m_radius;
    complex_t q1 =
        sqrt(q.x() * q.x() + q.y() * q.y() + q.z() * q.z()); // NO sesquilinear dot product!
    complex_t qR = q1 * R;

    complex_t ret;
    if (std::abs(qR) < 1e-4) { // relative error is O(qR^4) with small prefactor
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis = { 0, 1 };
#endif
        ret = 4 * M_PI / 3 * pow(R, 3) * (1. - 0.1 * pow(qR, 2));
    } else {
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis = { 0, 0 };
#endif
        ret = 4 * M_PI * pow(q1, -3) * (sin(qR) - qR * cos(qR));
    }

    return exp_I(q.z() * R) * ret;
}
