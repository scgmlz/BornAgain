//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Histo/SimulationResult.cpp
//! @brief     Implements class SimulationResult.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Histo/SimulationResult.h"
#include "Device/Histo/Histogram2D.h"

SimulationResult::SimulationResult(const OutputData<double>& data,
                                   const IUnitConverter& unit_converter)
    : m_data(data.clone()), m_unit_converter(unit_converter.clone()) {
    checkDimensions();
}

SimulationResult::SimulationResult(const SimulationResult& other) {
    if (!other.m_data || !other.m_unit_converter)
        throw std::runtime_error("Error in SimulationResult(const SimulationResult& other): "
                                 "not initialized");
    m_data.reset(other.m_data->clone());
    m_unit_converter.reset(other.m_unit_converter->clone());
}

SimulationResult::SimulationResult(SimulationResult&& other)
    : m_data(std::move(other.m_data)), m_unit_converter(std::move(other.m_unit_converter)) {}

SimulationResult& SimulationResult::operator=(const SimulationResult& other) {
    if (!other.m_data || !other.m_unit_converter)
        throw std::runtime_error("Error in SimulationResult(const SimulationResult& other): "
                                 "not initialized");

    m_data.reset(other.m_data->clone());
    m_unit_converter.reset(other.m_unit_converter->clone());
    return *this;
}

SimulationResult& SimulationResult::operator=(SimulationResult&& other) {
    m_data.reset(other.m_data.release());
    m_unit_converter.reset(other.m_unit_converter.release());
    return *this;
}

std::unique_ptr<OutputData<double>> SimulationResult::data(Axes::Units units) const {
    if (!m_data)
        throw std::runtime_error(
            "Error in SimulationResult::data:Attempt to access non-initialized data");
    return m_unit_converter->createConvertedData(*m_data, units);
}

Histogram2D* SimulationResult::histogram2d(Axes::Units units) const {
    if (m_data->rank() != 2 || m_unit_converter->dimension() != 2)
        throw std::runtime_error("Error in SimulationResult::histogram2d: "
                                 "dimension of data is not 2. Please use axis(), array() and "
                                 "data() functions for 1D data.");
    auto P_data = data(units);
    return new Histogram2D(*P_data);
}

std::vector<AxisInfo> SimulationResult::axisInfo(Axes::Units units) const {
    if (!m_unit_converter)
        return {};
    std::vector<AxisInfo> result;
    auto dim = m_unit_converter->dimension();
    for (size_t i = 0; i < dim; ++i) {
        AxisInfo info = {m_unit_converter->axisName(i, units),
                         m_unit_converter->calculateMin(i, units),
                         m_unit_converter->calculateMax(i, units)};
        result.push_back(info);
    }
    return result;
}

const IUnitConverter& SimulationResult::converter() const {
    ASSERT(m_unit_converter);
    return *m_unit_converter;
}

double& SimulationResult::operator[](size_t i) {
    ASSERT(m_data);
    return (*m_data)[i];
}

const double& SimulationResult::operator[](size_t i) const {
    ASSERT(m_data);
    return (*m_data)[i];
}

size_t SimulationResult::size() const {
    return m_data ? m_data->getAllocatedSize() : 0;
}

double SimulationResult::max() const {
    ASSERT(m_data);
    double result = 0;
    for (size_t i = 0; i < size(); ++i)
        if ((*m_data)[i] > result)
            result = (*m_data)[i];
    return result;
}

#ifdef BORNAGAIN_PYTHON
PyObject* SimulationResult::array(Axes::Units units) const {
    if (!m_data || !m_unit_converter)
        throw std::runtime_error(
            "Error in SimulationResult::array: attempt to access non-initialized data");
    return m_unit_converter->createConvertedData(*m_data, units)->getArray();
}
#endif

std::vector<double> SimulationResult::axis(Axes::Units units) const {
    return axis(0, units);
}

std::vector<double> SimulationResult::axis(size_t i_axis, Axes::Units units) const {
    if (i_axis >= m_unit_converter->dimension())
        throw std::runtime_error(
            "Error in SimulationResult::axis: no axis corresponds to passed index.");
    auto axis = m_unit_converter->createConvertedAxis(i_axis, units);
    return axis->binCenters();
}

void SimulationResult::checkDimensions() const {
    if (m_data->rank() != m_unit_converter->dimension())
        throw std::runtime_error("Error in SimulationResults::checkDimensions(): "
                                 "dimensions of data and unit converter don't match");
}
