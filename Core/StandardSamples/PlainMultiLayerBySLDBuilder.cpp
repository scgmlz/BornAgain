// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/PlainMultiLayerBySLDBuilder.cpp
//! @brief     Implements class PlainMultiLayerBySLDBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PlainMultiLayerBySLDBuilder.h"
#include "MaterialFactoryFuncs.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Units.h"

PlainMultiLayerBySLDBuilder::PlainMultiLayerBySLDBuilder()
    : m_number_of_layers(10)
    , m_si { 2.0704e-06, 2.3726e-11}
    , m_ti {-1.9493e-06, 9.6013e-10}
    , m_ni { 9.4245e-06, 1.1423e-09}
    , m_thick_ti(3.0) // nm
    , m_thick_ni(7.0) //nm
{
    registerParameter("ti_thickness", &m_thick_ti);
}

MultiLayer* PlainMultiLayerBySLDBuilder::buildSample() const
{
    std::unique_ptr<MultiLayer> multi_layer(new MultiLayer());

    Material vacuum_material = MaterialBySLD();
    Material substrate_material = MaterialBySLD("Si_substrate", m_si.sld_real, m_si.sld_imag);
    Material ni_material = MaterialBySLD("Ni", m_ni.sld_real, m_ni.sld_imag);
    Material ti_material = MaterialBySLD("Ti", m_ti.sld_real, m_ti.sld_imag);

    Layer vacuum_layer(vacuum_material);
    Layer ni_layer(ni_material, m_thick_ni);
    Layer ti_layer(ti_material, m_thick_ti);
    Layer substrate_layer(substrate_material);

    multi_layer->addLayer(vacuum_layer);
    for (size_t i = 0; i < m_number_of_layers; ++i) {
        multi_layer->addLayer(ti_layer);
        multi_layer->addLayer(ni_layer);
    }
    multi_layer->addLayer(substrate_layer);
    return multi_layer.release();
}
