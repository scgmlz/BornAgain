//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/ISimulation.cpp
//! @brief     Implements interface ISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Simulation/ISimulation.h"
#include "Base/Utils/StringUtils.h"
#include "Core/Computation/IBackground.h"
#include "Core/Computation/IComputation.h"
#include "Core/Simulation/MPISimulation.h"
#include "Core/Simulation/UnitConverterUtils.h"
#include "Param/Base/ParameterPool.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Multilayer/MultiLayerUtils.h"
#include "Sample/SampleBuilderEngine/ISampleBuilder.h"
#include <gsl/gsl_errno.h>
#include <iomanip>
#include <iostream>
#include <thread>

namespace {

bool detHasSameDimensions(const IDetector& detector, const OutputData<double>& data) {
    if (data.rank() != detector.dimension())
        return false;

    for (size_t i = 0; i < detector.dimension(); ++i)
        if (data.axis(i).size() != detector.axis(i).size())
            return false;

    return true;
}

size_t getIndexStep(size_t total_size, size_t n_handlers) {
    ASSERT(total_size > 0);
    ASSERT(n_handlers > 0);
    size_t result = total_size / n_handlers;
    return total_size % n_handlers ? ++result : result;
}

size_t getStartIndex(size_t n_handlers, size_t current_handler, size_t n_elements) {
    const size_t handler_size = getIndexStep(n_elements, static_cast<size_t>(n_handlers));
    const size_t start_index = current_handler * handler_size;
    if (start_index >= n_elements)
        return n_elements;
    return start_index;
}

size_t getNumberOfElements(size_t n_handlers, size_t current_handler, size_t n_elements) {
    const size_t handler_size = getIndexStep(n_elements, static_cast<size_t>(n_handlers));
    const size_t start_index = current_handler * handler_size;
    if (start_index >= n_elements)
        return 0;
    return std::min(handler_size, n_elements - start_index);
}

void runComputations(std::vector<std::unique_ptr<IComputation>>& computations) {
    ASSERT(!computations.empty());

    if (computations.size() == 1) { // Running computation in current thread
        auto& computation = computations.front();
        computation->run();
        if (computation->isCompleted())
            return;
        std::string message = computation->errorMessage();
        throw std::runtime_error("Error in runComputations: ISimulation has "
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

    if (failure_messages.empty())
        return;
    throw std::runtime_error("Error in runComputations: "
                             "At least one simulation thread has terminated unexpectedly.\n"
                             "Messages: "
                             + StringUtils::join(failure_messages, " --- "));
}

} // namespace

//  ************************************************************************************************
//  class ISimulation
//  ************************************************************************************************

ISimulation::ISimulation(const Beam& beam, const MultiLayer& sample, const IDetector& detector)
    : m_instrument(beam, detector) {
    setSample(sample);
    initialize();
}

ISimulation::ISimulation() {
    initialize();
}

ISimulation::ISimulation(const ISimulation& other)
    : ICloneable()
    , INode()
    , m_options(other.m_options)
    , m_progress(other.m_progress)
    , m_sample_provider(other.m_sample_provider)
    , m_distribution_handler(other.m_distribution_handler)
    , m_instrument(other.instrument()) {
    if (other.m_background)
        setBackground(*other.m_background);
    initialize();
}

ISimulation::~ISimulation() = default;

void ISimulation::initialize() {
    registerChild(&m_instrument);
    registerChild(&m_sample_provider);
}

//! Initializes a progress monitor that prints to stdout.
void ISimulation::setTerminalProgressMonitor() {
    m_progress.subscribe([](size_t percentage_done) -> bool {
        if (percentage_done < 100)
            std::cout << std::setprecision(2) << "\r... " << percentage_done << "%" << std::flush;
        else // wipe out
            std::cout << "\r... 100%\n";
        return true;
    });
}

void ISimulation::setDetectorResolutionFunction(const IResolutionFunction2D& resolution_function) {
    detector().setResolutionFunction(resolution_function);
}

//! Sets the polarization analyzer characteristics of the detector
void ISimulation::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                        double total_transmission) {
    detector().setAnalyzerProperties(direction, efficiency, total_transmission);
}

void ISimulation::prepareSimulation() {
    m_sample_provider.updateSample();
    if (!MultiLayerUtils::ContainsCompatibleMaterials(*m_sample_provider.sample()))
        throw std::runtime_error(
            "Error in ISimulation::prepareSimulation(): non-default materials of"
            " several different types are used in the sample provided");
    gsl_set_error_handler_off();
}

//! Run simulation with possible averaging over parameter distributions
void ISimulation::runSimulation() {
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

    std::unique_ptr<ParameterPool> param_pool(createParameterTree());
    for (size_t index = 0; index < param_combinations; ++index) {
        double weight = m_distribution_handler.setParameterValues(param_pool.get(), index);
        runSingleSimulation(batch_start, batch_size, weight);
    }
    m_distribution_handler.setParameterToMeans(param_pool.get());
    moveDataFromCache();
    transferResultsToIntensityMap();
}

void ISimulation::runMPISimulation() {
    MPISimulation ompi;
    ompi.runSimulation(this);
}

void ISimulation::setInstrument(const Instrument& instrument_) {
    m_instrument = instrument_;
    updateIntensityMap();
}

//! The MultiLayer object will not be owned by the ISimulation object
void ISimulation::setSample(const MultiLayer& sample) {
    m_sample_provider.setSample(sample);
}

const MultiLayer* ISimulation::sample() const {
    return m_sample_provider.sample();
}

void ISimulation::setSampleBuilder(const std::shared_ptr<class ISampleBuilder>& sample_builder) {
    m_sample_provider.setBuilder(sample_builder);
}

void ISimulation::setBackground(const IBackground& bg) {
    m_background.reset(bg.clone());
    registerChild(m_background.get());
}

std::vector<const INode*> ISimulation::getChildren() const {
    std::vector<const INode*> result;
    result.push_back(&instrument());
    result << m_sample_provider.getChildren();
    if (m_background)
        result.push_back(m_background.get());
    return result;
}

void ISimulation::addParameterDistribution(const std::string& param_name,
                                           const IDistribution1D& distribution, size_t nbr_samples,
                                           double sigma_factor, const RealLimits& limits) {
    ParameterDistribution par_distr(param_name, distribution, nbr_samples, sigma_factor, limits);
    addParameterDistribution(par_distr);
}

void ISimulation::addParameterDistribution(const ParameterDistribution& par_distr) {
    validateParametrization(par_distr);
    m_distribution_handler.addParameterDistribution(par_distr);
}

//! Runs a single simulation with fixed parameter values.
//! If desired, the simulation is run in several threads.
void ISimulation::runSingleSimulation(size_t batch_start, size_t batch_size, double weight) {
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
    runComputations(computations);

    normalize(batch_start, batch_size);
    addBackgroundIntensity(batch_start, batch_size);
    addDataToCache(weight);
}

//! Convert user data to SimulationResult object for later drawing in various axes units.
//! User data will be cropped to the ROI defined in the simulation, amplitudes in areas
//! corresponding to the masked areas of the detector will be set to zero.

SimulationResult ISimulation::convertData(const OutputData<double>& data,
                                          bool put_masked_areas_to_zero) {
    auto converter = UnitConverterUtils::createConverter(*this);
    auto roi_data = UnitConverterUtils::createOutputData(*converter, converter->defaultUnits());

    const IDetector& detector = instrument().detector();

    if (roi_data->hasSameDimensions(data)) {
        // data is already cropped to ROI
        if (put_masked_areas_to_zero) {
            detector.iterate(
                [&](IDetector::const_iterator it) {
                    (*roi_data)[it.roiIndex()] = data[it.roiIndex()];
                },
                /*visit_masked*/ false);
        } else {
            roi_data->setRawDataVector(data.getRawDataVector());
        }

    } else if (detHasSameDimensions(detector, data)) {
        // exp data has same shape as the detector, we have to put orig data to smaller roi map
        detector.iterate(
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
