// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MinimizerItem.cpp
//! @brief     Implements MinimizerItem class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/MinimizerItem.h"
#include "Core/Fitting/ObjectiveMetric.h"
#include "Core/Fitting/ObjectiveMetricUtils.h"
#include "Fit/Minimizer/TestMinimizer.h"
#include "Fit/RootAdapter/GSLLevenbergMarquardtMinimizer.h"
#include "Fit/RootAdapter/GSLMultiMinimizer.h"
#include "Fit/RootAdapter/GeneticMinimizer.h"
#include "Fit/RootAdapter/Minuit2Minimizer.h"
#include "Fit/RootAdapter/SimAnMinimizer.h"
#include "GUI/coregui/Models/MinimizerItemCatalog.h"

MinimizerItem::MinimizerItem(const QString& model_type) : SessionItem(model_type) {}

// ----------------------------------------------------------------------------

const QString MinimizerContainerItem::P_MINIMIZERS = "Minimizer";
const QString MinimizerContainerItem::P_METRIC = "Objective metric";
const QString MinimizerContainerItem::P_NORM = "Norm function";

MinimizerContainerItem::MinimizerContainerItem() : MinimizerItem("MinimizerContainer")
{
    addGroupProperty(P_MINIMIZERS, "Minimizer library group")->setToolTip("Minimizer library");

    ComboProperty metric_combo;
    for (auto& item : ObjectiveMetricUtils::metricNames())
        metric_combo << QString::fromStdString(item);
    metric_combo.setValue(QString::fromStdString(ObjectiveMetricUtils::defaultMetricName()));
    addProperty(P_METRIC, metric_combo.variant())
        ->setToolTip("Objective metric to use for estimating distance between simulated and "
                     "experimental data.");

    ComboProperty norm_combo;
    for (auto& item : ObjectiveMetricUtils::normNames())
        norm_combo << QString::fromStdString(item);
    norm_combo.setValue(QString::fromStdString(ObjectiveMetricUtils::defaultNormName()));
    addProperty(P_NORM, norm_combo.variant())
        ->setToolTip("Normalization to use for estimating distance between simulated and "
                     "experimental data.");
}

std::unique_ptr<IMinimizer> MinimizerContainerItem::createMinimizer() const
{
    return groupItem<MinimizerItem>(P_MINIMIZERS).createMinimizer();
}

std::unique_ptr<ObjectiveMetric> MinimizerContainerItem::createMetric() const
{
    QString metric = getItemValue(P_METRIC).value<ComboProperty>().getValue();
    QString norm = getItemValue(P_NORM).value<ComboProperty>().getValue();
    return ObjectiveMetricUtils::createMetric(metric.toStdString(), norm.toStdString());
}

// ----------------------------------------------------------------------------

const QString MinuitMinimizerItem::P_ALGORITHMS = "Algorithms";
const QString MinuitMinimizerItem::P_STRATEGY = QString::fromStdString("Strategy");
const QString MinuitMinimizerItem::P_ERRORDEF = QString::fromStdString("ErrorDef");
const QString MinuitMinimizerItem::P_TOLERANCE = QString::fromStdString("Tolerance");
const QString MinuitMinimizerItem::P_PRECISION = QString::fromStdString("Precision");
const QString MinuitMinimizerItem::P_MAXFUNCTIONCALLS = QString::fromStdString("MaxFunctionCalls");

MinuitMinimizerItem::MinuitMinimizerItem() : MinimizerItem("Minuit2")
{
    addProperty(P_ALGORITHMS, MinimizerItemCatalog::algorithmCombo(modelType()).variant());

    addProperty(P_STRATEGY, 1)
        ->setToolTip("Minimization strategy (0-low, 1-medium, 2-high quality)");

    addProperty(P_ERRORDEF, 1.0)
        ->setToolTip("Error definition factor for parameter error calculation");

    addProperty(P_TOLERANCE, 0.01)->setToolTip("Tolerance on the function value at the minimum");

    addProperty(P_PRECISION, -1.0)->setToolTip("Relative floating point arithmetic precision");

    // Minimizer internal print level is working to std::cout and is not intercepted by GUI
    //    addProperty(P_PRINTLEVEL, 0)->setToolTip("Minimizer internal print level");

    addProperty(P_MAXFUNCTIONCALLS, 0)->setToolTip("Maximum number of function calls");
}

