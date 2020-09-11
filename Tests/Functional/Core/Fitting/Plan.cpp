// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/Plan.cpp
//! @brief     Defines class Plan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/Fitting/Plan.h"
#include "Core/Fitting/FitObjective.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Fit/Kernel/KernelTypes.h"
#include "Fit/Kernel/Minimizer.h"
#include "Fit/Kernel/Parameters.h"

Plan::Plan(const std::string& name, bool residual_based)
    : MinimizerTestPlan(name), m_residual_based(residual_based)
{
}

Plan::~Plan() = default;

bool Plan::checkMinimizer(Fit::Minimizer& minimizer)
{
    auto fit_objective = createFitObjective();

    fcn_scalar_t scalar_func = [&](const Fit::Parameters& params) {
        return fit_objective->evaluate(params);
    };

    fcn_residual_t residual_func = [&](const Fit::Parameters& params) {
        return fit_objective->evaluate_residuals(params);
    };

    bool success(true);
    Fit::MinimizerResult result;

    if (m_residual_based)
        result = minimizer.minimize(residual_func, parameters());
    else
        result = minimizer.minimize(scalar_func, parameters());

    fit_objective->finalize(result);

    std::cout << "Plan::checkResult() -> " << name() << std::endl;
    success &= valuesAsExpected(result.parameters().values());
    std::cout << std::endl;

    return success;
}

void Plan::setBuilderName(const std::string& name)
{
    m_sample_builder_name = name;
}

void Plan::setSimulationName(const std::string& name)
{
    m_simulation_name = name;
}

std::unique_ptr<FitObjective> Plan::createFitObjective() const
{
    std::unique_ptr<FitObjective> result(new FitObjective);

    simulation_builder_t builder = [&](const Fit::Parameters& params) {
        return buildSimulation(params);
    };

    result->addSimulationAndData(builder, *createOutputData(), nullptr, 1.0);
    result->initPrint(1);

    return result;
}

//! Build simulation (sample included) for given set of fit parameters.

std::unique_ptr<Simulation> Plan::buildSimulation(const Fit::Parameters& params) const
{
    auto simulation = createSimulation(params);
    auto sample = createMultiLayer(params);
    simulation->setSample(*sample);
    return simulation;
}

//! Creates simulation for given set of fit parameters. No sample yets.

std::unique_ptr<Simulation> Plan::createSimulation(const Fit::Parameters& params) const
{
    (void)params;
    SimulationFactory factory;
    auto simulation = factory.createItemPtr(m_simulation_name);
    return simulation;
}

//! Creates sample for given set of fit parameters.

std::unique_ptr<MultiLayer> Plan::createMultiLayer(const Fit::Parameters& params) const
{
    SampleBuilderFactory factory;
    auto sample_builder = factory.createItemPtr(m_sample_builder_name);

    // propagating current values of fit parameters to sample builder before building the sample
    for (const auto& par : params)
        sample_builder->setParameterValue(par.name(), par.value());

    return std::unique_ptr<MultiLayer>(sample_builder->buildSample());
}

//! Creates "experimental" data for fitting.

std::unique_ptr<OutputData<double>> Plan::createOutputData() const
{
    // use expected values of fit parameters to construct simulation
    auto params = parameters();
    params.setValues(expectedValues());
    auto simulation = buildSimulation(params);
    simulation->runSimulation();
    return simulation->result().data();
}
