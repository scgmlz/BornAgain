// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/UnitConverter1D.cpp
//! @brief     Implements UnitConverter1D class and derived classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Intensity/UnitConverter1D.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Binning/PointwiseAxis.h"
#include "Core/Instrument/AngularSpecScan.h"
#include "Core/Instrument/QSpecScan.h"
#include "Core/Intensity/AxisNames.h"
#include "Core/Intensity/OutputData.h"

namespace
{
double getQ(double wavelength, double angle);

double getInvQ(double wavelength, double q);

std::unique_ptr<PointwiseAxis>
createTranslatedAxis(const IAxis& axis, std::function<double(double)> translator, std::string name);
} // namespace

std::unique_ptr<UnitConverter1D> UnitConverter1D::createUnitConverter(const ISpecularScan& handler)
{
    if (handler.dataType() == ISpecularScan::angle)
        return std::make_unique<UnitConverterConvSpec>(
            static_cast<const AngularSpecScan&>(handler));

    if (handler.dataType() == ISpecularScan::q)
        return std::make_unique<UnitConverterQSpec>(static_cast<const QSpecScan&>(handler));

    throw std::runtime_error("No known unit conversions for passed type of specular data handler.");
}

size_t UnitConverter1D::dimension() const
{
    return 1u;
}

double UnitConverter1D::calculateMin(size_t i_axis, AxesUnits units_type) const
{
    checkIndex(i_axis);
    units_type = substituteDefaultUnits(units_type);
    if (units_type == AxesUnits::NBINS)
        return 0.0;
    auto translator = getTraslatorTo(units_type);
    return translator(coordinateAxis()->getBinCenter(0));
}

double UnitConverter1D::calculateMax(size_t i_axis, AxesUnits units_type) const
{
    checkIndex(i_axis);
    units_type = substituteDefaultUnits(units_type);
    auto coordinate_axis = coordinateAxis();
    if (units_type == AxesUnits::NBINS)
        return static_cast<double>(coordinate_axis->size());
    auto translator = getTraslatorTo(units_type);
    return translator(coordinate_axis->getBinCenter(coordinate_axis->size() - 1));
}

std::unique_ptr<IAxis> UnitConverter1D::createConvertedAxis(size_t i_axis, AxesUnits units) const
{
    checkIndex(i_axis);
    units = substituteDefaultUnits(units);
    if (units == AxesUnits::NBINS)
        return std::make_unique<FixedBinAxis>(axisName(0, units), coordinateAxis()->size(),
                                              calculateMin(0, units), calculateMax(0, units));
    return createTranslatedAxis(*coordinateAxis(), getTraslatorTo(units), axisName(0, units));
}

std::unique_ptr<OutputData<double>>
UnitConverter1D::createConvertedData(const OutputData<double>& data, AxesUnits units) const
{
    if (data.getRank() != 1)
        throw std::runtime_error("Error in UnitConverter1D::createConvertedData: unexpected "
                                 "dimensions of the input data");

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    auto q_axis = createConvertedAxis(0, units);
    result->addAxis(*q_axis);

    if (units != AxesUnits::RQ4) {
        result->setRawDataVector(data.getRawDataVector());
        return result;
    }

    for (size_t i = 0, size = result->getAllocatedSize(); i < size; ++i)
        (*result)[i] = data[i] * std::pow((*q_axis)[i], 4);
    return result;
}

UnitConverterConvSpec::UnitConverterConvSpec(const Beam& beam, const IAxis& axis,
                                             AxesUnits axis_units)
    : m_wavelength(beam.getWavelength())
{
    m_axis = createTranslatedAxis(axis, getTraslatorFrom(axis_units), axisName(0, axis_units));
    if (m_axis->getMin() < 0 || m_axis->getMax() > M_PI_2)
        throw std::runtime_error("Error in UnitConverter1D: input axis range is out of bounds");
}

UnitConverterConvSpec::UnitConverterConvSpec(const AngularSpecScan& handler)
    : m_wavelength(handler.wavelength()), m_axis(handler.coordinateAxis()->clone())
{
}

UnitConverterConvSpec::~UnitConverterConvSpec() = default;

UnitConverterConvSpec* UnitConverterConvSpec::clone() const
{
    return new UnitConverterConvSpec(*this);
}

size_t UnitConverterConvSpec::axisSize(size_t i_axis) const
{
    checkIndex(i_axis);
    return m_axis->size();
}

