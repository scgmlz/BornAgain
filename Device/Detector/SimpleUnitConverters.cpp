//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/SimpleUnitConverters.cpp
//! @brief     Implements IUnitConverter classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Detector/SimpleUnitConverters.h"
#include "Base/Const/Units.h"
#include "Base/Math/Constants.h"
#include "Device/Beam/Beam.h"
#include "Device/Detector/RectangularDetector.h"
#include "Device/Detector/RectangularPixel.h"
#include "Device/Detector/RegionOfInterest.h"
#include "Device/Detector/SphericalDetector.h"
#include "Device/Unit/AxisNames.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace {
double getQ(double wavelength, double angle) {
    return 4.0 * M_PI * std::sin(angle) / wavelength;
}
} // namespace

//  ************************************************************************************************
//  class UnitConverterSimple
//  ************************************************************************************************

UnitConverterSimple::UnitConverterSimple(const Beam& beam)
    : m_wavelength(beam.wavelength())
    , m_alpha_i(-beam.direction().alpha())
    , m_phi_i(beam.direction().phi()) {}

size_t UnitConverterSimple::dimension() const {
    return m_axis_data_table.size();
}

void UnitConverterSimple::addAxisData(std::string name, double min, double max,
                                      Axes::Units default_units, size_t nbins) {
    AxisData axis_data{name, min, max, default_units, nbins};
    m_axis_data_table.push_back(axis_data);
}

double UnitConverterSimple::calculateMin(size_t i_axis, Axes::Units units_type) const {
    checkIndex(i_axis);
    units_type = substituteDefaultUnits(units_type);
    const auto& axis_data = m_axis_data_table[i_axis];
    if (units_type == Axes::Units::NBINS)
        return 0.0;
    return calculateValue(i_axis, units_type, axis_data.min);
}

double UnitConverterSimple::calculateMax(size_t i_axis, Axes::Units units_type) const {
    checkIndex(i_axis);
    units_type = substituteDefaultUnits(units_type);
    const auto& axis_data = m_axis_data_table[i_axis];
    if (units_type == Axes::Units::NBINS)
        return static_cast<double>(axis_data.nbins);
    return calculateValue(i_axis, units_type, axis_data.max);
}

size_t UnitConverterSimple::axisSize(size_t i_axis) const {
    checkIndex(i_axis);
    return m_axis_data_table[i_axis].nbins;
}

std::vector<Axes::Units> UnitConverterSimple::availableUnits() const {
    return {Axes::Units::NBINS, Axes::Units::RADIANS, Axes::Units::DEGREES};
}

std::unique_ptr<IAxis> UnitConverterSimple::createConvertedAxis(size_t i_axis,
                                                                Axes::Units units) const {
    const double min = calculateMin(i_axis, units);
    const double max = calculateMax(i_axis, units);
    const auto& axis_name = axisName(i_axis, units);
    const auto axis_size = axisSize(i_axis);
    return std::make_unique<FixedBinAxis>(axis_name, axis_size, min, max);
}

UnitConverterSimple::UnitConverterSimple(const UnitConverterSimple& other)
    : m_axis_data_table(other.m_axis_data_table)
    , m_wavelength(other.m_wavelength)
    , m_alpha_i(other.m_alpha_i)
    , m_phi_i(other.m_phi_i) {}

void UnitConverterSimple::addDetectorAxis(const IDetector& detector, size_t i_axis) {
    const auto& axis = detector.axis(i_axis);
    const auto* p_roi = detector.regionOfInterest();
    const auto& axis_name = axisName(i_axis);
    if (!p_roi) {
        addAxisData(axis_name, axis.lowerBound(), axis.upperBound(), defaultUnits(), axis.size());
        return;
    }
    auto P_roi_axis = p_roi->clipAxisToRoi(i_axis, axis);
    addAxisData(axis_name, P_roi_axis->lowerBound(), P_roi_axis->upperBound(), defaultUnits(),
                P_roi_axis->size());
}

//  ************************************************************************************************
//  class SphericalConverter
//  ************************************************************************************************

