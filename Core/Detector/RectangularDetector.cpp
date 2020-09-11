// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/RectangularDetector.cpp
//! @brief     Implements class RectangularDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/RectangularDetector.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Detector/IDetectorResolution.h"
#include "Core/Detector/RectangularPixel.h"
#include "Core/Detector/RegionOfInterest.h"
#include "Core/SimulationElement/SimulationElement.h"

RectangularDetector::RectangularDetector(size_t nxbins, double width, size_t nybins, double height)
    : m_u0(0.0), m_v0(0.0), m_direction(kvector_t(0.0, -1.0, 0.0)), m_distance(0.0),
      m_dbeam_u0(0.0), m_dbeam_v0(0.0), m_detector_arrangement(GENERIC)
{
    setDetectorParameters(nxbins, 0.0, width, nybins, 0.0, height);
    setName("RectangularDetector");
}

RectangularDetector::RectangularDetector(const RectangularDetector& other)
    : IDetector2D(other), m_normal_to_detector(other.m_normal_to_detector), m_u0(other.m_u0),
      m_v0(other.m_v0), m_direction(other.m_direction), m_distance(other.m_distance),
      m_dbeam_u0(other.m_dbeam_u0), m_dbeam_v0(other.m_dbeam_v0),
      m_detector_arrangement(other.m_detector_arrangement), m_u_unit(other.m_u_unit),
      m_v_unit(other.m_v_unit)
{
    setName("RectangularDetector");
}

RectangularDetector::~RectangularDetector() {}

RectangularDetector* RectangularDetector::clone() const
{
    return new RectangularDetector(*this);
}

void RectangularDetector::init(const Beam& beam)
{
    double alpha_i = beam.getAlpha();
    kvector_t central_k = beam.getCentralK();
    initNormalVector(central_k);
    initUandV(alpha_i);
}

void RectangularDetector::setPosition(const kvector_t normal_to_detector, double u0, double v0,
                                      const kvector_t direction)
{
    m_detector_arrangement = GENERIC;
    m_normal_to_detector = normal_to_detector;
    m_u0 = u0;
    m_v0 = v0;
    m_direction = direction;
}

void RectangularDetector::setPerpendicularToSampleX(double distance, double u0, double v0)
{
    m_detector_arrangement = PERPENDICULAR_TO_SAMPLE;
    setDistanceAndOffset(distance, u0, v0);
}

void RectangularDetector::setPerpendicularToDirectBeam(double distance, double u0, double v0)
{
    m_detector_arrangement = PERPENDICULAR_TO_DIRECT_BEAM;
    setDistanceAndOffset(distance, u0, v0);
}

void RectangularDetector::setPerpendicularToReflectedBeam(double distance, double u0, double v0)
{
    m_detector_arrangement = PERPENDICULAR_TO_REFLECTED_BEAM;
    setDistanceAndOffset(distance, u0, v0);
}

void RectangularDetector::setDirectBeamPosition(double u0, double v0)
{
    m_detector_arrangement = PERPENDICULAR_TO_REFLECTED_BEAM_DPOS;
    m_dbeam_u0 = u0;
    m_dbeam_v0 = v0;
}

double RectangularDetector::getWidth() const
{
    const IAxis& axis = getAxis(0);
    return axis.getMax() - axis.getMin();
}

double RectangularDetector::getHeight() const
{
    const IAxis& axis = getAxis(1);
    return axis.getMax() - axis.getMin();
}

size_t RectangularDetector::getNbinsX() const
{
    return getAxis(0).size();
}

size_t RectangularDetector::getNbinsY() const
{
    return getAxis(1).size();
}

kvector_t RectangularDetector::getNormalVector() const
{
    return m_normal_to_detector;
}

double RectangularDetector::getU0() const
{
    return m_u0;
}

double RectangularDetector::getV0() const
{
    return m_v0;
}

kvector_t RectangularDetector::getDirectionVector() const
{
    return m_direction;
}

double RectangularDetector::getDistance() const
{
    return m_distance;
}

double RectangularDetector::getDirectBeamU0() const
{
    return m_dbeam_u0;
}

double RectangularDetector::getDirectBeamV0() const
{
    return m_dbeam_v0;
}

RectangularDetector::EDetectorArrangement RectangularDetector::getDetectorArrangment() const
{
    return m_detector_arrangement;
}

AxesUnits RectangularDetector::defaultAxesUnits() const
{
    return AxesUnits::MM;
}

RectangularPixel* RectangularDetector::regionOfInterestPixel() const
{
    const IAxis& u_axis = getAxis(0);
    const IAxis& v_axis = getAxis(1);
    double u_min, v_min, width, height;
    auto p_roi = regionOfInterest();
    if (p_roi) {
        u_min = p_roi->getXlow();
        v_min = p_roi->getYlow();
        width = p_roi->getXup() - p_roi->getXlow();
        height = p_roi->getYup() - p_roi->getYlow();
    } else {
        u_min = u_axis.getMin();
        v_min = v_axis.getMin();
        width = getWidth();
        height = getHeight();
    }
    const kvector_t corner_position(m_normal_to_detector + (u_min - m_u0) * m_u_unit
                                    + (v_min - m_v0) * m_v_unit);
    const kvector_t uaxis_vector = width * m_u_unit;
    const kvector_t vaxis_vector = height * m_v_unit;
    return new RectangularPixel(corner_position, uaxis_vector, vaxis_vector);
}

