// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Simulation/Simulation.h"
#include "Core/Computation/IBackground.h"
#include "Core/Computation/IComputation.h"
#include "Core/Detector/DetectorFunctions.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/MultiLayerUtils.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Simulation/MPISimulation.h"
#include "Core/Simulation/UnitConverterUtils.h"
#include "Fit/Tools/StringUtils.h"
#include <gsl/gsl_errno.h>
#include <iomanip>
#include <iostream>
#include <thread>

namespace
{
size_t getIndexStep(size_t total_size, size_t n_handlers);
size_t getStartIndex(size_t n_handlers, size_t current_handler, size_t n_elements);
size_t getNumberOfElements(size_t n_handlers, size_t current_handler, size_t n_elements);
void runComputations(std::vector<std::unique_ptr<IComputation>> computations);
} // namespace

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
    : m_sample_provider(other.m_sample_provider), m_options(other.m_options),
      m_distribution_handler(other.m_distribution_handler), m_progress(other.m_progress),
      m_instrument(other.m_instrument)
{
    if (other.mP_background)
        setBackground(*other.mP_background);
    initialize();
}

Simulation::~Simulation() {}

//! Initializes a progress monitor that prints to stdout.
void Simulation::setTerminalProgressMonitor()
{
    m_progress.subscribe([](size_t percentage_done) -> bool {
        if (percentage_done < 100)
            std::cout << std::setprecision(2) << "\r... " << percentage_done << "%" << std::flush;
        else // wipe out
            std::cout << "\r... 100%\n";
        return true;
    });
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
    if (!MultiLayerUtils::ContainsCompatibleMaterials(*m_sample_provider.sample()))
        throw std::runtime_error(
            "Error in Simulation::prepareSimulation(): non-default materials of"
            " several different types are used in the sample provided");
    gsl_set_error_handler_off();
}

//! Run simulation with possible averaging over parameter distributions
void Simulation::runSimulation()
{
    prepareSimulation();

    const size_t total_size = numberOfSimulationElements();
    size_t param_combinations = m_distribution_handler.getTotalNumberOfSamples();

    m_progress.reset();
    m_progress.setExpectedNTicks(param_combinations * total_size);

    // restrict calculation to current batch
    const size_t n_batches = m_options.getNumberOfBatches();
    const size_t current_batch = m_options.getCurrentBatch();

    const size_t batch_start = getStartIndex(n_batches, current_batch, total_size);
    const size_t batch_size = getNumberOfElements(n_batches, current_batch, total_size);
    if (batch_size == 0)
        return;

    std::unique_ptr<ParameterPool> P_param_pool(createParameterTree());
    for (size_t index = 0; index < param_combinations; ++index) {
        double weight = m_distribution_handler.setParameterValues(P_param_pool.get(), index);
        runSingleSimulation(batch_start, batch_size, weight);
    }
    m_distribution_handler.setParameterToMeans(P_param_pool.get());
    moveDataFromCache();
    transferResultsToIntensityMap();
}

void Simulation::runMPISimulation()
{
    MPISimulation ompi;
    ompi.runSimulation(this);
}

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

void Simulation::setBackground(const IBackground& bg)
{
    mP_background.reset(bg.clone());
    registerChild(mP_background.get());
}

std::vector<const INode*> Simulation::getChildren() const
{
    std::vector<const INode*> result;
    result.push_back(&m_instrument);
    result << m_sample_provider.getChildren();
    if (mP_background)
        result.push_back(mP_background.get());
    return result;
}

void Simulation::addParameterDistribution(const std::string& param_name,
                                          const IDistribution1D& distribution, size_t nbr_samples,
                                          double sigma_factor, const RealLimits& limits)
{
    ParameterDistribution par_distr(param_name, distribution, nbr_samples, sigma_factor, limits);
    addParameterDistribution(par_distr);
}

void Simulation::addParameterDistribution(const ParameterDistribution& par_distr)
{
    validateParametrization(par_distr);
    m_distribution_handler.addParameterDistribution(par_distr);
}

void Simulation::updateSample()
{
    m_sample_provider.updateSample();
}

//! Runs a single simulation with fixed parameter values.
//! If desired, the simulation is run in several threads.
void Simulation::runSingleSimulation(size_t batch_start, size_t batch_size, double weight)
{
    initSimulationElementVector();

    const size_t n_threads = m_options.getNumberOfThreads();
    ASSERT(n_threads > 0);

    std::vector<std::unique_ptr<IComputation>> computations;

    for (size_t i_thread = 0; i_thread < n_threads;
         ++i_thread) { // Distribute computations by threads
        const size_t thread_start = batch_start + getStartIndex(n_threads, i_thread, batch_size);
        const size_t thread_size = getNumberOfElements(n_threads, i_thread, batch_size);
        if (thread_size == 0)
            break;
        computations.push_back(generateSingleThreadedComputation(thread_start, thread_size));
    }
    runComputations(std::move(computations));

    normalize(batch_start, batch_size);
    addBackGroundIntensity(batch_start, batch_size);
    addDataToCache(weight);
}

