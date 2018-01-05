// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation.h
//! @brief     Defines class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
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
class IMultiLayerBuilder;
class MultiLayer;

//! Abstract base class for simulation implementations.
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

    //! Run a simulation, possibly averaged over parameter distributions
    virtual void runSimulation() = 0;

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

    void setBackground(const IBackground& bg);
    const IBackground* background() const { return mP_background.get(); }

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

    void subscribe(ProgressHandler::Callback_t inform) { m_progress->subscribe(inform); }
    void setTerminalProgressMonitor();

    std::vector<const INode*> getChildren() const;

protected:
    Simulation(const Simulation& other);

    //! Put into a clean state for running a simulation
    virtual void prepareSimulation();

    //! Update the sample by calling the sample builder, if present
    void updateSample();

    virtual void updateIntensityMap() =0;

    SampleProvider m_sample_provider;
    SimulationOptions m_options;
    DistributionHandler m_distribution_handler;
    std::shared_ptr<ProgressHandler> m_progress;
    Instrument m_instrument;
    std::unique_ptr<IBackground> mP_background;

private:
    void initialize();
};

#endif // SIMULATION_H
