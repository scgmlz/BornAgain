//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scan/UnitConverter1D.cpp
//! @brief     Implements UnitConverter1D class and derived classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Scan/UnitConverter1D.h"
#include "Base/Axis/PointwiseAxis.h"
#include "Base/Const/Units.h"
#include "Base/Math/Constants.h"
#include "Core/Scan/AngularSpecScan.h"
#include "Core/Scan/QSpecScan.h"
#include "Device/Beam/Beam.h"
#include "Device/Data/OutputData.h"
#include "Device/Unit/AxisNames.h"

namespace {
double getQ(double wavelength, double angle);

double getInvQ(double wavelength, double q);

std::unique_ptr<PointwiseAxis>
createTranslatedAxis(const IAxis& axis, std::function<double(double)> translator, std::string name);
} // namespace

std::unique_ptr<UnitConverter1D> UnitConverter1D::createUnitConverter(const ISpecularScan& scan) {
    if (const auto* aScan = dynamic_cast<const AngularSpecScan*>(&scan))
        return std::make_unique<UnitConverterConvSpec>(*aScan);

    if (const auto* qScan = dynamic_cast<const QSpecScan*>(&scan))
        return std::make_unique<UnitConverterQSpec>(*qScan);

    throw std::runtime_error("Bug in UnitConverter1D::createUnitConverter: invalid case");
}

size_t UnitConverter1D::dimension() const {
    return 1u;
}

double UnitConverter1D::calculateMin(size_t i_axis, Axes::Units units_type) const {
    checkIndex(i_axis);
    units_type = substituteDefaultUnits(units_type);
    if (units_type == Axes::Units::NBINS)
        return 0.0;
    auto translator = getTraslatorTo(units_type);
    return translator(coordinateAxis()->binCenter(0));
}

double UnitConverter1D::calculateMax(size_t i_axis, Axes::Units units_type) const {
    checkIndex(i_axis);
    units_type = substituteDefaultUnits(units_type);
    auto coordinate_axis = coordinateAxis();
    if (units_type == Axes::Units::NBINS)
        return static_cast<double>(coordinate_axis->size());
    auto translator = getTraslatorTo(units_type);
    return translator(coordinate_axis->binCenter(coordinate_axis->size() - 1));
}

std::unique_ptr<IAxis> UnitConverter1D::createConvertedAxis(size_t i_axis,
                                                            Axes::Units units) const {
    checkIndex(i_axis);
    units = substituteDefaultUnits(units);
    if (units == Axes::Units::NBINS)
        return std::make_unique<FixedBinAxis>(axisName(0, units), coordinateAxis()->size(),
                                              calculateMin(0, units), calculateMax(0, units));
    return createTranslatedAxis(*coordinateAxis(), getTraslatorTo(units), axisName(0, units));
}

std::unique_ptr<OutputData<double>>
UnitConverter1D::createConvertedData(const OutputData<double>& data, Axes::Units units) const {
    if (data.rank() != 1)
        throw std::runtime_error("Error in UnitConverter1D::createConvertedData: unexpected "
                                 "dimensions of the input data");

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    auto q_axis = createConvertedAxis(0, units);
    result->addAxis(*q_axis);

    if (units != Axes::Units::RQ4) {
        result->setRawDataVector(data.getRawDataVector());
        return result;
    }

    for (size_t i = 0, size = result->getAllocatedSize(); i < size; ++i)
        (*result)[i] = data[i] * std::pow((*q_axis)[i], 4);
    return result;
}

UnitConverterConvSpec::UnitConverterConvSpec(const Beam& beam, const IAxis& axis,
                                             Axes::Units axis_units)
    : m_wavelength(beam.wavelength()) {
    m_axis = createTranslatedAxis(axis, getTraslatorFrom(axis_units), axisName(0, axis_units));
    if (m_axis->lowerBound() < 0 || m_axis->upperBound() > M_PI_2)
        throw std::runtime_error("Error in UnitConverter1D: input axis range is out of bounds");
}

UnitConverterConvSpec::UnitConverterConvSpec(const AngularSpecScan& handler)
    : m_wavelength(handler.wavelength()), m_axis(handler.coordinateAxis()->clone()) {}

UnitConverterConvSpec::~UnitConverterConvSpec() = default;

UnitConverterConvSpec* UnitConverterConvSpec::clone() const {
    return new UnitConverterConvSpec(*this);
}

size_t UnitConverterConvSpec::axisSize(size_t i_axis) const {
    checkIndex(i_axis);
    return m_axis->size();
}

