// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Simulation.h"
#include "IMultiLayerBuilder.h"
#include "MultiLayer.h"
#include "MainComputation.h"
#include "ParameterPool.h"
#include "ParameterSample.h"
#include "SimulationElement.h"
#include "StringUtils.h"
#include <thread>
#include <gsl/gsl_errno.h>
#include <iomanip>
#include <iostream>

Simulation::Simulation()
{
    initialize();
}

Simulation::Simulation(const MultiLayer& p_sample)
{
    initialize();
    m_sample_provider.setSample(p_sample);
}

Simulation::Simulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
{
    initialize();
    m_sample_provider.setSampleBuilder(p_sample_builder);
}

Simulation::Simulation(const Simulation& other)
    : m_sample_provider(other.m_sample_provider)
    , m_options(other.m_options)
    , m_distribution_handler(other.m_distribution_handler)
    , m_progress(other.m_progress)
    , m_instrument(other.m_instrument)
{
    initialize();
}

Simulation::~Simulation() {}

//! Initializes a progress monitor that prints to stdout.
void Simulation::setTerminalProgressMonitor()
{
    m_progress.subscribe( [] (size_t percentage_done) -> bool {
            if (percentage_done<100)
                std::cout << std::setprecision(2)
                          << "\r... " << percentage_done << "%" << std::flush;
            else // wipe out
                std::cout << "\r... 100%\n";
            return true;
    } );
}

void Simulation::setDetectorResolutionFunction(const IResolutionFunction2D& resolution_function)
{
    m_instrument.setDetectorResolutionFunction(resolution_function);
}

void Simulation::removeDetectorResolutionFunction()
{
    m_instrument.removeDetectorResolution();
}

//! Sets the polarization analyzer characteristics of the detector
void Simulation::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                       double total_transmission)
{
    m_instrument.setAnalyzerProperties(direction, efficiency, total_transmission);
}

void Simulation::setBeamIntensity(double intensity)
{
    m_instrument.setBeamIntensity(intensity);
}

double Simulation::getBeamIntensity() const
{
    return m_instrument.getBeamIntensity();
}

//! Sets the beam polarization according to the given Bloch vector
void Simulation::setBeamPolarization(const kvector_t bloch_vector)
{
    m_instrument.setBeamPolarization(bloch_vector);
}

void Simulation::prepareSimulation()
{
    updateSample();
    gsl_set_error_handler_off();
}

//! Run simulation with possible averaging over parameter distributions
void Simulation::runSimulation()
{
    prepareSimulation();

    size_t param_combinations = m_distribution_handler.getTotalNumberOfSamples();

    m_progress.reset();
    size_t prefactor = ( sample()->totalNofLayouts()>0 ? 1 : 0 )
        + ( sample()->hasRoughness() ? 1 : 0 );
    m_progress.setExpectedNTicks(prefactor*param_combinations*numberOfSimulationElements());

    // no averaging needed:
    if (param_combinations == 1) {
        std::unique_ptr<ParameterPool> P_param_pool(createParameterTree());
        m_distribution_handler.setParameterValues(P_param_pool.get(), 0);
        runSingleSimulation();
        transferResultsToIntensityMap();
        return;
    }

    // average over parameter distributions:
    initSimulationElementVector();
    std::vector<SimulationElement> total_intensity = m_sim_elements;
    std::unique_ptr<ParameterPool> P_param_pool(createParameterTree());
    for (size_t index = 0; index < param_combinations; ++index) {
        double weight = m_distribution_handler.setParameterValues(P_param_pool.get(), index);
        runSingleSimulation();
        addElementsWithWeight(m_sim_elements.begin(), m_sim_elements.end(), total_intensity.begin(),
                              weight);
    }
    m_sim_elements = total_intensity;
    transferResultsToIntensityMap();
}

/* currently unused
void Simulation::runOMPISimulation()
{
    OMPISimulation ompi;
    ompi.runSimulation(this);
}
*/

void Simulation::setInstrument(const Instrument& instrument)
{
    m_instrument = instrument;
    updateIntensityMap();
}

//! The MultiLayer object will not be owned by the Simulation object
void Simulation::setSample(const MultiLayer& sample)
{
    m_sample_provider.setSample(sample);
}

const MultiLayer* Simulation::sample() const
{
    return m_sample_provider.sample();
}

void Simulation::setSampleBuilder(const std::shared_ptr<class IMultiLayerBuilder> p_sample_builder)
{
    m_sample_provider.setSampleBuilder(p_sample_builder);
}

std::vector<const INode*> Simulation::getChildren() const
{
    std::vector<const INode*> result;
    result.push_back(&m_instrument);
    result << m_sample_provider.getChildren();
    return result;
}

void Simulation::addParameterDistribution(const std::string& param_name,
                                          const IDistribution1D& distribution, size_t nbr_samples,
                                          double sigma_factor, const RealLimits& limits)
{
    m_distribution_handler.addParameterDistribution(
        param_name, distribution, nbr_samples, sigma_factor, limits);
}

void Simulation::addParameterDistribution(const ParameterDistribution& par_distr)
{
    m_distribution_handler.addParameterDistribution(par_distr);
}

void Simulation::updateSample()
{
    m_sample_provider.updateSample();
}

