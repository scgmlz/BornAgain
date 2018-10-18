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
#include "ChiSquaredModule.h"
#include "Parameters.h"
#include "PyFittingCallbacks.h"
#include "Simulation.h"
#include "ArrayUtils.h"
#include "FitStatus.h"
#include "MinimizerResult.h"
#include <stdexcept>

namespace {
void insert_to(std::vector<double>& to, const std::vector<double>& from)
{
    to.insert(to.end(), from.begin(), from.end());
}

simulation_builder_t simulationBuilder(PyBuilderCallback& callback)
{
    return [&callback](const Fit::Parameters& params) {
        return std::unique_ptr<Simulation>(callback.build_simulation(params)->clone());
    };
}
}


FitObjective::FitObjective()
    : m_total_weight(0.0)
    , m_chi2_module(new ChiSquaredModule())
    , m_fit_status(new FitStatus(this))
{}

FitObjective::~FitObjective() = default;

void FitObjective::addSimulationAndData(simulation_builder_t builder,
                                        const OutputData<double>& data, double weight)
{
    m_fit_objects.push_back(new SimDataPair(builder, data, weight));
    m_total_weight += weight;
}

void FitObjective::addSimulationAndData(PyBuilderCallback& callback,
                                        const std::vector<double>& data,
                                        double weight)
{
    auto output_data = ArrayUtils::createData1D(data);
    addSimulationAndData(simulationBuilder(callback), *output_data, weight);
}

void FitObjective::addSimulationAndData(PyBuilderCallback& callback,
                                        const std::vector<std::vector<double>>& data,
                                        double weight)
{
    auto output_data = ArrayUtils::createData2D(data);
    addSimulationAndData(simulationBuilder(callback), *output_data, weight);
}

double FitObjective::evaluate(const Fit::Parameters& params)
{
    return evaluate_chi2(evaluate_residuals(params), params);
}

std::vector<double> FitObjective::evaluate_residuals(const Fit::Parameters& params)
{
    run_simulations(params);

    std::vector<double> result;

    std::vector<double> weights;
    weights.resize(numberOfFitElements(), 1.0); // FIXME make correct weights

    for(size_t i = 0; i<m_simulation_array.size(); ++i)
        result.push_back(residual(m_simulation_array[i], m_experimental_array[i], weights[i]));

    double chi2 = evaluate_chi2(result, params);

    m_fit_status->update(params, chi2);

    return result;
}

size_t FitObjective::numberOfFitElements() const
{
    size_t result(0);
    for (auto obj : m_fit_objects)
        result += obj->numberOfFitElements();

    return result;
}

std::vector<double> FitObjective::experimental_array() const
{
    return m_experimental_array;
}

std::vector<double> FitObjective::simulation_array() const
{
    return m_simulation_array;
}

SimulationResult FitObjective::simulationResult(size_t i_item) const
{
    return m_fit_objects[check_index(i_item)]->simulationResult();
}

SimulationResult FitObjective::experimentalData(size_t i_item) const
{
    return m_fit_objects[check_index(i_item)]->experimentalData();
}

SimulationResult FitObjective::relativeDifference(size_t i_item) const
{
    return m_fit_objects[check_index(i_item)]->relativeDifference();
}

SimulationResult FitObjective::absoluteDifference(size_t i_item) const
{
    return m_fit_objects[check_index(i_item)]->absoluteDifference();
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

    m_simulation_array.clear();
    m_experimental_array.clear();

    for (auto obj : m_fit_objects) {
        obj->runSimulation(params);
        insert_to(m_simulation_array, obj->simulation_array());
        insert_to(m_experimental_array, obj->experimental_array());
    }
}

double FitObjective::residual(double a, double b, double weight) const
{
    return m_chi2_module->residual(a, b, weight);
}

double FitObjective::evaluate_chi2(const std::vector<double>& residuals,
                                   const Fit::Parameters& params)
{
    double chi2(0.0);

    for(auto res : residuals)
        chi2 += res*res;

    int fnorm = static_cast<int>(numberOfFitElements()) -
            static_cast<int>(params.freeParameterCount());
    if (fnorm <= 0)
        throw std::runtime_error("FitObjective::chi2() -> Error. Normalization is 0");

    return chi2 / fnorm;
}

size_t FitObjective::check_index(size_t index) const
{
    if (index >= m_fit_objects.size())
        throw std::runtime_error("FitObjective::check_index() -> Index outside of range");
    return index;
}
