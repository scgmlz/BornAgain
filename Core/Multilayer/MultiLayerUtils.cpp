// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayerUtils.cpp
//! @brief     Implements helper functions for MultiLayer objects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/MultiLayerUtils.h"
#include "Core/Correlations/ILayout.h"
#include "Core/Material/MaterialUtils.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerFillLimits.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/IParticle.h"

namespace
{
std::vector<double> BottomLayerCoordinates(const MultiLayer& multilayer);
} // namespace

double MultiLayerUtils::LayerThickness(const MultiLayer& multilayer, size_t i)
{
    return multilayer.layer(i)->thickness();
}

const LayerInterface* MultiLayerUtils::LayerTopInterface(const MultiLayer& multilayer, size_t i)
{
    if (i == 0)
        return nullptr;
    return multilayer.layerInterface(i - 1);
}

const LayerInterface* MultiLayerUtils::LayerBottomInterface(const MultiLayer& multilayer, size_t i)
{
    if (i + 1 < multilayer.numberOfLayers())
        return multilayer.layerInterface(i);
    return nullptr;
}

const LayerRoughness* MultiLayerUtils::LayerTopRoughness(const MultiLayer& multilayer, size_t i)
{
    if (i == 0)
        return nullptr;
    return multilayer.layerInterface(i - 1)->getRoughness();
}

size_t MultiLayerUtils::IndexOfLayer(const MultiLayer& multilayer, const Layer* p_layer)
{
    for (size_t i = 0; i < multilayer.numberOfLayers(); ++i)
        if (p_layer == multilayer.layer(i))
            return i;
    throw std::out_of_range("MultiLayerUtils::IndexOfLayer: layer not found");
}

bool MultiLayerUtils::ContainsCompatibleMaterials(const MultiLayer& multilayer)
{
    return MaterialUtils::checkMaterialTypes(multilayer.containedMaterials())
           != MATERIAL_TYPES::InvalidMaterialType;
}

std::vector<ZLimits> MultiLayerUtils::ParticleRegions(const MultiLayer& multilayer,
                                                      bool use_slicing)
{
    auto bottom_coords = BottomLayerCoordinates(multilayer);
    LayerFillLimits layer_fill_limits(bottom_coords);
    if (use_slicing) {
        for (size_t i = 0; i < multilayer.numberOfLayers(); ++i) {
            auto p_layer = multilayer.layer(i);
            double offset = (i == 0) ? 0 : bottom_coords[i - 1];
            for (auto p_layout : p_layer->layouts()) {
                for (auto p_particle : p_layout->particles())
                    layer_fill_limits.update(p_particle->bottomTopZ(), offset);
            }
        }
    }
    return layer_fill_limits.layerZLimits();
}

bool MultiLayerUtils::hasRoughness(const MultiLayer& sample)
{
    for (size_t i = 0; i < sample.numberOfLayers() - 1; i++) {
        if (sample.layerInterface(i)->getRoughness())
            return true;
    }
    return false;
}

namespace
{
std::vector<double> BottomLayerCoordinates(const MultiLayer& multilayer)
{
    auto n_layers = multilayer.numberOfLayers();
    if (n_layers < 2)
        return {};
    std::vector<double> result(n_layers - 1);
    result[0] = 0.0;
    for (size_t i = 1; i < n_layers - 1; ++i) {
        result[i] = result[i - 1] - MultiLayerUtils::LayerThickness(multilayer, i);
    }
    return result;
}
} // unnamed namespace
