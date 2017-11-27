// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/IMinimizerTest.cpp
//! @brief     Implements class IMinimizerTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMinimizerTest.h"
#include "FitSuite.h"
#include "Simulation.h"
#include "MultiLayer.h"
#include "MinimizerFactory.h"
#include "SampleBuilderFactory.h"
#include "SimulationFactory.h"
#include "FitParameterSet.h"
#include "Units.h"
#include <boost/format.hpp>
#include <memory>

namespace {
    const double default_parameter_tolerance = 0.01;
}

IMinimizerTest::IMinimizerTest(const std::string& minimizer_name,
                               const std::string& minimizer_algorithm)
    : m_minimizer_name(minimizer_name)
    , m_minimizer_algorithm(minimizer_algorithm)
    , m_simulation_name("MiniGISAS")
    , m_sample_builder_name("CylindersInBABuilder")
{
}

IMinimizerTest::~IMinimizerTest()
{
    for(auto par : m_parplans)
        delete par;
}


bool IMinimizerTest::runTest()
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

    std::vector<double> valuesAtMinimum = fitSuite->fitParameters()->values();

    // analyze results
    bool success = true;
    size_t index(0);
    for(auto plan : m_parplans) {
        double foundValue = valuesAtMinimum[index];
        double diff = std::abs(foundValue - plan->expectedValue()) / plan->expectedValue();
        if (diff > plan->tolerance())
            success = false;
        std::cout << boost::format("%|12t| %-10s : %-6.4f (diff %6.4g) %s\n") %
            ("par"+std::to_string(index)) % foundValue % diff % (success ? "OK" : "FAILED");
        ++index;
    }

    return success;
}

//! Creates plan with initial/real values of fit parameters.

void IMinimizerTest::initParameterPlan() {
  m_parplans.clear();
  m_parplans.push_back(new FitParameterPlan("*Height", 4.5 * Units::nanometer,
                                          5.0 * Units::nanometer,
                                          AttLimits::lowerLimited(0.01), 0.01));
  m_parplans.push_back(new FitParameterPlan("*Radius", 5.5 * Units::nanometer,
                                          5.0 * Units::nanometer,
                                          AttLimits::lowerLimited(0.01), 0.01));

  for(auto plan : m_parplans)
      plan->setTolerance(default_parameter_tolerance);
}

std::unique_ptr<FitSuite> IMinimizerTest::createFitSuite()
{
    std::unique_ptr<FitSuite> result(new FitSuite());
    result->initPrint(10);
    IMinimizer* minimizer = MinimizerFactory::createMinimizer(
                m_minimizer_name, m_minimizer_algorithm);
    result->setMinimizer(minimizer);

    for(auto plan : m_parplans)
        result->addFitParameter(plan->fitParameter());

    return result;
}

std::unique_ptr<MultiLayer> IMinimizerTest::createSample()
{
    SampleBuilderFactory builderFactory;
    std::unique_ptr<MultiLayer> result(builderFactory.createSample(m_sample_builder_name));
    for(auto plan : m_parplans)
        for(auto pattern : plan->fitParameter().patterns())
            result->setParameterValue(pattern, plan->expectedValue());
    return result;
}

std::unique_ptr<Simulation> IMinimizerTest::createSimulation()
{
    SimulationFactory simRegistry;
    return simRegistry.create(m_simulation_name);
}

std::unique_ptr<OutputData<double> > IMinimizerTest::createOutputData(
    const Simulation* simulation)
{
    std::unique_ptr<OutputData<double>> result(simulation->getDetectorIntensity());
    return result;
}
