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

#include "MinimizerItem.h"
#include "GSLLevenbergMarquardtMinimizer.h"
#include "GSLMultiMinimizer.h"
#include "GeneticMinimizer.h"
#include "MinimizerConstants.h"
#include "MinimizerItemCatalogue.h"
#include "Minuit2Minimizer.h"
#include "ObjectiveMetric.h"
#include "ObjectiveMetricUtils.h"
#include "SimAnMinimizer.h"
#include "TestMinimizer.h"

MinimizerItem::MinimizerItem(const QString &model_type) : SessionItem(model_type)
{
}

// ----------------------------------------------------------------------------

const QString MinimizerContainerItem::P_MINIMIZERS = "Minimizer";
const QString MinimizerContainerItem::P_METRIC = "Objective metric";
const QString MinimizerContainerItem::P_NORM = "Norm function";

MinimizerContainerItem::MinimizerContainerItem()
    : MinimizerItem(Constants::MinimizerContainerType)
{
    addGroupProperty(P_MINIMIZERS, Constants::MinimizerLibraryGroup)
        ->setToolTip(QStringLiteral("Minimizer library"));

    ComboProperty metric_combo;
    for (auto& item: ObjectiveMetricUtils::metricNames())
        metric_combo << QString::fromStdString(item);
    metric_combo.setValue(QString::fromStdString(ObjectiveMetricUtils::defaultMetricName()));
    addProperty(P_METRIC, metric_combo.variant())
        ->setToolTip("Objective metric to use for estimating distance between simulated and "
                     "experimental data.");

    ComboProperty norm_combo;
    for (auto& item: ObjectiveMetricUtils::normNames())
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
const QString MinuitMinimizerItem::P_STRATEGY = QString::fromStdString(OptionNames::Strategy);
const QString MinuitMinimizerItem::P_ERRORDEF = QString::fromStdString(OptionNames::ErrorDef);
const QString MinuitMinimizerItem::P_TOLERANCE = QString::fromStdString(OptionNames::Tolerance);
const QString MinuitMinimizerItem::P_PRECISION = QString::fromStdString(OptionNames::Precision);
const QString MinuitMinimizerItem::P_MAXFUNCTIONCALLS
    = QString::fromStdString(OptionNames::MaxFunctionCalls);

MinuitMinimizerItem::MinuitMinimizerItem() : MinimizerItem(Constants::MinuitMinimizerType)
{
    addProperty(P_ALGORITHMS, MinimizerItemCatalogue::algorithmCombo(modelType()).variant());

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

    Minuit2Minimizer *domainMinimizer = new Minuit2Minimizer(algorithmName.toStdString());
    domainMinimizer->setStrategy(getItemValue(P_STRATEGY).toInt());
    domainMinimizer->setErrorDefinition(getItemValue(P_ERRORDEF).toDouble());
    domainMinimizer->setTolerance(getItemValue(P_TOLERANCE).toDouble());
    domainMinimizer->setPrecision(getItemValue(P_PRECISION).toDouble());
    domainMinimizer->setMaxFunctionCalls(getItemValue(P_MAXFUNCTIONCALLS).toInt());

    return std::unique_ptr<IMinimizer>(domainMinimizer);
}

// ----------------------------------------------------------------------------

const QString GSLMultiMinimizerItem::P_ALGORITHMS = "Algorithms";
const QString GSLMultiMinimizerItem::P_MAXITERATIONS
    = QString::fromStdString(OptionNames::MaxIterations);

GSLMultiMinimizerItem::GSLMultiMinimizerItem() : MinimizerItem(Constants::GSLMultiMinimizerType)
{
    addProperty(P_ALGORITHMS, MinimizerItemCatalogue::algorithmCombo(modelType()).variant());
    addProperty(P_MAXITERATIONS, 0)->setToolTip("Maximum number of iterations");
}

std::unique_ptr<IMinimizer> GSLMultiMinimizerItem::createMinimizer() const
{
    QString algorithmName = getItemValue(P_ALGORITHMS).value<ComboProperty>().getValue();

    GSLMultiMinimizer *domainMinimizer = new GSLMultiMinimizer(algorithmName.toStdString());
    domainMinimizer->setMaxIterations(getItemValue(P_MAXITERATIONS).toInt());
    return std::unique_ptr<IMinimizer>(domainMinimizer);
}

// ----------------------------------------------------------------------------

const QString GeneticMinimizerItem::P_TOLERANCE = QString::fromStdString(OptionNames::Tolerance);
const QString GeneticMinimizerItem::P_MAXITERATIONS
    = QString::fromStdString(OptionNames::MaxIterations);
const QString GeneticMinimizerItem::P_POPULATIONSIZE
    = QString::fromStdString(OptionNames::PopulationSize);
const QString GeneticMinimizerItem::P_RANDOMSEED = QString::fromStdString(OptionNames::RandomSeed);

GeneticMinimizerItem::GeneticMinimizerItem() : MinimizerItem(Constants::GeneticMinimizerType)
{
    addProperty(P_TOLERANCE, 0.01)->setToolTip("Tolerance on the function value at the minimum");
    addProperty(P_MAXITERATIONS, 3)->setToolTip("Maximum number of iterations");
    addProperty(P_POPULATIONSIZE, 300)->setToolTip("Population size");
    addProperty(P_RANDOMSEED, 0)->setToolTip("Random seed");
}

std::unique_ptr<IMinimizer> GeneticMinimizerItem::createMinimizer() const
{
    GeneticMinimizer *domainMinimizer = new GeneticMinimizer();
    domainMinimizer->setTolerance(getItemValue(P_TOLERANCE).toDouble());
    domainMinimizer->setMaxIterations(getItemValue(P_MAXITERATIONS).toInt());
    domainMinimizer->setPopulationSize(getItemValue(P_POPULATIONSIZE).toInt());
    domainMinimizer->setRandomSeed(getItemValue(P_RANDOMSEED).toInt());
    return std::unique_ptr<IMinimizer>(domainMinimizer);
}

// ----------------------------------------------------------------------------

const QString SimAnMinimizerItem::P_MAXITERATIONS
    = QString::fromStdString(OptionNames::MaxIterations);
const QString SimAnMinimizerItem::P_ITERATIONSTEMP
    = QString::fromStdString(OptionNames::IterationTemp);
const QString SimAnMinimizerItem::P_STEPSIZE = QString::fromStdString(OptionNames::StepSize);
const QString SimAnMinimizerItem::P_BOLTZMANN_K = QString::fromStdString(OptionNames::BoltzmannK);
const QString SimAnMinimizerItem::P_BOLTZMANN_TINIT
    = QString::fromStdString(OptionNames::BoltzmannInitT);
const QString SimAnMinimizerItem::P_BOLTZMANN_MU = QString::fromStdString(OptionNames::BoltzmannMu);
const QString SimAnMinimizerItem::P_BOLTZMANN_TMIN
    = QString::fromStdString(OptionNames::BoltzmannTmin);

SimAnMinimizerItem::SimAnMinimizerItem() : MinimizerItem(Constants::GSLSimAnMinimizerType)
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
    SimAnMinimizer *domainMinimizer = new SimAnMinimizer();
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

const QString GSLLMAMinimizerItem::P_TOLERANCE = QString::fromStdString(OptionNames::Tolerance);
const QString GSLLMAMinimizerItem::P_MAXITERATIONS
    = QString::fromStdString(OptionNames::MaxIterations);

GSLLMAMinimizerItem::GSLLMAMinimizerItem()
    : MinimizerItem(Constants::GSLLMAMinimizerType)
{
    addProperty(P_TOLERANCE, 0.01)->setToolTip("Tolerance on the function value at the minimum");
    addProperty(P_MAXITERATIONS, 0)->setToolTip("Maximum number of iterations");
}

std::unique_ptr<IMinimizer> GSLLMAMinimizerItem::createMinimizer() const
{
    GSLLevenbergMarquardtMinimizer *domainMinimizer = new GSLLevenbergMarquardtMinimizer();
    domainMinimizer->setTolerance(getItemValue(P_TOLERANCE).toDouble());
    domainMinimizer->setMaxIterations(getItemValue(P_MAXITERATIONS).toInt());
    return std::unique_ptr<IMinimizer>(domainMinimizer);
}

// ----------------------------------------------------------------------------

TestMinimizerItem::TestMinimizerItem()
    : MinimizerItem(Constants::TestMinimizerType)
{

}

std::unique_ptr<IMinimizer> TestMinimizerItem::createMinimizer() const
{
    return std::unique_ptr<IMinimizer>(new TestMinimizer());
}
