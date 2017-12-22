// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ParticleLayoutComputation.h
//! @brief     Defines class ParticleLayoutComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTCOMPUTATION_H
#define PARTICLELAYOUTCOMPUTATION_H

#include "DelayedProgressCounter.h"
#include "IComputationTerm.h"
#include <memory>

using std::size_t;

class ILayout;
class IInterferenceFunctionStrategy;
class ProgressHandler;

//! Computes the scattering contribution from one particle layout.
//! Used by DWBAComputation.
//! @ingroup algorithms_internal

class ParticleLayoutComputation final : public IComputationTerm
{
public:
    ParticleLayoutComputation(
        const MultiLayer* p_multilayer, const IFresnelMap* p_fresnel_map, const ILayout* p_layout,
        size_t layer_index, const SimulationOptions& options, bool polarized, ProgressHandler& progress);

private:
    virtual void evalSingle(SimulationElement& element) const override;
    std::unique_ptr<const IInterferenceFunctionStrategy> mP_strategy;
    double m_surface_density;
    ProgressHandler& m_progress;
    mutable DelayedProgressCounter m_progress_counter;
};

#endif // PARTICLELAYOUTCOMPUTATION_H
