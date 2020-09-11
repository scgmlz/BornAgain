// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/IUnitConverter.cpp
//! @brief     Implements IUnitConverter class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Intensity/IUnitConverter.h"
#include "Core/Intensity/OutputData.h"

namespace
{
const std::map<AxesUnits, std::string> unit_names = {
    {AxesUnits::NBINS, "AxesUnits::NBINS"},     {AxesUnits::RADIANS, "AxesUnits::RADIANS"},
    {AxesUnits::DEGREES, "AxesUnits::DEGREES"}, {AxesUnits::MM, "AxesUnits::MM"},
    {AxesUnits::QSPACE, "AxesUnits::QSPACE"},   {AxesUnits::QXQY, "AxesUnits::QXQY"},
    {AxesUnits::RQ4, "AxesUnits::RQ4"}};
}

std::string AxesUnitsWrap::unitName(AxesUnits unit)
{
    auto iter = unit_names.find(unit);
    if (iter != unit_names.end())
        return iter->second;
    return "Unknown units";
}

IUnitConverter::~IUnitConverter() = default;

std::string IUnitConverter::axisName(size_t i_axis, AxesUnits units_type) const
{
    const auto& name_maps = createNameMaps();
    if (name_maps.size() <= i_axis)
        throw std::runtime_error("Error in IUnitConverter::axisName: the size of name map vector "
                                 "is smaller or equal to the axis index"
                                 + std::to_string(static_cast<int>(i_axis)));
    const auto& name_map = name_maps[i_axis];
    units_type = substituteDefaultUnits(units_type);
    const auto& it = name_map.find(units_type);
    if (it == name_map.cend())
        throwUnitsError("IUnitConverter::axisName", availableUnits());
    return it->second;
}

std::unique_ptr<OutputData<double>>
IUnitConverter::createConvertedData(const OutputData<double>& data, AxesUnits units) const
{
    const size_t dim = data.getRank();
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    for (size_t i = 0; i < dim; ++i)
        result->addAxis(*createConvertedAxis(i, units));
    result->setRawDataVector(data.getRawDataVector());
    return result;
}

void IUnitConverter::checkIndex(size_t i_axis) const
{
    if (i_axis < dimension())
        return;
    throw std::runtime_error("Error in IUnitConverter::checkIndex: passed axis index too big: "
                             + std::to_string(static_cast<int>(i_axis)));
}

void IUnitConverter::throwUnitsError(std::string method, std::vector<AxesUnits> available) const
{
    std::stringstream ss;
    ss << "Unit type error in " << method
       << ": unknown or unsupported unit type. Available units "
          "are:\n";
    for (auto unit : available)
        ss << AxesUnitsWrap::unitName(unit) << "\n";
    throw std::runtime_error(ss.str());
}

AxesUnits IUnitConverter::substituteDefaultUnits(AxesUnits units) const
{
    return units == AxesUnits::DEFAULT ? defaultUnits() : units;
}
