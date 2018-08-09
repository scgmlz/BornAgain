// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/IObsoleteFittingTest.cpp
//! @brief     Implements class IObsoleteFittingTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IObsoleteFittingTest.h"
#include "FitSuite.h"
#include "Simulation.h"
#include "MultiLayer.h"
#include "MinimizerFactory.h"
#include "SampleBuilderFactory.h"
#include "SimulationFactory.h"
#include "FitParameterSet.h"
#include <boost/format.hpp>

namespace {
    const double default_parameter_tolerance = 0.01;
}

IObsoleteFittingTest::IObsoleteFittingTest(const std::string& minimizer_name,
                           const std::string& minimizer_algorithm,
                           const std::string& simulation_name,
                           const std::string& builder_name)
    : m_minimizer_name(minimizer_name), m_minimizer_algorithm(minimizer_algorithm),
      m_simulation_name(simulation_name), m_sample_builder_name(builder_name)
{
}

IObsoleteFittingTest::~IObsoleteFittingTest() = default;


bool IObsoleteFittingTest::runTest()
{
    initParameterPlan();

    std::unique_ptr<MultiLayer> sample(createSample());

    std::unique_ptr<Simulation> simulation(createSimulation());
    simulation->setSample(*sample.get());
    simulation->runSimulation();

    std::unique_ptr<OutputData<double> > real_data(createOutputData(simulation.get()));

    std::unique_ptr<FitSuite> fitSuite(createFitSuite());
    fitSuite->addSimulationAndRealData(*simulation.get(), *real_data.get());

    // run fit
    std::cout << fitSuite->treeToString() << std::endl;
    std::cout << fitSuite->parametersToString() << std::endl;
    std::cout << fitSuite->setupToString() << std::endl;
    fitSuite->runFit();

    const bool success = analyzeResults(*fitSuite);
    return success;
}

void IObsoleteFittingTest::initParameterPlan() {
  for(auto& plan : m_parplans)
      plan->setTolerance(default_parameter_tolerance);
}

std::unique_ptr<FitSuite> IObsoleteFittingTest::createFitSuite()
{
    std::unique_ptr<FitSuite> result(new FitSuite());
    result->initPrint(10);
    IMinimizer* minimizer = MinimizerFactory::createMinimizer(
                m_minimizer_name, m_minimizer_algorithm);
    result->setMinimizer(minimizer);

    for(auto& plan : m_parplans)
        result->addFitParameter(plan->fitParameter());

    return result;
}

std::unique_ptr<MultiLayer> IObsoleteFittingTest::createSample()
{
    SampleBuilderFactory builderFactory;
    std::unique_ptr<MultiLayer> result(builderFactory.createSample(m_sample_builder_name));
    for(auto& plan : m_parplans)
        for(auto pattern : plan->fitParameter().patterns())
            result->setParameterValue(pattern, plan->expectedValue());
    return result;
}

std::unique_ptr<Simulation> IObsoleteFittingTest::createSimulation()
{
    SimulationFactory simRegistry;
    auto P_sim = simRegistry.create(m_simulation_name);
    P_sim->setBeamIntensity(1e2);
    return P_sim;
}

std::unique_ptr<OutputData<double> > IObsoleteFittingTest::createOutputData(
    const Simulation* simulation)
{
    auto sim_result = simulation->result();
    return std::unique_ptr<OutputData<double>>(sim_result.data());
}

bool IObsoleteFittingTest::analyzeResults(FitSuite& fit_suite) const
{
    const std::vector<double>& actual = fit_suite.fitParameters()->values();
    std::vector<bool> result(actual.size(), true);
    for(size_t i = 0; i < m_parplans.size(); ++i) {
        const double expected = m_parplans[i]->expectedValue();
        const double diff = std::abs(actual[i] - expected) / expected;
        result[i] = diff <= m_parplans[i]->tolerance();
        std::cout << boost::format("%|12t| %-10s : %-6.4f (diff %6.4g) %s\n") %
            ("par"+std::to_string(i)) % actual[i] % diff % (result[i] ? "OK" : "FAILED");
    }
    return std::accumulate(result.cbegin(), result.cend(), true, std::logical_and<>());
}
