// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitObjective.cpp
//! @brief     Implements class FitObjective.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitObjective.h"
#include "ArrayUtils.h"
#include "ChiSquaredModule.h"
#include "FitStatus.h"
#include "MinimizerResult.h"
#include "ObjectiveMetric.h"
#include "ObjectiveMetricUtils.h"
#include "Parameters.h"
#include "PyFittingCallbacks.h"
#include "Simulation.h"
#include <stdexcept>

class IMetricWrapper
{
public:
    virtual ~IMetricWrapper();
    virtual double compute(const std::vector<SimDataPair>& fit_objects, size_t n_pars) const = 0;
};

//! Metric wrapper for back-compaptibility with old scripts
class ChiModuleWrapper : public IMetricWrapper
{
public:
    ChiModuleWrapper(std::unique_ptr<IChiSquaredModule> module);
    double compute(const std::vector<SimDataPair>& fit_objects, size_t n_pars) const override;

private:
    std::unique_ptr<IChiSquaredModule> m_module;
};

class ObjectiveMetricWrapper : public IMetricWrapper
{
public:
    ObjectiveMetricWrapper(std::unique_ptr<ObjectiveMetric> module);
    double compute(const std::vector<SimDataPair>& fit_objects, size_t n_pars) const override;

private:
    std::unique_ptr<ObjectiveMetric> m_module;
};

simulation_builder_t FitObjective::simulationBuilder(PyBuilderCallback& callback)
{
    return [&callback](const Fit::Parameters& params) {
        auto simulation = callback.build_simulation(params);
        std::unique_ptr<Simulation> clone(simulation->clone());
        delete simulation; // deleting Python object
        return clone;
    };
}

FitObjective::FitObjective()
    : m_metric_module(
          std::make_unique<ObjectiveMetricWrapper>(std::make_unique<PoissonLikeMetric>()))
    , m_fit_status(std::make_unique<FitStatus>(this))
{}

FitObjective::~FitObjective() = default;

//! Constructs simulation/data pair for later fit.
//! @param builder: simulation builder capable of producing simulations
//! @param data: experimental data array
//! @param uncertainties: data uncertainties array
//! @param weight: weight of dataset in metric calculations
void FitObjective::addSimulationAndData(simulation_builder_t builder,
                                        const OutputData<double>& data,
                                        std::unique_ptr<OutputData<double>> uncertainties,
                                        double weight)
{
    m_fit_objects.emplace_back(builder, data, std::move(uncertainties), weight);
}

double FitObjective::evaluate(const Fit::Parameters& params)
{
    run_simulations(params);
    const double metric_value = m_metric_module->compute(m_fit_objects, params.size());
    m_fit_status->update(params, metric_value);
    return metric_value;
}

std::vector<double> FitObjective::evaluate_residuals(const Fit::Parameters& params)
{
    evaluate(params);

    std::vector<double> result = experimental_array(); // init result with experimental data values
    const std::vector<double> sim_values = simulation_array();
    std::transform(result.begin(), result.end(), sim_values.begin(), result.begin(),
                   [](double lhs, double rhs) { return lhs - rhs; });
    return result;
}

size_t FitObjective::numberOfFitElements() const
{
    return std::accumulate(m_fit_objects.begin(), m_fit_objects.end(), 0u,
                           [](size_t acc, auto& obj) { return acc + obj.numberOfFitElements(); });
}

//! Returns simulation result in the form of SimulationResult.
SimulationResult FitObjective::simulationResult(size_t i_item) const
{
    return dataPair(i_item).simulationResult();
}

//! Returns experimental data in the form of SimulationResult.
SimulationResult FitObjective::experimentalData(size_t i_item) const
{
    return dataPair(i_item).experimentalData();
}

//! Returns experimental data uncertainties in the form of SimulationResult.
SimulationResult FitObjective::uncertaintyData(size_t i_item) const
{
    return dataPair(i_item).uncertainties();
}

