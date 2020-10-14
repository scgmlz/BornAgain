// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ThickAbsorptiveSampleBuilder.cpp
//! @brief     Implements class to build thick highly-absorptive sample with roughness
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/ThickAbsorptiveSampleBuilder.h"
#include "Base/Const/Units.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"

MultiLayer* ThickAbsorptiveSampleBuilder::buildSample() const
{
    Material vacuum_material = MaterialBySLD("Vacuum", 0.0, 0.0);
    Material au_material = MaterialBySLD("Au", 3.48388057043e-05, 1.79057609656e-05);
    Material si_material = MaterialBySLD("Si", 3.84197565094e-07, 6.28211531498e-07);

    Layer vacuum_layer(vacuum_material);
    Layer au_layer(au_material, 200.0);
    Layer vacuum_layer_2(vacuum_material, 10.0);
    Layer substrate_layer(si_material);

    LayerRoughness rough(5.0, 0.5, 10.0);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(au_layer);
    multi_layer->addLayer(vacuum_layer_2);
    multi_layer->addLayerWithTopRoughness(substrate_layer, rough);
    return multi_layer;
}
