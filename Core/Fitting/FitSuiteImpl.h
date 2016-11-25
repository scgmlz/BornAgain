// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteImpl.h
//! @brief     Defines class FitSuiteImpl.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEIMPL_H
#define FITSUITEIMPL_H

#include "FitOptions.h"
#include "FitParameterSet.h"
#include "FitSuiteFunctions.h"
#include "FitSuiteObjects.h"
#include "FitSuiteStrategies.h"
#include <functional>
#ifndef SWIG
#include <atomic>
#endif

class AttLimits;
class GISASSimulation;
class IMinimizer;
class FitKernel;
class FitParameterLinked;

//! Fitting kernel for FitSuite.
//! @ingroup fitting_internal

class BA_CORE_API_ FitSuiteImpl
{
public:
    FitSuiteImpl(const std::function<void()>& notifyObservers);
    FitSuiteImpl& operator=(const FitSuiteImpl&) = delete;
    FitSuiteImpl(const FitSuiteImpl&) = delete;
    virtual ~FitSuiteImpl();

    //! Resets most state variables, to get prepared for the next fit
    void clear();

    //! Adds pair of (simulation, real data) for consecutive simulation
    void addSimulationAndRealData(
        const GISASSimulation& simulation, const OutputData<double>& real_data, double weight);

    //! Adds fit parameter
    FitParameterLinked* addFitParameter(
        const std::string& name, double value, const AttLimits& limits, double step = 0.0);

    //! Adds fit strategy
    void addFitStrategy(const IFitStrategy& strategy);

    //! Sets minimizer
    void setMinimizer(IMinimizer* minimizer);

    //! Runs a fit, which may consist of several minimization rounds
    virtual void runFit();

    //! Runs a single minimization round (called by FitSuiteStrategy)
    void minimize();

    //! Returns reference to the kit with data
    FitSuiteObjects* fitObjects() { return &m_fit_objects; }
    const FitSuiteObjects* fitObjects() const { return &m_fit_objects; }

    //! Returns reference to fit parameters
    FitParameterSet* fitParameters();

    //! Returns reference to fit parameters
    FitSuiteStrategies* fitStrategies() { return &m_fit_strategies; }

    //! Returns true if the last iteration is done (used by observers to print summary)
    bool isLastIteration() const { return m_is_last_iteration; }

    //! Returns current number of minimization function calls
    size_t numberOfIterations() const;

    //! Returns the number of current strategy
    size_t currentStrategyIndex() const;

    //! Reports results of minimization in the form of multi-line string.
    std::string reportResults() const;

    //! Returns current fit options
    FitOptions& getOptions() { return m_fit_options; }

    //! Sets fit options
    void setOptions(const FitOptions& fit_options) { m_fit_options = fit_options; }

    void notifyObservers() { m_notifyObservers(); }

    void interruptFitting() { m_is_interrupted = true; }
    void resetInterrupt() { m_is_interrupted = false; }
    bool isInterrupted() const { return m_is_interrupted; }

    const FitKernel* kernel() const;

private:
    bool check_prerequisites() const;
    void link_fit_parameters();

    FitOptions m_fit_options;
    FitSuiteObjects m_fit_objects;
    FitSuiteStrategies m_fit_strategies;
    FitSuiteChiSquaredFunction m_function_chi2;
    FitSuiteGradientFunction m_function_gradient;
    bool m_is_last_iteration;
#ifndef SWIG
    std::atomic<bool> m_is_interrupted;
#endif
    std::function<void()> m_notifyObservers;
    std::unique_ptr<FitKernel> m_kernel;
};

#endif // FITSUITEIMPL_H
