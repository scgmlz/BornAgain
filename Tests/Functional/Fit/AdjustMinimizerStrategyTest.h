// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/AdjustMinimizerStrategyTest.h
//! @brief     Declares class MinimizerStrategyTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ADJUSTMINIMIZERSTRATEGYTEST_H
#define ADJUSTMINIMIZERSTRATEGYTEST_H

#include "IMinimizerTest.h"

//! @class AdjustMinimizerStrategyTest
//! @ingroup standard_samples
//! @brief The AdjustMinimizerStrategyTest verifies fitting with the chain of minimizers.

class AdjustMinimizerStrategyTest : public IMinimizerTest
{
public:
    AdjustMinimizerStrategyTest();

protected:
    void initParameterPlan() override;
    std::unique_ptr<FitSuite> createFitSuite() override;
};

#endif // ADJUSTMINIMIZERSTRATEGYTEST_H
