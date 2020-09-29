// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ResonatorBuilder.cpp
//! @brief     Implements ResonatorBuilder class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/ResonatorBuilder.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"
#include <memory>

ResonatorBuilder::ResonatorBuilder() : ISampleBuilder(), m_l_ti(13.0 * Units::nm)
{
    registerParameter("ti_thickness", &m_l_ti);
}

MultiLayer* ResonatorBuilder::buildSample() const
{
    std::unique_ptr<MultiLayer> result(new MultiLayer);

    Material m_Si = HomogeneousMaterial("Si", 8.25218379931e-06, 0.0);
    Material m_Ti = HomogeneousMaterial("Ti", -7.6593316363e-06, 3.81961616312e-09);
    Material m_TiO2 = HomogeneousMaterial("TiO2", 1.04803530026e-05, 2.03233519385e-09);
    Material m_Pt = HomogeneousMaterial("Pt", 2.52936993309e-05, 7.54553992473e-09);
    Material m_D2O = HomogeneousMaterial("D2O", 2.52897204573e-05, 4.5224432814e-13);

    Layer l_TiO2(m_TiO2, 3.0 * Units::nm);
    Layer l_Ti_top(m_Ti, 10.0 * Units::nm);
    Layer l_Ti(m_Ti, m_l_ti);
    Layer l_Si(m_Si);
    Layer l_Pt(m_Pt, 32.0 * Units::nm);
    Layer l_D2O(m_D2O);

    LayerRoughness roughness(2.0 * Units::nm, 0.8, 10.0 * Units::micrometer);

    result->addLayer(l_Si);

    const int nlayers = 3;
    for (size_t i = 0; i < nlayers; ++i) {
        result->addLayerWithTopRoughness(l_Ti, roughness);
        result->addLayerWithTopRoughness(l_Pt, roughness);
    }

    result->addLayerWithTopRoughness(l_Ti_top, roughness);
    result->addLayerWithTopRoughness(l_TiO2, roughness);
    result->addLayerWithTopRoughness(l_D2O, roughness);

    result->setCrossCorrLength(400 * Units::nm);

    return result.release();
}
