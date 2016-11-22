// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/StandaloneFitPlan.h
//! @brief     Declares classes to define plans for testing standalone fit.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDALONEFITPLAN_H
#define STANDALONEFITPLAN_H

#include "FitParameterPlan.h"
#include "KernelTypes.h"
#include <string>
#include <memory>
class ObjectiveFunctionPlan;

//! @class StandaloneFitPlan
//! @ingroup standard_samples
//! @brief Represent FitKernel setting for testing arbitrary objective functions.

class StandaloneFitPlan
{
public:
    StandaloneFitPlan(const std::string &minimizerName, const std::string &algorithmName,
                      ObjectiveFunctionPlan *plan);
    ~StandaloneFitPlan();

    std::string minimizerName() const { return m_minimizerName; }
    std::string algorithmName() const { return m_algorithmName; }
    std::string functionPlanName() const;

    objective_function_t objectiveFunction() const;

    const std::vector<FitParameterPlan>& parameterPlan() const;

    bool planSucceeded(const std::vector<double> &foundParValues);

private:
    std::string m_minimizerName;
    std::string m_algorithmName;
    std::unique_ptr<ObjectiveFunctionPlan> m_plan;
};

#endif // STANDALONEFITPLAN_H
