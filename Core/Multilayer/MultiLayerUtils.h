// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayerUtils.h
//! @brief     Defines helper functions for MultiLayer objects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_MULTILAYERUTILS_H
#define BORNAGAIN_CORE_MULTILAYER_MULTILAYERUTILS_H

#include <cstddef>
#include <vector>

class Layer;
class LayerInterface;
class LayerRoughness;
class MultiLayer;
class ZLimits;

namespace MultiLayerUtils
{
//! Returns thickness of layer
double LayerThickness(const MultiLayer& multilayer, size_t i);

//! Returns top interface of layer
const LayerInterface* LayerTopInterface(const MultiLayer& multilayer, size_t i);

//! Returns bottom interface of layer
const LayerInterface* LayerBottomInterface(const MultiLayer& multilayer, size_t i);

//! Returns top roughness of layer
const LayerRoughness* LayerTopRoughness(const MultiLayer& multilayer, size_t i);

//! Returns the index of the given layer
size_t IndexOfLayer(const MultiLayer& multilayer, const Layer* p_layer);

//! Returns true if the multilayer contains non-default materials of one type only
bool ContainsCompatibleMaterials(const MultiLayer& multilayer);

//! Calculate z-regions occupied by particles
std::vector<ZLimits> ParticleRegions(const MultiLayer& multilayer, bool use_slicing);

bool hasRoughness(const MultiLayer& sample);
} // namespace MultiLayerUtils

#endif // BORNAGAIN_CORE_MULTILAYER_MULTILAYERUTILS_H
