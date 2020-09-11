// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimulationResult.cpp
//! @brief     Implements class SimulationResult.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Instrument/SimulationResult.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Intensity/Histogram2D.h"
#include "Core/Intensity/OutputData.h"

SimulationResult::SimulationResult(const OutputData<double>& data,
                                   const IUnitConverter& unit_converter)
    : mP_data(data.clone()), mP_unit_converter(unit_converter.clone())
{
    checkDimensions();
}

SimulationResult::SimulationResult(const SimulationResult& other)
{
    if (!other.mP_data || !other.mP_unit_converter)
        throw std::runtime_error("Error in SimulationResult(const SimulationResult& other): "
                                 "not initialized");
    mP_data.reset(other.mP_data->clone());
    mP_unit_converter.reset(other.mP_unit_converter->clone());
}

SimulationResult::SimulationResult(SimulationResult&& other)
    : mP_data(std::move(other.mP_data)), mP_unit_converter(std::move(other.mP_unit_converter))
{
}

SimulationResult& SimulationResult::operator=(const SimulationResult& other)
{
    if (!other.mP_data || !other.mP_unit_converter)
        throw std::runtime_error("Error in SimulationResult(const SimulationResult& other): "
                                 "not initialized");

    mP_data.reset(other.mP_data->clone());
    mP_unit_converter.reset(other.mP_unit_converter->clone());
    return *this;
}

SimulationResult& SimulationResult::operator=(SimulationResult&& other)
{
    mP_data.reset(other.mP_data.release());
    mP_unit_converter.reset(other.mP_unit_converter.release());
    return *this;
}

std::unique_ptr<OutputData<double>> SimulationResult::data(AxesUnits units) const
{
    if (!mP_data)
        throw std::runtime_error(
            "Error in SimulationResult::data:Attempt to access non-initialized data");
    return mP_unit_converter->createConvertedData(*mP_data, units);
}

Histogram2D* SimulationResult::histogram2d(AxesUnits units) const
{
    if (mP_data->getRank() != 2 || mP_unit_converter->dimension() != 2)
        throw std::runtime_error("Error in SimulationResult::histogram2d: "
                                 "dimension of data is not 2. Please use axis(), array() and "
                                 "data() functions for 1D data.");
    auto P_data = data(units);
    return new Histogram2D(*P_data);
}

std::vector<AxisInfo> SimulationResult::axisInfo(AxesUnits units) const
{
    if (!mP_unit_converter)
        return {};
    std::vector<AxisInfo> result;
    auto dim = mP_unit_converter->dimension();
    for (size_t i = 0; i < dim; ++i) {
        AxisInfo info = {mP_unit_converter->axisName(i, units),
                         mP_unit_converter->calculateMin(i, units),
                         mP_unit_converter->calculateMax(i, units)};
        result.push_back(info);
    }
    return result;
}

const IUnitConverter& SimulationResult::converter() const
{
    if (!mP_unit_converter)
        throw std::runtime_error(
            "Error in SimulationResult::converter: unit converter was not initialized");
    return *mP_unit_converter;
}

double& SimulationResult::operator[](size_t i)
{
    if (mP_data)
        return (*mP_data)[i];
    throw std::runtime_error("Error in SimulationResult::operator[]: "
                             "no data initialized");
}

const double& SimulationResult::operator[](size_t i) const
{
    if (mP_data)
        return (*mP_data)[i];
    throw std::runtime_error("Error in SimulationResult::operator[]: "
                             "no data initialized");
}

size_t SimulationResult::size() const
{
    return mP_data ? mP_data->getAllocatedSize() : 0;
}

#ifdef BORNAGAIN_PYTHON
PyObject* SimulationResult::array(AxesUnits units) const
{
    if (!mP_data || !mP_unit_converter)
        throw std::runtime_error(
            "Error in SimulationResult::array: attempt to access non-initialized data");
    return mP_unit_converter->createConvertedData(*mP_data, units)->getArray();
}
#endif

std::vector<double> SimulationResult::axis(AxesUnits units) const
{
    return axis(0, units);
}

std::vector<double> SimulationResult::axis(size_t i_axis, AxesUnits units) const
{
    if (i_axis >= mP_unit_converter->dimension())
        throw std::runtime_error(
            "Error in SimulationResult::axis: no axis corresponds to passed index.");
    auto axis = mP_unit_converter->createConvertedAxis(i_axis, units);
    return axis->getBinCenters();
}

void SimulationResult::checkDimensions() const
{
    if (mP_data->getRank() != mP_unit_converter->dimension())
        throw std::runtime_error("Error in SimulationResults::checkDimensions(): "
                                 "dimensions of data and unit converter don't match");
    return;
}
