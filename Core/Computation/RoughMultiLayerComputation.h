// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/RoughMultiLayerComputation.h
//! @brief     Defines class RoughMultiLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ROUGHMULTILAYERCOMPUTATION_H
#define ROUGHMULTILAYERCOMPUTATION_H

#include "Complex.h"
#include "InnerCounter.h"
#include <vector>

class LayerSpecularInfo;
class MultiLayer;
class ProgressHandler;
class SimulationElement;

//! Computes the diffuse reflection from the rough interfaces of a multilayer.
//! Controlled by MainComputation.
//! @ingroup algorithms_internal

class RoughMultiLayerComputation
{
public:
    RoughMultiLayerComputation(const MultiLayer* p_multi_layer);
    ~RoughMultiLayerComputation();

    void eval(
        ProgressHandler* progress, const std::vector<SimulationElement>::iterator& begin_it,
        const std::vector<SimulationElement>::iterator& end_it);

    //! Sets magnetic reflection/transmission info for specific layer
    void setSpecularInfo(size_t i_layer, const LayerSpecularInfo& specular_info);

    // evaluate
    double evaluate(const SimulationElement& sim_element);

private:
    complex_t get_refractive_term(size_t ilayer) const;
    complex_t get_sum8terms(size_t ilayer, const SimulationElement& sim_element);

    const MultiLayer* mp_multi_layer;
    std::vector<LayerSpecularInfo*> mp_specular_info_vector;
};

#endif // ROUGHMULTILAYERCOMPUTATION_H
