// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MultipleLayoutBuilder.cpp
//! @brief     Implements class MultipleLayoutBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/MultipleLayoutBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/HardParticle/FormFactorPrism3.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"

MultipleLayoutBuilder::MultipleLayoutBuilder()
    : m_cylinder_height(5 * Units::nanometer), m_cylinder_radius(5 * Units::nanometer),
      m_prism_height(5 * Units::nanometer), m_prism_length(10 * Units::nanometer),
      m_cylinder_weight(0.5)
{
}

MultiLayer* MultipleLayoutBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0., 0.);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    ParticleLayout particle_layout_1;
    ParticleLayout particle_layout_2;

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);
    Particle cylinder(particle_material, ff_cylinder);

    FormFactorPrism3 ff_prism3(m_prism_length, m_prism_height);
    Particle prism3(particle_material, ff_prism3);

    particle_layout_1.addParticle(cylinder, m_cylinder_weight);
    particle_layout_2.addParticle(prism3, 1.0 - m_cylinder_weight);

    air_layer.addLayout(particle_layout_1);
    air_layer.addLayout(particle_layout_2);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
