// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/RectangularDetector.cpp
//! @brief     Implements class RectangularDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RectangularDetector.h"
#include "Beam.h"
#include "BornAgainNamespace.h"
#include "IDetectorResolution.h"
#include "SimulationElement.h"
#include "MathConstants.h"
#include "Units.h"

RectangularDetector::RectangularDetector(int nxbins, double width, int nybins, double height)
    : m_u0(0.0)
    , m_v0(0.0)
    , m_direction(kvector_t(0.0, -1.0, 0.0))
    , m_distance(0.0)
    , m_dbeam_u0(0.0)
    , m_dbeam_v0(0.0)
    , m_detector_arrangement(GENERIC)
{
    setDetectorParameters(nxbins, 0.0, width, nybins, 0.0, height);
    setName(BornAgain::RectangularDetectorType);
    init_parameters();
}

RectangularDetector::RectangularDetector(const RectangularDetector& other)
    : IDetector2D(other)
    , m_normal_to_detector(other.m_normal_to_detector)
    , m_u0(other.m_u0)
    , m_v0(other.m_v0)
    , m_direction(other.m_direction)
    , m_distance(other.m_distance)
    , m_dbeam_u0(other.m_dbeam_u0)
    , m_dbeam_v0(other.m_dbeam_v0)
    , m_detector_arrangement(other.m_detector_arrangement)
    , m_u_unit(other.m_u_unit)
    , m_v_unit(other.m_v_unit)
{
    setName(BornAgain::RectangularDetectorType);
    init_parameters();
}

RectangularDetector::~RectangularDetector() {}

RectangularDetector *RectangularDetector::clone() const
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

void RectangularDetector::setPosition(const kvector_t normal_to_detector,
                                      double u0, double v0, const kvector_t direction)
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

IPixelMap *RectangularDetector::createPixelMap(size_t index) const
{
    const IAxis& u_axis = getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis& v_axis = getAxis(BornAgain::Y_AXIS_INDEX);
    size_t u_index = getAxisBinIndex(index, BornAgain::X_AXIS_INDEX);
    size_t v_index = getAxisBinIndex(index, BornAgain::Y_AXIS_INDEX);

    Bin1D u_bin = u_axis.getBin(u_index);
    Bin1D v_bin = v_axis.getBin(v_index);
    kvector_t corner_position( m_normal_to_detector
            + (u_bin.m_lower - m_u0)*m_u_unit + (v_bin.m_lower - m_v0)*m_v_unit );
    kvector_t width = u_bin.getBinSize()*m_u_unit;
    kvector_t height = v_bin.getBinSize()*m_v_unit;
    return new RectPixelMap(corner_position, width, height);
}

std::string RectangularDetector::addParametersToExternalPool(
    const std::string& path, ParameterPool *external_pool, int copy_number) const
{
    // add own parameters
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the resolution function
    if (mP_detector_resolution)
        mP_detector_resolution->addParametersToExternalPool(new_path, external_pool, -1);
    return new_path;
}

double RectangularDetector::getWidth() const
{
    const IAxis& axis = getAxis(BornAgain::X_AXIS_INDEX);
    return axis.getMax() - axis.getMin();
}

double RectangularDetector::getHeight() const
{
    const IAxis& axis = getAxis(BornAgain::Y_AXIS_INDEX);
    return axis.getMax() - axis.getMin();
}

size_t RectangularDetector::getNbinsX() const
{
    return getAxis(BornAgain::X_AXIS_INDEX).size();
}