//! Returns relative difference between simulation and experimental data
//! in the form of SimulationResult.
SimulationResult FitObjective::relativeDifference(size_t i_item) const
{
    return dataPair(i_item).relativeDifference();
}

//! Returns absolute value of difference between simulation and experimental data
//! in the form of SimulationResult.
SimulationResult FitObjective::absoluteDifference(size_t i_item) const
{
    return dataPair(i_item).absoluteDifference();
}

//! Returns one dimensional array representing merged experimental data.
//! The area outside of the region of interest is not included, masked data is nullified.
std::vector<double> FitObjective::experimental_array() const
{
    return composeArray(&SimDataPair::experimental_array);
}

//! Returns one dimensional array representing merged simulated intensities data.
//! The area outside of the region of interest is not included, masked data is nullified.
std::vector<double> FitObjective::simulation_array() const
{
    return composeArray(&SimDataPair::simulation_array);
}

//! Returns one-dimensional array representing merged data uncertainties.
//! The area outside of the region of interest is not included, masked data is nullified.
std::vector<double> FitObjective::uncertainties() const
{
    return composeArray(&SimDataPair::uncertainties_array);
}

//! Returns one-dimensional array representing merged user weights.
//! The area outside of the region of interest is not included, masked data is nullified.
std::vector<double> FitObjective::weights_array() const
{
    return composeArray(&SimDataPair::user_weights_array);
}

const SimDataPair& FitObjective::dataPair(size_t i_item) const
{
    return m_fit_objects[check_index(i_item)];
}

void FitObjective::initPrint(int every_nth)
{
    m_fit_status->initPrint(every_nth);
}

void FitObjective::initPlot(int every_nth, fit_observer_t observer)
{
    m_fit_status->addObserver(every_nth, observer);
}

void FitObjective::initPlot(int every_nth, PyObserverCallback& callback)
{
    fit_observer_t observer = [&](const FitObjective& objective) {
        callback.update(objective);
    };
    m_fit_status->addObserver(every_nth, observer);
}

bool FitObjective::isCompleted() const
{
    return m_fit_status->isCompleted();
}

IterationInfo FitObjective::iterationInfo() const
{
    return m_fit_status->iterationInfo();
}

Fit::MinimizerResult FitObjective::minimizerResult() const
{
    return m_fit_status->minimizerResult();
}

void FitObjective::finalize(const Fit::MinimizerResult& result)
{
    m_fit_status->finalize(result);
}

unsigned FitObjective::fitObjectCount() const
{
    return static_cast<unsigned>(m_fit_objects.size());
}

void FitObjective::interruptFitting()
{
    m_fit_status->setInterrupted();
}

bool FitObjective::isInterrupted() const
{
    return m_fit_status->isInterrupted();
}

bool FitObjective::isFirstIteration() const
{
    return iterationInfo().iterationCount() == 1;
}

void FitObjective::run_simulations(const Fit::Parameters& params)
{
    if (m_fit_status->isInterrupted())
        throw std::runtime_error("Fitting was interrupted by the user.");

    if (m_fit_objects.empty())
        throw std::runtime_error("FitObjective::run_simulations() -> Error. "
                                 "No simulation/data defined.");

    for (auto& obj : m_fit_objects)
        obj.runSimulation(params);
}

void FitObjective::setChiSquaredModule(const IChiSquaredModule& module)
{
    std::cout << "Warning in FitObjective::setChiSquaredModule: setChiSquaredModule is deprecated "
                 "and will be removed in future versions. Please use "
                 "FitObjective::setObjectiveMetric instead."
              << std::endl;

    std::unique_ptr<IChiSquaredModule> chi_module(module.clone());
    m_metric_module = std::make_unique<ChiModuleWrapper>(std::move(chi_module));
}

void FitObjective::setObjectiveMetric(std::unique_ptr<ObjectiveMetric> metric)
{
    m_metric_module = std::make_unique<ObjectiveMetricWrapper>(std::move(metric));
}

