// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputation.h
//! @brief     Defines interface IComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPUTATION_H
#define ICOMPUTATION_H

#include "ComputationStatus.h"
#include <memory>
#include <vector>

class ProgressHandler;
class SimulationElement;

//! Interface for a single-threaded computation with given range of SimulationElements
//! and ProgressHandler.
//!
//! Controlled by the multi-threading machinery in Simulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class IComputation
{
public:
    IComputation(ProgressHandler& progress,
                 const std::vector<SimulationElement>::iterator& start,
                 const std::vector<SimulationElement>::iterator& end);
    virtual ~IComputation();

    virtual void run() =0;

    bool isCompleted() const { return m_status.isCompleted(); }
    std::string errorMessage() const { return m_status.errorMessage(); }

protected:
    ProgressHandler* m_progress;

    //! these iterators define the span of detector bins this simulation will work on
    std::vector<SimulationElement>::iterator m_begin_it, m_end_it;

    ComputationStatus m_status;
};

#endif // ICOMPUTATION_H
