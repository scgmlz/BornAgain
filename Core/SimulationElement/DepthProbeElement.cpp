// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/DepthProbeElement.cpp
//! @brief     Implements class DepthProbeElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/SimulationElement/DepthProbeElement.h"
#include "Core/Binning/IAxis.h"

const double phi_i_0 = 0.0;

DepthProbeElement::DepthProbeElement(double wavelength, double alpha_i, const IAxis* z_positions)
    : m_wavelength(wavelength), m_alpha_i(alpha_i), m_z_positions(z_positions),
      m_calculation_flag(true)
{
    if (!z_positions)
        throw std::runtime_error(
            "Error in DepthProbeElement::DepthProbeElement: z positions are not specified");
    m_intensities.resize(z_positions->size(), 0.0);
}

DepthProbeElement::DepthProbeElement(const DepthProbeElement& other)
    : m_wavelength(other.m_wavelength), m_alpha_i(other.m_alpha_i),
      m_intensities(other.m_intensities), m_z_positions(other.m_z_positions),
      m_calculation_flag(other.m_calculation_flag)
{
}

DepthProbeElement::DepthProbeElement(DepthProbeElement&& other) noexcept
    : m_wavelength(other.m_wavelength), m_alpha_i(other.m_alpha_i),
      m_intensities(std::move(other.m_intensities)), m_z_positions(other.m_z_positions),
      m_calculation_flag(other.m_calculation_flag)
{
}

DepthProbeElement::~DepthProbeElement() = default;

DepthProbeElement& DepthProbeElement::operator=(const DepthProbeElement& other)
{
    if (this != &other) {
        DepthProbeElement tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

kvector_t DepthProbeElement::getKi() const
{
    return vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, phi_i_0);
}

void DepthProbeElement::swapContent(DepthProbeElement& other)
{
    std::swap(m_wavelength, other.m_wavelength);
    std::swap(m_alpha_i, other.m_alpha_i);
    m_intensities.swap(other.m_intensities);
    std::swap(m_z_positions, other.m_z_positions);
    std::swap(m_calculation_flag, other.m_calculation_flag);
}
