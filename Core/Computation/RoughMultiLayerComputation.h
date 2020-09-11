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

#ifndef BORNAGAIN_CORE_COMPUTATION_ROUGHMULTILAYERCOMPUTATION_H
#define BORNAGAIN_CORE_COMPUTATION_ROUGHMULTILAYERCOMPUTATION_H

#include "Core/Basics/Complex.h"

class ProcessedSample;
class SimulationElement;

//! Computes the diffuse reflection from the rough interfaces of a multilayer.
//! Used by DWBAComputation.
//! @ingroup algorithms_internal

class RoughMultiLayerComputation final
{
public:
    RoughMultiLayerComputation(const ProcessedSample* p_sample);

    void compute(SimulationElement& elem) const;

private:
    const ProcessedSample* mp_sample;
    complex_t get_refractive_term(size_t ilayer, double wavelength) const;
    complex_t get_sum8terms(size_t ilayer, const SimulationElement& sim_element) const;
};

#endif // BORNAGAIN_CORE_COMPUTATION_ROUGHMULTILAYERCOMPUTATION_H