SphericalConverter::SphericalConverter(const SphericalDetector& detector, const Beam& beam)
    : UnitConverterSimple(beam) {
    if (detector.dimension() != 2)
        throw std::runtime_error("Error in SphericalConverter constructor: "
                                 "detector has wrong dimension: "
                                 + std::to_string(static_cast<int>(detector.dimension())));
    addDetectorAxis(detector, 0);
    addDetectorAxis(detector, 1);
}

SphericalConverter::~SphericalConverter() = default;

SphericalConverter* SphericalConverter::clone() const {
    return new SphericalConverter(*this);
}

std::vector<Axes::Units> SphericalConverter::availableUnits() const {
    auto result = UnitConverterSimple::availableUnits();
    result.push_back(Axes::Units::QSPACE);
    return result;
}

Axes::Units SphericalConverter::defaultUnits() const {
    return Axes::Units::DEGREES;
}

SphericalConverter::SphericalConverter(const SphericalConverter& other)
    : UnitConverterSimple(other) {}

double SphericalConverter::calculateValue(size_t i_axis, Axes::Units units_type,
                                          double value) const {
    switch (units_type) {
    case Axes::Units::RADIANS:
        return value;
    case Axes::Units::DEGREES:
        return Units::rad2deg(value);
    case Axes::Units::QSPACE: {
        const auto k_i = vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
        if (i_axis == 0) {
            const auto k_f = vecOfLambdaAlphaPhi(m_wavelength, 0.0, value);
            return (k_i - k_f).y();
        } else if (i_axis == 1) {
            const auto k_f = vecOfLambdaAlphaPhi(m_wavelength, value, 0.0);
            return (k_f - k_i).z();
        }
        throw std::runtime_error("Error in SphericalConverter::calculateValue: "
                                 "incorrect axis index: "
                                 + std::to_string(static_cast<int>(i_axis)));
    }
    case Axes::Units::QXQY: {
        const auto k_i = vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
        if (i_axis == 0) {
            const auto k_f = vecOfLambdaAlphaPhi(m_wavelength, 0.0, value);
            return (k_i - k_f).y();
        } else if (i_axis == 1) {
            const auto k_f = vecOfLambdaAlphaPhi(m_wavelength, value, 0.0);
            return (k_f - k_i).x();
        }
        throw std::runtime_error("Error in SphericalConverter::calculateValue: "
                                 "incorrect axis index: "
                                 + std::to_string(static_cast<int>(i_axis)));
    }
    default:
        throwUnitsError("SphericalConverter::calculateValue", availableUnits());
    }
}

std::vector<std::map<Axes::Units, std::string>> SphericalConverter::createNameMaps() const {
    std::vector<std::map<Axes::Units, std::string>> result;
    result.push_back(AxisNames::InitSphericalAxis0());
    result.push_back(AxisNames::InitSphericalAxis1());
    return result;
}

//  ************************************************************************************************
//  class RectangularConverter
//  ************************************************************************************************

RectangularConverter::RectangularConverter(const RectangularDetector& detector, const Beam& beam)
    : UnitConverterSimple(beam) {
    if (detector.dimension() != 2)
        throw std::runtime_error("Error in RectangularConverter constructor: "
                                 "detector has wrong dimension: "
                                 + std::to_string(static_cast<int>(detector.dimension())));
    addDetectorAxis(detector, 0);
    addDetectorAxis(detector, 1);
    m_detector_pixel.reset(detector.regionOfInterestPixel());
}

RectangularConverter::~RectangularConverter() = default;

RectangularConverter* RectangularConverter::clone() const {
    return new RectangularConverter(*this);
}

std::vector<Axes::Units> RectangularConverter::availableUnits() const {
    auto result = UnitConverterSimple::availableUnits();
    result.push_back(Axes::Units::QSPACE);
    result.push_back(Axes::Units::MM);
    return result;
}

Axes::Units RectangularConverter::defaultUnits() const {
    return Axes::Units::MM;
}

RectangularConverter::RectangularConverter(const RectangularConverter& other)
    : UnitConverterSimple(other), m_detector_pixel(other.m_detector_pixel->clone()) {}

