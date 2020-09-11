// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MultiLayerWithNCRoughnessBuilder.cpp
//! @brief     Implement class MultiLayerWithNCRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/MultiLayerWithNCRoughnessBuilder.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"

MultiLayerWithNCRoughnessBuilder::MultiLayerWithNCRoughnessBuilder() {}

MultiLayer* MultiLayerWithNCRoughnessBuilder::buildSample() const
{
    auto multi_layer = MultiLayerWithRoughnessBuilder::buildSample();
    multi_layer->setRoughnessModel(RoughnessModel::NEVOT_CROCE);
    return multi_layer;
}
