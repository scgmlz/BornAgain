// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorEllipsoidalCylinder.cpp
//! @brief     Implements class FormFactorEllipsoidalCylinder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorEllipsoidalCylinder.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Shapes/DoubleEllipse.h"
#include "Core/Tools/MathFunctions.h"

//! Constructor of a cylinder with an ellipse cross section.
//! @param radius_x: radius of the ellipse base in the x-direction, in nanometers
//! @param radius_y: radius of the ellipse base in the y-direction, in nanometers
//! @param height: height of the ellipsoidal cylinder in nanometers
FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(const std::vector<double> P)
    : IFormFactorBorn({"EllipsoidalCylinder",
                       "class_tooltip",
                       {{"RadiusX", "nm", "para_tooltip", 0, +INF, 0},
                        {"RadiusY", "nm", "para_tooltip", 0, +INF, 0},
                        {"Height", "nm", "para_tooltip", 0, +INF, 0}}},
                      P),
      m_radius_x(m_P[0]), m_radius_y(m_P[1]), m_height(m_P[2])
{
    onChange();
}

FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(double radius_x, double radius_y,
                                                             double height)
    : FormFactorEllipsoidalCylinder(std::vector<double>{radius_x, radius_y, height})
{
}

double FormFactorEllipsoidalCylinder::radialExtension() const
{
    return (m_radius_x + m_radius_y) / 2.0;
}

complex_t FormFactorEllipsoidalCylinder::evaluate_for_q(cvector_t q) const
{
    complex_t qxRa = q.x() * m_radius_x;
    complex_t qyRb = q.y() * m_radius_y;
    complex_t qzHdiv2 = m_height / 2 * q.z();

    complex_t Fz = exp_I(qzHdiv2) * MathFunctions::sinc(qzHdiv2);
    complex_t gamma = std::sqrt((qxRa) * (qxRa) + (qyRb) * (qyRb));
    complex_t J1_gamma_div_gamma = MathFunctions::Bessel_J1c(gamma);

    return M_TWOPI * m_radius_x * m_radius_y * m_height * Fz * J1_gamma_div_gamma;
}

IFormFactor* FormFactorEllipsoidalCylinder::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                            kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorEllipsoidalCylinder slicedff(m_radius_x, m_radius_y,
                                           m_height - effects.dz_bottom - effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorEllipsoidalCylinder::onChange()
{
    mP_shape.reset(new DoubleEllipse(m_radius_x, m_radius_y, m_height, m_radius_x, m_radius_y));
}