std::vector<Axes::Units> UnitConverterConvSpec::availableUnits() const {
    return {Axes::Units::NBINS, Axes::Units::RADIANS, Axes::Units::DEGREES, Axes::Units::QSPACE,
            Axes::Units::RQ4};
}

Axes::Units UnitConverterConvSpec::defaultUnits() const {
    return Axes::Units::DEGREES;
}

UnitConverterConvSpec::UnitConverterConvSpec(const UnitConverterConvSpec& other)
    : m_wavelength(other.m_wavelength), m_axis(other.m_axis->clone()) {}

std::vector<std::map<Axes::Units, std::string>> UnitConverterConvSpec::createNameMaps() const {
    std::vector<std::map<Axes::Units, std::string>> result;
    result.push_back(AxisNames::InitSpecAxis());
    return result;
}

std::function<double(double)>
UnitConverterConvSpec::getTraslatorFrom(Axes::Units units_type) const {
    switch (units_type) {
    case Axes::Units::RADIANS:
        return [](double value) { return value; };
    case Axes::Units::DEGREES:
        return [](double value) { return Units::deg2rad(value); };
    case Axes::Units::QSPACE:
        return [this](double value) { return getInvQ(m_wavelength, value); };
    default:
        throwUnitsError("UnitConverterConvSpec::getTraslatorFrom",
                        {Axes::Units::RADIANS, Axes::Units::DEGREES, Axes::Units::QSPACE});
    }
}

std::function<double(double)> UnitConverterConvSpec::getTraslatorTo(Axes::Units units_type) const {
    switch (units_type) {
    case Axes::Units::RADIANS:
        return [](double value) { return value; };
    case Axes::Units::DEGREES:
        return [](double value) { return Units::rad2deg(value); };
    case Axes::Units::QSPACE:
        return [wl = m_wavelength](double value) { return getQ(wl, value); };
    case Axes::Units::RQ4:
        return [wl = m_wavelength](double value) { return getQ(wl, value); };
    default:
        throwUnitsError("UnitConverterConvSpec::getTraslatorTo", availableUnits());
    }
}

UnitConverterQSpec::UnitConverterQSpec(const QSpecScan& handler)
    : m_axis(handler.coordinateAxis()->clone()) {}

UnitConverterQSpec::~UnitConverterQSpec() = default;

UnitConverterQSpec* UnitConverterQSpec::clone() const {
    return new UnitConverterQSpec(*this);
}

//! Returns the size of underlying axis.
size_t UnitConverterQSpec::axisSize(size_t i_axis) const {
    checkIndex(i_axis);
    return m_axis->size();
}

//! Returns the list of all available units
std::vector<Axes::Units> UnitConverterQSpec::availableUnits() const {
    return {Axes::Units::NBINS, Axes::Units::QSPACE, Axes::Units::RQ4};
}

//! Returns default units to convert to.
Axes::Units UnitConverterQSpec::defaultUnits() const {
    return Axes::Units::QSPACE;
}

UnitConverterQSpec::UnitConverterQSpec(const UnitConverterQSpec& other)
    : m_axis(std::unique_ptr<IAxis>(other.coordinateAxis()->clone())) {}

//! Creates name map for axis in various units
std::vector<std::map<Axes::Units, std::string>> UnitConverterQSpec::createNameMaps() const {
    std::vector<std::map<Axes::Units, std::string>> result;
    result.push_back(AxisNames::InitSpecAxisQ());
    return result;
}

//! Returns translating functional (inv. nm --> desired units)
std::function<double(double)> UnitConverterQSpec::getTraslatorTo(Axes::Units units_type) const {
    switch (units_type) {
    case Axes::Units::QSPACE:
        return [](double value) { return value; };
    case Axes::Units::RQ4:
        return [](double value) { return value; };
    default:
        throwUnitsError("UnitConverterQSpec::getTraslatorTo", availableUnits());
    }
}

namespace {
double getQ(double wavelength, double angle) {
    return 4.0 * M_PI * std::sin(angle) / wavelength;
}

double getInvQ(double wavelength, double q) {
    double sin_angle = q * wavelength / (4.0 * M_PI);
    return std::asin(sin_angle);
}

std::unique_ptr<PointwiseAxis> createTranslatedAxis(const IAxis& axis,
                                                    std::function<double(double)> translator,
                                                    std::string name) {
    auto coordinates = axis.binCenters();
    for (size_t i = 0, size = coordinates.size(); i < size; ++i)
        coordinates[i] = translator(coordinates[i]);
    return std::make_unique<PointwiseAxis>(name, coordinates);
}
} // namespace
