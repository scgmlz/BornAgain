// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/TwoLayerRoughnessBuilder.cpp
//! @brief     Implement class TwoLayerRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/TwoLayerRoughnessBuilder.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"

TwoLayerRoughnessBuilder::TwoLayerRoughnessBuilder()
    : m_sigma(1.0 * Units::nanometer), m_hurst(0.3), m_lateralCorrLength(5.0 * Units::nanometer)
{
}

MultiLayer* TwoLayerRoughnessBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();
    Material air_material = HomogeneousMaterial("Air", 0., 0.);
    Material substrate_material = HomogeneousMaterial("Substrate", 15e-6, 0.0);

    Layer air_layer(air_material, 0);
    Layer substrate_layer(substrate_material, 0);

    LayerRoughness roughness(m_sigma, m_hurst, m_lateralCorrLength);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);
    return multi_layer;
}
