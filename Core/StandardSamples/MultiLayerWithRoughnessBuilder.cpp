// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MultiLayerWithRoughnessBuilder.cpp
//! @brief     Implement class MultiLayerWithRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/MultiLayerWithRoughnessBuilder.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"

MultiLayer* MultiLayerWithRoughnessBuilder::buildSample() const
{
    const double thicknessA(2.5 * Units::nanometer);
    const double thicknessB(5.0 * Units::nanometer);
    const double sigma(1.0 * Units::nanometer);
    const double hurst(0.3);
    const double lateralCorrLength(5.0 * Units::nanometer);
    const double crossCorrLength(10.0 * Units::nanometer);

    Material vacuum_material = HomogeneousMaterial("Vacuum", 0., 0.);
    Material substrate_material = HomogeneousMaterial("Substrate", 15e-6, 0.0);
    Material part_a_material = HomogeneousMaterial("PartA", 5e-6, 0.0);
    Material part_b_material = HomogeneousMaterial("PartB", 10e-6, 0.0);

    Layer vacuum_layer(vacuum_material, 0);
    Layer partA_layer(part_a_material, thicknessA);
    Layer partB_layer(part_b_material, thicknessB);
    Layer substrate_layer(substrate_material, 0);

    LayerRoughness roughness(sigma, hurst, lateralCorrLength);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    for (int i = 0; i < 5; ++i) {
        multi_layer->addLayerWithTopRoughness(partA_layer, roughness);
        multi_layer->addLayerWithTopRoughness(partB_layer, roughness);
    }
    multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);
    multi_layer->setCrossCorrLength(crossCorrLength);
    return multi_layer;
}
