// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/SimDataPair.h
//! @brief     Defines class SimDataPair.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SimDataPair.h"
#include "Simulation.h"
#include "IntensityDataFunctions.h"

static_assert(std::is_copy_constructible<SimDataPair>::value == false,
              "SimDataPair should not be copy constructable");
static_assert(std::is_copy_assignable<SimDataPair>::value == false,
              "SimDataPair should not be copy assignable");

//! Constructs simulation/data pair for later fit.
//! @param simulation: simulation builder capable of producing simulations
//! @param data: experimental data
//! @param weight: weight of dataset in chi2 calculations

SimDataPair::SimDataPair(simulation_builder_t builder, const OutputData<double>& data,
                         double weight)
    : m_simulation_builder(builder)
    , m_data(data.clone())
    , m_weight(weight)
    , m_fit_elements_count(0)
{

}

SimDataPair* SimDataPair::clone() const
{
    return new SimDataPair(m_simulation_builder, *m_data, m_weight);
}

//! Returns the size of the data. It is equal to the number of non-masked detector channels
//! which will participate in chi2 calculations.

size_t SimDataPair::numberOfFitElements() const
{
    return m_fit_elements_count;
}

double SimDataPair::weight() const
{
    return m_weight;
}

//! Returns simulation result.

SimulationResult SimDataPair::simulationResult() const
{
    return m_simulation_result;
}

//! Returns experimental data.

SimulationResult SimDataPair::experimentalData() const
{
    return m_experimental_data;
}

SimDataPair::~SimDataPair() = default;

void SimDataPair::runSimulation(const Fit::Parameters& params)
{
    create_simulation(params);

    m_simulation->runSimulation();
    m_simulation_result = m_simulation->result();

    m_simulation_array.clear();
    m_simulation_array.reserve(numberOfFitElements());
    auto detector = m_simulation->getInstrument().getDetector();
    detector->iterate([&](IDetector::const_iterator it){
        m_simulation_array.push_back(m_simulation_result[it.roiIndex()]);
    });
}

//! Returns one dimensional array representing experimental data.
//! Masked areas and the area outside of region of interest are not included.

std::vector<double> SimDataPair::experimental_array() const
{
    return m_experimental_array;
}

//! Returns one dimensional array representing simulated intensities data.
//! Masked areas and the area outside of region of interest are not included.

std::vector<double> SimDataPair::simulation_array() const
{
    return m_simulation_array;
}

//! Creates new simulation for given set of fit parameters.
//! If it is first call, save number of fit elements (supposed to stay the same during the fit),
//! and converts raw user data to SimulationResult.

void SimDataPair::create_simulation(const Fit::Parameters& params)
{
    m_simulation = m_simulation_builder(params);

    if (m_fit_elements_count == 0) {
        m_fit_elements_count = m_simulation->numberOfSimulationElements();
        m_experimental_data = IntensityDataFunctions::ConvertData(*m_simulation, *m_data, false);

        m_experimental_array.clear();
        m_experimental_array.reserve(numberOfFitElements());

        auto detector = m_simulation->getInstrument().getDetector();
        detector->iterate([&](IDetector::const_iterator it){
            m_experimental_array.push_back(m_experimental_data[it.roiIndex()]);
        });
    }
}


