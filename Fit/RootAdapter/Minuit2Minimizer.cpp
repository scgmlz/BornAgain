// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/Minuit2Minimizer.cpp
//! @brief     Declares class Minuit2Minimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Minuit2Minimizer.h"
#include "Minuit2/Minuit2Minimizer.h"
#include "StringUtils.h"

namespace {

    std::map<int, std::string> statusDescription()
    {
        std::map<int, std::string> result;
        result[0] = "OK, valid minimum";
        result[1] = "Didn't converge, covariance was made pos defined";
        result[2] = "Didn't converge, Hessian is invalid";
        result[3] = "Didn't converge, Edm is above max";
        result[4] = "Didn't converge, reached call limit";
        result[5] = "Didn't converge, unknown failure";
        return result;
    }

    std::map<int, std::string> covmatrixStatusDescription()
    {
        std::map<int, std::string> result;
        result[-1] = "Not available (inversion failed or Hessian failed)";
        result[ 0] = "Available but not positive defined";
        result[ 1] = "Covariance only approximate";
        result[ 2] = "Full matrix but forced pos def";
        result[ 3] = "Full accurate";
        return result;
    }

} // namespace

Minuit2Minimizer::Minuit2Minimizer(const std::string &algorithmName)
    : RootMinimizerAdapter(MinimizerInfo::buildMinuit2Info(algorithmName))
    , m_minuit2_minimizer(new BA_ROOT::Minuit2::Minuit2Minimizer(algorithmName.c_str()))
{
    addOption(OptionNames::Strategy, 1,
              "Minimization strategy (0-low, 1-medium, 2-high quality)");
    addOption(OptionNames::ErrorDef, 1.0,
              "Error definition factor for parameter error calculation");
    addOption(OptionNames::Tolerance, 0.01,
              "Tolerance on the function value at the minimum");
    addOption(OptionNames::Precision, -1.0,
              "Relative floating point arithmetic precision");
    addOption(OptionNames::PrintLevel, 0,
              "Minimizer internal print level");
    addOption(OptionNames::MaxFunctionCalls, 0,
              "Maximum number of function calls");
}

Minuit2Minimizer::~Minuit2Minimizer()
{

}

void Minuit2Minimizer::setStrategy(int value)
{
    setOptionValue(OptionNames::Strategy, value);
}

int Minuit2Minimizer::strategy() const
{
    return optionValue<int>(OptionNames::Strategy);
}

void Minuit2Minimizer::setErrorDefinition(double value)
{
    setOptionValue(OptionNames::ErrorDef, value);
}

double Minuit2Minimizer::errorDefinition() const
{
    return optionValue<double>(OptionNames::ErrorDef);
}

void Minuit2Minimizer::setTolerance(double value)
{
    setOptionValue(OptionNames::Tolerance, value);
}

double Minuit2Minimizer::tolerance() const
{
    return optionValue<double>(OptionNames::Tolerance);
}

void Minuit2Minimizer::setPrecision(double value)
{
    setOptionValue(OptionNames::Precision, value);
}

double Minuit2Minimizer::precision() const
{
    return optionValue<double>(OptionNames::Precision);
}

void Minuit2Minimizer::setPrintLevel(int value)
{
    setOptionValue(OptionNames::PrintLevel, value);
}

int Minuit2Minimizer::printLevel() const
{
    return optionValue<int>(OptionNames::PrintLevel);
}

void Minuit2Minimizer::setMaxFunctionCalls(int value)
{
    setOptionValue(OptionNames::MaxFunctionCalls, value);
}

int Minuit2Minimizer::maxFunctionCalls() const
{
    return optionValue<int>(OptionNames::MaxFunctionCalls);
}

std::string Minuit2Minimizer::statusToString() const
{
    return statusDescription()[rootMinimizer()->Status()];
}

std::map<std::string, std::string> Minuit2Minimizer::statusMap() const
{
    auto result = RootMinimizerAdapter::statusMap();
    result["Edm"] = StringUtils::scientific(rootMinimizer()->Edm());
    result["CovMatrixStatus"] = covmatrixStatusDescription()[rootMinimizer()->CovMatrixStatus()];
    result["functionCalls"] = std::to_string(rootMinimizer()->NCalls());
    return result;
}

// Fumili algorithm can work only with gradient based objective function, while others can
// work with both, gradient based and chi2 based functions. Historically however, we use
// simplified approach: if not Fumili, then chi2 only. Think of refactoring TODO.
bool Minuit2Minimizer::isGradientBasedAgorithm()
{
    if(algorithmName() == AlgorithmNames::Fumili)
        return true;

    return false;
}

//! Propagate options down to ROOT's Minuit2Minimizer.

void Minuit2Minimizer::propagateOptions()
{
    m_minuit2_minimizer->SetStrategy(strategy());
    m_minuit2_minimizer->SetErrorDef(errorDefinition());
    m_minuit2_minimizer->SetTolerance(tolerance());
    m_minuit2_minimizer->SetPrecision(precision());
    m_minuit2_minimizer->SetPrintLevel(printLevel());
    m_minuit2_minimizer->SetMaxFunctionCalls(maxFunctionCalls());
}

const RootMinimizerAdapter::root_minimizer_t *Minuit2Minimizer::rootMinimizer() const
{
    return m_minuit2_minimizer.get();
}
