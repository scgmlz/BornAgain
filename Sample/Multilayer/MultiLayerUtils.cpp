//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Multilayer/MultiLayerUtils.cpp
//! @brief     Implements helper functions for MultiLayer objects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Multilayer/MultiLayerUtils.h"
#include "Sample/Material/MaterialUtils.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Slice/LayerInterface.h"

const LayerRoughness* MultiLayerUtils::LayerTopRoughness(const MultiLayer& multilayer, size_t i) {
    if (i == 0)
        return nullptr;
    return multilayer.layerInterface(i - 1)->getRoughness();
}

size_t MultiLayerUtils::IndexOfLayer(const MultiLayer& multilayer, const Layer* p_layer) {
    for (size_t i = 0; i < multilayer.numberOfLayers(); ++i)
        if (p_layer == multilayer.layer(i))
            return i;
    throw std::out_of_range("MultiLayerUtils::IndexOfLayer: layer not found");
}

bool MultiLayerUtils::ContainsCompatibleMaterials(const MultiLayer& multilayer) {
    return MaterialUtils::checkMaterialTypes(multilayer.containedMaterials())
           != MATERIAL_TYPES::InvalidMaterialType;
}

bool MultiLayerUtils::hasRoughness(const MultiLayer& sample) {
    for (size_t i = 0; i < sample.numberOfLayers() - 1; i++)
        if (sample.layerInterface(i)->getRoughness())
            return true;
    return false;
}
