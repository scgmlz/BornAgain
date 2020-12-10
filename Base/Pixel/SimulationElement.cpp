//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Pixel/SimulationElement.cpp
//! @brief     Implements class SimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Base/Pixel/SimulationElement.h"
#include "Base/Pixel/IPixel.h"
#include "Base/Vector/Direction.h"

SimulationElement::SimulationElement(double wavelength, double alpha_i, double phi_i,
                                     std::unique_ptr<IPixel> pixel,
                                     const Eigen::Matrix2cd& beam_polarization,
                                     const Eigen::Matrix2cd& analyzer, bool isSpecular_)
    : m_polarization(beam_polarization, analyzer)
    , m_wavelength(wavelength)
    , m_alpha_i(alpha_i)
    , m_phi_i(phi_i)
    , m_k_i(vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i))
    , m_mean_kf(pixel->getK(0.5, 0.5, m_wavelength))
    , m_pixel(std::move(pixel))
    , m_is_specular(isSpecular_)
    , m_intensity(0.0) {}

SimulationElement::SimulationElement(const SimulationElement& other)
    : m_polarization(other.m_polarization)
    , m_wavelength(other.m_wavelength)
    , m_alpha_i(other.m_alpha_i)
    , m_phi_i(other.m_phi_i)
    , m_k_i(other.m_k_i)
    , m_mean_kf(other.m_mean_kf)
    , m_pixel(std::move(other.m_pixel->clone()))
    , m_is_specular(other.m_is_specular)
    , m_intensity(other.m_intensity) {}

SimulationElement::SimulationElement(SimulationElement&&) = default;

SimulationElement::~SimulationElement() = default;

SimulationElement SimulationElement::pointElement(double x, double y) const {
    return {m_wavelength,
            m_alpha_i,
            m_phi_i,
            std::unique_ptr<IPixel>(m_pixel->createZeroSizePixel(x, y)), // TODO simplify
            m_polarization.getPolarization(),
            m_polarization.getAnalyzerOperator(),
            m_is_specular};
}

kvector_t SimulationElement::getKi() const {
    return m_k_i;
}

kvector_t SimulationElement::getMeanKf() const {
    return m_mean_kf;
}

//! Returns outgoing wavevector Kf for in-pixel coordinates x,y.
//! In-pixel coordinates take values from 0 to 1.
kvector_t SimulationElement::getKf(double x, double y) const {
    return m_pixel->getK(x, y, m_wavelength);
}

kvector_t SimulationElement::meanQ() const {
    return getKi() - getMeanKf();
}

//! Returns scattering vector Q, with Kf determined from in-pixel coordinates x,y.
//! In-pixel coordinates take values from 0 to 1.
kvector_t SimulationElement::getQ(double x, double y) const {
    return getKi() - m_pixel->getK(x, y, m_wavelength);
}

double SimulationElement::getAlpha(double x, double y) const {
    return M_PI_2 - getKf(x, y).theta();
}

double SimulationElement::getPhi(double x, double y) const {
    return getKf(x, y).phi();
}

double SimulationElement::integrationFactor(double x, double y) const {
    return m_pixel->integrationFactor(x, y);
}

double SimulationElement::solidAngle() const {
    return m_pixel->solidAngle();
}
