// ************************************************************************** //
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
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SIMULATION_SIMULATIONFACTORY_H
#define BORNAGAIN_CORE_SIMULATION_SIMULATIONFACTORY_H

#include "Core/Simulation/GISASSimulation.h"
#include "Fit/TestEngine/IFactory.h"
#include <string>

//! Registry to create standard pre-defined simulations.
//! Used in functional tests, performance measurements, etc.
//! @ingroup standard_samples

class SimulationFactory : public IFactory<std::string, Simulation>
{
public:
    SimulationFactory();
};

#endif // BORNAGAIN_CORE_SIMULATION_SIMULATIONFACTORY_H