double RectangularConverter::calculateValue(size_t i_axis, Axes::Units units_type,
                                            double value) const {
    if (units_type == Axes::Units::MM)
        return value;
    const auto k00 = m_detector_pixel->getPosition(0.0, 0.0);
    const auto k01 = m_detector_pixel->getPosition(0.0, 1.0);
    const auto k10 = m_detector_pixel->getPosition(1.0, 0.0);
    const auto& max_pos = i_axis == 0 ? k10 : k01; // position of max along given axis
    const double shift = value - m_axis_data_table[i_axis].min;
    const auto k_f = normalizeToWavelength(k00 + shift * (max_pos - k00).unit());
    switch (units_type) {
    case Axes::Units::RADIANS:
        return axisAngle(i_axis, k_f);
    case Axes::Units::DEGREES:
        return Units::rad2deg(axisAngle(i_axis, k_f));
    case Axes::Units::QSPACE: {
        const auto k_i = vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
        if (i_axis == 0)
            return (k_i - k_f).y();
        if (i_axis == 1)
            return (k_f - k_i).z();
        throw std::runtime_error("Error in RectangularConverter::calculateValue: "
                                 "incorrect axis index: "
                                 + std::to_string(static_cast<int>(i_axis)));
    }
    case Axes::Units::QXQY: {
        const auto k_i = vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
        if (i_axis == 0)
            return (k_i - k_f).y();
        if (i_axis == 1)
            return (k_f - k_i).x();
        throw std::runtime_error("Error in RectangularConverter::calculateValue: "
                                 "incorrect axis index: "
                                 + std::to_string(static_cast<int>(i_axis)));
    }
    default:
        throwUnitsError("RectangularConverter::calculateValue", availableUnits());
    }
}

std::vector<std::map<Axes::Units, std::string>> RectangularConverter::createNameMaps() const {
    std::vector<std::map<Axes::Units, std::string>> result;
    result.push_back(AxisNames::InitRectangularAxis0());
    result.push_back(AxisNames::InitRectangularAxis1());
    return result;
}

kvector_t RectangularConverter::normalizeToWavelength(kvector_t vector) const {
    if (m_wavelength <= 0.0)
        throw std::runtime_error("Error in RectangularConverter::normalizeToWavelength: "
                                 "wavelength <= 0");
    double K = M_TWOPI / m_wavelength;
    return vector.unit() * K;
}

double RectangularConverter::axisAngle(size_t i_axis, kvector_t k_f) const {
    if (i_axis == 0)
        return k_f.phi();
    if (i_axis == 1)
        return M_PI_2 - k_f.theta();
    throw std::runtime_error("Error in RectangularConverter::axisAngle: "
                             "incorrect axis index: "
                             + std::to_string(static_cast<int>(i_axis)));
}

//  ************************************************************************************************
//  class OffSpecularConverter
//  ************************************************************************************************

OffSpecularConverter::OffSpecularConverter(const IDetector2D& detector, const Beam& beam,
                                           const IAxis& alpha_axis)
    : UnitConverterSimple(beam) {
    if (detector.dimension() != 2)
        throw std::runtime_error("Error in OffSpecularConverter constructor: "
                                 "detector has wrong dimension: "
                                 + std::to_string(static_cast<int>(detector.dimension())));
    addAxisData(axisName(0), alpha_axis.lowerBound(), alpha_axis.upperBound(), defaultUnits(),
                alpha_axis.size());
    addDetectorYAxis(detector);
}

OffSpecularConverter::~OffSpecularConverter() = default;

OffSpecularConverter* OffSpecularConverter::clone() const {
    return new OffSpecularConverter(*this);
}

Axes::Units OffSpecularConverter::defaultUnits() const {
    return Axes::Units::DEGREES;
}

OffSpecularConverter::OffSpecularConverter(const OffSpecularConverter& other)
    : UnitConverterSimple(other) {}

double OffSpecularConverter::calculateValue(size_t, Axes::Units units_type, double value) const {
    switch (units_type) {
    case Axes::Units::RADIANS:
        return value;
    case Axes::Units::DEGREES:
        return Units::rad2deg(value);
    default:
        throwUnitsError("OffSpecularConverter::calculateValue", availableUnits());
    }
}

