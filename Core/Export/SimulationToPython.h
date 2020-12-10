//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SimulationToPython.h
//! @brief     Defines class SimulationToPython.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_CORE_EXPORT_SIMULATIONTOPYTHON_H
#define BORNAGAIN_CORE_EXPORT_SIMULATIONTOPYTHON_H

#include <string>

class ISimulation;

//! Write a Python script that allows to run the current simulation.

class SimulationToPython {
public:
    //! Returns a Python script that sets up a simulation and runs it if invoked as main program.
    std::string generateSimulationCode(const ISimulation& simulation);
};

#endif // BORNAGAIN_CORE_EXPORT_SIMULATIONTOPYTHON_H
#endif // USER_API
