//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/HomogeneousMultilayerBuilder.cpp
//! @brief     Implements class HomogeneousMultilayerBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/HomogeneousMultilayerBuilder.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"

MultiLayer* HomogeneousMultilayerBuilder::buildSample() const {
    const size_t number_of_layers = 10;
    const double delta_ti = -7.36e-7;
    const double delta_ni = 3.557e-6;
    const double delta_si = 7.81e-7;
    const double thick_ti = 3.0; // nm
    const double thick_ni = 7.0; // nm

    Material vacuumaterial = HomogeneousMaterial();
    Material substrate_material = HomogeneousMaterial("Si_substrate", delta_si, 0.0);
    Material ni_material = HomogeneousMaterial("Ni", delta_ni, 0.0);
    Material ti_material = HomogeneousMaterial("Ti", delta_ti, 0.0);

    Layer vacuulayer(vacuumaterial, 0);
    Layer ni_layer(ni_material, thick_ni);
    Layer ti_layer(ti_material, thick_ti);
    Layer substrate_layer(substrate_material, 0);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuulayer);
    for (size_t i = 0; i < number_of_layers; ++i) {
        multi_layer->addLayer(ti_layer);
        multi_layer->addLayer(ni_layer);
    }
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