//! Runs a single simulation with fixed parameter values.
//! If desired, the simulation is run in several threads.
void Simulation::runSingleSimulation()
{
    prepareSimulation();
    initSimulationElementVector();

    // restrict calculation to current batch
    std::vector<SimulationElement>::iterator batch_start
        = getBatchStart(m_options.getNumberOfBatches(), m_options.getCurrentBatch());

    std::vector<SimulationElement>::iterator batch_end
        = getBatchEnd(m_options.getNumberOfBatches(), m_options.getCurrentBatch());

    if (m_options.getNumberOfThreads() == 1) {
        // Single thread.
        std::unique_ptr<MainComputation> P_computation(
            new MainComputation(*sample(), m_options, m_progress, batch_start, batch_end));
        P_computation->run(); // the work is done here
        if (!P_computation->isCompleted()) {
            std::string message = P_computation->errorMessage();
            throw Exceptions::RuntimeErrorException("Simulation::runSimulation() -> Simulation has "
                                                    "terminated unexpectedly with following error "
                                                    "message.\n" + message);
        }
    } else {
        // Multithreading.
        std::vector<std::unique_ptr<std::thread>> threads;
        std::vector<std::unique_ptr<MainComputation>> computations;

        // Initialize n computations.
        auto total_batch_elements = batch_end - batch_start;
        auto element_thread_step = total_batch_elements / m_options.getNumberOfThreads();
        if (total_batch_elements % m_options.getNumberOfThreads()) // there is a remainder
            ++element_thread_step;

        for (int i_thread = 0; i_thread < m_options.getNumberOfThreads(); ++i_thread) {
            if (i_thread*element_thread_step >= total_batch_elements)
                break;
            std::vector<SimulationElement>::iterator begin_it = batch_start
                                                                + i_thread * element_thread_step;
            std::vector<SimulationElement>::iterator end_it;
            auto end_thread_index = (i_thread+1) * element_thread_step;
            if (end_thread_index >= total_batch_elements)
                end_it = batch_end;
            else
                end_it = batch_start + end_thread_index;
            computations.emplace_back(
                new MainComputation(*sample(), m_options, m_progress, begin_it, end_it));
        }

        // Run simulations in n threads.
        for (auto& comp: computations)
            threads.emplace_back(new std::thread([&comp]() {comp->run();}));

        // Wait for threads to complete.
        for (auto& thread: threads) {
            thread->join();
        }

        // Check successful completion.
        std::vector<std::string> failure_messages;
        for (auto& comp: computations) {
            if (!comp->isCompleted())
                failure_messages.push_back(comp->errorMessage());
        }
        if (failure_messages.size())
            throw Exceptions::RuntimeErrorException(
                "Simulation::runSingleSimulation() -> "
                "At least one simulation thread has terminated unexpectedly.\n"
                "Messages: " + StringUtils::join(failure_messages, " --- "));
    }
    normalize(batch_start, batch_end);
}

//! Normalize the detector counts to beam intensity, to solid angle, and to exposure angle.
void Simulation::normalize(std::vector<SimulationElement>::iterator begin_it,
                           std::vector<SimulationElement>::iterator end_it) const
{
    double beam_intensity = getBeamIntensity();
    if (beam_intensity==0.0)
        return; // no normalization when beam intensity is zero
    for(auto it=begin_it; it!=end_it; ++it) {
        double sin_alpha_i = std::abs(std::sin(it->getAlphaI()));
        if (sin_alpha_i==0.0) sin_alpha_i = 1.0;
        double solid_angle = it->getSolidAngle();
        it->setIntensity(it->getIntensity()*beam_intensity*solid_angle/sin_alpha_i);
    }
}

std::vector<SimulationElement>::iterator Simulation::getBatchStart(int n_batches, int current_batch)
{
    imposeConsistencyOfBatchNumbers(n_batches, current_batch);
    int total_size = static_cast<int>(m_sim_elements.size());
    int size_per_batch = total_size/n_batches;
    if (total_size%n_batches)
        ++size_per_batch;
    if (current_batch*size_per_batch >= total_size)
        return m_sim_elements.end();
    return m_sim_elements.begin() + current_batch*size_per_batch;
}

std::vector<SimulationElement>::iterator Simulation::getBatchEnd(int n_batches, int current_batch)
{
    imposeConsistencyOfBatchNumbers(n_batches, current_batch);
    int total_size = static_cast<int>(m_sim_elements.size());
    int size_per_batch = total_size/n_batches;
    if (total_size%n_batches)
        ++size_per_batch;
    int end_index = (current_batch + 1)*size_per_batch;
    if (end_index >= total_size)
        return m_sim_elements.end();
    return m_sim_elements.begin() + end_index;
}

void Simulation::initialize()
{
    registerChild(&m_instrument);
    registerChild(&m_sample_provider);
}

void Simulation::imposeConsistencyOfBatchNumbers(int& n_batches, int& current_batch)
{
    if (n_batches < 2) {
        n_batches = 1;
        current_batch = 0;
    }
    if (current_batch >= n_batches)
        throw Exceptions::ClassInitializationException(
            "Simulation::imposeConsistencyOfBatchNumbers(): Batch number must be smaller than "
            "number of batches.");
}
