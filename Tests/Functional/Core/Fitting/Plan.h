//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/Plan.h
//! @brief     Defines class Plan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_PLAN_H
#define BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_PLAN_H

#include "Fit/TestEngine/MinimizerTestPlan.h"
#include <memory>

namespace mumufit {
class Parameters;
}
class ISimulation;
class MultiLayer;
template <class T> class OutputData;
class FitObjective;

//! Contains all logic to construct FitObjective, setup Minimizer and check minimization results.
//! Parent of various *Plan classes in source file PlanCases.

class Plan : public MinimizerTestPlan {
public:
    Plan(const std::string& name, bool residual_based = false);
    ~Plan();

    virtual bool checkMinimizer(mumufit::Minimizer& minimizer);

    void setBuilderName(const std::string& name);
    void setSimulationName(const std::string& name);

protected:
    virtual std::unique_ptr<FitObjective> createFitObjective() const;
    virtual std::unique_ptr<ISimulation> buildSimulation(const mumufit::Parameters& params) const;
    virtual std::unique_ptr<ISimulation> createSimulation(const mumufit::Parameters& params) const;
    virtual std::unique_ptr<MultiLayer> createMultiLayer(const mumufit::Parameters& params) const;
    virtual std::unique_ptr<OutputData<double>> createOutputData() const;

    std::string m_simulation_name;
    std::string m_sample_builder_name;
    bool m_residual_based;
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_PLAN_H