std::vector<std::map<Axes::Units, std::string>> OffSpecularConverter::createNameMaps() const {
    std::vector<std::map<Axes::Units, std::string>> result;
    result.push_back(AxisNames::InitOffSpecularAxis0());
    result.push_back(AxisNames::InitOffSpecularAxis1());
    return result;
}

void OffSpecularConverter::addDetectorYAxis(const IDetector2D& detector) {
    const auto& axis = detector.axis(1);
    const auto* p_roi = detector.regionOfInterest();
    const auto& axis_name = axisName(1);
    std::unique_ptr<IAxis> P_new_axis;
    if (p_roi) {
        P_new_axis = p_roi->clipAxisToRoi(1, axis);
    } else {
        P_new_axis.reset(axis.clone());
    }
    if (!P_new_axis)
        throw std::runtime_error("Error in OffSpecularConverter::addDetectorYAxis: "
                                 "could not retrieve the y-axis of the detector");
    if (const auto* P_rect_det = dynamic_cast<const RectangularDetector*>(&detector)) {
        std::unique_ptr<RectangularPixel> P_det_pixel(P_rect_det->regionOfInterestPixel());
        const auto k00 = P_det_pixel->getPosition(0.0, 0.0);
        const auto k01 = P_det_pixel->getPosition(0.0, 1.0);
        const double alpha_f_min = M_PI_2 - k00.theta();
        const double alpha_f_max = M_PI_2 - k01.theta();
        addAxisData(axis_name, alpha_f_min, alpha_f_max, defaultUnits(), P_new_axis->size());
    } else if (dynamic_cast<const SphericalDetector*>(&detector)) {
        const double alpha_f_min = P_new_axis->lowerBound();
        const double alpha_f_max = P_new_axis->upperBound();
        addAxisData(axis_name, alpha_f_min, alpha_f_max, defaultUnits(), P_new_axis->size());
    } else {
        throw std::runtime_error("Error in OffSpecularConverter::addDetectorYAxis: "
                                 "wrong detector type");
    }
}

//  ************************************************************************************************
//  class DepthProbeConverter
//  ************************************************************************************************

const std::string z_axis_name = "Position [nm]";

DepthProbeConverter::DepthProbeConverter(const Beam& beam, const IAxis& alpha_axis,
                                         const IAxis& z_axis)
    : UnitConverterSimple(beam) {
    const auto& alpha_axis_name = axisName(0);
    const auto& z_axis_name = axisName(1);
    addAxisData(alpha_axis_name, alpha_axis.lowerBound(), alpha_axis.upperBound(), defaultUnits(),
                alpha_axis.size());
    addAxisData(z_axis_name, z_axis.lowerBound(), z_axis.upperBound(), defaultUnits(),
                z_axis.size());
}

DepthProbeConverter::~DepthProbeConverter() = default;

DepthProbeConverter* DepthProbeConverter::clone() const {
    return new DepthProbeConverter(*this);
}

std::vector<Axes::Units> DepthProbeConverter::availableUnits() const {
    auto result = UnitConverterSimple::availableUnits();
    result.push_back(Axes::Units::QSPACE);
    return result;
}

DepthProbeConverter::DepthProbeConverter(const DepthProbeConverter& other)
    : UnitConverterSimple(other) {}

double DepthProbeConverter::calculateValue(size_t i_axis, Axes::Units units_type,
                                           double value) const {
    checkUnits(units_type);
    if (i_axis == 1)
        return value; // unit conversions are not applied to sample position axis
    switch (units_type) {
    case Axes::Units::DEGREES:
        return Units::rad2deg(value);
    case Axes::Units::QSPACE:
        return getQ(m_wavelength, value);
    default:
        return value;
    }
}

std::vector<std::map<Axes::Units, std::string>> DepthProbeConverter::createNameMaps() const {
    std::vector<std::map<Axes::Units, std::string>> result;
    result.push_back(AxisNames::InitSpecAxis());
    result.push_back(AxisNames::InitSampleDepthAxis());
    return result;
}

void DepthProbeConverter::checkUnits(Axes::Units units_type) const {
    const auto& available_units = availableUnits();
    if (std::find(available_units.begin(), available_units.end(), units_type)
        == available_units.cend())
        throwUnitsError("DepthProbeConverter::checkUnits", available_units);
}
