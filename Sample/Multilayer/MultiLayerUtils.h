//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Multilayer/MultiLayerUtils.h
//! @brief     Defines helper functions for MultiLayer objects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_MULTILAYER_MULTILAYERUTILS_H
#define BORNAGAIN_SAMPLE_MULTILAYER_MULTILAYERUTILS_H

#include <cstddef>
#include <vector>

class Layer;
class LayerInterface;
class LayerRoughness;
class MultiLayer;

namespace MultiLayerUtils {

//! Returns top roughness of layer
const LayerRoughness* LayerTopRoughness(const MultiLayer& multilayer, size_t i);

//! Returns the index of the given layer
size_t IndexOfLayer(const MultiLayer& multilayer, const Layer* p_layer);

//! Returns true if the multilayer contains non-default materials of one type only
bool ContainsCompatibleMaterials(const MultiLayer& multilayer);

bool hasRoughness(const MultiLayer& sample);
} // namespace MultiLayerUtils

#endif // BORNAGAIN_SAMPLE_MULTILAYER_MULTILAYERUTILS_H
#endif // USER_API
