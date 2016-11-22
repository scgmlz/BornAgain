// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteStrategies.cpp
//! @brief     Implements class FitSuiteStrategies.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuiteStrategies.h"
#include "FitSuiteImpl.h"
#include <stdexcept>

FitSuiteStrategies::FitSuiteStrategies()
    : m_kernel(nullptr), m_current_strategy_index(0)
{
}

FitSuiteStrategies::~FitSuiteStrategies()
{
    clear();
}

void FitSuiteStrategies::clear()
{
    m_strategies.clear();
    m_current_strategy_index = 0;
}

IFitStrategy *FitSuiteStrategies::currentStrategy()
{
    if(m_current_strategy_index >= m_strategies.size())
        throw std::runtime_error("FitSuiteStrategies::currentStrategy() -> Error in index.");

    return m_strategies[m_current_strategy_index];
}

void FitSuiteStrategies::addStrategy(const IFitStrategy &strategy)
{
    IFitStrategy *clone = strategy.clone();
    clone->init(m_kernel);
    m_strategies.push_back(clone);
}

void FitSuiteStrategies::minimize()
{
    m_current_strategy_index = 0;
    if( m_strategies.empty() ) {
         m_kernel->minimize();
    } else {
        for(auto it=m_strategies.begin(); it!=m_strategies.end(); ++it) {
            //msglog(Logging::INFO) << "FitSuiteStrategies::minimize() -> Running strategy #"
            // << m_current_strategy_index << " '" << (*it)->getName() << "'";
            (*it)->execute();
            ++m_current_strategy_index;
        }
        --m_current_strategy_index;
    }
}
