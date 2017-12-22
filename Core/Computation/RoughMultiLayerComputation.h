// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/RoughMultiLayerComputation.h
//! @brief     Defines class RoughMultiLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ROUGHMULTILAYERCOMPUTATION_H
#define ROUGHMULTILAYERCOMPUTATION_H

#include "Complex.h"
#include "DelayedProgressCounter.h"
#include "IComputationTerm.h"
#include <vector>

class ProgressHandler;
class SimulationElement;

//! Computes the diffuse reflection from the rough interfaces of a multilayer.
//! Used by DWBAComputation.
//! @ingroup algorithms_internal

class RoughMultiLayerComputation final : public IComputationTerm
{
public:
    RoughMultiLayerComputation(const MultiLayer* p_multi_layer,
                               const IFresnelMap* p_fresnel_map,
                               ProgressHandler& progress);
    ~RoughMultiLayerComputation();

private:
    virtual void evalSingle(SimulationElement& element) const override;
    virtual bool checkComputation() const override;
    complex_t get_refractive_term(size_t ilayer, double wavelength) const;
    complex_t get_sum8terms(size_t ilayer, const SimulationElement& sim_element) const;

    ProgressHandler& m_progress;
    mutable DelayedProgressCounter m_progress_counter;
};

#endif // ROUGHMULTILAYERCOMPUTATION_H
