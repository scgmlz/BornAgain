// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/SimAnMinimizer.cpp
//! @brief     Implements class SimAnMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/RootAdapter/SimAnMinimizer.h"
#include "Fit/RootAdapter/GSLMultiMinimizer.h"

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4267)
#include "Math/GSLSimAnMinimizer.h"
#pragma warning(pop)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/GSLSimAnMinimizer.h"
#pragma GCC diagnostic pop
#endif

SimAnMinimizer::SimAnMinimizer()
    : RootMinimizerAdapter(MinimizerInfo::buildGSLSimAnInfo()),
      m_siman_minimizer(new ROOT::Math::GSLSimAnMinimizer())
{
    addOption("PrintLevel", 0, "Minimizer internal print level");
    addOption("MaxIterations", 100, "Number of points to try for each step");
    addOption("IterationsAtTemp", 10, "Number of iterations at each temperature");
    addOption("StepSize", 1.0, "Max step size used in random walk");
    addOption("k", 1.0, "Boltzmann k");
    addOption("t_init", 50.0, "Boltzmann initial temperature");
    addOption("mu", 1.05, "Boltzmann mu");
    addOption("t_min", 0.1, "Boltzmann minimal temperature");
}

SimAnMinimizer::~SimAnMinimizer() = default;

void SimAnMinimizer::setPrintLevel(int value)
{
    setOptionValue("PrintLevel", value);
}

int SimAnMinimizer::printLevel() const
{
    return optionValue<int>("PrintLevel");
}

void SimAnMinimizer::setMaxIterations(int value)
{
    setOptionValue("MaxIterations", value);
}

int SimAnMinimizer::maxIterations() const
{
    return optionValue<int>("MaxIterations");
}

void SimAnMinimizer::setIterationsAtEachTemp(int value)
{
    setOptionValue("IterationsAtTemp", value);
}

int SimAnMinimizer::iterationsAtEachTemp() const
{
    return optionValue<int>("IterationsAtTemp");
}

void SimAnMinimizer::setStepSize(double value)
{
    setOptionValue("StepSize", value);
}

double SimAnMinimizer::stepSize() const
{
    return optionValue<double>("StepSize");
}

void SimAnMinimizer::setBoltzmannK(double value)
{
    setOptionValue("k", value);
}

double SimAnMinimizer::boltzmannK() const
{
    return optionValue<double>("k");
}

void SimAnMinimizer::setBoltzmannInitialTemp(double value)
{
    setOptionValue("t_init", value);
}

double SimAnMinimizer::boltzmannInitialTemp() const
{
    return optionValue<double>("t_init");
}

void SimAnMinimizer::setBoltzmannMu(double value)
{
    setOptionValue("mu", value);
}

double SimAnMinimizer::boltzmannMu() const
{
    return optionValue<double>("mu");
}

void SimAnMinimizer::setBoltzmannMinTemp(double value)
{
    setOptionValue("t_min", value);
}

double SimAnMinimizer::boltzmannMinTemp() const
{
    return optionValue<double>("t_min");
}

std::map<std::string, std::string> SimAnMinimizer::statusMap() const
{
    auto result = RootMinimizerAdapter::statusMap();
    result["functionCalls"] = std::to_string(rootMinimizer()->NCalls());
    return result;
}

void SimAnMinimizer::propagateOptions()
{
    ROOT::Math::GSLSimAnParams& pars = m_siman_minimizer->getSolver().Params();
    pars.n_tries = maxIterations();
    pars.iters_fixed_T = iterationsAtEachTemp();
    pars.step_size = stepSize();
    pars.k = boltzmannK();
    pars.t_initial = boltzmannInitialTemp();
    pars.mu_t = boltzmannMu();
    pars.t_min = boltzmannMinTemp();
}

const RootMinimizerAdapter::root_minimizer_t* SimAnMinimizer::rootMinimizer() const
{
    return m_siman_minimizer.get();
}
