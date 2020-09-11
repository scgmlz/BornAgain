// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootMinimizerAdapter.cpp
//! @brief     Implements class RootMinimizerAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/RootAdapter/RootMinimizerAdapter.h"
#include "Fit/Kernel/Parameter.h"
#include "Fit/Kernel/Parameters.h"
#include "Fit/RootAdapter/MinimizerResultUtils.h"
#include "Fit/RootAdapter/ObjectiveFunctionAdapter.h"
#include "Fit/RootAdapter/RootResidualFunction.h"
#include "Fit/RootAdapter/RootScalarFunction.h"
#include "Fit/Tools/StringUtils.h"
#include "Math/Minimizer.h"

using namespace Fit;

RootMinimizerAdapter::RootMinimizerAdapter(const MinimizerInfo& minimizerInfo)
    : m_minimizerInfo(minimizerInfo), m_adapter(new Fit::ObjectiveFunctionAdapter), m_status(false)
{
}

RootMinimizerAdapter::~RootMinimizerAdapter() = default;

MinimizerResult RootMinimizerAdapter::minimize_scalar(fcn_scalar_t fcn, Parameters parameters)
{
    // Genetic minimizer requires SetFunction before setParameters, others don't care
    rootMinimizer()->SetFunction(*m_adapter->rootObjectiveFunction(fcn, parameters));
    return minimize(parameters);
}

MinimizerResult RootMinimizerAdapter::minimize_residual(fcn_residual_t fcn, Parameters parameters)
{
    // Genetic minimizer requires SetFunction before setParameters, others don't care
    rootMinimizer()->SetFunction(*m_adapter->rootResidualFunction(fcn, parameters));
    return minimize(parameters);
}

MinimizerResult RootMinimizerAdapter::minimize(Parameters parameters)
{
    setParameters(parameters);
    propagateOptions();

    m_status = rootMinimizer()->Minimize();
    propagateResults(parameters);

    MinimizerResult result;
    result.setParameters(parameters);
    result.setMinValue(minValue());
    result.setReport(MinimizerResultUtils::reportToString(*this));
    result.setNumberOfCalls(m_adapter->numberOfCalls());
    result.setNumberOfGradientCalls(m_adapter->numberOfGradientCalls());

    return result;
}

std::string RootMinimizerAdapter::minimizerName() const
{
    return m_minimizerInfo.name();
}

std::string RootMinimizerAdapter::algorithmName() const
{
    return m_minimizerInfo.algorithmName();
}

void RootMinimizerAdapter::setParameters(const Fit::Parameters& parameters)
{
    unsigned int index(0);
    for (const auto& par : parameters)
        setParameter(index++, par);
}

double RootMinimizerAdapter::minValue() const
{
    return rootMinimizer()->MinValue();
}

std::string RootMinimizerAdapter::statusToString() const
{
    return m_status ? "Minimum found" : "Error in solving";
}

bool RootMinimizerAdapter::providesError() const
{
    return rootMinimizer()->ProvidesError();
}

std::map<std::string, std::string> RootMinimizerAdapter::statusMap() const
{
    std::map<std::string, std::string> result;
    result["Status"] = statusToString();

    if (providesError())
        result["ProvidesError"] = "Provides parameters error and error matrix";
    else
        result["ProvidesError"] = "Doesn't provide error calculation";

    result["MinValue"] = StringUtils::scientific(minValue());

    return result;
}

void RootMinimizerAdapter::setOptions(const std::string& optionString)
{
    options().setOptionString(optionString);
}

//! Propagates results of minimization to fit parameter set

void RootMinimizerAdapter::propagateResults(Fit::Parameters& parameters)
{
    parameters.setValues(parValuesAtMinimum());
    parameters.setErrors(parErrorsAtMinimum());
    // sets correlation matrix
    if (providesError()) {
        Fit::Parameters::corr_matrix_t matrix;
        matrix.resize(fitDimension());

        for (size_t i = 0; i < fitDimension(); ++i) {
            matrix[i].resize(fitDimension(), 0.0);
            for (size_t j = 0; j < fitDimension(); ++j)
                matrix[i][j] = rootMinimizer()->Correlation(static_cast<unsigned int>(i),
                                                            static_cast<unsigned int>(j));
        }
        parameters.setCorrelationMatrix(matrix);
    }
}

void RootMinimizerAdapter::setParameter(unsigned int index, const Fit::Parameter& par)
{
    bool success;
    if (par.limits().isFixed()) {
        success = rootMinimizer()->SetFixedVariable(index, par.name().c_str(), par.value());

    }

    else if (par.limits().isLimited()) {
        success = rootMinimizer()->SetLimitedVariable(index, par.name().c_str(), par.value(),
                                                      par.step(), par.limits().lowerLimit(),
                                                      par.limits().upperLimit());
    }

    else if (par.limits().isLowerLimited()) {
        success = rootMinimizer()->SetLowerLimitedVariable(index, par.name().c_str(), par.value(),
                                                           par.step(), par.limits().lowerLimit());
    }

    else if (par.limits().isUpperLimited()) {
        success = rootMinimizer()->SetUpperLimitedVariable(index, par.name().c_str(), par.value(),
                                                           par.step(), par.limits().upperLimit());
    }

    else if (par.limits().isLimitless()) {
        success = rootMinimizer()->SetVariable(index, par.name().c_str(), par.value(), par.step());
    }

    else {
        throw std::runtime_error("BasicMinimizer::setParameter() -> Error! Unexpected parameter.");
    }

    if (!success) {
        std::ostringstream ostr;
        ostr << "BasicMinimizer::setParameter() -> Error! Can't set minimizer's fit parameter";
        ostr << "Index:" << index << " name '" << par.name() << "'";
        throw std::runtime_error(ostr.str());
    }
}

//! Returns number of fit parameters defined (i.e. dimension of the function to be minimized).

size_t RootMinimizerAdapter::fitDimension() const
{
    return rootMinimizer()->NDim();
}

//! Returns value of the variables at minimum.

std::vector<double> RootMinimizerAdapter::parValuesAtMinimum() const
{
    std::vector<double> result;
    result.resize(fitDimension(), 0.0);
    std::copy(rootMinimizer()->X(), rootMinimizer()->X() + fitDimension(), result.begin());
    return result;
}

//! Returns errors of the variables at minimum.

std::vector<double> RootMinimizerAdapter::parErrorsAtMinimum() const
{
    std::vector<double> result;
    result.resize(fitDimension(), 0.0);
    if (rootMinimizer()->Errors() != 0) {
        std::copy(rootMinimizer()->Errors(), rootMinimizer()->Errors() + fitDimension(),
                  result.begin());
    }
    return result;
}

RootMinimizerAdapter::root_minimizer_t* RootMinimizerAdapter::rootMinimizer()
{
    return const_cast<root_minimizer_t*>(
        static_cast<const RootMinimizerAdapter*>(this)->rootMinimizer());
}
