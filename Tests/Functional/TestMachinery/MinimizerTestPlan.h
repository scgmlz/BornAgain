// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/MinimizerTestPlan.h
//! @brief     Defines class MinimizerTestPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MINIMIZERTESTPLAN_H
#define MINIMIZERTESTPLAN_H

#include "WinDllMacros.h"
#include "ParameterPlan.h"
#include <vector>

namespace Fit { class Parameter; class Parameters; class Minimizer; }

//! Defines objective function to fit, expected minimum, initial fit parameters and
//! expected values of fit parameters at minimum.

class BA_CORE_API_ MinimizerTestPlan
{
public:
    MinimizerTestPlan(const std::string& name);

    virtual ~MinimizerTestPlan();

    void addParameter(const Fit::Parameter& param, double expected_value, double tolerance = 0.01);

    std::string name() const { return m_name; }

    //! Runs minimization and check minimization result.
    virtual bool checkMinimizer(Fit::Minimizer& minimizer) = 0;

protected:
    Fit::Parameters parameters() const;
    std::vector<double> expectedValues() const;
    bool valuesAsExpected(const std::vector<double>& values) const;

    std::string m_name;                          //!< plan name
    std::vector<ParameterPlan> m_parameter_plan; //! initial/expected parameter values
};

#endif // MINIMIZERTESTPLAN_H
