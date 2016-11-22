// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerInterface.cpp
//! @brief     Implements class LayerInterface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerInterface.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "LayerRoughness.h"
#include "Logger.h"

LayerInterface::LayerInterface()
    : m_roughness(0)
    , m_LayerTop(0)
    , m_LayerBottom(0)
{
    setName(BornAgain::LayerInterfaceType);
}

LayerInterface::~LayerInterface()
{
    delete m_roughness;
}

LayerInterface* LayerInterface::clone() const
{
    throw Exceptions::NotImplementedException("LayerInterface::clone() -> Not allowed to clone.");
}

LayerInterface* LayerInterface::createSmoothInterface(
    const Layer* p_layer_top, const Layer* p_layer_bottom)
{
    LayerInterface* lr = new LayerInterface();
    lr->setLayerTop(p_layer_top);
    lr->setLayerBottom(p_layer_bottom);
    return lr;
}

LayerInterface* LayerInterface::createRoughInterface(
    const Layer* p_layer_top, const Layer* p_layer_bottom, const LayerRoughness& roughness)
{
    LayerInterface* lr = new LayerInterface();
    lr->setLayerTop(p_layer_top);
    lr->setLayerBottom(p_layer_bottom);
    lr->setRoughness(roughness);
    return lr;
}

void LayerInterface::setRoughness(const LayerRoughness& roughness)
{
    if(m_roughness) {
        msglog(Logging::WARNING) << "LayerInterface::setRoughness() -> "
            "Info. Roughness already assigned to given interface, removing it ";
        deregisterChild(m_roughness);
        delete m_roughness;
    }
    //m_roughness = new LayerRoughness(roughness);
    m_roughness = roughness.clone();
    registerChild(m_roughness);
}

void LayerInterface::print(std::ostream& ostr) const
{
    ICompositeSample::print(ostr);
    ostr << "-->LayerI'face{top=" << getLayerTop() << ", bottom=" << getLayerBottom() << "}";
}
