// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IInterferenceFunctionStrategy.h
//! @brief     Defines class IInterferenceFunctionStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IINTERFERENCEFUNCTIONSTRATEGY_H
#define IINTERFERENCEFUNCTIONSTRATEGY_H

#include "Complex.h"
#include "SafePointerVector.h"
#include "SimulationOptions.h"
#include "Vectors3D.h"
#include <Eigen/StdVector>
#include <memory>
#include <vector>

template <class T> class IntegratorMCMiser;
class Bin1DCVector;
class FormFactorWrapper;
class IInterferenceFunction;
class LayerSpecularInfo;
class SimulationElement;

//! Virtual base class of the interference function strategy classes
//! DecouplingApproximationStrategy, SSCApproximationStrategy.
//! These classes provide 'evaluate' functions that compute the scattering intensity
//! from a decorated layer, taking into account a specific inter-particle interference function.
//!
//! Child classes are instantiated in LayerStrategyBuilder::createStrategy,
//! which is called from DecoratedLayerComputation::eval.
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ IInterferenceFunctionStrategy
{
public:
    IInterferenceFunctionStrategy(const SimulationOptions& sim_params);
    virtual ~IInterferenceFunctionStrategy();

    void init(const SafePointerVector<FormFactorWrapper>& weighted_formfactors,
              const IInterferenceFunction& iff, const LayerSpecularInfo& specular_info);

    //! Calculates the intensity for scalar particles/interactions
    virtual double evaluate(const SimulationElement& sim_element) const =0;

protected:
    virtual void strategy_specific_post_init() {}
    virtual void precomputeParticleFormfactors(const SimulationElement& sim_element) const =0;

    //! Evaluates the intensity for given list of evaluated form factors
    virtual double evaluateForList(const SimulationElement& sim_element) const =0;

    double m_total_abundance; //!< cached sum of particle abundances, computed by init()
    SafePointerVector<FormFactorWrapper> m_formfactor_wrappers;
    std::unique_ptr<IInterferenceFunction> mP_iff;
    SimulationOptions m_options;
    std::unique_ptr<LayerSpecularInfo> mP_specular_info; //!< R and T coefficients for DWBA

private:

    //! Perform a Monte Carlo integration over the bin for the evaluation of the intensity
    virtual double MCIntegratedEvaluate(const SimulationElement& sim_element) const =0;

    virtual double evaluate_for_fixed_angles(double* fractions, size_t dim, void* params) const =0;

#ifndef SWIG
    std::unique_ptr<IntegratorMCMiser<IInterferenceFunctionStrategy>> mP_integrator;
#endif
};

//!

class BA_CORE_API_ IInterferenceFunctionStrategy1 : public IInterferenceFunctionStrategy
{
public:
    IInterferenceFunctionStrategy1(const SimulationOptions& sim_params)
        : IInterferenceFunctionStrategy(sim_params) {}

protected:
    mutable std::vector<complex_t> m_ff; //!< cached form factor evaluations

private:
    void precomputeParticleFormfactors(const SimulationElement& sim_element) const final;
};

//!

class BA_CORE_API_ IInterferenceFunctionStrategy2 : public IInterferenceFunctionStrategy
{
public:
    typedef std::vector<Eigen::Matrix2cd, Eigen::aligned_allocator<Eigen::Matrix2cd>>
        matrixFFVector_t;

    IInterferenceFunctionStrategy2(const SimulationOptions& sim_params)
        : IInterferenceFunctionStrategy(sim_params) {}

    void init(const SafePointerVector<FormFactorWrapper>& weighted_formfactors,
              const IInterferenceFunction& iff, const LayerSpecularInfo& specular_info);

protected:
    mutable matrixFFVector_t m_ff_pol; //!< cached polarized form factors

private:
    void precomputeParticleFormfactors(const SimulationElement& sim_element) const final;
};

#endif // IINTERFERENCEFUNCTIONSTRATEGY_H
