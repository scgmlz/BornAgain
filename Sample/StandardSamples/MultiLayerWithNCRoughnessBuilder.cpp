//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/MultiLayerWithNCRoughnessBuilder.cpp
//! @brief     Implement class MultiLayerWithNCRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/MultiLayerWithNCRoughnessBuilder.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Slice/LayerRoughness.h"

MultiLayer* MultiLayerWithNCRoughnessBuilder::buildSample() const {
    auto multi_layer = MultiLayerWithRoughnessBuilder::buildSample();
    multi_layer->setRoughnessModel(RoughnessModel::NEVOT_CROCE);
    return multi_layer;
}
