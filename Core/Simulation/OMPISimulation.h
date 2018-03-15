// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      unused/OMPISimulation.h
//! @brief     Defines class OMPISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OMPISIMULATION_H
#define OMPISIMULATION_H

class Simulation;

class OMPISimulation
{
public:
    void runSimulation(Simulation *simulation);
};

#endif // OMPISIMULATION_H
