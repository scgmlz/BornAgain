// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/GISASSimulation.h
//! @brief     Defines class GISASSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SIMULATION_GISASSIMULATION_H
#define BORNAGAIN_CORE_SIMULATION_GISASSIMULATION_H

#include "Core/Simulation/Simulation2D.h"
#include "Core/SimulationElement/SimulationElement.h"

class MultiLayer;
class IMultiLayerBuilder;

//! Main class to run a Grazing-Incidence Small-Angle Scattering simulation.
//! @ingroup simulation

class BA_CORE_API_ GISASSimulation : public Simulation2D
{
public:
    GISASSimulation();
    GISASSimulation(const MultiLayer& p_sample);
    GISASSimulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder);

    ~GISASSimulation() {}

    GISASSimulation* clone() const override { return new GISASSimulation(*this); }

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Put into a clean state for running a simulation
    void prepareSimulation() override;

    //! Returns the results of the simulation in a format that supports unit conversion and export
    //! to numpy arrays
    SimulationResult result() const override;

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double wavelength, double alpha_i, double phi_i);

    //! Returns the total number of the intensity values in the simulation result
    size_t intensityMapSize() const override;

private:
    GISASSimulation(const GISASSimulation& other);

    //! Initializes the vector of Simulation elements
    void initSimulationElementVector() override;

    void initialize();
};

#endif // BORNAGAIN_CORE_SIMULATION_GISASSIMULATION_H
