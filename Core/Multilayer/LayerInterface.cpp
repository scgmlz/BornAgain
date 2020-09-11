// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerInterface.cpp
//! @brief     Implements class LayerInterface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/LayerInterface.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Multilayer/LayerRoughness.h"

LayerInterface::LayerInterface() : m_topLayer(nullptr), m_bottomLayer(nullptr)
{
    setName("LayerInterface");
}

LayerInterface::~LayerInterface() {}

LayerInterface* LayerInterface::clone() const
{
    throw Exceptions::NotImplementedException("LayerInterface::clone() -> Not allowed to clone.");
}

LayerInterface* LayerInterface::createSmoothInterface(const Layer* top_layer,
                                                      const Layer* bottom_layer)
{
    LayerInterface* result = new LayerInterface();
    result->setLayersTopBottom(top_layer, bottom_layer);
    return result;
}

LayerInterface* LayerInterface::createRoughInterface(const Layer* top_layer,
                                                     const Layer* bottom_layer,
                                                     const LayerRoughness& roughness)
{
    LayerInterface* result = createSmoothInterface(top_layer, bottom_layer);
    result->setRoughness(roughness);
    return result;
}

void LayerInterface::setRoughness(const LayerRoughness& roughness)
{
    m_roughness.reset(roughness.clone());
    registerChild(m_roughness.get());
}

std::vector<const INode*> LayerInterface::getChildren() const
{
    return std::vector<const INode*>() << m_roughness;
}

//! Sets links to the layers above and below the interface.

void LayerInterface::setLayersTopBottom(const Layer* top_layer, const Layer* bottom_layer)
{
    if (top_layer == nullptr || bottom_layer == nullptr)
        throw Exceptions::RuntimeErrorException("LayerInterface::setLayersTopBottom() -> Error. "
                                                "Attempt to set nullptr.");
    m_topLayer = top_layer;
    m_bottomLayer = bottom_layer;
}
