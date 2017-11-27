// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation.h
//! @brief     Defines class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATION_H
#define SIMULATION_H

#include "INode.h"
#include "DistributionHandler.h"
#include "IDetector2D.h"
#include "Instrument.h"
#include "ProgressHandler.h"
#include "SimulationOptions.h"
#include "SampleProvider.h"

template<class T> class OutputData;
class IBackground;
class IComputation;
class IMultiLayerBuilder;
class MultiLayer;

//! Pure virtual base class of OffSpecularSimulation, GISASSimulation and SpecularSimulation.
//! Holds the common infrastructure to run a simulation: multithreading, batch processing,
//! weighting over parameter distributions, ...
//! @ingroup simulation

class BA_CORE_API_ Simulation : public ICloneable, public INode
{
public:
    Simulation();
    Simulation(const MultiLayer& p_sample);
    Simulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder);
    virtual ~Simulation();

    virtual Simulation* clone() const =0;

    //! Put into a clean state for running a simulation
    virtual void prepareSimulation();

    //! Run a simulation, possibly averaged over parameter distributions
    virtual void runSimulation();

    void setInstrument(const Instrument& instrument);
    const Instrument& getInstrument() const { return m_instrument; }
    Instrument& getInstrument() { return m_instrument; }

    void setBeamIntensity(double intensity);
    double getBeamIntensity() const;

    void setBeamPolarization(const kvector_t bloch_vector);

    void setDetectorResolutionFunction(const IResolutionFunction2D& resolution_function);
    void removeDetectorResolutionFunction();

    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission);

    void setSample(const MultiLayer& sample);
    const MultiLayer* sample() const;

    void setSampleBuilder(const std::shared_ptr<IMultiLayerBuilder> sample_builder);

    void setBackGround(const IBackground& bg);

    virtual size_t numberOfSimulationElements() const=0;

    //! Clone simulated intensity map
    virtual OutputData<double>* getDetectorIntensity(
        AxesUnits units_type = AxesUnits::DEFAULT) const=0;

    void addParameterDistribution(
        const std::string& param_name, const IDistribution1D& distribution, size_t nbr_samples,
        double sigma_factor=0.0, const RealLimits& limits = RealLimits());
    void addParameterDistribution(const ParameterDistribution& par_distr);
    const DistributionHandler& getDistributionHandler() const { return m_distribution_handler; }

    void setOptions(const SimulationOptions& options) { m_options = options; }
    const SimulationOptions& getOptions() const { return m_options; }
    SimulationOptions& getOptions() { return m_options; }

    void subscribe(ProgressHandler::Callback_t inform) { m_progress.subscribe(inform); }
    void setTerminalProgressMonitor();

    std::vector<const INode*> getChildren() const;

protected:
    Simulation(const Simulation& other);

    virtual void initSimulationElementVector() =0;

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    virtual void transferResultsToIntensityMap() =0;

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    //! Generate a single threaded computation for a given range of SimulationElement's
    virtual std::unique_ptr<IComputation> generateSingleThreadedComputation(
            std::vector<SimulationElement>::iterator start,
            std::vector<SimulationElement>::iterator end);

    void runSingleSimulation();

    virtual void updateIntensityMap() =0;

#ifndef SWIG
    void normalize(std::vector<SimulationElement>::iterator begin_it,
                   std::vector<SimulationElement>::iterator end_it) const;

    void addBackGroundIntensity(std::vector<SimulationElement>::iterator begin_it,
                                std::vector<SimulationElement>::iterator end_it) const;
#endif

    //! Returns the start iterator of simulation elements for the current batch
    std::vector<SimulationElement>::iterator getBatchStart(int n_batches, int current_batch);

    //! Returns the end iterator of simulation elements for the current batch
    std::vector<SimulationElement>::iterator getBatchEnd(int n_batches, int current_batch);

    SampleProvider m_sample_provider;
    SimulationOptions m_options;
    DistributionHandler m_distribution_handler;
    ProgressHandler m_progress;
    std::vector<SimulationElement> m_sim_elements;
    Instrument m_instrument;
    std::unique_ptr<IBackground> mP_background;

private:
    void initialize();
    void imposeConsistencyOfBatchNumbers(int& n_batches, int& current_batch);
};

#endif // SIMULATION_H
