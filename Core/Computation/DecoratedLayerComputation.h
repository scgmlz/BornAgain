// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DecoratedLayerComputation.h
//! @brief     Defines class DecoratedLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DECORATEDLAYERCOMPUTATION_H
#define DECORATEDLAYERCOMPUTATION_H

#include "InnerCounter.h"
#include <memory>
#include <vector>

using std::size_t;

class Layer;
class LayerSpecularInfo;
class MultiLayer;
class ProgressHandler;
class SimulationElement;
class SimulationOptions;

//! Computes the scattering contribution from one layer with particles in/on it.
//! Controlled by MainComputation.
//! @ingroup algorithms_internal

class DecoratedLayerComputation
{
public:
    DecoratedLayerComputation(const Layer* p_layer, size_t layout_index = 0);

    void setSpecularInfo(const LayerSpecularInfo& specular_info);

    void eval(
        const SimulationOptions& options, ProgressHandler* progress, bool polarized,
        const std::vector<SimulationElement>::iterator& begin_it,
        const std::vector<SimulationElement>::iterator& end_it) const;

private:
    const Layer* mp_layer;
    std::unique_ptr<LayerSpecularInfo> mP_specular_info;
    size_t m_layout_index;
};

#endif // DECORATEDLAYERCOMPUTATION_H
