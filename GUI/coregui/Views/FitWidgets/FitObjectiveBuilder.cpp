// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitObjectiveBuilder.cpp
//! @brief     Implements class SimulationBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitObjectiveBuilder.h"
#include "ChiSquaredModule.h"
#include "DataItem.h"
#include "DomainSimulationBuilder.h"
#include "FitObjective.h"
#include "FitParameterItems.h"
#include "FitSuiteItem.h"
#include "GUIFitObserver.h"
#include "GUIHelpers.h"
#include "IIntensityFunction.h"
#include "IMinimizer.h"
#include "JobItem.h"
#include "KernelTypes.h"
#include "Minimizer.h"
#include "MinimizerItem.h"
#include "MultiLayer.h"
#include "ObjectiveMetric.h"
#include "OutputData.h"
#include "Parameters.h"
#include "RealDataItem.h"
#include "Simulation.h"
#include "VarianceFunctions.h"

FitObjectiveBuilder::FitObjectiveBuilder(JobItem* jobItem) : m_jobItem(jobItem)
{
    Q_ASSERT(m_jobItem->fitSuiteItem());
}

FitObjectiveBuilder::~FitObjectiveBuilder() = default;

void FitObjectiveBuilder::runFit()
{
    m_fit_objective = createFitObjective();

    auto module = m_jobItem->fitSuiteItem()->minimizerContainerItem()->createMetric();
    m_fit_objective->setObjectiveMetric(std::move(module));

    if (m_observer) {
        fit_observer_t plot_observer = [&](const FitObjective& obj) { m_observer->update(&obj); };
        m_fit_objective->initPlot(1, plot_observer);
    }

    auto minimizer_impl = createMinimizer();
    const bool requires_residuals = minimizer_impl->requiresResiduals();

    Fit::Minimizer minimizer;
    minimizer.setMinimizer(minimizer_impl.release());

    auto result =
        requires_residuals
            ? minimizer.minimize(
                  [&](const Fit::Parameters& params) {
                      return m_fit_objective->evaluate_residuals(params);
                  },
                  createParameters())
            : minimizer.minimize(
                  [&](const Fit::Parameters& params) { return m_fit_objective->evaluate(params); },
                  createParameters());
    m_fit_objective->finalize(result);
}

std::unique_ptr<FitObjective> FitObjectiveBuilder::createFitObjective() const
{
    std::unique_ptr<FitObjective> result(new FitObjective);

    simulation_builder_t builder = [&](const Fit::Parameters& params) {
        return buildSimulation(params);
    };

    result->addSimulationAndData(builder, *createOutputData(), nullptr, 1.0);

    return result;
}

std::unique_ptr<IMinimizer> FitObjectiveBuilder::createMinimizer() const
{
    auto fitSuiteItem = m_jobItem->fitSuiteItem();
    return fitSuiteItem->minimizerContainerItem()->createMinimizer();
}

Fit::Parameters FitObjectiveBuilder::createParameters() const
{
    auto fitSuiteItem = m_jobItem->fitSuiteItem();
    return fitSuiteItem->fitParameterContainerItem()->createParameters();
}

void FitObjectiveBuilder::attachObserver(std::shared_ptr<GUIFitObserver> observer)
{
    m_observer = observer;
}

void FitObjectiveBuilder::interruptFitting()
{
    m_fit_objective->interruptFitting();
}

std::unique_ptr<Simulation>
FitObjectiveBuilder::buildSimulation(const Fit::Parameters& params) const
{
    static std::mutex build_simulation_mutex;
    std::unique_lock<std::mutex> lock(build_simulation_mutex);

    update_fit_parameters(params);
    return DomainSimulationBuilder::createSimulation(m_jobItem->multiLayerItem(),
                                                     m_jobItem->instrumentItem(),
                                                     m_jobItem->simulationOptionsItem());
}

std::unique_ptr<OutputData<double>> FitObjectiveBuilder::createOutputData() const
{
    auto realDataItem = m_jobItem->realDataItem();
    if (!realDataItem)
        throw GUIHelpers::Error("FitObjectiveBuilder::createOutputData() -> No Real Data defined.");

    const DataItem* intensity_item = realDataItem->dataItem();
    Q_ASSERT(intensity_item);
    Q_ASSERT(intensity_item->getOutputData());

    return std::unique_ptr<OutputData<double>>(intensity_item->getOutputData()->clone());
}

void FitObjectiveBuilder::update_fit_parameters(const Fit::Parameters& params) const
{
    QVector<double> values = GUIHelpers::fromStdVector(params.values());

    auto fitParContainer = m_jobItem->fitParameterContainerItem();
    fitParContainer->setValuesInParameterContainer(values, m_jobItem->parameterContainerItem());
}
