// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerFillLimits.h
//! @brief     Defines class LayerFillLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_LAYERFILLLIMITS_H
#define BORNAGAIN_CORE_MULTILAYER_LAYERFILLLIMITS_H

#include "Core/Scattering/ZLimits.h"
#include <cstddef>
#include <utility>
#include <vector>

//! Helper class for the graded layer approximation. Generates limits for each layer, indicating
//! the region of the layer (along z) that contains particle(s)
//!
//! The constructor takes the bottom layer z-coordinates as parameter. This means that for N
//! layers, only N-1 coordinates need to be passed (the last layer is assumed to be semi-infinite).
//! @ingroup algorithms_internal

class BA_CORE_API_ LayerFillLimits
{
public:
    LayerFillLimits(std::vector<double> layers_bottomz);

    //! Particle limits are given in global coordinates
    void update(ParticleLimits particle_limits, double offset = 0.0);

    //! Returns the filled region limits for each layer (in local layer coordinates)
    std::vector<ZLimits> layerZLimits() const;

private:
    size_t layerIndexTop(double top_z) const;
    size_t layerIndexBottom(double bottom_z) const;
    void updateLayerLimits(size_t i_layer, ZLimits limits);
    std::vector<double> m_layers_bottomz;
    std::vector<ZLimits> m_layer_fill_limits;
};

#endif // BORNAGAIN_CORE_MULTILAYER_LAYERFILLLIMITS_H
