// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ParticleLayoutComputation.h
//! @brief     Defines class ParticleLayoutComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTCOMPUTATION_H
#define PARTICLELAYOUTCOMPUTATION_H

#include "IComputationTerm.h"
#include <memory>

using std::size_t;

class ILayout;
class IInterferenceFunctionStrategy;

//! Computes the scattering contribution from one particle layout.
//! Used by DWBAComputation.
//! @ingroup algorithms_internal

class ParticleLayoutComputation final : public IComputationTerm
{
public:
    ParticleLayoutComputation(
        const MultiLayer* p_multilayer, const IFresnelMap* p_fresnel_map, const ILayout* p_layout,
        size_t layer_index, const SimulationOptions& options, bool polarized);

    void eval(ProgressHandler* progress,
              const std::vector<SimulationElement>::iterator& begin_it,
              const std::vector<SimulationElement>::iterator& end_it) const override;

private:
    std::unique_ptr<const IInterferenceFunctionStrategy> mP_strategy;
    double m_surface_density;
};

#endif // PARTICLELAYOUTCOMPUTATION_H
