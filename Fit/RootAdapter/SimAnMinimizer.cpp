// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/SimAnMinimizer.cpp
//! @brief     Implements class SimAnMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SimAnMinimizer.h"
#include "GSLMultiMinimizer.h"
#include "MinimizerConstants.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/PatchedGSLSimAnMinimizer.h"
#pragma GCC diagnostic pop

SimAnMinimizer::SimAnMinimizer()
    : RootMinimizerAdapter(MinimizerInfo::buildGSLSimAnInfo())
    , m_siman_minimizer(new BA_ROOT::Math::GSLSimAnMinimizer())
{
    addOption(OptionNames::PrintLevel, 0, "Minimizer internal print level");
    addOption(OptionNames::MaxIterations, 100, "Number of points to try for each step");
    addOption(OptionNames::IterationTemp, 10, "Number of iterations at each temperature");
    addOption(OptionNames::StepSize, 1.0, "Max step size used in random walk");
    addOption(OptionNames::BoltzmannK, 1.0, "Boltzmann k");
    addOption(OptionNames::BoltzmannInitT, 50.0, "Boltzmann initial temperature");
    addOption(OptionNames::BoltzmannMu, 1.05, "Boltzmann mu");
    addOption(OptionNames::BoltzmannTmin, 0.1, "Boltzmann minimal temperature");
}

SimAnMinimizer::~SimAnMinimizer() {}

void SimAnMinimizer::setPrintLevel(int value)
{
    setOptionValue(OptionNames::PrintLevel, value);
}

int SimAnMinimizer::printLevel() const
{
    return optionValue<int>(OptionNames::PrintLevel);
}

void SimAnMinimizer::setMaxIterations(int value)
{
    setOptionValue(OptionNames::MaxIterations, value);
}

int SimAnMinimizer::maxIterations() const
{
    return optionValue<int>(OptionNames::MaxIterations);
}

void SimAnMinimizer::setIterationsAtEachTemp(int value)
{
    setOptionValue(OptionNames::IterationTemp, value);
}

int SimAnMinimizer::iterationsAtEachTemp() const
{
    return optionValue<int>(OptionNames::IterationTemp);
}

void SimAnMinimizer::setStepSize(double value)
{
    setOptionValue(OptionNames::StepSize, value);
}

double SimAnMinimizer::stepSize() const
{
    return optionValue<double>(OptionNames::StepSize);
}

void SimAnMinimizer::setBoltzmannK(double value)
{
    setOptionValue(OptionNames::BoltzmannK, value);
}

double SimAnMinimizer::boltzmannK() const
{
    return optionValue<double>(OptionNames::BoltzmannK);
}

void SimAnMinimizer::setBoltzmannInitialTemp(double value)
{
    setOptionValue(OptionNames::BoltzmannInitT, value);
}

double SimAnMinimizer::boltzmannInitialTemp() const
{
    return optionValue<double>(OptionNames::BoltzmannInitT);
}

void SimAnMinimizer::setBoltzmannMu(double value)
{
    setOptionValue(OptionNames::BoltzmannMu, value);
}

double SimAnMinimizer::boltzmannMu() const
{
    return optionValue<double>(OptionNames::BoltzmannMu);
}

void SimAnMinimizer::setBoltzmannMinTemp(double value)
{
    setOptionValue(OptionNames::BoltzmannTmin, value);
}

double SimAnMinimizer::boltzmannMinTemp() const
{
    return optionValue<double>(OptionNames::BoltzmannTmin);
}

std::map<std::string, std::string> SimAnMinimizer::statusMap() const
{
    auto result = RootMinimizerAdapter::statusMap();
    result["functionCalls"] = std::to_string(rootMinimizer()->NCalls());
    return result;
}

void SimAnMinimizer::propagateOptions()
{
    BA_ROOT::Math::GSLSimAnParams& pars = m_siman_minimizer->getSolver().Params();
    pars.n_tries = maxIterations();
    pars.iters_fixed_T = iterationsAtEachTemp();
    pars.step_size = stepSize();
    pars.k = boltzmannK();
    pars.t_initial = boltzmannInitialTemp();
    pars.mu = boltzmannMu();
    pars.t_min = boltzmannMinTemp();
}

const RootMinimizerAdapter::root_minimizer_t* SimAnMinimizer::rootMinimizer() const
{
    return m_siman_minimizer.get();
}
