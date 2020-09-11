// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayer.cpp
//! @brief     Implements class MultiLayer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/MultiLayer.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Correlations/ILayout.h"
#include "Core/Material/MaterialUtils.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerFillLimits.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayerUtils.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"

MultiLayer::MultiLayer() : m_crossCorrLength(0)
{
    setName("MultiLayer");
    registerParameter("CrossCorrelationLength", &m_crossCorrLength).setUnit("nm").setNonnegative();
    registerVector("ExternalField", &m_ext_field, "");
}

MultiLayer::~MultiLayer() = default;

MultiLayer* MultiLayer::clone() const
{
    std::unique_ptr<MultiLayer> P_result(new MultiLayer());
    P_result->setCrossCorrLength(crossCorrLength());
    P_result->setExternalField(externalField());
    P_result->setRoughnessModel(roughnessModel());
    for (size_t i = 0; i < numberOfLayers(); ++i) {
        auto p_interface = i > 0 ? m_interfaces[i - 1] : nullptr;
        std::unique_ptr<Layer> P_layer(m_layers[i]->clone());
        if (i > 0 && p_interface->getRoughness())
            P_result->addLayerWithTopRoughness(*P_layer, *p_interface->getRoughness());
        else
            P_result->addLayer(*P_layer);
    }
    return P_result.release();
}

//! Adds layer with default (zero) roughness
void MultiLayer::addLayer(const Layer& layer)
{
    LayerRoughness zero_roughness;
    addLayerWithTopRoughness(layer, zero_roughness);
}

//! Adds layer with top roughness
void MultiLayer::addLayerWithTopRoughness(const Layer& layer, const LayerRoughness& roughness)
{
    Layer* p_new_layer = layer.clone();
    if (numberOfLayers()) {
        // not the top layer
        const Layer* p_last_layer = m_layers.back();
        LayerInterface* interface(nullptr);
        if (roughness.getSigma() != 0.0)
            interface = LayerInterface::createRoughInterface(p_last_layer, p_new_layer, roughness);
        else
            interface = LayerInterface::createSmoothInterface(p_last_layer, p_new_layer);
        addAndRegisterInterface(interface);
    } else {
        // the top layer
        if (p_new_layer->thickness() != 0.0)
            throw std::runtime_error(
                "Invalid call to MultiLayer::addLayer(): the semi-infinite top layer "
                "must have a pro forma thickness of 0");

        if (roughness.getSigma() != 0.0)
            throw std::runtime_error(
                "Invalid call to MultiLayer::addLayer(): the semi-infinite top layer "
                "cannot have roughness.");
    }
    addAndRegisterLayer(p_new_layer);
}

const Layer* MultiLayer::layer(size_t i_layer) const
{
    return m_layers[check_layer_index(i_layer)];
}

const LayerInterface* MultiLayer::layerInterface(size_t i_interface) const
{
    return m_interfaces[check_interface_index(i_interface)];
}

void MultiLayer::setCrossCorrLength(double crossCorrLength)
{
    if (crossCorrLength < 0.0)
        throw Exceptions::LogicErrorException("Attempt to set crossCorrLength to negative value");
    m_crossCorrLength = crossCorrLength;
}

void MultiLayer::setExternalField(kvector_t ext_field)
{
    m_ext_field = ext_field;
}

void MultiLayer::setRoughnessModel(RoughnessModel roughnessModel)
{
    m_roughness_model = roughnessModel;
}

std::vector<const INode*> MultiLayer::getChildren() const
{
    std::vector<const INode*> result;
    const size_t layer_size = m_layers.size();
    result.reserve(layer_size + m_interfaces.size());

    for (size_t i = 0; i < layer_size; ++i) {
        result.push_back(m_layers[i]);
        const LayerInterface* p_interface = MultiLayerUtils::LayerBottomInterface(*this, i);
        if (p_interface)
            result.push_back(p_interface);
    }
    return result;
}

void MultiLayer::addAndRegisterLayer(Layer* child)
{
    m_layers.push_back(child);
    handleLayerThicknessRegistration();
    registerChild(child);
}

void MultiLayer::addAndRegisterInterface(LayerInterface* child)
{
    m_interfaces.push_back(child);
    registerChild(child);
}

void MultiLayer::handleLayerThicknessRegistration()
{
    size_t n_layers = numberOfLayers();
    for (size_t i = 0; i < numberOfLayers(); ++i) {
        if (i == 0 || i == n_layers - 1) {
            m_layers[i]->registerThickness(false);
        } else {
            m_layers[i]->registerThickness(true);
        }
    }
}

size_t MultiLayer::check_layer_index(size_t i_layer) const
{
    if (i_layer >= m_layers.size())
        throw Exceptions::OutOfBoundsException("Layer index is out of bounds");
    return i_layer;
}

size_t MultiLayer::check_interface_index(size_t i_interface) const
{
    if (i_interface >= m_interfaces.size())
        throw Exceptions::OutOfBoundsException("Interface index is out of bounds");
    return i_interface;
}