std::vector<AxesUnits> UnitConverterConvSpec::availableUnits() const
{
    return {AxesUnits::NBINS, AxesUnits::RADIANS, AxesUnits::DEGREES, AxesUnits::QSPACE,
            AxesUnits::RQ4};
}

AxesUnits UnitConverterConvSpec::defaultUnits() const
{
    return AxesUnits::DEGREES;
}

UnitConverterConvSpec::UnitConverterConvSpec(const UnitConverterConvSpec& other)
    : m_wavelength(other.m_wavelength), m_axis(other.m_axis->clone())
{
}

std::vector<std::map<AxesUnits, std::string>> UnitConverterConvSpec::createNameMaps() const
{
    std::vector<std::map<AxesUnits, std::string>> result;
    result.push_back(AxisNames::InitSpecAxis());
    return result;
}

std::function<double(double)> UnitConverterConvSpec::getTraslatorFrom(AxesUnits units_type) const
{
    switch (units_type) {
    case AxesUnits::RADIANS:
        return [](double value) { return value; };
    case AxesUnits::DEGREES:
        return [](double value) { return Units::deg2rad(value); };
    case AxesUnits::QSPACE:
        return [this](double value) { return getInvQ(m_wavelength, value); };
    default:
        throwUnitsError("UnitConverterConvSpec::getTraslatorFrom",
                        {AxesUnits::RADIANS, AxesUnits::DEGREES, AxesUnits::QSPACE});
    }
}

std::function<double(double)> UnitConverterConvSpec::getTraslatorTo(AxesUnits units_type) const
{
    switch (units_type) {
    case AxesUnits::RADIANS:
        return [](double value) { return value; };
    case AxesUnits::DEGREES:
        return [](double value) { return Units::rad2deg(value); };
    case AxesUnits::QSPACE:
        return [wl = m_wavelength](double value) { return getQ(wl, value); };
    case AxesUnits::RQ4:
        return [wl = m_wavelength](double value) { return getQ(wl, value); };
    default:
        throwUnitsError("UnitConverterConvSpec::getTraslatorTo", availableUnits());
    }
}

UnitConverterQSpec::UnitConverterQSpec(const QSpecScan& handler)
    : m_axis(handler.coordinateAxis()->clone())
{
}

UnitConverterQSpec::~UnitConverterQSpec() = default;

UnitConverterQSpec* UnitConverterQSpec::clone() const
{
    return new UnitConverterQSpec(*this);
}

//! Returns the size of underlying axis.
size_t UnitConverterQSpec::axisSize(size_t i_axis) const
{
    checkIndex(i_axis);
    return m_axis->size();
}

//! Returns the list of all available units
std::vector<AxesUnits> UnitConverterQSpec::availableUnits() const
{
    return {AxesUnits::NBINS, AxesUnits::QSPACE, AxesUnits::RQ4};
}

//! Returns default units to convert to.
AxesUnits UnitConverterQSpec::defaultUnits() const
{
    return AxesUnits::QSPACE;
}

UnitConverterQSpec::UnitConverterQSpec(const UnitConverterQSpec& other)
    : m_axis(std::unique_ptr<IAxis>(other.coordinateAxis()->clone()))
{
}

//! Creates name map for axis in various units
std::vector<std::map<AxesUnits, std::string>> UnitConverterQSpec::createNameMaps() const
{
    std::vector<std::map<AxesUnits, std::string>> result;
    result.push_back(AxisNames::InitSpecAxisQ());
    return result;
}

//! Returns translating functional (inv. nm --> desired units)
std::function<double(double)> UnitConverterQSpec::getTraslatorTo(AxesUnits units_type) const
{
    switch (units_type) {
    case AxesUnits::QSPACE:
        return [](double value) { return value; };
    case AxesUnits::RQ4:
        return [](double value) { return value; };
    default:
        throwUnitsError("UnitConverterQSpec::getTraslatorTo", availableUnits());
    }
}

namespace
{
double getQ(double wavelength, double angle)
{
    return 4.0 * M_PI * std::sin(angle) / wavelength;
}

double getInvQ(double wavelength, double q)
{
    double sin_angle = q * wavelength / (4.0 * M_PI);
    return std::asin(sin_angle);
}

std::unique_ptr<PointwiseAxis>
createTranslatedAxis(const IAxis& axis, std::function<double(double)> translator, std::string name)
{
    auto coordinates = axis.getBinCenters();
    for (size_t i = 0, size = coordinates.size(); i < size; ++i)
        coordinates[i] = translator(coordinates[i]);
    return std::make_unique<PointwiseAxis>(name, coordinates);
}
} // namespace
