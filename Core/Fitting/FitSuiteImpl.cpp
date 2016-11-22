// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteImpl.cpp
//! @brief     Implements class FitSuiteImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuiteImpl.h"
#include "RealLimits.h"
#include "FitParameter.h"
#include "FitParameterLinked.h"
#include "Logger.h"
#include "MinimizerFactory.h"
#include "ParameterPool.h"
#include "IMinimizer.h"
#include "FitKernel.h"
#include <stdexcept>

FitSuiteImpl::FitSuiteImpl(const std::function<void()>& notifyObservers)
    : m_is_last_iteration(false)
    , m_is_interrupted(false)
    , m_notifyObservers(notifyObservers)
    , m_kernel(new FitKernel)
{
    m_function_chi2.init(this);
    m_function_gradient.init(this);
    m_fit_strategies.init(this);
}

FitSuiteImpl::~FitSuiteImpl()
{
    clear();
}

//! Clears all data.
void FitSuiteImpl::clear()
{
    m_fit_objects.clear();
    m_kernel->clear();
    m_fit_strategies.clear();
    m_is_last_iteration = false;
    m_is_interrupted = false;
}

//! Adds pair of (simulation, real data) for consecutive simulation
void FitSuiteImpl::addSimulationAndRealData(const GISASSimulation& simulation,
                                         const OutputData<double>& real_data, double weight)
{
    m_fit_objects.add(simulation, real_data, weight);
}

//! Adds fit parameter, step is calculated from initial parameter value
FitParameterLinked* FitSuiteImpl::addFitParameter(const std::string& name, double value,
                                  const AttLimits& limits, double step)
{
    if(step <=0.0)
        step = value * getOptions().stepFactor();

    FitParameterLinked* result = new FitParameterLinked(name, value, limits, step);
    m_kernel->fitParameters()->addFitParameter(result);
    return result;
}

void FitSuiteImpl::addFitStrategy(const IFitStrategy& strategy)
{
    m_fit_strategies.addStrategy(strategy);
}

void FitSuiteImpl::setMinimizer(IMinimizer* minimizer)
{
    m_kernel->setMinimizer(minimizer);
}

void FitSuiteImpl::runFit()
{
    // check if all prerequisites are fullfilled before starting minimization
    check_prerequisites();

    m_is_last_iteration = false;

    // link fit parameters with parameters defined in the simulation
    link_fit_parameters();

    // run minimization using strategies
    m_fit_strategies.minimize();

    // call observers to let them to get results
    m_is_last_iteration = true;
    notifyObservers();
}

void FitSuiteImpl::minimize()
{
    objective_function_t fun_chi2 =
        [&] (const std::vector<double>& pars) {return m_function_chi2.evaluate(pars);};
    m_kernel->setObjectiveFunction( fun_chi2);

    gradient_function_t fun_gradient =
        [&] (const std::vector<double>& pars, int index, std::vector<double> &gradients)
        {
            return m_function_gradient.evaluate(pars, index, gradients);
        };
    m_kernel->setGradientFunction(
        fun_gradient, m_fit_objects.getSizeOfDataSet() );

    m_fit_objects.setNfreeParameters((int)fitParameters()->freeFitParameterCount());

    // minimize
    try {
//        m_minimizer->minimize();
        m_kernel->minimize();
    } catch (int) {}

    m_fit_objects.runSimulations(); // we run simulation once again for best values found
}

FitParameterSet* FitSuiteImpl::fitParameters() {
    return m_kernel->fitParameters();
}

// get current number of minimization function calls
size_t FitSuiteImpl::numberOfIterations() const
{
    return m_kernel->functionCalls();
}

size_t FitSuiteImpl::currentStrategyIndex() const
{
    return m_fit_strategies.currentStrategyIndex();
}

std::string FitSuiteImpl::reportResults() const
{
    return m_kernel->reportResults();
}

const FitKernel* FitSuiteImpl::kernel() const
{
   return m_kernel.get();
}

bool FitSuiteImpl::check_prerequisites() const
{
    if( !m_fit_objects.getNumberOfFitObjects() ) throw Exceptions::LogicErrorException(
        "FitSuite::check_prerequisites() -> Error! No simulation/data description defined");
    if( m_fit_objects.getSizeOfDataSet() == 0) throw Exceptions::LogicErrorException(
        "FitSuite::check_prerequisites() -> Error! No elements to fit. "
        "Looks like whole detector is masked.");
    return true;
}

//! link FitMultiParameters with simulation parameters
void FitSuiteImpl::link_fit_parameters()
{
    const std::unique_ptr<ParameterPool> pool(m_fit_objects.createParameterTree());
    for (auto par: *m_kernel->fitParameters()) {
        FitParameterLinked* linkedPar = dynamic_cast<FitParameterLinked*>(par);
        if( !linkedPar )
            throw std::runtime_error(
                "FitKernel::link_fit_parameters() -> Error! Can't cast to FitParameterLinked.");
        linkedPar->addMatchedParametersFromPool(pool.get());
    }
    msglog(Logging::DEBUG2) << "FitSuite::link_fit_parameters() -> Parameter pool:";
    msglog(Logging::DEBUG2) << *pool;
}
