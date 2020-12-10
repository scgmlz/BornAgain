//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Slice/LayerInterface.cpp
//! @brief     Implements class LayerInterface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Slice/LayerInterface.h"
#include "Sample/Slice/LayerRoughness.h"

LayerInterface::LayerInterface() : m_topLayer(nullptr), m_bottomLayer(nullptr) {
    setName("LayerInterface");
}

LayerInterface::~LayerInterface() = default;

LayerInterface* LayerInterface::clone() const {
    throw std::runtime_error("LayerInterface::clone() -> Not allowed to clone.");
}

LayerInterface* LayerInterface::createSmoothInterface(const Layer* top_layer,
                                                      const Layer* bottom_layer) {
    LayerInterface* result = new LayerInterface();
    result->setLayersTopBottom(top_layer, bottom_layer);
    return result;
}

LayerInterface* LayerInterface::createRoughInterface(const Layer* top_layer,
                                                     const Layer* bottom_layer,
                                                     const LayerRoughness& roughness) {
    LayerInterface* result = createSmoothInterface(top_layer, bottom_layer);
    result->setRoughness(roughness);
    return result;
}

void LayerInterface::setRoughness(const LayerRoughness& roughness) {
    m_roughness.reset(roughness.clone());
    registerChild(m_roughness.get());
}

std::vector<const INode*> LayerInterface::getChildren() const {
    return std::vector<const INode*>() << m_roughness;
}

//! Sets links to the layers above and below the interface.

void LayerInterface::setLayersTopBottom(const Layer* top_layer, const Layer* bottom_layer) {
    if (top_layer == nullptr || bottom_layer == nullptr)
        throw std::runtime_error("LayerInterface::setLayersTopBottom() -> Error. "
                                 "Attempt to set nullptr.");
    m_topLayer = top_layer;
    m_bottomLayer = bottom_layer;
}
