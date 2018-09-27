// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuite.h
//! @brief     Defines class FitSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITSUITE_H
#define FITSUITE_H

#include "IObserver.h"
#include "OutputData.h"
#include "AttLimits.h"
#include "SimulationResult.h"
#include <vector>

class Simulation;
class IHistogram;
class IChiSquaredModule;
class IFitStrategy;
class FitSuiteObjects;
class FitParameterSet;
class FitSuiteStrategies;
class FitOptions;
class FitSuiteImpl;
class IMinimizer;
class FitParameter;

//! @brief User interface class that wraps all fit methods.
//! @ingroup fitting

class BA_CORE_API_ FitSuite : public IObservable
{
public:
    FitSuite();
    FitSuite(const FitSuite&) = delete;
    FitSuite& operator=(const FitSuite&) = delete;
    ~FitSuite();

    // ------------------------------------------------------------------------
    // Fitting setup
    // ------------------------------------------------------------------------

    //! Assigns pair of (simulation, real data) for fitting. More than one pair can be added.
    void addSimulationAndRealData(const Simulation& simulation,
                                  const OutputData<double>& real_data, double weight=1);

    //! Assigns pair of (simulation, real data) for fitting. More than one pair can be added.
    void addSimulationAndRealData(const Simulation& simulation,
                                  const IHistogram& real_data, double weight=1);

    //! Assigns pair of (simulation, real data) for fitting. A version for the _real_data_
    //! represented as a two-dimensional numpy array. Simulation output must agree in dimensions
    //! with _real_data_.
    void addSimulationAndRealData(const Simulation& simulation,
                                  const std::vector<std::vector<double>>& real_data,
                                  double weight=1);

    //! Assigns pair of (simulation, real_data) for fitting. A version for the _real_data_
    //! represented as a one-dimensional numpy array. Simulation output must agree in dimensions
    //! with _real_data_.
    void addSimulationAndRealData(const Simulation& simulation,
                                  const std::vector<double>& real_data,
                                  double weight = 1);

    //! Adds fit parameter
    //! @param name The name of sample parameter(s) to fit (may contain wildcards).
    //! @param value Parameter's starting value
    //! @param limits Limits attribute
    //! @param step Initial parameter's step (some minimizers don't use it)
    FitParameter* addFitParameter(const std::string& pattern, double value,
                         const AttLimits& limits=AttLimits::limitless(), double step = 0.0);

    //! Adds fit parameter
    //! @param fitPar Fully constructed fit parameter.
    FitParameter* addFitParameter(const FitParameter& fitPar);

    //! Sets minimizer with given name and algorithm type
    //! @param minimizer_name The name of the minimizer
    //! @param algorithm_name Optional name of the minimizer's algorithm
    //! @param minimizer_options Optional string with additional minimizer settings
    void setMinimizer(const std::string& minimizer_name,
                      const std::string& algorithm_name = std::string(),
                      const std::string& minimizer_options=std::string());

    //! Replaces default ChiSquaredModule with new one
    void setChiSquaredModule(const IChiSquaredModule& chi2_module);

    //! Adds fit strategy
    void addFitStrategy(const IFitStrategy& strategy);

    //! Sets minimizer
    void setMinimizer(IMinimizer* minimizer);

    //! Returns minimizer.
//    const IMinimizer *minimizer() const;
    std::string minimizerName() const;

    //! Initializes printing to standard output during the fitting.
    //! Prints also the summary when completed.
    //! @param print_every_nth Print every n'th iteration
    void initPrint(int print_every_nth);

    //! main method to run the fitting
    void runFit();

    // ------------------------------------------------------------------------
    // Access to the data
    // ------------------------------------------------------------------------

    //! Returns number of fit objects, where fit object stands for (real, simulated) pair.
    size_t numberOfFitObjects() const;

    //! returns FitObject (pair of simulation/real data)
    FitSuiteObjects* fitObjects();

    //! Returns reference to fit parameters
    FitParameterSet* fitParameters();

    //! Returns reference to fit parameters
    FitSuiteStrategies* fitStrategies();

    //! temporary method to check if it is first iteration
    bool isFirstIteration() const;

    //! if the last iteration is done (used by observers to print summary)
    bool isLastIteration() const;

    //! Returns current number of minimization function calls
    size_t numberOfIterations() const;

    //! Returns the number of current strategy
    size_t currentStrategyIndex() const;

    //! Prints results of the minimization to the standard output.
    void printResults() const;

    //! Reports results of minimization in the form of multi-line string.
    std::string reportResults() const;

    //! Returns minimum chi squared value found
    double getChi2() const;

    void interruptFitting();
    void resetInterrupt();
    bool isInterrupted();

    //! Returns multiline string representing possible fit parameters.
    std::string parametersToString() const;

    //! Returns multiline string representing tree structure of fit components.
    std::string treeToString() const;

    //! Returns multiline string representing fit setup
    std::string setupToString();

    //! Returns simulation result.
    //! @param i_item: the index of fit pair
    SimulationResult simulationResult(size_t i_item = 0) const;

    //! Returns experimental data.
    //! @param i_item: the index of fit pair
    SimulationResult experimentalData(size_t i_item = 0) const;

    //! Returns relative difference between simulation and experimental data.
    //! @param i_item: the index of fit pair
    SimulationResult relativeDifference(size_t i_item = 0) const;

private:
    std::unique_ptr<FitSuiteImpl> m_impl;
};

#endif // FITSUITE_H
