// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/SphericalPixel.cpp
//! @brief     Implements class SphericalPixel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/SphericalPixel.h"
#include "Core/Binning/Bin.h"

SphericalPixel::SphericalPixel(const Bin1D& alpha_bin, const Bin1D& phi_bin)
    : m_alpha(alpha_bin.m_lower), m_phi(phi_bin.m_lower), m_dalpha(alpha_bin.getBinSize()),
      m_dphi(phi_bin.getBinSize())
{
    auto solid_angle_value = std::abs(m_dphi * (std::sin(m_alpha + m_dalpha) - std::sin(m_alpha)));
    m_solid_angle = solid_angle_value <= 0.0 ? 1.0 : solid_angle_value;
}

SphericalPixel* SphericalPixel::clone() const
{
    return new SphericalPixel(*this);
}

SphericalPixel* SphericalPixel::createZeroSizePixel(double x, double y) const
{
    double phi = m_phi + x * m_dphi;
    double alpha = m_alpha + y * m_dalpha;
    Bin1D alpha_bin(alpha, alpha);
    Bin1D phi_bin(phi, phi);
    return new SphericalPixel(alpha_bin, phi_bin);
}

kvector_t SphericalPixel::getK(double x, double y, double wavelength) const
{
    double phi = m_phi + x * m_dphi;
    double alpha = m_alpha + y * m_dalpha;
    return vecOfLambdaAlphaPhi(wavelength, alpha, phi);
}

double SphericalPixel::getIntegrationFactor(double /* x */, double y) const
{
    if (m_dalpha == 0.0)
        return 1.0;
    double alpha = m_alpha + y * m_dalpha;
    return std::cos(alpha) * m_dalpha / (std::sin(m_alpha + m_dalpha) - std::sin(m_alpha));
}

double SphericalPixel::getSolidAngle() const
{
    return m_solid_angle;
}
