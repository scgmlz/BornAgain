// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerInfo.cpp
//! @brief     Implements class MinimizerInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerInfo.h"
#include "MinimizerConstants.h"
#include <sstream>
#include <stdexcept>

MinimizerInfo::MinimizerInfo(const std::string& minimizerType,
                             const std::string& minimizerDescription)
    : InfoItem(minimizerType, minimizerDescription)
{
}

void MinimizerInfo::setAlgorithmName(const std::string& algorithmName)
{
    for (const AlgorithmInfo algo : m_algorithms) {
        if(algo.name() == algorithmName) {
            m_current_algorithm = algorithmName;
            return;
        }
    }

    std::ostringstream msg;
    msg << "MinimizerInfo::setAlgorithmName() -> Error. Algorithm name '" << algorithmName
        <<"' is not in the list of defined algorithms (";
    for (const AlgorithmInfo algo : m_algorithms)
        msg << algo.name() << " ";
    msg << ")";
    throw std::runtime_error(msg.str());
}

std::string MinimizerInfo::algorithmName() const
{
    return m_current_algorithm;
}

//! Return list of defined algorithm names.

std::vector<std::string> MinimizerInfo::algorithmNames() const
{
    std::vector<std::string> result;
    for (const AlgorithmInfo algo : m_algorithms)
        result.push_back(algo.name());
    return result;
}

//! Returns list of string with description of all available algorithms.

std::vector<std::string> MinimizerInfo::algorithmDescriptions() const
{
    std::vector<std::string> result;
    for (const AlgorithmInfo algo : m_algorithms)
        result.push_back(algo.description());
    return result;
}

//! Creates information for Minuit2Minimizer.

MinimizerInfo MinimizerInfo::buildMinuit2Info(const std::string& defaultAlgo)
{
    MinimizerInfo result(MinimizerNames::Minuit2, "Minuit2 minimizer from ROOT library");

    result.addAlgorithm(
        AlgorithmNames::Migrad,
        "Variable-metric method with inexact line search, best minimizer according to ROOT.");

    result.addAlgorithm(AlgorithmNames::Simplex, "Simplex method of Nelder and Meadh, robust "
                                                 "against big fluctuations in objective function.");

    result.addAlgorithm(AlgorithmNames::Combined,
                        "Combination of Migrad and Simplex (if Migrad fails).");

    result.addAlgorithm(AlgorithmNames::Scan,
                        "Simple objective function scan, one parameter at a time.");

    result.addAlgorithm(AlgorithmNames::Fumili, "Gradient descent minimizer similar to "
                                                "Levenberg-Margquardt, sometimes can be better "
                                                "than all others.");

    if (defaultAlgo.empty())
        result.setAlgorithmName(AlgorithmNames::Migrad);
    else
        result.setAlgorithmName(defaultAlgo);

    return result;
}

//! Creates information for GSLMultiMinMinimizer.

MinimizerInfo MinimizerInfo::buildGSLMultiMinInfo(const std::string& defaultAlgo)
{
    MinimizerInfo result(MinimizerNames::GSLMultiMin, "MultiMin minimizer from GSL library");

    result.addAlgorithm(AlgorithmNames::SteepestDescent, "Steepest descent");
    result.addAlgorithm(AlgorithmNames::ConjugateFR, "Fletcher-Reeves conjugate gradient");
    result.addAlgorithm(AlgorithmNames::ConjugatePR, "Polak-Ribiere conjugate gradient");
    result.addAlgorithm(AlgorithmNames::BFGS, "BFGS conjugate gradient");
    result.addAlgorithm(AlgorithmNames::BFGS2, "BFGS conjugate gradient (Version 2)");

    if(defaultAlgo.empty())
        result.setAlgorithmName(AlgorithmNames::ConjugateFR);
    else
        result.setAlgorithmName(defaultAlgo);

    return result;
}

//! Creates information for GSL's Levenberg-Marquardt.

MinimizerInfo MinimizerInfo::buildGSLLMAInfo()
{
    MinimizerInfo result(MinimizerNames::GSLLMA, "Levenberg-Marquardt from GSL library");
    result.addAlgorithm(AlgorithmNames::Default, "Default algorithm");
    return result;
}

//! Creates information for GSL's simmulated annealing algorithm.

MinimizerInfo MinimizerInfo::buildGSLSimAnInfo()
{
    MinimizerInfo result(MinimizerNames::GSLSimAn,
                         "Simmulated annealing minimizer from GSL library");
    result.addAlgorithm(AlgorithmNames::Default, "Default algorithm");
    return result;
}

//! Creates information for TMVA genetic minimizer

MinimizerInfo MinimizerInfo::buildGeneticInfo()
{
    MinimizerInfo result(MinimizerNames::Genetic, "Genetic minimizer from TMVA library");
    result.addAlgorithm(AlgorithmNames::Default, "Default algorithm");
    return result;
}

//! Creates information for simple test minimizer

MinimizerInfo MinimizerInfo::buildTestMinimizerInfo()
{
    MinimizerInfo result(MinimizerNames::Test, "One-shot minimizer to test whole chain");
    result.addAlgorithm(AlgorithmNames::Default, "Default algorithm");
    return result;
}

//! Adds minimizer algorithm to the list of defined algorithms.

void MinimizerInfo::addAlgorithm(const AlgorithmInfo& algorithm)
{
    m_current_algorithm = algorithm.name();
    m_algorithms.push_back(algorithm);
}

void MinimizerInfo::addAlgorithm(const std::string& algorithmName,
                                 const std::string& algorithmDescription)
{
    addAlgorithm(AlgorithmInfo(algorithmName, algorithmDescription));
}
