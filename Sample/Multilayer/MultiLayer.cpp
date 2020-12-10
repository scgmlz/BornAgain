//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Multilayer/MultiLayer.cpp
//! @brief     Implements class MultiLayer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Multilayer/MultiLayer.h"
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/Material/MaterialUtils.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayerUtils.h"
#include "Sample/Scattering/LayerFillLimits.h"
#include "Sample/Slice/LayerInterface.h"
#include "Sample/Slice/LayerRoughness.h"

MultiLayer::MultiLayer() : m_crossCorrLength(0) {
    setName("MultiLayer");
    registerParameter("CrossCorrelationLength", &m_crossCorrLength).setUnit("nm").setNonnegative();
    registerVector("ExternalField", &m_ext_field, "");
}

MultiLayer::~MultiLayer() = default;

MultiLayer* MultiLayer::clone() const {
    auto* ret = new MultiLayer;
    ret->setCrossCorrLength(crossCorrLength());
    ret->setExternalField(externalField());
    ret->setRoughnessModel(roughnessModel());
    for (size_t i = 0; i < numberOfLayers(); ++i) {
        const auto* interface = i > 0 ? m_interfaces[i - 1] : nullptr;
        Layer* layer = m_layers[i]->clone();
        if (i > 0 && interface->getRoughness())
            ret->addLayerWithTopRoughness(*layer, *interface->getRoughness());
        else
            ret->addLayer(*layer);
    }
    return ret;
}

//! Adds layer with default (zero) roughness
void MultiLayer::addLayer(const Layer& layer) {
    LayerRoughness zero_roughness;
    addLayerWithTopRoughness(layer, zero_roughness);
}

//! Adds layer with top roughness
void MultiLayer::addLayerWithTopRoughness(const Layer& layer, const LayerRoughness& roughness) {
    Layer* new_layer = layer.clone();
    if (numberOfLayers()) {
        // not the top layer
        const Layer* last_layer = m_layers.back();
        LayerInterface* interface(nullptr);
        if (roughness.getSigma() != 0.0)
            interface = LayerInterface::createRoughInterface(last_layer, new_layer, roughness);
        else
            interface = LayerInterface::createSmoothInterface(last_layer, new_layer);
        addAndRegisterInterface(interface);
    } else {
        // the top layer
        if (new_layer->thickness() != 0.0)
            throw std::runtime_error(
                "Invalid call to MultiLayer::addLayer(): the semi-infinite top layer "
                "must have a pro forma thickness of 0");

        if (roughness.getSigma() != 0.0)
            throw std::runtime_error(
                "Invalid call to MultiLayer::addLayer(): the semi-infinite top layer "
                "cannot have roughness.");
    }
    addAndRegisterLayer(new_layer);
}

const Layer* MultiLayer::layer(size_t i_layer) const {
    return m_layers[check_layer_index(i_layer)];
}

const LayerInterface* MultiLayer::layerInterface(size_t i_interface) const {
    return m_interfaces[check_interface_index(i_interface)];
}

void MultiLayer::setCrossCorrLength(double crossCorrLength) {
    if (crossCorrLength < 0.0)
        throw std::runtime_error("Attempt to set crossCorrLength to negative value");
    m_crossCorrLength = crossCorrLength;
}

void MultiLayer::setExternalField(kvector_t ext_field) {
    m_ext_field = ext_field;
}

void MultiLayer::setRoughnessModel(RoughnessModel roughnessModel) {
    m_roughness_model = roughnessModel;
}

std::vector<const INode*> MultiLayer::getChildren() const {
    std::vector<const INode*> ret;
    const size_t N = m_layers.size();
    ret.reserve(N + m_interfaces.size());

    for (size_t i = 0; i < N; ++i) {
        ret.push_back(m_layers[i]);
        if (i == N - 1)
            break;
        ret.push_back(layerInterface(i));
    }
    return ret;
}

void MultiLayer::addAndRegisterLayer(Layer* child) {
    m_layers.push_back(child);
    handleLayerThicknessRegistration();
    registerChild(child);
}

void MultiLayer::addAndRegisterInterface(LayerInterface* child) {
    m_interfaces.push_back(child);
    registerChild(child);
}

void MultiLayer::handleLayerThicknessRegistration() {
    size_t n_layers = numberOfLayers();
    for (size_t i = 0; i < numberOfLayers(); ++i)
        m_layers[i]->registerThickness(i > 0 && i < n_layers - 1);
}

size_t MultiLayer::check_layer_index(size_t i_layer) const {
    if (i_layer >= m_layers.size())
        throw std::runtime_error("Layer index is out of bounds");
    return i_layer;
}

size_t MultiLayer::check_interface_index(size_t i_interface) const {
    if (i_interface >= m_interfaces.size())
        throw std::runtime_error("Interface index is out of bounds");
    return i_interface;
}
