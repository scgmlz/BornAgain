// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IMinimizerTest.h
//! @brief     Defines class MinimizerTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IMINIMIZERTEST_H
#define IMINIMIZERTEST_H

#include "IFunctionalTest.h"
#include <string>
#include <memory>

class MinimizerTestPlan;

//! Base class for minimizer tests.

class BA_CORE_API_ IMinimizerTest : public IFunctionalTest
{
public:
    IMinimizerTest(const std::string& minimizer_name, const std::string& algorithm_name,
                  const std::string& fit_plan_name);

    bool runTest();

    void setMinimizerOptions(const std::string& options);

protected:
    virtual std::unique_ptr<MinimizerTestPlan> createPlan() const = 0;

    std::string m_minimizer_name;
    std::string m_algorithm_name;
    std::string m_option_string;
    std::string m_fit_plan_name;
};

#endif // IMINIMIZERTEST_H
