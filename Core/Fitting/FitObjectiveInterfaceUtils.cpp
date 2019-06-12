// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitObjectiveInterfaceUtils.cpp
//! @brief     Implements extensions to the FitObjective public interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitObjectiveInterfaceUtils.h"
#include "ObjectiveMetric.h"
#include "ObjectiveMetricUtils.h"
#include "PyFittingCallbacks.h"
#include "Simulation.h"

simulation_builder_t FitObjectiveInterfaceUtils::simulationBuilder(PyBuilderCallback& callback)
{
    return [&callback](const Fit::Parameters& params) {
        auto simulation = callback.build_simulation(params);
        std::unique_ptr<Simulation> clone(simulation->clone());
        delete simulation; // deleting Python object
        return clone;
    };
}

//! Returns one dimensional array representing merged experimental data.
//! The area outside of the region of interest is not included, masked data is nullified.
//! @param objective: FitObjective object
std::vector<double> FitObjectiveInterfaceUtils::experimental_array(const FitObjective& objective)
{
    return objective.composeArray(&SimDataPair::experimental_array);
}

//! Returns one dimensional array representing merged simulated intensities data.
//! The area outside of the region of interest is not included, masked data is nullified.
//! @param objective: FitObjective object
std::vector<double> FitObjectiveInterfaceUtils::simulation_array(const FitObjective& objective)
{
    return objective.composeArray(&SimDataPair::simulation_array);
}

//! Returns one-dimensional array representing merged data uncertainties.
//! The area outside of the region of interest is not included, masked data is nullified.
//! @param objective: FitObjective object
std::vector<double> FitObjectiveInterfaceUtils::uncertainties(const FitObjective& objective)
{
    return objective.composeArray(&SimDataPair::uncertainties_array);
}

//! Returns one-dimensional array representing merged user weights.
//! The area outside of the region of interest is not included, masked data is nullified.
//! @param objective: FitObjective object
std::vector<double> FitObjectiveInterfaceUtils::weights_array(const FitObjective& objective)
{
    return objective.composeArray(&SimDataPair::user_weights_array);
}

//! Returns simulation result.
//! @param objective: FitObjective object
//! @param i_item: the index of fit pair
SimulationResult FitObjectiveInterfaceUtils::simulationResult(const FitObjective& objective,
                                                              size_t i_item)
{
    return objective.dataPair(i_item).simulationResult();
}

//! Returns experimental data.
//! @param objective: FitObjective object
//! @param i_item: the index of fit pair
SimulationResult FitObjectiveInterfaceUtils::experimentalData(const FitObjective& objective,
                                                              size_t i_item)
{
    return objective.dataPair(i_item).experimentalData();
}

//! Returns experimental data uncertainties.
//! @param objective: FitObjective object
//! @param i_item: the index of fit pair
SimulationResult FitObjectiveInterfaceUtils::uncertaintyData(const FitObjective& objective,
                                                             size_t i_item)
{
    return objective.dataPair(i_item).uncertainties();
}

//! Returns relative difference between simulation and experimental data.
//! @param objective: FitObjective object
//! @param i_item: the index of fit pair
SimulationResult FitObjectiveInterfaceUtils::relativeDifference(const FitObjective& objective,
                                                                size_t i_item)
{
    return objective.dataPair(i_item).relativeDifference();
}

//! Returns absolute value of difference between simulation and experimental data.
//! @param objective: FitObjective object
//! @param i_item: the index of fit pair
SimulationResult FitObjectiveInterfaceUtils::absoluteDifference(const FitObjective& objective,
                                                                size_t i_item)
{
    return objective.dataPair(i_item).absoluteDifference();
}

//! Initializes plotting during the fitting using Python callable.
//! @param objective: FitObjective object
//! @param every_nth: Called on every n'th iteration.
//! @param callback: observer callback called each every_nth iterations.
void FitObjectiveInterfaceUtils::initPlot(FitObjective& objective, int every_nth,
                                          PyObserverCallback& callback)
{
    fit_observer_t observer = [&](const FitObjective& objective) { callback.update(objective); };
    objective.initPlot(every_nth, observer);
}

//! Sets objective metric with the default L2-norm to the FitObjective.
//! @param objective: FitObjective object
//! @param metric: metric name
void FitObjectiveInterfaceUtils::setObjectiveMetric(FitObjective& objective,
                                                    const std::string& metric)
{
    objective.setObjectiveMetric(ObjectiveMetricUtils::createMetric(metric));
}

//! Sets objective metric to the FitObjective.
//! @param objective: FitObjective object
//! @param metric: metric name
//! @param norm: metric norm name
void FitObjectiveInterfaceUtils::setObjectiveMetric(FitObjective& objective,
                                                    const std::string& metric,
                                                    const std::string& norm)
{
    objective.setObjectiveMetric(ObjectiveMetricUtils::createMetric(metric, norm));
}

//! Returns true if the specified DataPair element contains uncertainties
bool FitObjectiveInterfaceUtils::containsUncertainties(const FitObjective& objective, size_t i_item)
{
    return objective.dataPair(i_item).containsUncertainties();
}

//! Returns true if all the data pairs in FitObjective instance contain uncertainties
bool FitObjectiveInterfaceUtils::allPairsHaveUncertainties(const FitObjective& objective)
{
    bool result = true;
    for (size_t i = 0, size = objective.fitObjectCount(); i < size; ++i)
        result = result && objective.dataPair(i).containsUncertainties();
    return result;
}

//! Returns available objective metrics and norms
std::string FitObjectiveInterfaceUtils::availableMetricOptions()
{
    return ObjectiveMetricUtils::availableMetricOptions();
}
