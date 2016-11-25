// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IInterferenceFunctionStrategy.h
//! @brief     Defines classes IInterferenceFunctionStrategy,
//!              IInterferenceFunctionStrategy1, IInterferenceFunctionStrategy2
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

//! Pure virtual base class of all interference function strategy classes.
//! Provides an 'evaluate' function that computes the total scattering intensity
//! from a decorated layer, taking into account a specific inter-particle interference function.
//! This function uses low-level functions precomputeParticleFormfactors, evaluateForList
//! that are implemented differently in different inheriting classes.
//! Multiple inheritance is used to support scalar and polarized scattering
//! (through IInterferenceFunctionStrategy1, IInterferenceFunctionStrategy2)
//! and to implement different approximation schemes
//! (DecouplingApproximationStrategy1, SSCApproximationStrategy1, and their polarized
//! counterparts).
//!
//! Instantiation of child classes takes place in LayerStrategyBuilder::createStrategy,
//! which is called from DecoratedLayerComputation::eval.
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ IInterferenceFunctionStrategy
{
public:
    IInterferenceFunctionStrategy();
    IInterferenceFunctionStrategy(const SimulationOptions& sim_params);
    virtual ~IInterferenceFunctionStrategy();

    void init(
        const SafePointerVector<FormFactorWrapper>& weighted_formfactors,
        const IInterferenceFunction& iff, const LayerSpecularInfo& specular_info);

    //! Calculates the intensity for scalar particles/interactions
    double evaluate(const SimulationElement& sim_element) const;

protected:
    virtual void strategy_specific_post_init() {}
    virtual void precomputeParticleFormfactors(const SimulationElement& sim_element) const = 0;

    //! Evaluates the intensity for given list of evaluated form factors
    virtual double evaluateForList(const SimulationElement& sim_element) const = 0;

    double m_total_abundance; //!< cached sum of particle abundances, computed by init()
    SafePointerVector<FormFactorWrapper> m_formfactor_wrappers;
    std::unique_ptr<IInterferenceFunction> mP_iff;
    SimulationOptions m_options;
    std::unique_ptr<LayerSpecularInfo> mP_specular_info; //!< R and T coefficients for DWBA

private:
    double MCIntegratedEvaluate(const SimulationElement& sim_element) const;
    double evaluate_for_fixed_angles(double* fractions, size_t dim, void* params) const;

#ifndef SWIG
    std::unique_ptr<IntegratorMCMiser<IInterferenceFunctionStrategy>> mP_integrator;
#endif
};

//! Pure virtual base class of all scalar interference function strategy classes.
//! Provides the precomputation of particle form factors.

class BA_CORE_API_ IInterferenceFunctionStrategy1 : public virtual IInterferenceFunctionStrategy
{
protected:
    mutable std::vector<complex_t> m_precomputed_ff1; //!< cached form factor evaluations

private:
    void precomputeParticleFormfactors(const SimulationElement& sim_element) const final;
};

//! Pure virtual base class of all polarized interference function strategy classes.
//! Provides the precomputation of particle form factors.

class BA_CORE_API_ IInterferenceFunctionStrategy2 : public virtual IInterferenceFunctionStrategy
{
public:
    typedef std::vector<Eigen::Matrix2cd, Eigen::aligned_allocator<Eigen::Matrix2cd>>
        matrixFFVector_t;

protected:
    mutable matrixFFVector_t m_precomputed_ff2; //!< cached polarized form factors

private:
    void precomputeParticleFormfactors(const SimulationElement& sim_element) const final;
};

#endif // IINTERFERENCEFUNCTIONSTRATEGY_H
