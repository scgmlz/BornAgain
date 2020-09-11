// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/HomogeneousMultilayerBuilder.cpp
//! @brief     Implements class HomogeneousMultilayerBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/HomogeneousMultilayerBuilder.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"

HomogeneousMultilayerBuilder::HomogeneousMultilayerBuilder()
    : m_number_of_layers(10), m_delta_ti(-7.36e-7), m_delta_ni(3.557e-6), m_delta_si(7.81e-7),
      m_thick_ti(3.0) // nm
      ,
      m_thick_ni(7.0) // nm
{
}

MultiLayer* HomogeneousMultilayerBuilder::buildSample() const
{
    std::unique_ptr<MultiLayer> multi_layer(new MultiLayer());

    Material vacuum_material = HomogeneousMaterial();
    Material substrate_material = HomogeneousMaterial("Si_substrate", m_delta_si, 0.0);
    Material ni_material = HomogeneousMaterial("Ni", m_delta_ni, 0.0);
    Material ti_material = HomogeneousMaterial("Ti", m_delta_ti, 0.0);

    Layer vacuum_layer(vacuum_material, 0);
    Layer ni_layer(ni_material, m_thick_ni);
    Layer ti_layer(ti_material, m_thick_ti);
    Layer substrate_layer(substrate_material, 0);

    multi_layer->addLayer(vacuum_layer);
    for (size_t i = 0; i < m_number_of_layers; ++i) {
        multi_layer->addLayer(ti_layer);
        multi_layer->addLayer(ni_layer);
    }
    multi_layer->addLayer(substrate_layer);
    return multi_layer.release();
}
