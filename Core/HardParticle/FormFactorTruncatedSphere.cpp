// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTruncatedSphere.cpp
//! @brief     Implements class FormFactorTruncatedSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorTruncatedSphere.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Shapes/TruncatedEllipsoid.h"
#include "Core/Tools/Integrator.h"
#include "Core/Tools/MathFunctions.h"
#include "Fit/Tools/RealLimits.h"
#include <limits>

//! Constructor of a spherical dome.
//! @param radius: radius of the truncated sphere in nanometers
//! @param height: height of the truncated sphere in nanometers
//! @param dh: length of cup truncated from the top
FormFactorTruncatedSphere::FormFactorTruncatedSphere(const std::vector<double> P)
    : IFormFactorBorn({"TruncatedSphere",
                       "class_tooltip",
                       {{"Radius", "nm", "para_tooltip", 0, +INF, 0},
                        {"Height", "nm", "para_tooltip", 0, +INF, 0},
                        {"DeltaHeight", "nm", "para_tooltip", 0, +INF, 0}}},
                      P),
      m_radius(m_P[0]), m_height(m_P[1]), m_dh(m_P[2])
{
    check_initialization();
    onChange();
}

FormFactorTruncatedSphere::FormFactorTruncatedSphere(double radius, double height, double dh)
    : FormFactorTruncatedSphere(std::vector<double>{radius, height, dh})
{
}

bool FormFactorTruncatedSphere::check_initialization() const
{
    bool result(true);
    if (m_height > 2. * m_radius || m_dh > m_height) {
        std::ostringstream ostr;
        ostr << "::FormFactorTruncatedSphere() -> Error in class initialization ";
        ostr << "with parameters 'radius':" << m_radius << " 'height':" << m_height
             << " 'delta_height':" << m_dh << "\n\n";
        ostr << "Check for height <= 2.*radius AND delta_height < height failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

//! Integrand for complex form factor.
complex_t FormFactorTruncatedSphere::Integrand(double Z) const
{
    double Rz = std::sqrt(m_radius * m_radius - Z * Z);
    complex_t qx = m_q.x();
    complex_t qy = m_q.y();
    complex_t q_p = std::sqrt(qx * qx + qy * qy); // NOT the modulus!
    return Rz * Rz * MathFunctions::Bessel_J1c(q_p * Rz) * exp_I(m_q.z() * Z);
}

//! Complex form factor.
complex_t FormFactorTruncatedSphere::evaluate_for_q(cvector_t q) const
{
    m_q = q;
    if (std::abs(q.mag()) < std::numeric_limits<double>::epsilon()) {
        return M_PI / 3.
               * (m_height * m_height * (3. * m_radius - m_height)
                  - m_dh * m_dh * (3. * m_radius - m_dh));
    }
    // else
    complex_t integral = ComplexIntegrator().integrate([&](double Z) { return Integrand(Z); },
                                                       m_radius - m_height, m_radius - m_dh);
    return M_TWOPI * integral * exp_I(q.z() * (m_height - m_radius));
}

IFormFactor* FormFactorTruncatedSphere::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                        kvector_t translation) const
{
    double height = m_height - m_dh;
    auto effects = computeSlicingEffects(limits, translation, height);
    FormFactorTruncatedSphere slicedff(m_radius, m_height - effects.dz_bottom,
                                       effects.dz_top + m_dh);
    return createTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorTruncatedSphere::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_radius, m_radius, m_radius, m_height, m_dh));
}
