// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteStrategies.h
//! @brief     Defines class FitSuiteStrategies.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITESTRATEGIES_H
#define FITSUITESTRATEGIES_H

#include "IFitStrategy.h"
#include "SafePointerVector.h"

//! Collection of strategies to fit.
//! @ingroup fitting_internal

class BA_CORE_API_ FitSuiteStrategies
{
public:
    FitSuiteStrategies();
    virtual ~FitSuiteStrategies();
    FitSuiteStrategies(const FitSuiteStrategies &other) = delete;
    FitSuiteStrategies& operator=(const FitSuiteStrategies &other) = delete;

    void init(FitSuiteImpl* fit_suite) { m_kernel = fit_suite; }

    void addStrategy(const IFitStrategy& strategy);

    void minimize();

    size_t currentStrategyIndex() const { return m_current_strategy_index; }

    size_t size() const { return m_strategies.size(); }

    void clear();

    IFitStrategy* currentStrategy();

private:
    SafePointerVector<IFitStrategy> m_strategies;
    FitSuiteImpl* m_kernel;
    size_t m_current_strategy_index;
};

#endif // FITSUITESTRATEGIES_H
