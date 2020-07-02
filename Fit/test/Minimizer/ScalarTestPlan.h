// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/Minimizer/ScalarTestPlan.h
//! @brief     Defines class ScalarTestPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SCALARTESTPLAN_H
#define SCALARTESTPLAN_H

#include "KernelTypes.h"
#include "MinimizerTestPlan.h"

//! Testing logic for Minimizer and scalar-type objective functions.

class ScalarTestPlan : public MinimizerTestPlan
{
public:
    ScalarTestPlan(const std::string& name, scalar_function_t func, double expected_minimum,
                   double tolerance = 0.01);

    bool checkMinimizer(Fit::Minimizer& minimizer);

private:
    fcn_scalar_t scalarFunction() const;
    bool minimumAsExpected(double found_minimum, double tolerance = 0.01) const;

    scalar_function_t m_objective_function; //!< objective function to minimize
    double m_expected_minimum;              //!< expected function minimum
    //!< Tolerance on found minimum of objective function wrt expected.
    double m_tolerance_on_minimum;
};

#endif // SCALARTESTPLAN_H
