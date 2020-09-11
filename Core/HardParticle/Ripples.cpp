// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/Ripples.cpp
//! @brief     Implements computations in namespace ripples.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/Ripples.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/Integrator.h"
#include "Core/Tools/MathFunctions.h"

complex_t ripples::factor_x_box(complex_t q, double r)
{
    return r * MathFunctions::sinc(q * r / 2.0);
}

complex_t ripples::factor_x_Gauss(complex_t q, double r)
{
    return r * exp(-q * r / 8.0);
}

complex_t ripples::factor_x_Lorentz(complex_t q, double r)
{
    return r / (1.0 + (q * r) * (q * r));
}

//! Complex form factor of rectangular ripple (bar).
complex_t ripples::profile_yz_bar(complex_t qy, complex_t qz, double width, double height)
{
    const complex_t qyWdiv2 = width * qy / 2.0;
    const complex_t qzHdiv2 = height * qz / 2.0;

    return height * width * exp_I(qzHdiv2) * MathFunctions::sinc(qyWdiv2)
           * MathFunctions::sinc(qzHdiv2);
}

//! Complex form factor of triangular ripple.
complex_t ripples::profile_yz_cosine(complex_t qy, complex_t qz, double width, double height)
{
    complex_t factor = width / M_PI;

    // analytical expressions for some particular cases
    if (qz == 0.) {
        if (qy == 0.)
            return factor * M_PI_2 * height;
        complex_t aaa = qy * width / (M_TWOPI);
        complex_t aaa2 = aaa * aaa;
        if (aaa2 == 1.)
            return factor * M_PI_4 * height;
        return factor * M_PI_2 * height * MathFunctions::sinc(qy * width * 0.5) / (1.0 - aaa2);
    }

    // numerical integration otherwise
    const complex_t ay = qy * width / M_TWOPI;
    const complex_t az = complex_t(0, 1) * qz * (height / 2);

    const auto integrand = [&](double u) -> complex_t {
        return sin(u) * exp(az * std::cos(u)) * (ay == 0. ? u : sin(ay * u) / ay);
    };
    complex_t integral = ComplexIntegrator().integrate(integrand, 0, M_PI);
    return factor * integral * exp(az) * (height / 2);
}

//! Complex form factor of triangular ripple.
complex_t ripples::profile_yz_triangular(complex_t qy, complex_t qz, double width, double height,
                                         double asymmetry)
{
    complex_t result;
    const complex_t factor = height * width;
    const complex_t qyW2 = qy * width * 0.5;
    const complex_t qyd = qy * asymmetry;
    const complex_t qzH = qz * height;
    const complex_t a = qzH + qyd;
    // dimensionless scale factors
    const double a_scale = std::abs(a);
    const double w_scale = std::abs(qyW2);

    if (w_scale < 1.e-5) {    // |q_y*W| << 1
        if (a_scale < 1e-5) { // |q_y*W| << 1 && |q_z*H + q_y*d| << 1
            // relative error is O((q_y*W)^2) and O((q_z*H + q_y*d)^2)
            result = exp_I(-qyd) * (0.5 + mul_I(a) / 6.);
        } else {
            // relative error is O((q_y*W)^2)
            result = exp_I(-qyd) * (1.0 + mul_I(a) - exp_I(a)) / (a * a);
        }
    } else {
        const complex_t gamma_p = (a + qyW2) * 0.5;
        const complex_t gamma_m = (a - qyW2) * 0.5;
        result = exp_I(gamma_m) * MathFunctions::sinc(gamma_p)
                 - exp_I(gamma_p) * MathFunctions::sinc(gamma_m);
        result = mul_I(exp_I(-qyd) * result / (qyW2 * 2.));
    }
    return factor * result;
}
