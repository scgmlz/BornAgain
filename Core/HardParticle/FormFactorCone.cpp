// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCone.cpp
//! @brief     Implements class FormFactorCone.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorCone.h"
#include "Base/Const/MathConstants.h"
#include "Base/Types/Exceptions.h"
#include "Base/Utils/Integrator.h"
#include "Base/Utils/MathFunctions.h"
#include "Core/Shapes/DoubleEllipse.h"
#include <limits>

FormFactorCone::FormFactorCone(const std::vector<double> P)
    : IFormFactorBorn({"Cone",
                       "frustum with circular base",
                       {{"Radius", "nm", "radius of base", 0, +INF, 0},
                        {"Height", "nm", "height", 0, +INF, 0},
                        {"Alpha", "rad", "angle between base and side", 0., M_PI_2, 0}}},
                      P),
      m_radius(m_P[0]), m_height(m_P[1]), m_alpha(m_P[2])
{
    m_cot_alpha = MathFunctions::cot(m_alpha);
    if (!std::isfinite(m_cot_alpha) || m_cot_alpha < 0)
        throw Exceptions::OutOfBoundsException("pyramid angle alpha out of bounds");
    if (m_cot_alpha * m_height > m_radius) {
        std::ostringstream ostr;
        ostr << "FormFactorCone() -> Error in class initialization ";
        ostr << "with parameters radius:" << m_radius;
        ostr << " m_height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= radius*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    onChange();
}

FormFactorCone::FormFactorCone(double radius, double height, double alpha)
    : FormFactorCone(std::vector<double>{radius, height, alpha})
{
}

//! Integrand for complex form factor.
complex_t FormFactorCone::Integrand(double Z) const
{
    double Rz = m_radius - Z * m_cot_alpha;
    complex_t q_p = std::sqrt(m_q.x() * m_q.x() + m_q.y() * m_q.y()); // sqrt(x*x + y*y)
    return Rz * Rz * MathFunctions::Bessel_J1c(q_p * Rz) * exp_I(m_q.z() * Z);
}

complex_t FormFactorCone::evaluate_for_q(cvector_t q) const
{
    m_q = q;
    if (std::abs(m_q.mag()) < std::numeric_limits<double>::epsilon()) {
        double R = m_radius;
        double H = m_height;
        if (m_cot_alpha == 0.0)
            return M_PI * R * R * H; // cylinder case
        double R2 = R - H * m_cot_alpha;
        double apex_height = R / m_cot_alpha;
        return M_PI / 3. * (R * R * H + (R * R - R2 * R2) * (apex_height - H));
    } else {
        complex_t integral =
            ComplexIntegrator().integrate([&](double Z) { return Integrand(Z); }, 0., m_height);
        return M_TWOPI * integral;
    }
}

IFormFactor* FormFactorCone::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                             kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    double dradius = effects.dz_bottom * m_cot_alpha;
    FormFactorCone slicedff(m_radius - dradius, m_height - effects.dz_bottom - effects.dz_top,
                            m_alpha);
    return createTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorCone::onChange()
{
    m_cot_alpha = MathFunctions::cot(m_alpha);
    double radius2 = m_radius - m_height * m_cot_alpha;
    mP_shape = std::make_unique<DoubleEllipse>(m_radius, m_radius, m_height, radius2, radius2);
}
