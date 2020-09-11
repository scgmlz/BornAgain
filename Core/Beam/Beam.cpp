// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/Beam.cpp
//! @brief     Implements class Beam.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Beam/Beam.h"
#include "Core/Basics/Assert.h"
#include "Core/Basics/Complex.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Beam/FootprintGauss.h"
#include "Core/Parametrization/RealParameter.h"

// Allow for 90 degrees by adding a relatively small constant to pi/2
static constexpr double INCLINATION_LIMIT = M_PI_2 + 1e-10;

Beam::Beam(double wavelength, double alpha, double phi, double intensity)
    : m_wavelength(wavelength), m_alpha(alpha), m_phi(phi), m_intensity(intensity)
{
    setName("Beam");
    registerParameter("Wavelength", &m_wavelength).setUnit("nm").setNonnegative();
    registerParameter("InclinationAngle", &m_alpha).setUnit("rad").setLimited(0, INCLINATION_LIMIT);
    registerParameter("AzimuthalAngle", &m_phi).setUnit("rad").setLimited(-M_PI_2, M_PI_2);
    registerParameter("Intensity", &m_intensity).setNonnegative();
    registerVector("BlochVector", &m_bloch_vector, "");
}

Beam Beam::horizontalBeam()
{
    return Beam(1.0, 0.0, 0.0, 1.0);
}

Beam::Beam(const Beam& other)
    : Beam(other.m_wavelength, other.m_alpha, other.m_phi, other.m_intensity)
{
    m_bloch_vector = other.m_bloch_vector;
    setName(other.getName());
    if (other.m_shape_factor) {
        m_shape_factor.reset(other.m_shape_factor->clone());
        registerChild(m_shape_factor.get());
    }
}

Beam& Beam::operator=(const Beam& other)
{
    m_wavelength = other.m_wavelength;
    m_alpha = other.m_alpha;
    m_phi = other.m_phi;
    m_intensity = other.m_intensity;
    m_bloch_vector = other.m_bloch_vector;
    setName(other.getName());
    if (other.m_shape_factor) {
        m_shape_factor.reset(other.m_shape_factor->clone());
        registerChild(m_shape_factor.get());
    } else
        m_shape_factor.release();
    return *this;
}

Beam::~Beam() = default;

kvector_t Beam::getCentralK() const
{
    return vecOfLambdaAlphaPhi(m_wavelength, -m_alpha, m_phi);
}

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

const IFootprintFactor* Beam::footprintFactor() const
{
    return m_shape_factor.get();
}

void Beam::setFootprintFactor(const IFootprintFactor& shape_factor)
{
    m_shape_factor.reset(shape_factor.clone());
    registerChild(m_shape_factor.get());
}

void Beam::setWidthRatio(double width_ratio)
{
    if (!m_shape_factor)
        throw std::runtime_error("Error in Beam::setWidthRatio: footprint factor is nullptr. "
                                 "Probably, you have forgotten to initialize it.");
    m_shape_factor->setWidthRatio(width_ratio);
}

void Beam::setPolarization(const kvector_t bloch_vector)
{
    if (bloch_vector.mag() > 1.0) {
        throw Exceptions::ClassInitializationException(
            "Beam::setPolarization: "
            "The given Bloch vector cannot represent a real physical ensemble");
    }
    m_bloch_vector = bloch_vector;
}

kvector_t Beam::getBlochVector() const
{
    return m_bloch_vector;
}

Eigen::Matrix2cd Beam::getPolarization() const
{
    Eigen::Matrix2cd result;
    double x = m_bloch_vector.x();
    double y = m_bloch_vector.y();
    double z = m_bloch_vector.z();
    result(0, 0) = (1.0 + z) / 2.0;
    result(0, 1) = complex_t(x, -y) / 2.0;
    result(1, 0) = complex_t(x, y) / 2.0;
    result(1, 1) = (1.0 - z) / 2.0;
    return result;
}

std::vector<const INode*> Beam::getChildren() const
{
    if (m_shape_factor)
        return {m_shape_factor.get()};
    return {};
}
