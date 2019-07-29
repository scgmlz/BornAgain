// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitPlan.cpp
//! @brief     Defines class FitPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitPlan.h"
#include "SimulationFactory.h"
#include "SampleBuilderFactory.h"
#include "Parameters.h"
#include "MultiLayer.h"
#include "FitObjective.h"
#include "KernelTypes.h"
#include "Minimizer.h"

FitPlan::FitPlan(const std::string& name, bool residual_based)
    : MinimizerTestPlan(name)
    , m_residual_based(residual_based)
{

}

FitPlan::~FitPlan() = default;

bool FitPlan::checkMinimizer(Fit::Minimizer& minimizer)
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

    std::cout << "FitPlan::checkResult() -> " << name() << std::endl;
    success &= valuesAsExpected(result.parameters().values());
    std::cout << std::endl;

    return success;
}

void FitPlan::setBuilderName(const std::string& name)
{
    m_sample_builder_name = name;
}

void FitPlan::setSimulationName(const std::string& name)
{
    m_simulation_name = name;
}

std::unique_ptr<FitObjective> FitPlan::createFitObjective() const
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

std::unique_ptr<Simulation> FitPlan::buildSimulation(const Fit::Parameters& params) const
{
    auto simulation = createSimulation(params);
    auto sample = createMultiLayer(params);
    simulation->setSample(*sample);
    return simulation;
}

//! Creates simulation for given set of fit parameters. No sample yets.

std::unique_ptr<Simulation> FitPlan::createSimulation(const Fit::Parameters& params) const
{
    (void)params;
    SimulationFactory factory;
    auto simulation = factory.create(m_simulation_name);
    return simulation;
}

//! Creates sample for given set of fit parameters.

std::unique_ptr<MultiLayer> FitPlan::createMultiLayer(const Fit::Parameters& params) const
{
    SampleBuilderFactory factory;
    auto sample_builder = factory.create(m_sample_builder_name);

    // propagating current values of fit parameters to sample builder before building the sample
    for(const auto& par : params)
        sample_builder->setParameterValue(par.name(), par.value());

    return std::unique_ptr<MultiLayer>(sample_builder->buildSample());
}

//! Creates "experimental" data for fitting.

std::unique_ptr<OutputData<double> > FitPlan::createOutputData() const
{
    // use expected values of fit parameters to construct simulation
    auto params = parameters();
    params.setValues(expectedValues());
    auto simulation = buildSimulation(params);
    simulation->runSimulation();
    return std::unique_ptr<OutputData<double>>(simulation->result().data());
}
