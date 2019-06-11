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
#include "ArrayUtils.h"
#include "IterationInfo.h"
#include "MinimizerResult.h"
#include "OutputData.h"
#include "SimDataPair.h"

class FitStatus;
class IChiSquaredModule;
class IMetricWrapper;
class ObjectiveMetric;
class PyBuilderCallback;
class PyObserverCallback;

//! Holds vector of `SimDataPair`s (experimental data and simulation results) for use in fitting.
//! @ingroup fitting_internal

class BA_CORE_API_ FitObjective
{
    static simulation_builder_t simulationBuilder(PyBuilderCallback& callback);

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
#endif
    //! Constructs simulation/data pair for later fit.
    //! @param callback: simulation builder capable of producing simulations
    //! @param data: experimental data array
    //! @param weight: weight of dataset in metric calculations
    template <class T>
    void addSimulationAndData(PyBuilderCallback& callback, const T& data, double weight = 1.0)
    {
        addSimulationAndData(simulationBuilder(callback), *ArrayUtils::createData(data), nullptr,
                             weight);
    }

    //! Constructs simulation/data pair for later fit.
    //! @param callback: simulation builder capable of producing simulations
    //! @param data: experimental data array
    //! @param uncertainties: data uncertainties array
    //! @param weight: weight of dataset in metric calculations
    template <class T>
    void addSimulationAndData(PyBuilderCallback& callback, const T& data, const T& uncertainties,
                              double weight = 1.0)
    {
        addSimulationAndData(simulationBuilder(callback), *ArrayUtils::createData(data),
                             ArrayUtils::createData(uncertainties), weight);
    }

    virtual double evaluate(const Fit::Parameters& params);

    virtual std::vector<double> evaluate_residuals(const Fit::Parameters& params);

    size_t numberOfFitElements() const;

    //! Returns one dimensional array representing merged experimental data.
    //! The area outside of the region of interest is not included, masked data is nullified.
    std::vector<double> experimental_array() const;

    //! Returns one dimensional array representing merged simulated intensities data.
    //! The area outside of the region of interest is not included, masked data is nullified.
    std::vector<double> simulation_array() const;

    //! Returns one-dimensional array representing merged data uncertainties.
    //! The area outside of the region of interest is not included, masked data is nullified.
    std::vector<double> uncertainties() const;

    //! Returns one-dimensional array representing merged user weights.
    //! The area outside of the region of interest is not included, masked data is nullified.
    std::vector<double> weights_array() const;

    //! Returns a reference to i-th SimDataPair.
    const SimDataPair& dataPair(size_t i_item = 0) const;

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

    void setChiSquaredModule(const IChiSquaredModule& module);

#ifndef SWIG
    void setObjectiveMetric(std::unique_ptr<ObjectiveMetric> metric);
#endif //SWIG

    //! Sets objective metric to the FitObjective.
    //! @param metric: metric name
    //! @param norm: metric norm name (defaults to "l2")
    void setObjectiveMetric(const std::string& metric, const std::string& norm = "L2");

private:
    typedef std::vector<double> (SimDataPair::*DataPairAccessor)() const;

    std::vector<double> composeArray(DataPairAccessor getter) const;
    size_t check_index(size_t index) const;

    std::vector<SimDataPair> m_fit_objects;
    std::unique_ptr<IMetricWrapper> m_metric_module;
    std::unique_ptr<FitStatus> m_fit_status;
};

#endif  // FITOBJECTIVE_H
