// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/Minimizer/ResidualTestPlan.h
//! @brief     Defines class ResidualTestPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef RESIDUALTESTPLAN_H
#define RESIDUALTESTPLAN_H

#include "KernelTypes.h"
#include "MinimizerTestPlan.h"

class ResidualTestPlan : public MinimizerTestPlan
{
public:
    using test_funct_t = std::function<double(double, const std::vector<double>&)>;

    ResidualTestPlan(const std::string& name, test_funct_t func);
    ~ResidualTestPlan();

    fcn_residual_t residualFunction();

    bool checkMinimizer(Fit::Minimizer& minimizer);

private:
    void init_data_values();

    std::vector<double> evaluate(const std::vector<double>& pars);
    std::vector<double> m_xvalues;
    std::vector<double> m_data_values;
    test_funct_t m_test_func;
};

#endif // RESIDUALTESTPLAN_H
