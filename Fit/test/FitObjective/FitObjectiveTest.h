// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/FitObjective/FitObjectiveTest.h
//! @brief     Defines class FitObjectiveTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITOBJECTIVETEST_H
#define FITOBJECTIVETEST_H

#include "IMinimizerTest.h"

//! Collection of standalone tests for fitting library.

class FitObjectiveTest : public IMinimizerTest
{
public:
    FitObjectiveTest(const std::string& minimizer_name, const std::string& algorithm_name,
                     const std::string& fit_plan_name);

protected:
    std::unique_ptr<MinimizerTestPlan> createPlan() const;
};

#endif // FITOBJECTIVETEST_H
