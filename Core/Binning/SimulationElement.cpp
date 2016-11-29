// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/SimulationElement.cpp
//! @brief     Implements class SimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SimulationElement.h"
#include "IPixelMap.h"
#include "MathConstants.h"
#include <vector>

SimulationElement::SimulationElement(double wavelength, double alpha_i, double phi_i,
                                     std::unique_ptr<IPixelMap> pixelmap)
    : m_wavelength(wavelength)
    , m_alpha_i(alpha_i)
    , m_phi_i(phi_i)
    , m_intensity(0.0)
    , mP_pixel_map(std::move(pixelmap))
    , m_contains_specular(false)
{
    initPolarization();
}

SimulationElement::SimulationElement(const SimulationElement& other)
    : m_wavelength(other.m_wavelength), m_alpha_i(other.m_alpha_i), m_phi_i(other.m_phi_i)
    , m_intensity(other.m_intensity), m_contains_specular(other.m_contains_specular)
{
    mP_pixel_map.reset(other.mP_pixel_map->clone());
    m_polarization = other.m_polarization;
    m_analyzer_operator = other.m_analyzer_operator;
}

SimulationElement::SimulationElement(const SimulationElement& other, double x, double y)
    : m_wavelength(other.m_wavelength), m_alpha_i(other.m_alpha_i), m_phi_i(other.m_phi_i)
    , m_intensity(other.m_intensity), m_contains_specular(other.m_contains_specular)
{
    mP_pixel_map.reset(other.mP_pixel_map->createZeroSizeMap(x, y));
    m_polarization = other.m_polarization;
    m_analyzer_operator = other.m_analyzer_operator;
}

SimulationElement::SimulationElement(SimulationElement&& other) noexcept
    : m_wavelength(other.m_wavelength)
    , m_alpha_i(other.m_alpha_i)
    , m_phi_i(other.m_phi_i)
    , m_intensity(other.m_intensity)
    , m_polarization(std::move(other.m_polarization))
    , m_analyzer_operator(std::move(other.m_analyzer_operator))
    , mP_pixel_map(std::move(other.mP_pixel_map))
    , m_contains_specular(other.m_contains_specular)
{
}

SimulationElement::~SimulationElement() {}

SimulationElement& SimulationElement::operator=(const SimulationElement &other)
{
    if (this != &other) {
        SimulationElement tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

kvector_t SimulationElement::getKi() const
{
    return vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
}

kvector_t SimulationElement::getMeanKf() const
{
    return mP_pixel_map->getK(0.5, 0.5, m_wavelength);
}

//! Returns outgoing wavevector Kf for in-pixel coordinates x,y.
//! In-pixel coordinates take values from 0 to 1.
kvector_t SimulationElement::getKf(double x, double y) const {
    return mP_pixel_map->getK(x, y, m_wavelength);
}

kvector_t SimulationElement::getMeanQ() const
{
    return getKi() - getMeanKf();
}

//! Returns scattering vector Q, with Kf determined from in-pixel coordinates x,y.
//! In-pixel coordinates take values from 0 to 1.
kvector_t SimulationElement::getQ(double x, double y) const
{
    return getKi() - mP_pixel_map->getK(x, y, m_wavelength);
}

void SimulationElement::swapContent(SimulationElement &other)
{
    std::swap(m_wavelength, other.m_wavelength);
    std::swap(m_alpha_i, other.m_alpha_i);
    std::swap(m_phi_i, other.m_phi_i);
    std::swap(m_intensity, other.m_intensity);
    std::swap(m_polarization, other.m_polarization);
    std::swap(m_analyzer_operator, other.m_analyzer_operator);
    std::swap(mP_pixel_map, other.mP_pixel_map);
    std::swap(m_contains_specular, other.m_contains_specular);
}

void SimulationElement::initPolarization()
{
    m_polarization = Eigen::Matrix2cd::Identity();
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}

double SimulationElement::getAlpha(double x, double y) const
{
    return M_PI_2 - getKf(x,y).theta();
}

double SimulationElement::getPhi(double x, double y) const
{
    return getKf(x,y).phi();
}

bool SimulationElement::containsSpecularWavevector() const
{
    return m_contains_specular;
}

void SimulationElement::setSpecular(bool contains_specular)
{
    m_contains_specular = contains_specular;
}

double SimulationElement::getIntegrationFactor(double x, double y) const {
    return mP_pixel_map->getIntegrationFactor(x, y);
}

double SimulationElement::getSolidAngle() const {
    return mP_pixel_map->getSolidAngle();
}

void addElementsWithWeight(std::vector<SimulationElement>::const_iterator first,
                           std::vector<SimulationElement>::const_iterator last,
                           std::vector<SimulationElement>::iterator result, double weight)
{
    for (std::vector<SimulationElement>::const_iterator it = first; it != last; ++it, ++result)
        result->addIntensity(it->getIntensity() * weight);
}

void setAllElementIntensities(std::vector<SimulationElement>::iterator first,
                              std::vector<SimulationElement>::iterator last, double intensity)
{
    for (std::vector<SimulationElement>::iterator it = first; it != last; ++it)
        it->setIntensity(intensity);
}
