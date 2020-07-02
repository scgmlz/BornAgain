// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/GeneticMinimizer.cpp
//! @brief     Implements class GeneticMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GeneticMinimizer.h"
#include "Math/GeneticMinimizer.h"
#include "MinimizerConstants.h"
#include "Parameter.h"

namespace
{

std::map<int, std::string> statusDescription()
{
    std::map<int, std::string> result;
    result[0] = std::string("OK, minimum found");
    result[1] = std::string("Maximum number of iterations reached");
    return result;
}
} // namespace

GeneticMinimizer::GeneticMinimizer()
    : RootMinimizerAdapter(MinimizerInfo::buildGeneticInfo()),
      m_genetic_minimizer(new ROOT::Math::GeneticMinimizer())
{
    addOption(OptionNames::Tolerance, 0.01, "Tolerance on the function value at the minimum");
    addOption(OptionNames::PrintLevel, 0, "Minimizer internal print level");
    addOption(OptionNames::MaxIterations, 3, "Maximum number of iterations");
    addOption(OptionNames::PopulationSize, 300, "Population size");
    addOption(OptionNames::RandomSeed, 0, "Random seed");

    // Seems it is not used inside Root, no need to expose
    // addOption("Cycles", 3, "Number of cycles");

    // It's hard to understand (without going to much into genetics details), what parameters below
    // are doing. So better to not to expose and rely on their internal ROOT's default values.

    // addOption("sc_steps", 10, "Spread control steps");
    // addOption("sc_rate", 5, "Spread control rate");
    // addOption("sc_factor", 0.95, "Spread control factor");
}

GeneticMinimizer::~GeneticMinimizer() = default;

void GeneticMinimizer::setTolerance(double value)
{
    setOptionValue(OptionNames::Tolerance, value);
}

double GeneticMinimizer::tolerance() const
{
    return optionValue<double>(OptionNames::Tolerance);
}

void GeneticMinimizer::setPrintLevel(int value)
{
    setOptionValue(OptionNames::PrintLevel, value);
}

int GeneticMinimizer::printLevel() const
{
    return optionValue<int>(OptionNames::PrintLevel);
}

void GeneticMinimizer::setMaxIterations(int value)
{
    setOptionValue(OptionNames::MaxIterations, value);
}

int GeneticMinimizer::maxIterations() const
{
    return optionValue<int>(OptionNames::MaxIterations);
}

void GeneticMinimizer::setPopulationSize(int value)
{
    setOptionValue(OptionNames::PopulationSize, value);
}

int GeneticMinimizer::populationSize() const
{
    return optionValue<int>(OptionNames::PopulationSize);
}

void GeneticMinimizer::setRandomSeed(int value)
{
    setOptionValue(OptionNames::RandomSeed, value);
}

int GeneticMinimizer::randomSeed() const
{
    return optionValue<int>(OptionNames::RandomSeed);
}

void GeneticMinimizer::setParameter(unsigned int index, const Fit::Parameter& par)
{
    if (!par.limits().isFixed() && !par.limits().isLimited()) {
        std::ostringstream ostr;
        ostr << "GeneticMinimizer::setParameter() -> Error! "
             << "Genetic minimizer requires either fixed or "
             << "limited AttLimits::limited(left,right) parameter. "
             << " Parameter name '" << par.name() << "', limits:" << par.limits().toString();
        throw std::runtime_error(ostr.str());
    }
    RootMinimizerAdapter::setParameter(index, par);
}

std::string GeneticMinimizer::statusToString() const
{
    return statusDescription()[rootMinimizer()->Status()];
}

std::map<std::string, std::string> GeneticMinimizer::statusMap() const
{
    auto result = RootMinimizerAdapter::statusMap();
    result["functionCalls"] = std::to_string(rootMinimizer()->NCalls());
    return result;
}

void GeneticMinimizer::propagateOptions()
{
    ROOT::Math::GeneticMinimizerParameters pars;
    pars.fPopSize = populationSize();
    pars.fNsteps = maxIterations();
    //    pars.fCycles = m_options.getIntValue("Cycles"); // seems it's not used inside ROOT
    //    pars.fSC_steps = m_options.getIntValue("SC_steps"); // no idea what it is doing
    //    pars.fSC_rate = m_options.getIntValue("SC_rate"); // no idea what it is doing
    //    pars.fSC_factor = m_options.getRealValue("SC_factor"); // no idea what it is doing
    const double scale_as_in_root = 10.0;
    pars.fConvCrit = scale_as_in_root * tolerance();
    pars.fSeed = randomSeed();
    m_genetic_minimizer->SetParameters(pars);
}

const RootMinimizerAdapter::root_minimizer_t* GeneticMinimizer::rootMinimizer() const
{
    return m_genetic_minimizer.get();
}
