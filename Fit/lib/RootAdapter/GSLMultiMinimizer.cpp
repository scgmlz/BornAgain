// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/GSLMultiMinimizer.cpp
//! @brief     Implements class GSLMultiMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GSLMultiMinimizer.h"
#include "MinimizerUtils.h"
#include <string>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4267)
#include "Math/GSLMinimizer.h"
#pragma warning(pop)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/GSLMinimizer.h"
#pragma GCC diagnostic pop
#endif

GSLMultiMinimizer::GSLMultiMinimizer(const std::string& algorithmName)
    : RootMinimizerAdapter(MinimizerInfo::buildGSLMultiMinInfo(algorithmName)),
      m_gsl_minimizer(new ROOT::Math::GSLMinimizer(algorithmName.c_str()))
{
    addOption(OptionNames::PrintLevel, 0, "Minimizer internal print level");
    addOption(OptionNames::MaxIterations, 0, "Maximum number of iterations");
}

GSLMultiMinimizer::~GSLMultiMinimizer() = default;

void GSLMultiMinimizer::setPrintLevel(int value)
{
    setOptionValue(OptionNames::PrintLevel, value);
}

int GSLMultiMinimizer::printLevel() const
{
    return optionValue<int>(OptionNames::PrintLevel);
}

void GSLMultiMinimizer::setMaxIterations(int value)
{
    setOptionValue(OptionNames::MaxIterations, value);
}

int GSLMultiMinimizer::maxIterations() const
{
    return optionValue<int>(OptionNames::MaxIterations);
}

std::string GSLMultiMinimizer::statusToString() const
{
    return MinimizerUtils::gslErrorDescription(rootMinimizer()->Status());
}

void GSLMultiMinimizer::propagateOptions()
{
    m_gsl_minimizer->SetPrintLevel(printLevel());
    m_gsl_minimizer->SetMaxIterations(static_cast<unsigned int>(maxIterations()));
}

const RootMinimizerAdapter::root_minimizer_t* GSLMultiMinimizer::rootMinimizer() const
{
    return m_gsl_minimizer.get();
}
