// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitObjective.h
//! @brief     Defines class FitObjective.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITOBJECTIVE_H
#define FITOBJECTIVE_H

#include "FitTypes.h"
#include "OutputData.h"
#include "SafePointerVector.h"
#include "SimDataPair.h"
#include "IterationInfo.h"
#include "MinimizerResult.h"

class IChiSquaredModule;
class PyBuilderCallback;
class PyObserverCallback;
class FitStatus;

//! Main class to hold pairs of simulation
//! Holds vector of FitObject's (simulation and real data) to fit
//! @ingroup fitting_internal

class BA_CORE_API_ FitObjective
{
public:

    FitObjective();
    virtual ~FitObjective();

    //! Constructs simulation/data pair for later fit.
    //! @param simulation: simulation builder capable of producing simulations
    //! @param data: experimental data
    //! @param weight: weight of dataset in chi2 calculations
#ifndef SWIG
    void addSimulationAndData(simulation_builder_t builder, const OutputData<double>& data,
                              double weight = 1.0);
#endif
    void addSimulationAndData(PyBuilderCallback& callback,
                              const std::vector<double>& data,
                              double weight = 1.0);

    void addSimulationAndData(PyBuilderCallback& callback,
                              const std::vector<std::vector<double>>& data,
                              double weight = 1.0);

    virtual double evaluate(const Fit::Parameters& params);

    virtual std::vector<double> evaluate_residuals(const Fit::Parameters& params);

    size_t numberOfFitElements() const;

    //! Returns one dimensional array representing experimental data.
    //! Masked areas and the area outside of region of interest are not included.
    //! Data from different datasets merged together.
    std::vector<double> experimental_array() const;

    //! Returns one dimensional array representing simulated intensities data.
    //! Masked areas and the area outside of region of interest are not included.
    //! Data from different datasets merged together.
    std::vector<double> simulation_array() const;

    //! Returns simulation result.
    //! @param i_item: the index of fit pair
    SimulationResult simulationResult(size_t i_item = 0) const;

    //! Returns experimental data.
    //! @param i_item: the index of fit pair
    SimulationResult experimentalData(size_t i_item = 0) const;

    //! Returns relative difference between simulation and experimental data.
    //! @param i_item: the index of fit pair
    SimulationResult relativeDifference(size_t i_item = 0) const;

    //! Returns absolute value of difference between simulation and experimental data.
    //! @param i_item: the index of fit pair
    SimulationResult absoluteDifference(size_t i_item = 0) const;

    //! Initializes printing to standard output during the fitting.
    //! @param every_nth: Print every n'th iteration.
    void initPrint(int every_nth);

    //! Initializes plotting during the fitting using Python callable.
    //! @param every_nth: Called on every n'th iteration.
#ifndef SWIG
    void initPlot(int every_nth, fit_observer_t observer);
#endif
    void initPlot(int every_nth, PyObserverCallback& callback);

    bool isCompleted() const;

    IterationInfo iterationInfo() const;

    Fit::MinimizerResult minimizerResult() const;

    //! Should be explicitely called on last iteration to notify all observers.
    void finalize(const Fit::MinimizerResult& result);

    unsigned fitObjectCount() const;

    void interruptFitting();

    bool isInterrupted() const;

    bool isFirstIteration() const;

    void run_simulations(const Fit::Parameters& params);

private:
    double residual(double a, double b, double weight) const;
    double evaluate_chi2(const std::vector<double>& residuals, const Fit::Parameters& params);
    size_t check_index(size_t index) const;

    std::vector<double> m_experimental_array;
    std::vector<double> m_simulation_array;

    SafePointerVector<SimDataPair> m_fit_objects;
    double m_total_weight;
    std::unique_ptr<IChiSquaredModule> m_chi2_module;
    std::unique_ptr<FitStatus> m_fit_status;
};

#endif  // FITOBJECTIVE_H
