// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularSimulation.h
//! @brief     Defines class SpecularSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SIMULATION_SPECULARSIMULATION_H
#define BORNAGAIN_CORE_SIMULATION_SPECULARSIMULATION_H

#include "Core/Intensity/OutputData.h"
#include "Core/RT/ILayerRTCoefficients.h"
#include "Core/Simulation/Simulation.h"

class IAxis;
class IComputation;
class IFootprintFactor;
class IMultiLayerBuilder;
class ISample;
class ISpecularScan;
class MultiLayer;
class SpecularSimulationElement;

//! Main class to run a specular simulation.
//! @ingroup simulation

class BA_CORE_API_ SpecularSimulation : public Simulation
{
public:
    SpecularSimulation();
    SpecularSimulation(const MultiLayer& sample);
    SpecularSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder);
    ~SpecularSimulation() override;

    SpecularSimulation* clone() const override;

    //! Put into a clean state for running a simulation.
    void prepareSimulation() override;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    //! Returns the results of the simulation in a format that supports unit conversion and export
    //! to numpy arrays. If simulation was not run, returns an array of proper size filled with
    //! zeros.
    SimulationResult result() const override;

    //! Sets chosen specular scan to the simulation.
    void setScan(const ISpecularScan& scan);

    //! Returns a pointer to coordinate axis.
    const IAxis* coordinateAxis() const;

    //! Returns a pointer to footprint factor holder
    const IFootprintFactor* footprintFactor() const;

    //! Returns the total number of the intensity values in the simulation result
    size_t intensityMapSize() const override;

#ifndef SWIG
    //! Returns internal data handler
    const ISpecularScan* dataHandler() const { return m_data_handler.get(); }
#endif // SWIG

private:
    SpecularSimulation(const SpecularSimulation& other);

    //! Initializes the vector of Simulation elements
    void initSimulationElementVector() override;

    //! Generate simulation elements for given beam
    std::vector<SpecularSimulationElement> generateSimulationElements(const Beam& beam);

    //! Generate a single threaded computation for a given range of simulation elements
    //! @param start Index of the first element to include into computation
    //! @param n_elements Number of elements to process
    std::unique_ptr<IComputation> generateSingleThreadedComputation(size_t start,
                                                                    size_t n_elements) override;

    void checkCache() const;

    //! Checks the distribution validity for simulation.
    void validateParametrization(const ParameterDistribution& par_distr) const override;

    //! Initializes simulation
    void initialize();

    //! Normalize the detector counts to beam intensity, to solid angle, and to exposure angle.
    //! @param start_ind Index of the first element to operate on
    //! @param n_elements Number of elements to process
    void normalize(size_t start_ind, size_t n_elements) override;

    void addBackGroundIntensity(size_t start_ind, size_t n_elements) override;

    void addDataToCache(double weight) override;

    void moveDataFromCache() override;

    //! Gets the number of elements this simulation needs to calculate
    size_t numberOfSimulationElements() const override;

    //! Creates intensity data from simulation elements
    std::unique_ptr<OutputData<double>> createIntensityData() const;

    std::vector<double> rawResults() const override;
    void setRawResults(const std::vector<double>& raw_data) override;

    std::unique_ptr<ISpecularScan> m_data_handler;
    std::vector<SpecularSimulationElement> m_sim_elements;
    std::vector<double> m_cache;
};

#endif // BORNAGAIN_CORE_SIMULATION_SPECULARSIMULATION_H
