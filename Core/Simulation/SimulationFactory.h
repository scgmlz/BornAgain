//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SimulationFactory.h
//! @brief     Defines class SimulationFactory.
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
#ifndef BORNAGAIN_CORE_SIMULATION_SIMULATIONFACTORY_H
#define BORNAGAIN_CORE_SIMULATION_SIMULATIONFACTORY_H

#include "Base/Utils/IFactory.h"
#include "Core/Simulation/GISASSimulation.h"
#include <string>

//! Registry to create standard pre-defined simulations.
//! Used in functional tests, performance measurements, etc.
//! @ingroup standard_samples

class SimulationFactory : public IFactory<std::string, ISimulation> {
public:
    SimulationFactory();
};

#endif // BORNAGAIN_CORE_SIMULATION_SIMULATIONFACTORY_H
#endif // USER_API
