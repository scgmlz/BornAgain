// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionHardDisk.cpp
//! @brief     Implements class InterferenceFunctionHardDisk.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/InterferenceFunctionHardDisk.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Tools/Integrator.h"
#include "Core/Tools/MathFunctions.h"
#include <cmath>

namespace
{
static const double p = 7.0 / 3.0 - 4.0 * std::sqrt(3.0) / M_PI;
double Czero(double packing); // TODO ASAP why these variables?
double S2(double packing);
double W2(double x);
} // namespace

InterferenceFunctionHardDisk::InterferenceFunctionHardDisk(double radius, double density,
                                                           double position_var)
    : IInterferenceFunction(position_var), m_radius(radius), m_density(density)
{
    setName("InterferenceHardDisk");
    if (m_radius < 0.0 || m_density < 0.0 || packingRatio() > 0.65)
        throw std::runtime_error("InterferenceFunctionHardDisk::validateParameters: "
                                 "radius and density must be positive and packing ratio between "
                                 "0 and 0.65");
    registerParameter("Radius", &m_radius).setUnit("nm").setNonnegative();
    registerParameter("TotalParticleDensity", &m_density).setUnit("nm").setNonnegative();
}

InterferenceFunctionHardDisk* InterferenceFunctionHardDisk::clone() const
{
    auto* ret = new InterferenceFunctionHardDisk(m_radius, m_density, m_position_var);
    return ret;
}

double InterferenceFunctionHardDisk::getParticleDensity() const
{
    return m_density;
}

double InterferenceFunctionHardDisk::radius() const
{
    return m_radius;
}

double InterferenceFunctionHardDisk::density() const
{
    return m_density;
}

double InterferenceFunctionHardDisk::iff_without_dw(const kvector_t q) const
{
    double qx = q.x();
    double qy = q.y();
    m_q = 2.0 * std::sqrt(qx * qx + qy * qy) * m_radius;
    m_packing = packingRatio();
    m_c_zero = Czero(m_packing);
    m_s2 = S2(m_packing);
    double c_q =
        2.0 * M_PI
        * RealIntegrator().integrate([&](double x) -> double { return integrand(x); }, 0.0, 1.0);
    double rho = 4.0 * m_packing / M_PI;
    return 1.0 / (1.0 - rho * c_q);
}

double InterferenceFunctionHardDisk::packingRatio() const
{
    return M_PI * m_radius * m_radius * m_density;
}

double InterferenceFunctionHardDisk::integrand(double x) const
{
    double cx = m_c_zero * (1.0 + 4.0 * m_packing * (W2(x / 2.0) - 1.0) + m_s2 * x);
    return x * cx * MathFunctions::Bessel_J0(m_q * x);
}

namespace
{
double Czero(double packing)
{
    double numerator = 1.0 + packing + 3.0 * p * packing * packing - p * std::pow(packing, 3);
    double denominator = std::pow(1.0 - packing, 3);
    return -numerator / denominator;
}

double S2(double packing)
{
    double factor = 3.0 * packing * packing / 8.0;
    double numerator = 8.0 * (1.0 - 2.0 * p) + (25.0 - 9.0 * p) * p * packing
                       - (7.0 - 3.0 * p) * p * packing * packing;
    double denominator = 1.0 + packing + 3.0 * p * packing * packing - p * std::pow(packing, 3);
    return factor * numerator / denominator;
}

double W2(double x)
{
    return 2.0 * (std::acos(x) - x * std::sqrt(1.0 - x * x)) / M_PI;
}
} // namespace
