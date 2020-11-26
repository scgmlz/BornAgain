//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorHemiEllipsoid.cpp
//! @brief     Implements class FormFactorHemiEllipsoid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/HardParticle/FormFactorHemiEllipsoid.h"
#include "Base/Math/Bessel.h"
#include "Base/Math/Constants.h"
#include "Base/Math/IntegratorGK.h"
#include "Sample/Shapes/TruncatedEllipsoid.h"
#include <limits>

FormFactorHemiEllipsoid::FormFactorHemiEllipsoid(const std::vector<double> P)
    : IBornFF({"HemiEllipsoid",
               "actually a spheroid, truncated at central xy plane",
               {{"RadiusX", "nm", "radius in x direction", 0, +INF, 0},
                {"RadiusY", "nm", "radius in y direction", 0, +INF, 0},
                {"Height", "nm", "height = radius in z direction", 0, +INF, 0}}},
              P)
    , m_radius_x(m_P[0])
    , m_radius_y(m_P[1])
    , m_height(m_P[2]) {
    onChange();
}

FormFactorHemiEllipsoid::FormFactorHemiEllipsoid(double radius_x, double radius_y, double height)
    : FormFactorHemiEllipsoid(std::vector<double>{radius_x, radius_y, height}) {}

double FormFactorHemiEllipsoid::radialExtension() const {
    return (m_radius_x + m_radius_y) / 2.0;
}

//! Integrand for complex form factor.
complex_t FormFactorHemiEllipsoid::Integrand(double Z) const {
    double R = m_radius_x;
    double W = m_radius_y;
    double H = m_height;

    double Rz = R * std::sqrt(1.0 - Z * Z / (H * H));
    double Wz = W * std::sqrt(1.0 - Z * Z / (H * H));

    complex_t qxRz = m_q.x() * Rz;
    complex_t qyWz = m_q.y() * Wz;

    complex_t gamma = std::sqrt(qxRz * qxRz + qyWz * qyWz);
    complex_t J1_gamma_div_gamma = Math::Bessel::J1c(gamma);

    return Rz * Wz * J1_gamma_div_gamma * exp_I(m_q.z() * Z);
}

complex_t FormFactorHemiEllipsoid::evaluate_for_q(cvector_t q) const {
    m_q = q;
    double R = m_radius_x;
    double W = m_radius_y;
    double H = m_height;

    if (std::abs(m_q.mag()) <= std::numeric_limits<double>::epsilon())
        return M_TWOPI * R * W * H / 3.;
    return M_TWOPI * ComplexIntegrator().integrate([&](double Z) { return Integrand(Z); }, 0., H);
}

void FormFactorHemiEllipsoid::onChange() {
    m_shape = std::make_unique<TruncatedEllipsoid>(m_radius_x, m_radius_x, m_height, m_height, 0.0);
}
