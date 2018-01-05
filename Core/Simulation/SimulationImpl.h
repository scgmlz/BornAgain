//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SimulationImpl.h
//! @brief     Defines class SimulationImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SIMULATIONIMPL_H_
#define SIMULATIONIMPL_H_

#include "Simulation.h"
#include "SimulationElement.h"

class IComputation;

//! Abstract Simulation implementation,
//! base class for OffSpecularSimulation, GISASSimulation and SpecularSimulation.
//! Operates on the vector of simulation elements
//! @ingroup simulation

class BA_CORE_API_ SimulationImpl : public Simulation
{
public:
    using Simulation::Simulation;
    SimulationImpl(); // required until C++17
    virtual ~SimulationImpl();

    //! Run a simulation, possibly averaged over parameter distributions
    virtual void runSimulation() override final;

    typedef std::vector<SimulationElement> SimElementVector;

protected:
    SimulationImpl(const SimulationImpl& other);

    //! Initializes the vector of Simulation elements
    virtual void initSimulationElementVector();

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    virtual void transferResultsToIntensityMap() = 0;

    //! Generate a single threaded computation for a given range of SimulationElement's
    virtual std::unique_ptr<IComputation>
    generateSingleThreadedComputation(SimElementVector::iterator start,
                                      SimElementVector::iterator end) = 0;

    //! Normalize the detector counts to beam intensity, to solid angle, and to exposure angle.
    virtual void normalize(SimElementVector::iterator begin_it,
                           SimElementVector::iterator end_it) const;

    void addBackGroundIntensity(SimElementVector::iterator begin_it,
                                SimElementVector::iterator end_it) const;

    SimElementVector m_sim_elements;

private:
    //! Runs a single simulation with fixed parameter values.
    //! If desired, the simulation is run in several threads.
    void runSingleSimulation();

    //! Returns the start iterator of simulation elements for the current batch
    SimElementVector::iterator getBatchStart(int n_batches, int current_batch);

    //! Returns the end iterator of simulation elements for the current batch
    SimElementVector::iterator getBatchEnd(int n_batches, int current_batch);

    //! Add element vector to element vector with weight
    void addElementsWithWeight(SimElementVector::iterator result, double weight) const;
    void imposeConsistencyOfBatchNumbers(int& n_batches, int& current_batch);
};

#endif /* SIMULATIONIMPL_H_ */
