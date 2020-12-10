//  ************************************************************************************************
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
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_CORE_SIMULATION_MPISIMULATION_H
#define BORNAGAIN_CORE_SIMULATION_MPISIMULATION_H

class ISimulation;

class MPISimulation {
public:
    void runSimulation(ISimulation* simulation);
};

#endif // BORNAGAIN_CORE_SIMULATION_MPISIMULATION_H
#endif // USER_API