size_t RectangularDetector::getNbinsY() const
{
    return getAxis(BornAgain::Y_AXIS_INDEX).size();
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

std::vector<IDetector2D::EAxesUnits> RectangularDetector::getValidAxesUnits() const
{
    std::vector<IDetector2D::EAxesUnits> result = IDetector2D::getValidAxesUnits();
    std::vector<IDetector2D::EAxesUnits> addon =
        { IDetector2D::RADIANS, IDetector2D::DEGREES, IDetector2D::MM, IDetector2D::QYQZ };
    result.insert(result.end(), addon.begin(), addon.end());
    return result;
}

IDetector2D::EAxesUnits RectangularDetector::getDefaultAxesUnits() const
{
    return IDetector2D::MM;
}

void RectangularDetector::print(std::ostream& ostr) const
{
    ostr << "RectangularDetector: '" << getName() << "' " << getParameterPool();
    for (size_t i = 0; i < m_axes.size(); ++i)
        ostr << "    IAxis:" << *m_axes[i] << std::endl;
}

IAxis *RectangularDetector::createAxis(size_t index, size_t n_bins, double min, double max) const
{
    if (max <= min)
        throw Exceptions::LogicErrorException(
            "RectangularDetector::createAxis() -> Error! max <= min");
    if (n_bins == 0)
        throw Exceptions::LogicErrorException(
            "RectangularDetector::createAxis() -> Error! Number n_bins can't be zero.");
    return new FixedBinAxis(getAxisName(index), n_bins, min, max);
}

void RectangularDetector::calculateAxisRange(size_t axis_index, const Beam &beam,
    IDetector2D::EAxesUnits units, double &amin, double &amax) const
{
    amin = 0.0; amax=0.0;
    if(units == MM) {
        amin = getAxis(axis_index).getMin();
        amax = getAxis(axis_index).getMax();
    }else if(units == RADIANS || units == DEGREES) {
        double scale(1.0);
        if (units == DEGREES)
            scale = 1. / Units::degree;

        if(axis_index == BornAgain::X_AXIS_INDEX) {
            const IAxis &aX = getAxis(BornAgain::X_AXIS_INDEX);
            SimulationElement el_left_bottom
                = getSimulationElement(getGlobalIndex(0, 0), beam);
            SimulationElement el_right_bottom
                = getSimulationElement(getGlobalIndex(aX.size()-1, 0), beam);
            amin = scale * el_left_bottom.getPhi(0.0, 0.0);
            amax = scale * el_right_bottom.getPhi(1.0, 0.0);
        } else if(axis_index == BornAgain::Y_AXIS_INDEX) {
            const IAxis &aX = getAxis(BornAgain::X_AXIS_INDEX);
            const IAxis &aY = getAxis(BornAgain::Y_AXIS_INDEX);
            SimulationElement el_center_bottom
                = getSimulationElement(getGlobalIndex(aX.size()/2, 0), beam);
            SimulationElement el_center_top
                = getSimulationElement(getGlobalIndex(aX.size()/2, aY.size()-1), beam);
            amin = scale * el_center_bottom.getAlpha(0.5, 0.0);
            amax = scale * el_center_top.getAlpha(0.5, 1.0);
        }

    } else {
        IDetector2D::calculateAxisRange(axis_index, beam, units, amin, amax);
    }

}

std::string RectangularDetector::getAxisName(size_t index) const
{
    switch (index) {
    case 0:
        return BornAgain::U_AXIS_NAME;
    case 1:
        return BornAgain::V_AXIS_NAME;
    default:
        throw Exceptions::LogicErrorException(
            "RectangularDetector::getAxisName(size_t index) -> Error! index > 1");
    }
}

size_t RectangularDetector::getIndexOfSpecular(const Beam& beam) const
{
    if (getDimension()!=2) return getTotalSize();
    double alpha = beam.getAlpha();
    double phi = beam.getPhi();
    kvector_t k_spec = vecOfLambdaAlphaPhi(beam.getWavelength(), alpha, phi);
    kvector_t normal_unit = m_normal_to_detector.unit();
    double kd = k_spec.dot(normal_unit);
    if (kd<=0.0) return getTotalSize();
    kvector_t k_orth = (k_spec/kd - normal_unit)*m_distance;
    double u = k_orth.dot(m_u_unit) + m_u0;
    double v = k_orth.dot(m_v_unit) + m_v0;
    const IAxis& u_axis = getAxis(BornAgain::X_AXIS_INDEX);
    const IAxis& v_axis = getAxis(BornAgain::Y_AXIS_INDEX);
    size_t u_index = u_axis.findIndex(u);
    size_t v_index = v_axis.findIndex(v);
    if (u_index < u_axis.size() && v_index < v_axis.size()) {
        return getGlobalIndex(u_index, v_index);
    }
    return getTotalSize();
}

void RectangularDetector::setDistanceAndOffset(double distance, double u0, double v0)
{
    if(distance <= 0.0) {
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

    else if(m_detector_arrangement == PERPENDICULAR_TO_SAMPLE) {
        m_normal_to_detector = kvector_t(m_distance, 0.0, 0.0);
    }

    else if(m_detector_arrangement == PERPENDICULAR_TO_DIRECT_BEAM) {
        m_normal_to_detector = m_distance*central_k_unit;
    }

    else if(m_detector_arrangement == PERPENDICULAR_TO_REFLECTED_BEAM) {
        m_normal_to_detector = m_distance*central_k_unit;
        m_normal_to_detector.setZ(-m_normal_to_detector.z());
    }

    else if(m_detector_arrangement == PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
        m_normal_to_detector = m_distance*central_k_unit;
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

    if(m_detector_arrangement == PERPENDICULAR_TO_REFLECTED_BEAM_DPOS) {
        kvector_t z(0.0, 0.0, 1.0);
        kvector_t normal_unit = m_normal_to_detector.unit();
        kvector_t zp = z - z.dot(normal_unit)*normal_unit;
        double uz = zp.dot(m_u_unit)/zp.mag();
        double vz = zp.dot(m_v_unit)/zp.mag();
        m_u0 = m_dbeam_u0 + m_distance*std::tan(2*alpha_i)*uz;
        m_v0 = m_dbeam_v0 + m_distance*std::tan(2*alpha_i)*vz;
    }
}

RectPixelMap::RectPixelMap(kvector_t corner_pos, kvector_t width, kvector_t height)
    : m_corner_pos(corner_pos), m_width(width), m_height(height)
{
    m_normal = m_width.cross(m_height);
    m_solid_angle = calculateSolidAngle();
}

RectPixelMap *RectPixelMap::clone() const
{
    return new RectPixelMap(m_corner_pos, m_width, m_height);
}

RectPixelMap *RectPixelMap::createZeroSizeMap(double x, double y) const
{
    kvector_t position = m_corner_pos + x*m_width + y*m_height;
    kvector_t null_vector;
    return new RectPixelMap(position, null_vector, null_vector);
}

kvector_t RectPixelMap::getK(double x, double y, double wavelength) const
{
    kvector_t direction = m_corner_pos + x*m_width + y*m_height;
    double length = M_TWOPI/wavelength;
    return normalizeLength(direction, length);
}

double RectPixelMap::getIntegrationFactor(double x, double y) const
{
    if (m_solid_angle==0.0) return 1.0;
    kvector_t position = m_corner_pos + x*m_width + y*m_height;
    double length = position.mag();
    return std::abs(position.dot(m_normal))/std::pow(length, 3)/m_solid_angle;
}

double RectPixelMap::getSolidAngle() const
{
    if (m_solid_angle<=0.0) return 1.0;
    return m_solid_angle;
}

kvector_t RectPixelMap::normalizeLength(const kvector_t direction, double length) const
{
    return direction.unit()*length;
}

double RectPixelMap::calculateSolidAngle() const
{
    kvector_t position = m_corner_pos + 0.5*m_width + 0.5*m_height;
    double length = position.mag();
    return std::abs(position.dot(m_normal))/std::pow(length, 3);
}
