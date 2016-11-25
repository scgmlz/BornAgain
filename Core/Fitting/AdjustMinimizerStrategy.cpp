// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/AdjustMinimizerStrategy.cpp
//! @brief     Implements class AdjustMinimizerStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AdjustMinimizerStrategy.h"
#include "FitSuiteImpl.h"
#include "IMinimizer.h"
#include "MinimizerFactory.h"

AdjustMinimizerStrategy::AdjustMinimizerStrategy() : IFitStrategy("FitStrategy/AdjustMinimizer") {}

AdjustMinimizerStrategy::AdjustMinimizerStrategy(
    const std::string& minimizerName, const std::string& algorithmName,
    const std::string& optionString)
    : IFitStrategy("FitStrategy/AdjustMinimizer")
    , m_minimizerName(minimizerName)
    , m_algorithmName(algorithmName)
    , m_optionString(optionString)
{
    setMinimizer(minimizerName, algorithmName, optionString);
}


AdjustMinimizerStrategy* AdjustMinimizerStrategy::clone() const
{
    AdjustMinimizerStrategy* result = new AdjustMinimizerStrategy(*this);
    return result;
}

void AdjustMinimizerStrategy::setMinimizer(
    const std::string& minimizerName, const std::string& algorithmName,
    const std::string& optionString)
{
    m_minimizerName = minimizerName;
    m_algorithmName = algorithmName;
    m_optionString = optionString;
}

void AdjustMinimizerStrategy::execute()
{
    m_kernel->setMinimizer(
        MinimizerFactory::createMinimizer(m_minimizerName, m_algorithmName, m_optionString));
    m_kernel->minimize();
}

std::string AdjustMinimizerStrategy::toString() const
{
    std::ostringstream ostr;
    ostr << "FitStrategy/AdjustMinimizer (" << m_minimizerName << ", " << m_algorithmName << ", "
         << m_optionString << ")";
    return ostr.str();
}

AdjustMinimizerStrategy::AdjustMinimizerStrategy(const AdjustMinimizerStrategy& other)
    : IFitStrategy(other)
{
    m_minimizerName = other.m_minimizerName;
    m_algorithmName = other.m_algorithmName;
    m_optionString = other.m_optionString;
}
