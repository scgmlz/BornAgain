// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuite.cpp
//! @brief     Implements class FitSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuite.h"
#include "FitKernel.h"
#include "FitSuiteImpl.h"
#include "FitSuitePrintObserver.h"
#include "IHistogram.h"
#include "MinimizerFactory.h"
#include <iostream>

FitSuite::FitSuite() : m_impl(new FitSuiteImpl(std::bind(&FitSuite::notifyObservers, this))) {}

FitSuite::~FitSuite() {}

void FitSuite::addSimulationAndRealData(
    const GISASSimulation& simulation, const OutputData<double>& real_data, double weight)
{
    m_impl->addSimulationAndRealData(simulation, real_data, weight);
}

void FitSuite::addSimulationAndRealData(
    const GISASSimulation& simulation, const IHistogram& real_data, double weight)
{
    const std::unique_ptr<OutputData<double>> data(real_data.createOutputData());
    m_impl->addSimulationAndRealData(simulation, *data, weight);
}

void FitSuite::addSimulationAndRealData(
    const GISASSimulation& simulation, const std::vector<std::vector<double>>& real_data,
    double weight)
{
    std::unique_ptr<IHistogram> data(IHistogram::createFrom(real_data));
    addSimulationAndRealData(simulation, *data.get(), weight);
}


FitParameterLinked* FitSuite::addFitParameter(
    const std::string& name, double value, const AttLimits& limits, double step)
{
    return m_impl->addFitParameter(name, value, limits, step);
}

void FitSuite::setMinimizer(
    const std::string& minimizer_name, const std::string& algorithm_name,
    const std::string& minimizer_options)
{
    IMinimizer* minimizer =
        MinimizerFactory::createMinimizer(minimizer_name, algorithm_name, minimizer_options);
    m_impl->setMinimizer(minimizer);
}

void FitSuite::setChiSquaredModule(const IChiSquaredModule& chi2_module)
{
    m_impl->fitObjects()->setChiSquaredModule(chi2_module);
}

void FitSuite::addFitStrategy(const IFitStrategy& strategy) { m_impl->addFitStrategy(strategy); }

void FitSuite::setMinimizer(IMinimizer* minimizer) { m_impl->setMinimizer(minimizer); }

const IMinimizer* FitSuite::minimizer() const { return m_impl->kernel()->minimizer(); }

void FitSuite::initPrint(int print_every_nth)
{
    std::shared_ptr<FitSuitePrintObserver> observer(new FitSuitePrintObserver(print_every_nth));
    attachObserver(observer);
}

void FitSuite::runFit() { m_impl->runFit(); }

int FitSuite::numberOfFitObjects() const { return m_impl->fitObjects()->getNumberOfFitObjects(); }

IHistogram* FitSuite::getRealData(size_t i_item) const
{
    return IHistogram::createHistogram(m_impl->fitObjects()->getRealData(i_item));
}

IHistogram* FitSuite::getSimulationData(size_t i_item) const
{
    return IHistogram::createHistogram(m_impl->fitObjects()->getSimulationData(i_item));
}

IHistogram* FitSuite::getChiSquaredMap(size_t i_item) const
{
    return IHistogram::createHistogram(m_impl->fitObjects()->getChiSquaredMap(i_item));
}

const OutputData<double>* FitSuite::getRealOutputData(size_t i_item) const
{
    return &m_impl->fitObjects()->getRealData(i_item);
}

const OutputData<double>* FitSuite::getSimulationOutputData(size_t i_item) const
{
    return &m_impl->fitObjects()->getSimulationData(i_item);
}

const OutputData<double>* FitSuite::getChiSquaredOutputData(size_t i_item) const
{
    return &m_impl->fitObjects()->getChiSquaredMap(i_item);
}


FitSuiteObjects* FitSuite::fitObjects() { return m_impl->fitObjects(); }

FitParameterSet* FitSuite::fitParameters() { return m_impl->fitParameters(); }

FitSuiteStrategies* FitSuite::fitStrategies() { return m_impl->fitStrategies(); }

bool FitSuite::isLastIteration() const { return m_impl->isLastIteration(); }

size_t FitSuite::numberOfIterations() const { return m_impl->numberOfIterations(); }

size_t FitSuite::currentStrategyIndex() const { return m_impl->currentStrategyIndex(); }

void FitSuite::printResults() const { std::cout << reportResults() << std::endl; }

std::string FitSuite::reportResults() const { return m_impl->reportResults(); }

double FitSuite::getChi2() const { return m_impl->fitObjects()->getChiSquaredValue(); }

void FitSuite::interruptFitting() { m_impl->interruptFitting(); }

void FitSuite::resetInterrupt() { m_impl->resetInterrupt(); }

bool FitSuite::isInterrupted() { return m_impl->isInterrupted(); }
