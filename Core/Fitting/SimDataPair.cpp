// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/SimDataPair.cpp
//! @brief     Defines class SimDataPair.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Fitting/SimDataPair.h"
#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Intensity/OutputData.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Simulation/UnitConverterUtils.h"
#include "Fit/TestEngine/Numeric.h"

namespace
{
[[noreturn]] void throwInitializationException(std::string method)
{
    std::stringstream ss;
    ss << "Error in SimDataPair::" << method << ": Trying access non-initialized data\n";
    throw std::runtime_error(ss.str());
}

std::unique_ptr<OutputData<double>> initUserWeights(const OutputData<double>& shape, double value)
{
    auto result = std::make_unique<OutputData<double>>();
    result->copyShapeFrom(shape);
    result->setAllTo(value);
    return result;
}
} // namespace

SimDataPair::SimDataPair(simulation_builder_t builder, const OutputData<double>& data,
                         std::unique_ptr<OutputData<double>> uncertainties, double user_weight)
    : m_simulation_builder(builder), m_raw_data(data.clone()),
      m_raw_uncertainties(std::move(uncertainties))
{
    m_raw_user_weights = initUserWeights(*m_raw_data, user_weight);
    validate();
}

SimDataPair::SimDataPair(simulation_builder_t builder, const OutputData<double>& data,
                         std::unique_ptr<OutputData<double>> uncertainties,
                         std::unique_ptr<OutputData<double>> user_weights)
    : m_simulation_builder(builder), m_raw_data(data.clone()),
      m_raw_uncertainties(std::move(uncertainties)), m_raw_user_weights(std::move(user_weights))
{
    if (!m_raw_user_weights)
        m_raw_user_weights = initUserWeights(*m_raw_data, 1.0);
    validate();
}

SimDataPair::SimDataPair(SimDataPair&& other)
    : m_simulation_builder(std::move(other.m_simulation_builder)),
      m_simulation(std::move(other.m_simulation)), m_sim_data(std::move(other.m_sim_data)),
      m_exp_data(std::move(other.m_exp_data)), m_uncertainties(std::move(other.m_uncertainties)),
      m_user_weights(std::move(other.m_user_weights)), m_raw_data(std::move(other.m_raw_data)),
      m_raw_uncertainties(std::move(other.m_raw_uncertainties)),
      m_raw_user_weights(std::move(other.m_raw_user_weights))
{
    validate();
}

SimDataPair::~SimDataPair() = default;

void SimDataPair::runSimulation(const Fit::Parameters& params)
{
    m_simulation = m_simulation_builder(params);
    m_simulation->runSimulation();
    m_sim_data = m_simulation->result();

    initResultArrays();
}

bool SimDataPair::containsUncertainties() const
{
    return static_cast<bool>(m_raw_uncertainties);
}

size_t SimDataPair::numberOfFitElements() const
{
    return m_simulation ? m_simulation->intensityMapSize() : 0;
}

SimulationResult SimDataPair::simulationResult() const
{
    if (m_sim_data.size() == 0)
        throwInitializationException("simulationResult");
    return m_sim_data;
}

SimulationResult SimDataPair::experimentalData() const
{
    if (m_exp_data.size() == 0)
        throwInitializationException("experimentalData");
    return m_exp_data;
}

SimulationResult SimDataPair::uncertainties() const
{
    if (m_uncertainties.size() == 0)
        throwInitializationException("uncertainties");
    return m_uncertainties;
}

//! Returns the user uncertainties cut to the ROI area.
SimulationResult SimDataPair::userWeights() const
{
    if (m_user_weights.size() == 0)
        throwInitializationException("userWeights");
    return m_user_weights;
}

//! Returns relative difference between simulation and experimental data.

SimulationResult SimDataPair::relativeDifference() const
{
    if (m_sim_data.size() == 0 || m_exp_data.size() == 0)
        throwInitializationException("relativeDifference");

    SimulationResult result = m_sim_data;
    for (size_t i = 0, size = result.size(); i < size; ++i)
        result[i] = Numeric::GetRelativeDifference(result[i], m_exp_data[i]);

    return result;
}

SimulationResult SimDataPair::absoluteDifference() const
{
    if (m_sim_data.size() == 0 || m_exp_data.size() == 0)
        throwInitializationException("absoluteDifference");

    SimulationResult result = m_sim_data;
    for (size_t i = 0, size = result.size(); i < size; ++i)
        result[i] = Numeric::GetAbsoluteDifference(result[i], m_exp_data[i]);

    return result;
}

std::vector<double> SimDataPair::experimental_array() const
{
    if (m_exp_data.size() == 0)
        throwInitializationException("experimental_array");
    return m_exp_data.data()->getRawDataVector();
}

std::vector<double> SimDataPair::simulation_array() const
{
    if (m_sim_data.size() == 0)
        throwInitializationException("simulation_array");
    return m_sim_data.data()->getRawDataVector();
}

std::vector<double> SimDataPair::uncertainties_array() const
{
    if (m_uncertainties.size() == 0)
        throwInitializationException("uncertainties_array");
    return m_uncertainties.data()->getRawDataVector();
}

std::vector<double> SimDataPair::user_weights_array() const
{
    if (m_user_weights.size() == 0)
        throwInitializationException("user_weights_array");
    return m_user_weights.data()->getRawDataVector();
}

void SimDataPair::initResultArrays()
{
    if (m_exp_data.size() != 0 && m_uncertainties.size() != 0 && m_user_weights.size() != 0)
        return;

    if (!m_simulation || m_sim_data.size() == 0)
        throwInitializationException("initResultArrays");

    m_exp_data = m_simulation->convertData(*m_raw_data, true);

    if (containsUncertainties()) {
        m_uncertainties = m_simulation->convertData(*m_raw_uncertainties, true);
    } else {
        const IUnitConverter& converter = m_sim_data.converter();
        std::unique_ptr<OutputData<double>> dummy_array =
            UnitConverterUtils::createOutputData(converter, converter.defaultUnits());
        m_uncertainties = SimulationResult(*dummy_array, converter);
    }

    m_user_weights = m_simulation->convertData(*m_raw_user_weights, true);
}

void SimDataPair::validate() const
{
    if (!m_simulation_builder)
        throw std::runtime_error("Error in SimDataPair: simulation builder is empty");

    if (!m_raw_data)
        throw std::runtime_error("Error in SimDataPair: passed experimental data array is empty");

    if (m_raw_uncertainties && !m_raw_uncertainties->hasSameShape(*m_raw_data))
        throw std::runtime_error(
            "Error in SimDataPair: experimental data and uncertainties have different shape.");

    if (!m_raw_user_weights || !m_raw_user_weights->hasSameShape(*m_raw_data))
        throw std::runtime_error(
            "Error in SimDataPair: user weights are not initialized or have invalid shape");
}
