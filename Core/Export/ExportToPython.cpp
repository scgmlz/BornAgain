//  ************************************************************************************************
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
//  ************************************************************************************************

#include "Core/Export/ExportToPython.h"
#include "Core/Export/SampleToPython.h"
#include "Core/Export/SimulationToPython.h"
#include "Core/Simulation/ISimulation.h"

std::string ExportToPython::generateSampleCode(const MultiLayer& multilayer) {
    return SampleToPython().generateSampleCode(multilayer);
}

std::string ExportToPython::generateSimulationCode(const ISimulation& simulation) {
    return SimulationToPython().generateSimulationCode(simulation);
}
