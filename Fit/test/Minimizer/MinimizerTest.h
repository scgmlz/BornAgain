// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/Minimizer/MinimizerTest.h
//! @brief     Defines class MinimizerTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MINIMIZERTEST_H
#define MINIMIZERTEST_H

#include "IMinimizerTest.h"

//! Collection of standalone tests for fitting library.

class MinimizerTest : public IMinimizerTest
{
public:
    MinimizerTest(const std::string& minimizer_name, const std::string& algorithm_name,
                  const std::string& fit_plan_name);

protected:
    std::unique_ptr<MinimizerTestPlan> createPlan() const;
};

#endif // MINIMIZERTEST_H
