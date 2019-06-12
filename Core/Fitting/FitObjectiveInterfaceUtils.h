// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitObjectiveInterfaceUtils.h
//! @brief     Defines extensions to the FitObjective public interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITOBJECTIVEINTERFACEUTILS_H
#define FITOBJECTIVEINTERFACEUTILS_H

#include "FitObjective.h"
#include "ArrayUtils.h"

class PyBuilderCallback;
class PyObserverCallback;

//! Defines a set of functions primarily intended for interfacing FitObjective in python API.
struct BA_CORE_API_ FitObjectiveInterfaceUtils {
    //! Constructs simulation/data pair for later fit.
    //! @param objective: FitObjective object
    //! @param callback: simulation builder capable of producing simulations
    //! @param data: experimental data array
    //! @param weight: weight of dataset in metric calculations
    template <class T>
    static void addSimulationAndData(FitObjective& objective, PyBuilderCallback& callback,
                                     const std::vector<T>& data, double weight = 1.0)
    {
        objective.addSimulationAndData(simulationBuilder(callback), *ArrayUtils::createData(data),
                                       nullptr, weight);
    }

    //! Constructs simulation/data pair for later fit.
    //! @param objective: FitObjective object
    //! @param callback: simulation builder capable of producing simulations
    //! @param data: experimental data array
    //! @param uncertainties: data uncertainties array
    //! @param weight: weight of dataset in metric calculations
    template <class T>
    static void addSimulationAndData(FitObjective& objective, PyBuilderCallback& callback,
                                     const std::vector<T>& data,
                                     const std::vector<T>& uncertainties, double weight = 1.0)
    {
        objective.addSimulationAndData(simulationBuilder(callback), *ArrayUtils::createData(data),
                                       ArrayUtils::createData(uncertainties), weight);
    }

    static std::vector<double> experimental_array(const FitObjective& objective);
    static std::vector<double> simulation_array(const FitObjective& objective);
    static std::vector<double> uncertainties(const FitObjective& objective);
    static std::vector<double> weights_array(const FitObjective& objective);

    static SimulationResult simulationResult(const FitObjective& objective, size_t i_item);
    static SimulationResult experimentalData(const FitObjective& objective, size_t i_item);
    static SimulationResult uncertaintyData(const FitObjective& objective, size_t i_item);
    static SimulationResult relativeDifference(const FitObjective& objective, size_t i_item);
    static SimulationResult absoluteDifference(const FitObjective& objective, size_t i_item);

    static void initPlot(FitObjective& objective, int every_nth, PyObserverCallback& callback);

    static void setObjectiveMetric(FitObjective& objective, const std::string& metric);
    static void setObjectiveMetric(FitObjective& objective, const std::string& metric,
                                   const std::string& norm);

    static bool containsUncertainties(const FitObjective& objective, size_t i_item);
    static bool allPairsHaveUncertainties(const FitObjective& objective);

    static std::string availableMetricOptions();

private:
    static simulation_builder_t simulationBuilder(PyBuilderCallback& callback);
};

#endif // FITOBJECTIVEINTERFACEUTILS_H
