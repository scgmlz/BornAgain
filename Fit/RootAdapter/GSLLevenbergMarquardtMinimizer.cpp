// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/GSLLevenbergMarquardtMinimizer.cpp
//! @brief     Implements class GSLLevenbergMarquardtMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/RootAdapter/GSLLevenbergMarquardtMinimizer.h"
#include "Fit/RootAdapter/GSLMultiMinimizer.h"
#include "Fit/Tools/AttLimits.h"
#include "Fit/Tools/MinimizerUtils.h"
#include "Fit/Tools/StringUtils.h"
#include <stdexcept>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4267)
#include "Math/GSLNLSMinimizer.h"
#pragma warning(pop)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/GSLNLSMinimizer.h"
#pragma GCC diagnostic pop
#endif

namespace
{

std::map<int, std::string> covmatrixStatusDescription()
{
    std::map<int, std::string> result;
    result[0] = "Covariance matrix was not computed";
    result[1] = "Covariance matrix approximate because minimum is not valid";
    result[3] = "Covariance matrix OK";
    return result;
}

} // namespace

GSLLevenbergMarquardtMinimizer::GSLLevenbergMarquardtMinimizer()
    : RootMinimizerAdapter(MinimizerInfo::buildGSLLMAInfo()),
      m_gsl_minimizer(new ROOT::Math::GSLNLSMinimizer(2))
{
    addOption("Tolerance", 0.01, "Tolerance on the function value at the minimum");
    addOption("PrintLevel", 0, "Minimizer internal print level");
    addOption("MaxIterations", 0, "Maximum number of iterations");
}

GSLLevenbergMarquardtMinimizer::~GSLLevenbergMarquardtMinimizer() = default;

void GSLLevenbergMarquardtMinimizer::setTolerance(double value)
{
    setOptionValue("Tolerance", value);
}

double GSLLevenbergMarquardtMinimizer::tolerance() const
{
    return optionValue<double>("Tolerance");
}

void GSLLevenbergMarquardtMinimizer::setPrintLevel(int value)
{
    setOptionValue("PrintLevel", value);
}

int GSLLevenbergMarquardtMinimizer::printLevel() const
{
    return optionValue<int>("PrintLevel");
}

void GSLLevenbergMarquardtMinimizer::setMaxIterations(int value)
{
    setOptionValue("MaxIterations", value);
}

int GSLLevenbergMarquardtMinimizer::maxIterations() const
{
    return optionValue<int>("MaxIterations");
}

std::string GSLLevenbergMarquardtMinimizer::statusToString() const
{
    return MinimizerUtils::gslErrorDescription(rootMinimizer()->Status());
}

std::map<std::string, std::string> GSLLevenbergMarquardtMinimizer::statusMap() const
{
    auto result = RootMinimizerAdapter::statusMap();
    result["Edm"] = StringUtils::scientific(rootMinimizer()->Edm());
    result["CovMatrixStatus"] = covmatrixStatusDescription()[rootMinimizer()->CovMatrixStatus()];
    result["functionCalls"] = std::to_string(rootMinimizer()->NCalls());
    return result;
}

void GSLLevenbergMarquardtMinimizer::propagateOptions()
{
    m_gsl_minimizer->SetTolerance(tolerance());
    m_gsl_minimizer->SetPrintLevel(printLevel());
    m_gsl_minimizer->SetMaxIterations(static_cast<unsigned int>(maxIterations()));
}

const RootMinimizerAdapter::root_minimizer_t* GSLLevenbergMarquardtMinimizer::rootMinimizer() const
{
    return m_gsl_minimizer.get();
}

void GSLLevenbergMarquardtMinimizer::setParameter(unsigned int index, const Fit::Parameter& par)
{
    auto limits = par.limits();
    if (!limits.isLimitless() && !limits.isFixed())
        throw std::runtime_error("GSLLMA minimizer can't handle limited parameters."
                                 "Please make them free");
    RootMinimizerAdapter::setParameter(index, par);
}