void Simulation::initialize()
{
    registerChild(&m_instrument);
    registerChild(&m_sample_provider);
}

//! Convert user data to SimulationResult object for later drawing in various axes units.
//! User data will be cropped to the ROI defined in the simulation, amplitudes in areas
//! corresponding to the masked areas of the detector will be set to zero.
//! @param simulation: Simulation object with possible ROI and masks defined.
//! @param data: User data with amplitudes with the shape of data matching the detector.
//! @return SimulationResult object.

SimulationResult Simulation::convertData(const OutputData<double>& data,
                                         bool put_masked_areas_to_zero)
{
    auto converter = UnitConverterUtils::createConverter(*this);
    auto roi_data =
        UnitConverterUtils::createOutputData(*converter.get(), converter->defaultUnits());

    auto detector = getInstrument().getDetector();

    if (roi_data->hasSameDimensions(data)) {
        // data is already cropped to ROI
        if (put_masked_areas_to_zero) {
            detector->iterate(
                [&](IDetector::const_iterator it) {
                    (*roi_data)[it.roiIndex()] = data[it.roiIndex()];
                },
                /*visit_masked*/ false);
        } else {
            roi_data->setRawDataVector(data.getRawDataVector());
        }

    } else if (DetectorFunctions::hasSameDimensions(*detector, data)) {
        // exp data has same shape as the detector, we have to put orig data to smaller roi map
        detector->iterate(
            [&](IDetector::const_iterator it) {
                (*roi_data)[it.roiIndex()] = data[it.detectorIndex()];
            },
            /*visit_masked*/ !put_masked_areas_to_zero);

    } else {
        throw std::runtime_error("FitObject::init_dataset() -> Error. Detector and exp data have "
                                 "different shape.");
    }

    return SimulationResult(*roi_data, *converter);
}

namespace
{
size_t getIndexStep(size_t total_size, size_t n_handlers)
{
    ASSERT(total_size > 0);
    ASSERT(n_handlers > 0);
    size_t result = total_size / n_handlers;
    return total_size % n_handlers ? ++result : result;
}

size_t getStartIndex(size_t n_handlers, size_t current_handler, size_t n_elements)
{
    const size_t handler_size = getIndexStep(n_elements, static_cast<size_t>(n_handlers));
    const size_t start_index = current_handler * handler_size;
    if (start_index >= n_elements)
        return n_elements;
    return start_index;
}

size_t getNumberOfElements(size_t n_handlers, size_t current_handler, size_t n_elements)
{
    const size_t handler_size = getIndexStep(n_elements, static_cast<size_t>(n_handlers));
    const size_t start_index = current_handler * handler_size;
    if (start_index >= n_elements)
        return 0;
    return std::min(handler_size, n_elements - start_index);
}

void runComputations(std::vector<std::unique_ptr<IComputation>> computations)
{
    ASSERT(!computations.empty());

    if (computations.size() == 1) { // Running computation in current thread
        auto& computation = computations.front();
        computation->run();
        if (computation->isCompleted())
            return;
        std::string message = computation->errorMessage();
        throw Exceptions::RuntimeErrorException("Error in runComputations: Simulation has "
                                                "terminated unexpectedly with following error: "
                                                "message.\n"
                                                + message);
    }

    // Running computations in several threads.
    // The number of threads is equal to the number of computations.

    std::vector<std::unique_ptr<std::thread>> threads;

    // Run simulations in n threads.
    for (auto& comp : computations)
        threads.emplace_back(new std::thread([&comp]() { comp->run(); }));

    // Wait for threads to complete.
    for (auto& thread : threads)
        thread->join();

    // Check successful completion.
    std::vector<std::string> failure_messages;
    for (auto& comp : computations)
        if (!comp->isCompleted())
            failure_messages.push_back(comp->errorMessage());

    if (failure_messages.size() == 0)
        return;
    throw Exceptions::RuntimeErrorException(
        "Error in runComputations: "
        "At least one simulation thread has terminated unexpectedly.\n"
        "Messages: "
        + StringUtils::join(failure_messages, " --- "));
}
} // unnamed namespace
