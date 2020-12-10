//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Interference/IInterferenceFunctionStrategy.h
//! @brief     Defines interface IInterferenceFunctionStrategy.
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
#ifndef BORNAGAIN_SAMPLE_INTERFERENCE_IINTERFERENCEFUNCTIONSTRATEGY_H
#define BORNAGAIN_SAMPLE_INTERFERENCE_IINTERFERENCEFUNCTIONSTRATEGY_H

#include "Base/Types/Complex.h"
#include "Sample/RT/SimulationOptions.h"
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

class IInterferenceFunctionStrategy {
public:
    IInterferenceFunctionStrategy(const std::vector<FormFactorCoherentSum>& weighted_formfactors,
                                  const SimulationOptions& sim_params, bool polarized);
    virtual ~IInterferenceFunctionStrategy();

    //! Calculates the intensity for scalar particles/interactions
    double evaluate(const SimulationElement& sim_element) const;

protected:
    std::vector<FormFactorCoherentSum> m_weighted_formfactors;
    const SimulationOptions m_options;

private:
    double evaluateSinglePoint(const SimulationElement& sim_element) const;
    double MCIntegratedEvaluate(const SimulationElement& sim_element) const;
    double evaluate_for_fixed_angles(double* fractions, size_t dim, void* params) const;
    //! Evaluates the intensity in the scalar case
    virtual double scalarCalculation(const SimulationElement& sim_element) const = 0;
    //! Evaluates the intensity in the polarized case
    virtual double polarizedCalculation(const SimulationElement& sim_element) const = 0;

    bool m_polarized;

#ifndef SWIG
    std::unique_ptr<IntegratorMCMiser<IInterferenceFunctionStrategy>> m_integrator;
#endif
};

#endif // BORNAGAIN_SAMPLE_INTERFERENCE_IINTERFERENCEFUNCTIONSTRATEGY_H
#endif // USER_API
