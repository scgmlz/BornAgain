//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorEllipsoidalCylinder.cpp
//! @brief     Implements class FormFactorEllipsoidalCylinder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/HardParticle/FormFactorEllipsoidalCylinder.h"
#include "Base/Math/Bessel.h"
#include "Base/Math/Constants.h"
#include "Base/Math/Functions.h"
#include "Sample/Shapes/DoubleEllipse.h"

FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(const std::vector<double> P)
    : IBornFF({"EllipsoidalCylinder",
               "elliptical cylinder",
               {{"RadiusX", "nm", "radius in x direction", 0, +INF, 0},
                {"RadiusY", "nm", "radius in y direction", 0, +INF, 0},
                {"Height", "nm", "height", 0, +INF, 0}}},
              P)
    , m_radius_x(m_P[0])
    , m_radius_y(m_P[1])
    , m_height(m_P[2]) {
    onChange();
}

FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(double radius_x, double radius_y,
                                                             double height)
    : FormFactorEllipsoidalCylinder(std::vector<double>{radius_x, radius_y, height}) {}

double FormFactorEllipsoidalCylinder::radialExtension() const {
    return (m_radius_x + m_radius_y) / 2.0;
}

complex_t FormFactorEllipsoidalCylinder::evaluate_for_q(cvector_t q) const {
    complex_t qxRa = q.x() * m_radius_x;
    complex_t qyRb = q.y() * m_radius_y;
    complex_t qzHdiv2 = m_height / 2 * q.z();

    complex_t Fz = exp_I(qzHdiv2) * Math::sinc(qzHdiv2);
    complex_t gamma = std::sqrt((qxRa) * (qxRa) + (qyRb) * (qyRb));
    complex_t J1_gamma_div_gamma = Math::Bessel::J1c(gamma);

    return M_TWOPI * m_radius_x * m_radius_y * m_height * Fz * J1_gamma_div_gamma;
}

IFormFactor* FormFactorEllipsoidalCylinder::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                            kvector_t translation) const {
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorEllipsoidalCylinder slicedff(m_radius_x, m_radius_y,
                                           m_height - effects.dz_bottom - effects.dz_top);
    return createTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorEllipsoidalCylinder::onChange() {
    m_shape =
        std::make_unique<DoubleEllipse>(m_radius_x, m_radius_y, m_height, m_radius_x, m_radius_y);
}
