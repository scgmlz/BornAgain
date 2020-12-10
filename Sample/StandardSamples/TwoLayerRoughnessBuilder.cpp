//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/TwoLayerRoughnessBuilder.cpp
//! @brief     Implement class TwoLayerRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/TwoLayerRoughnessBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Slice/LayerRoughness.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* TwoLayerRoughnessBuilder::buildSample() const {
    const double m_sigma(1.0 * Units::nm);
    const double m_hurst(0.3);
    const double m_lateralCorrLength(5.0 * Units::nm);

    Layer vacuum_layer(refMat::Vacuum, 0);
    Layer substrate_layer(refMat::Substrate, 0);

    LayerRoughness roughness(m_sigma, m_hurst, m_lateralCorrLength);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);
    return multi_layer;
}