std::unique_ptr<IMinimizer> MinuitMinimizerItem::createMinimizer() const
{
    QString algorithmName = getItemValue(P_ALGORITHMS).value<ComboProperty>().getValue();

    Minuit2Minimizer* domainMinimizer = new Minuit2Minimizer(algorithmName.toStdString());
    domainMinimizer->setStrategy(getItemValue(P_STRATEGY).toInt());
    domainMinimizer->setErrorDefinition(getItemValue(P_ERRORDEF).toDouble());
    domainMinimizer->setTolerance(getItemValue(P_TOLERANCE).toDouble());
    domainMinimizer->setPrecision(getItemValue(P_PRECISION).toDouble());
    domainMinimizer->setMaxFunctionCalls(getItemValue(P_MAXFUNCTIONCALLS).toInt());

    return std::unique_ptr<IMinimizer>(domainMinimizer);
}

// ----------------------------------------------------------------------------

const QString GSLMultiMinimizerItem::P_ALGORITHMS = "Algorithms";
const QString GSLMultiMinimizerItem::P_MAXITERATIONS = QString::fromStdString("MaxIterations");

GSLMultiMinimizerItem::GSLMultiMinimizerItem() : MinimizerItem("GSLMultiMin")
{
    addProperty(P_ALGORITHMS, MinimizerItemCatalog::algorithmCombo(modelType()).variant());
    addProperty(P_MAXITERATIONS, 0)->setToolTip("Maximum number of iterations");
}

std::unique_ptr<IMinimizer> GSLMultiMinimizerItem::createMinimizer() const
{
    QString algorithmName = getItemValue(P_ALGORITHMS).value<ComboProperty>().getValue();

    GSLMultiMinimizer* domainMinimizer = new GSLMultiMinimizer(algorithmName.toStdString());
    domainMinimizer->setMaxIterations(getItemValue(P_MAXITERATIONS).toInt());
    return std::unique_ptr<IMinimizer>(domainMinimizer);
}

// ----------------------------------------------------------------------------

const QString GeneticMinimizerItem::P_TOLERANCE = QString::fromStdString("Tolerance");
const QString GeneticMinimizerItem::P_MAXITERATIONS = QString::fromStdString("MaxIterations");
const QString GeneticMinimizerItem::P_POPULATIONSIZE = QString::fromStdString("PopSize");
const QString GeneticMinimizerItem::P_RANDOMSEED = QString::fromStdString("RandomSeed");

GeneticMinimizerItem::GeneticMinimizerItem() : MinimizerItem("Genetic")
{
    addProperty(P_TOLERANCE, 0.01)->setToolTip("Tolerance on the function value at the minimum");
    addProperty(P_MAXITERATIONS, 3)->setToolTip("Maximum number of iterations");
    addProperty(P_POPULATIONSIZE, 300)->setToolTip("Population size");
    addProperty(P_RANDOMSEED, 0)->setToolTip("Random seed");
}

std::unique_ptr<IMinimizer> GeneticMinimizerItem::createMinimizer() const
{
    GeneticMinimizer* domainMinimizer = new GeneticMinimizer();
    domainMinimizer->setTolerance(getItemValue(P_TOLERANCE).toDouble());
    domainMinimizer->setMaxIterations(getItemValue(P_MAXITERATIONS).toInt());
    domainMinimizer->setPopulationSize(getItemValue(P_POPULATIONSIZE).toInt());
    domainMinimizer->setRandomSeed(getItemValue(P_RANDOMSEED).toInt());
    return std::unique_ptr<IMinimizer>(domainMinimizer);
}

// ----------------------------------------------------------------------------

