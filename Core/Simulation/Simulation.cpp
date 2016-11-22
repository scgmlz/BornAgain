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
#include "Logger.h"
#include "ParameterPool.h"
#include "ParameterSample.h"
#include "SimulationElement.h"
#include "StringUtils.h"
#include <gsl/gsl_errno.h>
#include <thread>
#include <iomanip>
#include <iostream>

Simulation::Simulation()
{}

Simulation::Simulation(const MultiLayer& p_sample)
{
    mP_sample.reset(p_sample.clone());
}

Simulation::Simulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
    : mP_sample_builder(p_sample_builder)
{}

Simulation::Simulation(const Simulation& other)
    : ICloneable()
    , IParameterized(other)
    , mP_sample_builder(other.mP_sample_builder)
    , m_options(other.m_options)
    , m_distribution_handler(other.m_distribution_handler)
    , m_progress(other.m_progress)
    , m_instrument(other.m_instrument)
    , m_intensity_map()
{
    if (other.mP_sample)
        mP_sample.reset(other.mP_sample->clone());
    m_intensity_map.copyFrom(other.m_intensity_map);
}

Simulation::~Simulation() {} // forward class declaration prevents move to .h

//! Initializes a progress monitor that prints to stdout.
void Simulation::setTerminalProgressMonitor()
{
    m_progress.subscribe( [] (int percentage_done) -> bool {
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
    m_instrument.setDetectorResolutionFunction(nullptr);
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
    gsl_set_error_handler_off();
}

//! Run simulation with possible averaging over parameter distributions
void Simulation::runSimulation()
{
    updateSample();
    if (!mP_sample)
        throw Exceptions::NullPointerException("Simulation::runSimulation() -> Error! No sample.");

    prepareSimulation();

    size_t param_combinations = m_distribution_handler.getTotalNumberOfSamples();

    m_progress.reset();
    int prefac = ( mP_sample->totalNofLayouts()>0 ? 1 : 0 )
        + ( mP_sample->hasRoughness() ? 1 : 0 );
    m_progress.setExpectedNTicks(prefac*param_combinations*numberOfSimulationElements());

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
    mP_sample.reset(sample.clone());
}

void Simulation::setSampleBuilder(const std::shared_ptr<class IMultiLayerBuilder> p_sample_builder)
{
    if (!p_sample_builder)
        throw Exceptions::NullPointerException("Simulation::setSampleBuilder() -> "
                                   "Error! Attempt to set null sample builder.");

    mP_sample_builder = p_sample_builder;
    mP_sample.reset(nullptr);
}

std::string Simulation::addSimulationParametersToExternalPool(
    const std::string& path, ParameterPool* external_pool) const
{
    std::string new_path = path;

    if (mP_sample_builder) {
        new_path = mP_sample_builder->addParametersToExternalPool(new_path, external_pool, -1);
    } else if (mP_sample) {
        new_path = mP_sample->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
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
    if (!mP_sample_builder)
        return;
    if (mP_sample_builder->isPythonBuilder()) {
        mP_sample.reset( mP_sample_builder->buildSample()->clone() );
    } else {
        mP_sample.reset( mP_sample_builder->buildSample() );
    }
}

//! Runs a single simulation with fixed parameter values.
//! If desired, the simulation is run in several threads.
void Simulation::runSingleSimulation()
{
    updateSample();
    initSimulationElementVector();

    // restrict calculation to current batch
    std::vector<SimulationElement>::iterator batch_start
        = getBatchStart(m_options.getNumberOfBatches(), m_options.getCurrentBatch());

    std::vector<SimulationElement>::iterator batch_end
        = getBatchEnd(m_options.getNumberOfBatches(), m_options.getCurrentBatch());

    if (m_options.getNumberOfThreads() == 1) {
        // Single thread.
        std::unique_ptr<MainComputation> P_dwba_simulation(
            new MainComputation(mP_sample.get(), m_options, m_progress, batch_start, batch_end));
        P_dwba_simulation->run(); // the work is done here
        if (!P_dwba_simulation->isCompleted()) {
            std::string message = P_dwba_simulation->getRunMessage();
            throw Exceptions::RuntimeErrorException("Simulation::runSimulation() -> Simulation has "
                                                    "terminated unexpectedly with following error "
                                                    "message.\n" + message);
        }
    } else {
        // Multithreading.

        msglog(Logging::DEBUG) << "Simulation::runSimulation() -> Info. Number of threads "
                           << m_options.getNumberOfThreads()
                           << ", n_batches = " << m_options.getNumberOfBatches()
                           << ", current_batch = " << m_options.getCurrentBatch();

        std::vector<std::thread*> threads;
        std::vector<MainComputation*> simulations;

        // Initialize n simulations.
        int total_batch_elements = batch_end - batch_start;
        int element_thread_step = total_batch_elements / m_options.getNumberOfThreads();
        if (total_batch_elements % m_options.getNumberOfThreads()) // there is a remainder
            ++element_thread_step;

        for (int i_thread = 0; i_thread < m_options.getNumberOfThreads(); ++i_thread) {
            if (i_thread*element_thread_step >= total_batch_elements)
                break;
            // TODO: why a plain pointer here, and a unique pointer in the single-thread case?
            std::vector<SimulationElement>::iterator begin_it = batch_start
                                                                + i_thread * element_thread_step;
            std::vector<SimulationElement>::iterator end_it;
            int end_thread_index = (i_thread+1) * element_thread_step;
            if (end_thread_index >= total_batch_elements)
                end_it = batch_end;
            else
                end_it = batch_start + end_thread_index;
            simulations.push_back(
                new MainComputation(
                    mP_sample.get(), m_options, m_progress, begin_it, end_it));
        }

        // Run simulations in n threads.
        for (MainComputation* sim: simulations)
            threads.push_back(new std::thread([sim]() {sim->run();}));

        // Wait for threads to complete.
        for (auto thread: threads) {
            thread->join();
            delete thread;
        }

        // Check successful completion.
        std::vector<std::string> failure_messages;
        for (auto sim: simulations) {
            if (!sim->isCompleted())
                failure_messages.push_back(sim->getRunMessage());
            delete sim;
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
    int total_size = m_sim_elements.size();
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
    int total_size = m_sim_elements.size();
    int size_per_batch = total_size/n_batches;
    if (total_size%n_batches)
        ++size_per_batch;
    int end_index = (current_batch + 1)*size_per_batch;
    if (end_index >= total_size)
        return m_sim_elements.end();
    return m_sim_elements.begin() + end_index;
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
