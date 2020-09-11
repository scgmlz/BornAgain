// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/TestMinimizer.h
//! @brief     Defines class TestMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_MINIMIZER_TESTMINIMIZER_H
#define BORNAGAIN_FIT_MINIMIZER_TESTMINIMIZER_H

#include "Fit/Minimizer/IMinimizer.h"

//! A trivial minimizer that calls the objective function once. Used to test the whole chain.

class BA_CORE_API_ TestMinimizer : public IMinimizer
{
public:
    TestMinimizer();
    ~TestMinimizer() override;

    std::string minimizerName() const final;
    std::string algorithmName() const final { return ""; }

    Fit::MinimizerResult minimize_scalar(fcn_scalar_t fcn, Fit::Parameters parameters) override;

private:
    std::vector<double> m_parameter_values;
    scalar_function_t m_fcn;
};

#endif // BORNAGAIN_FIT_MINIMIZER_TESTMINIMIZER_H
