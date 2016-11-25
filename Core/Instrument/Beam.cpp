// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/Beam.cpp
//! @brief     Implements class Beam.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Beam.h"
#include "BornAgainNamespace.h"
#include "Complex.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "RealParameter.h"

Beam::Beam() : m_wavelength(1.0), m_alpha(0.0), m_phi(0.0), m_intensity(0.0)
{
    setName(BornAgain::BeamType);
    init_parameters();
    initPolarization();
}

Beam::Beam(const Beam& other)
    : IParameterized()
    , m_wavelength(other.m_wavelength)
    , m_alpha(other.m_alpha)
    , m_phi(other.m_phi)
    , m_intensity(other.m_intensity)
    , m_polarization(other.m_polarization)
{
    setName(other.getName());
    init_parameters();
}

void Beam::init_parameters()
{
    registerParameter(BornAgain::Intensity, &m_intensity).setNonnegative();
    registerParameter(BornAgain::Wavelength, &m_wavelength).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Inclination, &m_alpha).setUnit("rad").setLimited(0, M_PI_2);
    registerParameter(BornAgain::Azimuth, &m_phi).setUnit("rad").setLimited(-M_PI_2, M_PI_2);
}

Beam& Beam::operator=(const Beam& other)
{
    if (this != &other) {
        Beam tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

kvector_t Beam::getCentralK() const { return vecOfLambdaAlphaPhi(m_wavelength, -m_alpha, m_phi); }

void Beam::setCentralK(double wavelength, double alpha_i, double phi_i)
{
    if (wavelength <= 0.0)
        throw Exceptions::ClassInitializationException(
            "Beam::setCentralK() -> Error. Wavelength can't be negative or zero.");
    if (alpha_i < 0.0)
        throw Exceptions::ClassInitializationException(
            "Beam::setCentralK() -> Error. Inclination angle alpha_i can't be negative.");
    m_wavelength = wavelength;
    m_alpha = alpha_i;
    m_phi = phi_i;
}

void Beam::setPolarization(const kvector_t bloch_vector)
{
    if (bloch_vector.mag() > 1.0)
        throw Exceptions::ClassInitializationException(
            "Beam::setPolarization: "
            "The given Bloch vector cannot represent a real physical ensemble");
    m_polarization = calculatePolarization(bloch_vector);
}

Eigen::Matrix2cd Beam::calculatePolarization(const kvector_t bloch_vector) const
{
    Eigen::Matrix2cd result;
    double x = bloch_vector.x();
    double y = bloch_vector.y();
    double z = bloch_vector.z();
    result(0, 0) = (1.0 + z) / 2.0;
    result(0, 1) = complex_t(x, -y) / 2.0;
    result(1, 0) = complex_t(x, y) / 2.0;
    result(1, 1) = (1.0 - z) / 2.0;
    return result;
}

void Beam::swapContent(Beam& other)
{
    std::swap(m_wavelength, other.m_wavelength);
    std::swap(m_alpha, other.m_alpha);
    std::swap(m_phi, other.m_phi);
    std::swap(m_intensity, other.m_intensity);
    std::swap(m_polarization, other.m_polarization);
}

void Beam::initPolarization()
{
    kvector_t zero;
    setPolarization(zero);
}

void Beam::print(std::ostream& ostr) const
{
    ostr << "Beam: '" << getName() << "' " << getParameterPool();
}