void FitObjective::setObjectiveMetric(const std::string& metric)
{
    m_metric_module = std::make_unique<ObjectiveMetricWrapper>(
        ObjectiveMetricUtils::createMetric(metric, ObjectiveMetricUtils::defaultNormName()));
}

void FitObjective::setObjectiveMetric(const std::string& metric, const std::string& norm)
{
    m_metric_module =
        std::make_unique<ObjectiveMetricWrapper>(ObjectiveMetricUtils::createMetric(metric, norm));
}

//! Returns true if the specified DataPair element contains uncertainties
bool FitObjective::containsUncertainties(size_t i_item) const
{
    return dataPair(i_item).containsUncertainties();
}

//! Returns true if all the data pairs in FitObjective instance contain uncertainties
bool FitObjective::allPairsHaveUncertainties() const
{
    bool result = true;
    for (size_t i = 0, size = fitObjectCount(); i < size; ++i)
        result = result && dataPair(i).containsUncertainties();
    return result;
}

//! Returns available metrics and norms
std::string FitObjective::availableMetricOptions()
{
    return ObjectiveMetricUtils::availableMetricOptions();
}

std::vector<double> FitObjective::composeArray(DataPairAccessor getter) const
{
    const size_t n_objs = m_fit_objects.size();
    if (n_objs == 0)
        return {};
    if (n_objs == 1)
        return (m_fit_objects[0].*getter)();

    std::vector<double> result;
    result.reserve(numberOfFitElements());
    for (auto& pair: m_fit_objects) {
        std::vector<double> array = (pair.*getter)();
        std::move(array.begin(), array.end(), std::back_inserter(result));
    }
    return result;
}

size_t FitObjective::check_index(size_t index) const
{
    if (index >= m_fit_objects.size())
        throw std::runtime_error("FitObjective::check_index() -> Index outside of range");
    return index;
}

// ------------------ metric wrappers -----------------------------

IMetricWrapper::~IMetricWrapper() = default;

ChiModuleWrapper::ChiModuleWrapper(std::unique_ptr<IChiSquaredModule> module)
    : IMetricWrapper()
    , m_module(std::move(module))
{
    if (!m_module)
        throw std::runtime_error("Error in ChiModuleWrapper: empty chi square module passed");
}

double ChiModuleWrapper::compute(const std::vector<SimDataPair>& fit_objects, size_t n_pars) const
{
    size_t n_points = 0;
    double result = 0.0;
    for (auto& obj: fit_objects) {
        const auto sim_array = obj.simulation_array();
        const auto exp_array = obj.experimental_array();
        const auto weights = obj.user_weights_array();
        const size_t n_elements = sim_array.size();
        for(size_t i = 0; i < n_elements; ++i) {
            double value = m_module->residual(sim_array[i], exp_array[i], weights[i]);
            result += value * value;
        }
        n_points += n_elements;
    }

    int fnorm = static_cast<int>(n_points) - static_cast<int>(n_pars);
    if (fnorm <= 0)
        throw std::runtime_error("Error in ChiModuleWrapper: Normalization shall be positive");

    return result / fnorm;
}

ObjectiveMetricWrapper::ObjectiveMetricWrapper(std::unique_ptr<ObjectiveMetric> module)
    : IMetricWrapper()
    , m_module(std::move(module))
{
    if (!m_module)
        throw std::runtime_error("Error in ObjectiveMetricWrapper: empty objective metric passed");
}

double ObjectiveMetricWrapper::compute(const std::vector<SimDataPair>& fit_objects,
                                       size_t) const
{
    // deciding whether to use uncertainties in metrics computation.
    bool use_uncertainties = true;
    for (auto& obj: fit_objects)
        use_uncertainties = use_uncertainties && obj.containsUncertainties();

    double result = 0.0;
    for (auto& obj: fit_objects)
        result += m_module->compute(obj, use_uncertainties);
    return result;
}
