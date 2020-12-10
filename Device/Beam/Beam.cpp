//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Beam/Beam.cpp
//! @brief     Implements class Beam.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Beam/Beam.h"
#include "Base/Math/Constants.h"
#include "Base/Types/Complex.h"
#include "Base/Utils/Assert.h"
#include "Device/Beam/FootprintGauss.h"
#include "Param/Base/RealParameter.h"

// Allow for 90 degrees by adding a relatively small constant to pi/2
static constexpr double INCLINATION_LIMIT = M_PI_2 + 1e-10;

Beam::Beam(double intensity, double wavelength, const Direction& direction)
    : m_intensity(intensity)
    , m_wavelength(wavelength)
    // , m_direction(direction)
    , m_alpha(direction.alpha())
    , m_phi(direction.phi()) {
    setName("Beam");
    registerParameter("Intensity", &m_intensity).setNonnegative();
    registerParameter("Wavelength", &m_wavelength).setUnit("nm").setNonnegative();
    registerParameter("InclinationAngle", &m_alpha).setUnit("rad").setLimited(0, INCLINATION_LIMIT);
    registerParameter("AzimuthalAngle", &m_phi).setUnit("rad").setLimited(-M_PI_2, M_PI_2);
    registerVector("BlochVector", &m_bloch_vector, "");
}

Beam Beam::horizontalBeam() {
    return Beam(1.0, 1.0, {0, 0});
}

Beam::Beam(const Beam& other) : Beam(other.m_intensity, other.m_wavelength, other.direction()) {
    m_bloch_vector = other.m_bloch_vector;
    setName(other.getName());
    if (other.m_shape_factor) {
        m_shape_factor.reset(other.m_shape_factor->clone());
        registerChild(m_shape_factor.get());
    }
}

Beam& Beam::operator=(const Beam& other) {
    m_intensity = other.m_intensity;
    m_wavelength = other.m_wavelength;
    // m_direction = other.m_direction;
    m_alpha = other.m_alpha;
    m_phi = other.m_phi;
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

kvector_t Beam::getCentralK() const {
    return M_TWOPI / m_wavelength * Direction(-direction().alpha(), direction().phi()).vector();
}

void Beam::setWavelength(double wavelength) {
    if (wavelength <= 0.0)
        throw std::runtime_error(
            "Beam::setCentralK() -> Error. Wavelength can't be negative or zero.");
    m_wavelength = wavelength;
}

void Beam::setDirection(const Direction& direction) {
    if (direction.alpha() < 0.0)
        throw std::runtime_error(
            "Beam::setCentralK() -> Error. Inclination angle alpha_i can't be negative.");
    // m_direction = direction;
    m_alpha = direction.alpha();
    m_phi = direction.phi();
}

void Beam::setInclination(const double alpha) {
    m_alpha = alpha;
}

const IFootprintFactor* Beam::footprintFactor() const {
    return m_shape_factor.get();
}

void Beam::setFootprintFactor(const IFootprintFactor& shape_factor) {
    m_shape_factor.reset(shape_factor.clone());
    registerChild(m_shape_factor.get());
}

void Beam::setWidthRatio(double width_ratio) {
    if (!m_shape_factor)
        throw std::runtime_error("Error in Beam::setWidthRatio: footprint factor is nullptr. "
                                 "Probably, you have forgotten to initialize it.");
    m_shape_factor->setWidthRatio(width_ratio);
}

void Beam::setPolarization(const kvector_t bloch_vector) {
    if (bloch_vector.mag() > 1.0) {
        throw std::runtime_error(
            "Beam::setPolarization: "
            "The given Bloch vector cannot represent a real physical ensemble");
    }
    m_bloch_vector = bloch_vector;
}

kvector_t Beam::getBlochVector() const {
    return m_bloch_vector;
}

Eigen::Matrix2cd Beam::getPolarization() const {
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

std::vector<const INode*> Beam::getChildren() const {
    if (m_shape_factor)
        return {m_shape_factor.get()};
    return {};
}
