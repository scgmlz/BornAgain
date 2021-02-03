//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Core/Simulation/ISimulation.h
//! @brief     Defines interface ISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_CORE_SIMULATION_ISIMULATION_H
#define BORNAGAIN_CORE_SIMULATION_ISIMULATION_H

#include "Base/Progress/ProgressHandler.h"
#include "Device/Detector/IDetector2D.h"
#include "Device/Histo/SimulationResult.h"
#include "Device/Instrument/Instrument.h"
#include "Param/Distrib/DistributionHandler.h"
#include "Sample/RT/SimulationOptions.h"
#include "Sample/SampleBuilderEngine/SampleProvider.h"

template <class T> class OutputData;
class IBackground;
class IComputation;
class ISampleBuilder;
class MultiLayer;

//! Abstract base class of OffSpecularSimulation, GISASSimulation and SpecularSimulation.
//! Holds the common infrastructure to run a simulation: multithreading, batch processing,
//! weighting over parameter distributions, ...
//! @ingroup simulation

class ISimulation : public ICloneable, public INode {
public:
    ISimulation(const Beam& beam, const MultiLayer& sample, const IDetector& detector);
    ISimulation();
    virtual ~ISimulation();

    virtual ISimulation* clone() const = 0;

    //! Put into a clean state for running a simulation
    virtual void prepareSimulation();

    //! Run a simulation, possibly averaged over parameter distributions
    void runSimulation();

    //! Run a simulation in a MPI environment
    void runMPISimulation();

    const Instrument& instrument() const { return m_instrument; }
    Instrument& instrument() { return m_instrument; }

    Beam& beam() { return m_instrument.beam(); }
    const Beam& beam() const { return m_instrument.beam(); }

    IDetector* getDetector() { return m_instrument.getDetector(); }
    const IDetector* getDetector() const { return m_instrument.getDetector(); }
    IDetector& detector() { return m_instrument.detector(); }
    const IDetector& detector() const { return m_instrument.detector(); }

    void setDetectorResolutionFunction(const IResolutionFunction2D& resolution_function);

    virtual void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission);

    void setSample(const MultiLayer& sample);
    const MultiLayer* sample() const;

    void setSampleBuilder(const std::shared_ptr<ISampleBuilder>& sample_builder);

    void setBackground(const IBackground& bg);
    const IBackground* background() const { return m_background.get(); }

    //! Returns the total number of the intensity values in the simulation result
    virtual size_t intensityMapSize() const = 0;

    //! Returns the results of the simulation in a format that supports unit conversion and export
    //! to numpy arrays
    virtual SimulationResult result() const = 0;

    void addParameterDistribution(const std::string& param_name,
                                  const IDistribution1D& distribution, size_t nbr_samples,
                                  double sigma_factor = 0.0,
                                  const RealLimits& limits = RealLimits());
    void addParameterDistribution(const ParameterDistribution& par_distr);
    const DistributionHandler& getDistributionHandler() const { return m_distribution_handler; }

    void setOptions(const SimulationOptions& options) { m_options = options; }
    const SimulationOptions& getOptions() const { return m_options; }
    SimulationOptions& getOptions() { return m_options; }

    void subscribe(ProgressHandler::Callback_t inform) { m_progress.subscribe(inform); }
    void setTerminalProgressMonitor();

    std::vector<const INode*> getChildren() const;

    SimulationResult convertData(const OutputData<double>& data,
                                 bool put_masked_areas_to_zero = true);

    friend class MPISimulation;

#ifndef SWIG
    ISimulation(const Beam& beam, const IDetector& detector);
    void setInstrument(const Instrument& instrument_);
#endif // SWIG

protected:
    ISimulation(const ISimulation& other);

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    virtual void transferResultsToIntensityMap() {}

    //! Initializes the vector of ISimulation elements
    virtual void initSimulationElementVector() = 0;

    virtual void updateIntensityMap() {}

    //! Gets the number of elements this simulation needs to calculate
    virtual size_t numberOfSimulationElements() const = 0;

    const SimulationOptions& options() const { return m_options; }
    ProgressHandler& progress() { return m_progress; }

private:
    void initialize();

    void runSingleSimulation(size_t batch_start, size_t batch_size, double weight = 1.0);

    //! Generate a single threaded computation for a given range of simulation elements
    //! @param start Index of the first element to include into computation
    //! @param n_elements Number of elements to process
    virtual std::unique_ptr<IComputation> generateSingleThreadedComputation(size_t start,
                                                                            size_t n_elements) = 0;

    //! Checks the distribution validity for simulation.
    virtual void validateParametrization(const ParameterDistribution&) const {}

    virtual void addBackgroundIntensity(size_t start_ind, size_t n_elements) = 0;

    //! Normalize the detector counts to beam intensity, to solid angle, and to exposure angle.
    //! @param start_ind Index of the first element to operate on
    //! @param n_elements Number of elements to process
    virtual void normalize(size_t start_ind, size_t n_elements) = 0;

    virtual void addDataToCache(double weight) = 0;

    virtual void moveDataFromCache() = 0;

    // used in MPI calculations for transfer of partial results
    virtual std::vector<double> rawResults() const = 0;
    virtual void setRawResults(const std::vector<double>& raw_data) = 0;

    SimulationOptions m_options;
    ProgressHandler m_progress;
    SampleProvider m_sample_provider;
    DistributionHandler m_distribution_handler;
    Instrument m_instrument;
    std::unique_ptr<IBackground> m_background;
};

#endif // BORNAGAIN_CORE_SIMULATION_ISIMULATION_H
#endif // USER_API
