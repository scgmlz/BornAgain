// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/ObjectiveFunctionPlan.h
//! @brief     Declares classes to define plans for testing objective functions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OBJECTIVEFUNCTIONPLAN_H
#define OBJECTIVEFUNCTIONPLAN_H

#include <memory>
#include "KernelTypes.h"
#include "FitParameterPlan.h"

//! @class ObjectiveFunctionPlan
//! @ingroup standard_samples
//! @brief The ObjectiveFunctionPlan defines objective function to fit and its fit parameters.

class ObjectiveFunctionPlan
{
public:
    ObjectiveFunctionPlan(const std::string &name, objective_function_t func, double expected_minimum,
                          double threshold = 0.01);

    void addParameter(double start_value, double expected_value,
                      const AttLimits &limits, double step);

    objective_function_t objectiveFunction() const { return m_objective_function; }

    const std::vector<FitParameterPlan>& parameterPlan() const { return m_parameters; }

    std::string name() const { return m_name; }
private:
    std::string m_name;
    objective_function_t m_objective_function;
    std::vector<FitParameterPlan> m_parameters;
};

//! @class Rosenbrock1
//! @ingroup standard_samples
//! @brief Setting for standalone fit of rosenbrock function.

class Rosenbrock1 : public ObjectiveFunctionPlan
{
public:
    Rosenbrock1();
};

//! @class Rosenbrock1
//! @ingroup standard_samples
//! @brief Setting for standalone fit of Wood4 function.

class WoodFour : public ObjectiveFunctionPlan
{
public:
    WoodFour();
};

#endif // OBJECTIVEFUNCTIONPLAN_H
