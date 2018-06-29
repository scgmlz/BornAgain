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
#include "PyBuilderCallback.h"
#include "Simulation.h"
#include "ArrayUtils.h"
#include <stdexcept>

namespace {
void insert_to(std::vector<double>& to, const std::vector<double>& from)
{
    to.insert(to.end(), from.begin(), from.end());
}
}


FitObjective::FitObjective()
    : m_total_weight(0.0)
    , m_chi2_module(new ChiSquaredModule())
{}

FitObjective::~FitObjective() = default;

void FitObjective::addSimulationAndData(simulation_builder_t builder,
                                        const OutputData<double>& data, double weight)
{
    m_fit_objects.push_back(new SimDataPair(builder, data, weight));
    m_total_weight += weight;
}

void FitObjective::addSimulationAndData(PyBuilderCallback& callback,
                                        const std::vector<std::vector<double> >& data,
                                        double weight)
{
    simulation_builder_t builder = [&](const Fit::Parameters& params) {
        std::unique_ptr<Simulation> result(callback.build_simulation(params)->clone());
        return result;
    };

    auto output_data = ArrayUtils::createData2D(data);
    addSimulationAndData(builder, *output_data, weight);
}

double FitObjective::evaluate(const Fit::Parameters& params)
{
    double chi2(0.0);

    for(auto res : evaluate_residuals(params))
        chi2 += res*res;

    const size_t free_parameter_count = params.size(); // FIXME make correct free pars calculation

    int fnorm = static_cast<int>(numberOfFitElements()) - static_cast<int>(free_parameter_count);
    if (fnorm <= 0)
        throw std::runtime_error("FitObjective::evaluate() -> Error. Normalization is 0");

    return chi2 / fnorm;
}

std::vector<double> FitObjective::evaluate_residuals(const Fit::Parameters& params)
{
    run_simulations(params);

    std::vector<double> result;

    std::vector<double> weights;
    weights.resize(numberOfFitElements(), 1.0); // FIXME make correct weights

    for(size_t i = 0; i<m_simulation_array.size(); ++i)
        result.push_back(residual(m_simulation_array[i], m_experimental_array[i], weights[i]));

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

void FitObjective::run_simulations(const Fit::Parameters& params)
{
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
