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
#include "IterationInfo.h"
#include "MinimizerResult.h"
#include "SimDataPair.h"

class FitStatus;
class IChiSquaredModule;
class IMetricWrapper;
class ObjectiveMetric;

//! Holds vector of `SimDataPair`s (experimental data and simulation results) for use in fitting.
//! @ingroup fitting_internal

class BA_CORE_API_ FitObjective
{
    typedef std::vector<double> (SimDataPair::*DataPairAccessor)() const;
public:
    FitObjective();
    virtual ~FitObjective();

#ifndef SWIG
    //! Constructs simulation/data pair for later fit.
    //! @param builder: simulation builder capable of producing simulations
    //! @param data: experimental data array
    //! @param uncertainties: data uncertainties array
    //! @param weight: weight of dataset in metric calculations
    void addSimulationAndData(simulation_builder_t builder, const OutputData<double>& data,
                              std::unique_ptr<OutputData<double>> uncertainties,
                              double weight = 1.0);

    //! Initializes plotting during the fitting procedure.
    //! @param every_nth: Called on every n'th iteration.
    //! @param observer: observer to report the result.
    void initPlot(int every_nth, fit_observer_t observer);

    bool isCompleted() const;

    //! Returns a reference to i-th SimDataPair.
    const SimDataPair& dataPair(size_t i_item = 0) const;

    void interruptFitting();

    bool isInterrupted() const;

    bool isFirstIteration() const;

    //! Sets objective metric to the FitObjective instance
    void setObjectiveMetric(std::unique_ptr<ObjectiveMetric> metric);

    std::vector<double> composeArray(DataPairAccessor getter) const;
#endif

    virtual double evaluate(const Fit::Parameters& params);

    virtual std::vector<double> evaluate_residuals(const Fit::Parameters& params);

    size_t numberOfFitElements() const;

    //! Initializes printing to standard output during the fitting.
    //! @param every_nth: Print every n'th iteration.
    void initPrint(int every_nth);

    Fit::MinimizerResult minimizerResult() const;

    //! Should be explicitely called on last iteration to notify all observers.
    void finalize(const Fit::MinimizerResult& result);

    unsigned fitObjectCount() const;

    void run_simulations(const Fit::Parameters& params);

    IterationInfo iterationInfo() const;

    void setChiSquaredModule(const IChiSquaredModule& module);

private:
    size_t check_index(size_t index) const;

    std::vector<SimDataPair> m_fit_objects;
    std::unique_ptr<IMetricWrapper> m_metric_module;
    std::unique_ptr<FitStatus> m_fit_status;
};

#endif  // FITOBJECTIVE_H