const QString SimAnMinimizerItem::P_MAXITERATIONS = QString::fromStdString("MaxIterations");
const QString SimAnMinimizerItem::P_ITERATIONSTEMP = QString::fromStdString("IterationsAtTemp");
const QString SimAnMinimizerItem::P_STEPSIZE = QString::fromStdString("StepSize");
const QString SimAnMinimizerItem::P_BOLTZMANN_K = QString::fromStdString("k");
const QString SimAnMinimizerItem::P_BOLTZMANN_TINIT = QString::fromStdString("t_init");
const QString SimAnMinimizerItem::P_BOLTZMANN_MU = QString::fromStdString("mu");
const QString SimAnMinimizerItem::P_BOLTZMANN_TMIN = QString::fromStdString("t_min");

SimAnMinimizerItem::SimAnMinimizerItem() : MinimizerItem("GSLSimAn")
{
    addProperty(P_MAXITERATIONS, 100)->setToolTip("Number of points to try for each step");
    addProperty(P_ITERATIONSTEMP, 10)->setToolTip("Number of iterations at each temperature");
    addProperty(P_STEPSIZE, 1.0)->setToolTip("Max step size used in random walk");
    addProperty(P_BOLTZMANN_K, 1.0)->setToolTip("Boltzmann k");
    addProperty(P_BOLTZMANN_TINIT, 50.0)->setToolTip("Boltzmann initial temperature");
    addProperty(P_BOLTZMANN_MU, 1.05)->setToolTip("Boltzmann mu");
    addProperty(P_BOLTZMANN_TMIN, 0.1)->setToolTip("Boltzmann minimal temperature");
}

std::unique_ptr<IMinimizer> SimAnMinimizerItem::createMinimizer() const
{
    SimAnMinimizer* domainMinimizer = new SimAnMinimizer();
    domainMinimizer->setMaxIterations(getItemValue(P_MAXITERATIONS).toInt());
    domainMinimizer->setIterationsAtEachTemp(getItemValue(P_ITERATIONSTEMP).toInt());
    domainMinimizer->setStepSize(getItemValue(P_STEPSIZE).toDouble());
    domainMinimizer->setBoltzmannK(getItemValue(P_BOLTZMANN_K).toDouble());
    domainMinimizer->setBoltzmannInitialTemp(getItemValue(P_BOLTZMANN_TINIT).toDouble());
    domainMinimizer->setBoltzmannMu(getItemValue(P_BOLTZMANN_MU).toDouble());
    domainMinimizer->setBoltzmannMinTemp(getItemValue(P_BOLTZMANN_TMIN).toDouble());
    return std::unique_ptr<IMinimizer>(domainMinimizer);
}

// ----------------------------------------------------------------------------

const QString GSLLMAMinimizerItem::P_TOLERANCE = QString::fromStdString("Tolerance");
const QString GSLLMAMinimizerItem::P_MAXITERATIONS = QString::fromStdString("MaxIterations");

GSLLMAMinimizerItem::GSLLMAMinimizerItem() : MinimizerItem("GSLLMA")
{
    addProperty(P_TOLERANCE, 0.01)->setToolTip("Tolerance on the function value at the minimum");
    addProperty(P_MAXITERATIONS, 0)->setToolTip("Maximum number of iterations");
}

std::unique_ptr<IMinimizer> GSLLMAMinimizerItem::createMinimizer() const
{
    GSLLevenbergMarquardtMinimizer* domainMinimizer = new GSLLevenbergMarquardtMinimizer();
    domainMinimizer->setTolerance(getItemValue(P_TOLERANCE).toDouble());
    domainMinimizer->setMaxIterations(getItemValue(P_MAXITERATIONS).toInt());
    return std::unique_ptr<IMinimizer>(domainMinimizer);
}

// ----------------------------------------------------------------------------

TestMinimizerItem::TestMinimizerItem() : MinimizerItem("Test") {}

std::unique_ptr<IMinimizer> TestMinimizerItem::createMinimizer() const
{
    return std::unique_ptr<IMinimizer>(new TestMinimizer());
}
