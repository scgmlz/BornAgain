// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/MPISimulation.h
//! @brief     Defines class MPISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SIMULATION_MPISIMULATION_H
#define BORNAGAIN_CORE_SIMULATION_MPISIMULATION_H

class Simulation;

class MPISimulation
{
public:
    void runSimulation(Simulation* simulation);
};

#endif // BORNAGAIN_CORE_SIMULATION_MPISIMULATION_H
