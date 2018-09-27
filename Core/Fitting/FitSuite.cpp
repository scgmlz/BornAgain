// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuite.cpp
//! @brief     Implements class FitSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitSuite.h"
#include "FitSuiteImpl.h"
#include "FitSuitePrintObserver.h"
#include "IHistogram.h"
#include "MinimizerFactory.h"
#include "ParameterPool.h"
#include <iostream>

FitSuite::FitSuite()
    : m_impl(new FitSuiteImpl(std::bind(&FitSuite::notifyObservers, this)))
{
}

FitSuite::~FitSuite()
{}

void FitSuite::addSimulationAndRealData(const Simulation& simulation,
                                        const OutputData<double>& real_data, double weight)
{
    m_impl->addSimulationAndRealData(simulation, real_data, weight);
}

void FitSuite::addSimulationAndRealData(const Simulation& simulation,
                                        const IHistogram& real_data, double weight)
{
    const std::unique_ptr<OutputData<double>> data(real_data.createOutputData());
    m_impl->addSimulationAndRealData(simulation, *data, weight);
}

void FitSuite::addSimulationAndRealData(const Simulation& simulation,
                              const std::vector<std::vector<double>>& real_data,
                              double weight)
{
    // TODO: provide a way to construct OutputData<double> right from numpy array
    std::unique_ptr<IHistogram> data(IHistogram::createFrom(real_data));
    addSimulationAndRealData(simulation, *data, weight);
}

void FitSuite::addSimulationAndRealData(const Simulation& simulation,
                                        const std::vector<double>& real_data,
                                        double weight)
{
    const size_t data_size = real_data.size();
    if (data_size == 0)
        throw std::runtime_error("Error in FitSuite::addSimulationAndRealData: real_data array"
                                 "is of zero size.");
    std::unique_ptr<OutputData<double>> data_container(new OutputData<double>);
    data_container->addAxis("x-axis", data_size, 0.0, static_cast<double>(data_size - 1));
    for (size_t i = 0; i < data_size; ++i)
        (*data_container)[i] = real_data[i];
    addSimulationAndRealData(simulation, *data_container, weight);
}

FitParameter *FitSuite::addFitParameter(const std::string& pattern, double value,
                               const AttLimits& limits, double step)
{
    return m_impl->addFitParameter(pattern, value, limits, step);
}

FitParameter* FitSuite::addFitParameter(const FitParameter& fitPar)
{
    return m_impl->addFitParameter(fitPar);
}

void FitSuite::setMinimizer(const std::string& minimizer_name, const std::string& algorithm_name,
                            const std::string& minimizer_options)
{
    IMinimizer* minimizer = MinimizerFactory::createMinimizer(minimizer_name, algorithm_name,
                                                              minimizer_options);
    m_impl->setMinimizer(minimizer);
}

void FitSuite::setChiSquaredModule(const IChiSquaredModule& chi2_module)
{
    m_impl->fitObjects()->setChiSquaredModule(chi2_module);
}

void FitSuite::addFitStrategy(const IFitStrategy& strategy)
{
    m_impl->addFitStrategy(strategy);
}

void FitSuite::setMinimizer(IMinimizer* minimizer)
{
    m_impl->setMinimizer(minimizer);
}

std::string FitSuite::minimizerName() const
{
    // FIXME
    return std::string("FIXME");
}

//const IMinimizer *FitSuite::minimizer() const
//{
//    return m_impl->kernel()->minimizer();
//}

void FitSuite::initPrint(int print_every_nth)
{
    std::shared_ptr<FitSuitePrintObserver> observer(new FitSuitePrintObserver(print_every_nth));
    attachObserver(observer);
}

void FitSuite::runFit()
{
    m_impl->runFit();
}

size_t FitSuite::numberOfFitObjects() const
{
    return m_impl->fitObjects()->size();
}

std::string FitSuite::parametersToString() const
{
    return m_impl->fitObjects()->parametersToString();
}

std::string FitSuite::treeToString() const
{
    return m_impl->fitObjects()->treeToString();
}

std::string FitSuite::setupToString()
{
    return m_impl->setupToString();
}

FitSuiteObjects* FitSuite::fitObjects()
{
    return m_impl->fitObjects();
}

FitParameterSet* FitSuite::fitParameters()
{
    return m_impl->fitParameters();
}

FitSuiteStrategies* FitSuite::fitStrategies()
{
    return m_impl->fitStrategies();
}

bool FitSuite::isFirstIteration() const
{
    // FIXME temporary method: before refactoring first iteration had index 0
    return m_impl->numberOfIterations() == 1;
}

bool FitSuite::isLastIteration() const
{
    return m_impl->isLastIteration();
}

size_t FitSuite::numberOfIterations() const
{
    return m_impl->numberOfIterations();
}

size_t FitSuite::currentStrategyIndex() const
{
    return m_impl->currentStrategyIndex();
}

void FitSuite::printResults() const
{
    std::cout <<reportResults() << std::endl;
}

std::string FitSuite::reportResults() const
{
    return m_impl->reportResults();
}

double FitSuite::getChi2() const
{
    return m_impl->fitObjects()->getChiSquaredValue();
}

void FitSuite::interruptFitting()
{
    m_impl->interruptFitting();
}

void FitSuite::resetInterrupt()
{
    m_impl->resetInterrupt();
}

bool FitSuite::isInterrupted()
{
    return m_impl->isInterrupted();
}

SimulationResult FitSuite::simulationResult(size_t i_item) const
{
    return m_impl->fitObjects()->simulationResult(i_item);
}

SimulationResult FitSuite::experimentalData(size_t i_item) const
{
    return m_impl->fitObjects()->experimentalData(i_item);
}

SimulationResult FitSuite::relativeDifference(size_t i_item) const
{
    return m_impl->fitObjects()->relativeDifference(i_item);
}

