// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootMinimizerAdapter.cpp
//! @brief     Implements class RootMinimizerAdapter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RootMinimizerAdapter.h"
#include "FitParameter.h"
#include "FitParameterSet.h"
#include "Math/Minimizer.h"
#include "MinimizerResultsHelper.h"
#include "RootMinimizerFunctions.h"
#include "RootObjectiveFuncAdapter.h"
#include "StringUtils.h"


RootMinimizerAdapter::RootMinimizerAdapter(const MinimizerInfo &minimizerInfo)
    :  m_minimizerInfo(minimizerInfo)
    , m_obj_func(new RootObjectiveFunctionAdapter)
    , m_status(false)
{}

RootMinimizerAdapter::~RootMinimizerAdapter() {}

void RootMinimizerAdapter::minimize()
{
    propagateOptions();
    m_status = rootMinimizer()->Minimize();
}

std::string RootMinimizerAdapter::minimizerName() const
{
    return m_minimizerInfo.name();
}

std::string RootMinimizerAdapter::algorithmName() const
{
    return m_minimizerInfo.algorithmName();
}

void RootMinimizerAdapter::setParameters(const FitParameterSet &parameters)
{
    m_obj_func->setNumberOfParameters(parameters.size());

    // Genetic minimizer requires SetFunction before setParameters, others don't care
    if( isGradientBasedAgorithm() ) {
        rootMinimizer()->SetFunction(*m_obj_func->rootGradientFunction());
    } else {
        rootMinimizer()->SetFunction(*m_obj_func->rootChiSquaredFunction());
    }

    size_t index(0);
    for (auto par: parameters)
        setParameter(index++, par );

    if( (int)parameters.size() != fitDimension())  {
        std::ostringstream ostr;
        ostr << "BasicMinimizer::setParameters() -> Error! Unconsistency in fit parameter number: ";
        ostr << "fitParameterCount = " << fitDimension() << ",";
        ostr << "parameters.size = " << parameters.size();
        throw std::runtime_error(ostr.str());
    }
}

void RootMinimizerAdapter::setObjectiveFunction(objective_function_t func)
{
    m_obj_func->setObjectiveCallback(func);
}

void RootMinimizerAdapter::setGradientFunction(gradient_function_t func, int ndatasize)
{
    m_obj_func->setGradientCallback(func, ndatasize);
}

double RootMinimizerAdapter::minValue() const
{
    return rootMinimizer()->MinValue();
}

std::string RootMinimizerAdapter::reportOutcome() const
{
    return MinimizerResultsHelper().reportOutcome(this);
}

std::string RootMinimizerAdapter::statusToString() const
{
    return m_status ? std::string("Minimum found") : std::string("Error in solving");
}

bool RootMinimizerAdapter::providesError() const
{
    return rootMinimizer()->ProvidesError();
}

std::map<std::string, std::string> RootMinimizerAdapter::statusMap() const
{
    std::map<std::string, std::string> result;
    result["Status"] = statusToString();

    if(providesError())
        result["ProvidesError"] = "Provides parameters error and error matrix";
    else
        result["ProvidesError"] = "Doesn't provide error calculation";

    result["MinValue"] = StringUtils::scientific(minValue());

    return result;
}

void RootMinimizerAdapter::propagateResults(FitParameterSet &parameters)
{
    // sets values and errors found
    parameters.setValues(parValuesAtMinimum());
    parameters.setErrors(parErrorsAtMinimum());

    // sets correlation matrix
    if(providesError()) {
        FitParameterSet::corr_matrix_t matrix;
        matrix.resize(fitDimension());

        for(size_t i=0; i<(size_t)fitDimension(); ++i) {
            matrix[i].resize(fitDimension(), 0.0);
            for(size_t j=0; j<(size_t)fitDimension(); ++j)
                matrix[i][j] = rootMinimizer()->Correlation(i,j);
        }
        parameters.setCorrelationMatrix(matrix);
    }
}

void RootMinimizerAdapter::setOptions(const std::string &optionString)
{
    options().setOptionString(optionString);
}

//! Propagate fit parameter down to ROOT minimizer.

void RootMinimizerAdapter::setParameter(size_t index, const FitParameter *par)
{
    bool success;
    if (par->limits().isFixed()) {
        success = rootMinimizer()->SetFixedVariable((int)index, par->name().c_str(),
                                                    par->value());

    }

    else if (par->limits().isLimited()) {
        success = rootMinimizer()->SetLimitedVariable((int)index, par->name().c_str(),
                                                      par->value(), par->step(),
                                                      par->limits().lowerLimit(),
                                                      par->limits().upperLimit());
    }

    else if (par->limits().isLowerLimited()) {
        success = rootMinimizer()->SetLowerLimitedVariable((int)index, par->name().c_str(),
                                                           par->value(), par->step(),
                                                           par->limits().lowerLimit());
    }

    else if (par->limits().isUpperLimited()) {
        success = rootMinimizer()->SetUpperLimitedVariable((int)index, par->name().c_str(),
                                                           par->value(), par->step(),
                                                           par->limits().upperLimit());
    }

    else if (!par->limits().isLimitless()) {
        success = rootMinimizer()->SetVariable((int)index, par->name().c_str(), par->value(),
                                               par->step());
    }

    else {
        throw std::runtime_error("BasicMinimizer::setParameter() -> Error! Unexpected parameter.");
    }

    if( !success ) {
        std::ostringstream ostr;
        ostr << "BasicMinimizer::setParameter() -> Error! Can't set minimizer's fit parameter";
        ostr << "Index:" << index << " name '" << par->name() << "'";
        throw std::runtime_error(ostr.str());
    }
}

//! Returns number of fit parameters defined (i.e. dimension of the function to be minimized).

int RootMinimizerAdapter::fitDimension() const
{
    return rootMinimizer()->NDim();
}

//! Returns value of the variables at minimum.

std::vector<double> RootMinimizerAdapter::parValuesAtMinimum() const
{
    std::vector<double > result;
    result.resize(fitDimension(), 0.0);
    std::copy(rootMinimizer()->X(), rootMinimizer()->X()+fitDimension(), result.begin());
    return result;
}

//! Returns errors of the variables at minimum.

std::vector<double> RootMinimizerAdapter::parErrorsAtMinimum() const
{
    std::vector<double > result;
    result.resize(fitDimension(), 0.0);
    if(rootMinimizer()->Errors() != 0 ) {
        std::copy(rootMinimizer()->Errors(), rootMinimizer()->Errors()+fitDimension(),
                  result.begin());
    }
    return result;
}

RootMinimizerAdapter::root_minimizer_t *RootMinimizerAdapter::rootMinimizer() {
    return const_cast<root_minimizer_t *>(
        static_cast<const RootMinimizerAdapter *>(this)->rootMinimizer());
}
