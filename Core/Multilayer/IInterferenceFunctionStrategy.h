// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IInterferenceFunctionStrategy.h
//! @brief     Defines class IInterferenceFunctionStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_IINTERFERENCEFUNCTIONSTRATEGY_H
#define BORNAGAIN_CORE_MULTILAYER_IINTERFERENCEFUNCTIONSTRATEGY_H

#include "Core/Basics/Complex.h"
#include "Core/Parametrization/SimulationOptions.h"
#include <memory>
#include <vector>

template <class T> class IntegratorMCMiser;
class FormFactorCoherentSum;
class IInterferenceFunction;
class SimulationElement;

//! Base class of all interference function strategy classes.
//! Provides an 'evaluate' function that computes the total scattering intensity
//! from a decorated layer, taking into account a specific inter-particle interference function.
//! This function uses the low-level functions scalarCalculation and polarizedCalculation
//! that are to be overriden in the derived classes.
//! Inheritance is used to support different approximation schemes
//! (DecouplingApproximationStrategy, SSCApproximationStrategy).
//!
//! Instantiation of child classes takes place in LayoutStrategyBuilder::createStrategy,
//! which is called from ParticleLayoutComputation::eval.
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ IInterferenceFunctionStrategy
{
public:
    IInterferenceFunctionStrategy(const SimulationOptions& sim_params, bool polarized);
    virtual ~IInterferenceFunctionStrategy();

    //! Initializes the object with form factors and an interference function
    void init(const std::vector<FormFactorCoherentSum>& weighted_formfactors,
              const IInterferenceFunction* p_iff);

    //! Calculates the intensity for scalar particles/interactions
    double evaluate(const SimulationElement& sim_element) const;

protected:
    std::vector<FormFactorCoherentSum> m_formfactor_wrappers;
    std::unique_ptr<IInterferenceFunction> mP_iff;
    SimulationOptions m_options;

private:
    double evaluateSinglePoint(const SimulationElement& sim_element) const;
    double MCIntegratedEvaluate(const SimulationElement& sim_element) const;
    double evaluate_for_fixed_angles(double* fractions, size_t dim, void* params) const;
    virtual void strategy_specific_post_init();
    //! Evaluates the intensity in the scalar case
    virtual double scalarCalculation(const SimulationElement& sim_element) const = 0;
    //! Evaluates the intensity in the polarized case
    virtual double polarizedCalculation(const SimulationElement& sim_element) const = 0;

    bool m_polarized;

#ifndef SWIG
    std::unique_ptr<IntegratorMCMiser<IInterferenceFunctionStrategy>> mP_integrator;
#endif
};

#endif // BORNAGAIN_CORE_MULTILAYER_IINTERFERENCEFUNCTIONSTRATEGY_H
