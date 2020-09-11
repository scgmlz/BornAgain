// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/ExportToPython.cpp
//! @brief     Implements ExportToPython namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Export/ExportToPython.h"
#include "Core/Export/SampleToPython.h"
#include "Core/Export/SimulationToPython.h"
#include "Core/Simulation/GISASSimulation.h"

namespace
{
std::string simulationCode(const Simulation& simulation,
                           SimulationToPython::EMainType mainFunctionType)
{
    std::unique_ptr<Simulation> sim(simulation.clone());
    sim->prepareSimulation();

    SimulationToPython generator;
    return generator.generateSimulationCode(*sim, mainFunctionType);
}
} // namespace

std::string ExportToPython::generateSampleCode(const MultiLayer& multilayer)
{
    SampleToPython generator;
    return generator.generateSampleCode(multilayer);
}

std::string ExportToPython::generateSimulationCode(const Simulation& simulation)
{
    return simulationCode(simulation, SimulationToPython::RUN_SIMULATION);
}

std::string ExportToPython::generatePyExportTest(const Simulation& simulation)
{
    return simulationCode(simulation, SimulationToPython::SAVE_DATA);
}