IPixel* RectangularDetector::createPixel(size_t index) const
{
    const IAxis& u_axis = getAxis(0);
    const IAxis& v_axis = getAxis(1);
    const size_t u_index = axisBinIndex(index, 0);
    const size_t v_index = axisBinIndex(index, 1);

    const Bin1D u_bin = u_axis.getBin(u_index);
    const Bin1D v_bin = v_axis.getBin(v_index);
    const kvector_t corner_position(m_normal_to_detector + (u_bin.m_lower - m_u0) * m_u_unit
                                    + (v_bin.m_lower - m_v0) * m_v_unit);
    const kvector_t width = u_bin.getBinSize() * m_u_unit;
    const kvector_t height = v_bin.getBinSize() * m_v_unit;
    return new RectangularPixel(corner_position, width, height);
}

std::string RectangularDetector::axisName(size_t index) const
{
    switch (index) {
    case 0:
        return "u";
    case 1:
        return "v";
    default:
        throw Exceptions::LogicErrorException(
            "RectangularDetector::getAxisName(size_t index) -> Error! index > 1");
    }
}

size_t RectangularDetector::getIndexOfSpecular(const Beam& beam) const
{
    if (dimension() != 2)
        return totalSize();
    double alpha = beam.getAlpha();
    double phi = beam.getPhi();
    kvector_t k_spec = vecOfLambdaAlphaPhi(beam.getWavelength(), alpha, phi);
    kvector_t normal_unit = m_normal_to_detector.unit();
    double kd = k_spec.dot(normal_unit);
    if (kd <= 0.0)
        return totalSize();
    kvector_t k_orth = (k_spec / kd - normal_unit) * m_distance;
    double u = k_orth.dot(m_u_unit) + m_u0;
    double v = k_orth.dot(m_v_unit) + m_v0;
    const IAxis& u_axis = getAxis(0);
    const IAxis& v_axis = getAxis(1);
    if (u_axis.contains(u) && v_axis.contains(v))
        return getGlobalIndex(u_axis.findClosestIndex(u), v_axis.findClosestIndex(v));
    return totalSize();
}

void RectangularDetector::setDistanceAndOffset(double distance, double u0, double v0)
{
    if (distance <= 0.0) {
        std::ostringstream message;
        message << "RectangularDetector::setPerpendicularToSample() -> Error. "
                << "Distance to sample can't be negative or zero";
        throw Exceptions::LogicErrorException(message.str());
    }
    m_distance = distance;
    m_u0 = u0;
    m_v0 = v0;
}

void RectangularDetector::initNormalVector(const kvector_t central_k)
{
    kvector_t central_k_unit = central_k.unit();

    if (m_detector_arrangement == GENERIC) {
        // do nothing
    }

    else if (m_detector_arrangement == PERPENDICULAR_TO_SAMPLE) {
        m_normal_to_detector = kvector_t(m_distance, 0.0, 0.0);
    }

    else if (m_detector_arrangement == PERPENDICULAR_TO_DIRECT_BEAM) {
        m_normal_to_detector = m_distance * central_k_unit;
    }

    else if (m_detector_arrangement == PERPENDICULAR_TO_REFLECTED_BEAM) {
        m_normal_to_detector = m_distance * central_k_unit;
        m_normal_to_detector.setZ(-m_normal_to_detector.z());
    }

    else if (m_detector_arrangement == PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
        m_normal_to_detector = m_distance * central_k_unit;
        m_normal_to_detector.setZ(-m_normal_to_detector.z());
    }

    else {
        throw Exceptions::LogicErrorException(
            "RectangularDetector::init() -> Unknown detector arrangement");
    }
}

void RectangularDetector::initUandV(double alpha_i)
{
    double d2 = m_normal_to_detector.dot(m_normal_to_detector);
    kvector_t u_direction =
        d2 * m_direction - m_direction.dot(m_normal_to_detector) * m_normal_to_detector;
    m_u_unit = u_direction.unit();
    m_v_unit = m_u_unit.cross(m_normal_to_detector).unit();

    if (m_detector_arrangement == PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
        kvector_t z(0.0, 0.0, 1.0);
        kvector_t normal_unit = m_normal_to_detector.unit();
        kvector_t zp = z - z.dot(normal_unit) * normal_unit;
        double uz = zp.dot(m_u_unit) / zp.mag();
        double vz = zp.dot(m_v_unit) / zp.mag();
        m_u0 = m_dbeam_u0 + m_distance * std::tan(2 * alpha_i) * uz;
        m_v0 = m_dbeam_v0 + m_distance * std::tan(2 * alpha_i) * vz;
    }
}
