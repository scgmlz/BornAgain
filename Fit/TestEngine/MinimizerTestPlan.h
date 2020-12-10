//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/TestEngine/MinimizerTestPlan.h
//! @brief     Defines class MinimizerTestPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_FIT_TESTENGINE_MINIMIZERTESTPLAN_H
#define BORNAGAIN_FIT_TESTENGINE_MINIMIZERTESTPLAN_H

#include "Fit/Param/ParameterPlan.h"
#include <vector>

namespace mumufit {
class Parameter;
class Parameters;
class Minimizer;
} // namespace mumufit

//! Defines objective function to fit, expected minimum, initial fit parameters and
//! expected values of fit parameters at minimum.

class MinimizerTestPlan {
public:
    MinimizerTestPlan(const std::string& name);

    virtual ~MinimizerTestPlan();

    void addParameter(const mumufit::Parameter& param, double expected_value,
                      double tolerance = 0.01);

    std::string name() const { return m_name; }

    //! Runs minimization and check minimization result.
    virtual bool checkMinimizer(mumufit::Minimizer& minimizer) = 0;

protected:
    mumufit::Parameters parameters() const;
    std::vector<double> expectedValues() const;
    bool valuesAsExpected(const std::vector<double>& values) const;

    std::string m_name;                          //!< plan name
    std::vector<ParameterPlan> m_parameter_plan; //! initial/expected parameter values
};

#endif // BORNAGAIN_FIT_TESTENGINE_MINIMIZERTESTPLAN_H
#endif // USER_API
