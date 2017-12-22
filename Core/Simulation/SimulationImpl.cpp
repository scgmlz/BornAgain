#include "IBackground.h"
#include "IComputation.h"
#include "MultiLayer.h"
#include "ParameterPool.h"
#include "SimulationImpl.h"
#include "StringUtils.h"
#include <thread>

SimulationImpl::SimulationImpl() = default;
SimulationImpl::SimulationImpl(const SimulationImpl& other)
    : Simulation(other)
    , m_sim_elements(other.m_sim_elements)
{}
SimulationImpl::~SimulationImpl() = default;

void SimulationImpl::runSimulation()
{
    prepareSimulation();

    size_t param_combinations = m_distribution_handler.getTotalNumberOfSamples();

    m_progress->reset();
    size_t prefactor = ( sample()->totalNofLayouts() > 0 ? 1 : 0 )
        + ( sample()->hasRoughness() ? 1 : 0 );
    m_progress->setExpectedNTicks(prefactor*param_combinations*numberOfSimulationElements());

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
    SimElementVector total_intensity = m_sim_elements;
    std::unique_ptr<ParameterPool> P_param_pool(createParameterTree());
    for (size_t index = 0; index < param_combinations; ++index) {
        double weight = m_distribution_handler.setParameterValues(P_param_pool.get(), index);
        runSingleSimulation();
        addElementsWithWeight(total_intensity.begin(), weight);
    }
    m_sim_elements = std::move(total_intensity);
    transferResultsToIntensityMap();
}

void SimulationImpl::initSimulationElementVector()
{
    m_sim_elements = m_instrument.createSimulationElements();
}

void SimulationImpl::runSingleSimulation()
{
    prepareSimulation();
    initSimulationElementVector();

    // restrict calculation to current batch
    auto batch_start = getBatchStart(m_options.getNumberOfBatches(), m_options.getCurrentBatch());

    auto batch_end = getBatchEnd(m_options.getNumberOfBatches(), m_options.getCurrentBatch());

    if (m_options.getNumberOfThreads() == 1) {
        // Single thread.
        auto P_computation = generateSingleThreadedComputation(batch_start, batch_end);
        P_computation->run(); // the work is done here
        if (!P_computation->isCompleted()) {
            std::string message = P_computation->errorMessage();
            throw Exceptions::RuntimeErrorException("SimulationImpl::runSimulation() -> Simulation has "
                                                    "terminated unexpectedly with following error "
                                                    "message.\n" + message);
        }
    } else {
        // Multithreading.
        std::vector<std::unique_ptr<std::thread>> threads;
        std::vector<std::unique_ptr<IComputation>> computations;

        // Initialize n computations.
        auto total_batch_elements = batch_end - batch_start;
        auto element_thread_step = total_batch_elements / m_options.getNumberOfThreads();
        if (total_batch_elements % m_options.getNumberOfThreads()) // there is a remainder
            ++element_thread_step;

        for (int i_thread = 0; i_thread < m_options.getNumberOfThreads(); ++i_thread) {
            if (i_thread*element_thread_step >= total_batch_elements)
                break;
            auto begin_it = batch_start + i_thread * element_thread_step;
            auto end_thread_index = (i_thread + 1) * element_thread_step;
            auto end_it = end_thread_index >= total_batch_elements ? batch_end
                                                                   : batch_start + end_thread_index;
            computations.push_back(generateSingleThreadedComputation(begin_it, end_it));
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
    addBackGroundIntensity(batch_start, batch_end);
}

void SimulationImpl::normalize(SimElementVector::iterator begin_it,
                               SimElementVector::iterator end_it) const
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

void SimulationImpl::addBackGroundIntensity(SimElementVector::iterator begin_it,
                                            SimElementVector::iterator end_it) const
{
    if (mP_background)
        mP_background->addBackGround(begin_it, end_it);
}

SimulationImpl::SimElementVector::iterator SimulationImpl::getBatchStart(int n_batches, int current_batch)
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

SimulationImpl::SimElementVector::iterator SimulationImpl::getBatchEnd(int n_batches, int current_batch)
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

void SimulationImpl::addElementsWithWeight(SimElementVector::iterator result, double weight) const
{
    for (auto it = m_sim_elements.cbegin(); it != m_sim_elements.cend(); ++it, ++result)
        result->addIntensity(it->getIntensity() * weight);
}

void SimulationImpl::imposeConsistencyOfBatchNumbers(int& n_batches, int& current_batch)
{
    if (n_batches < 2) {
        n_batches = 1;
        current_batch = 0;
    }
    if (current_batch >= n_batches)
        throw Exceptions::ClassInitializationException(
            "SimulationImpl::imposeConsistencyOfBatchNumbers(): Batch number must be smaller than "
            "number of batches.");
}

