// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/PercusYevickBuilder.cpp
//! @brief     Implements class PercusYevickBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/PercusYevickBuilder.h"
#include "Core/Aggregate/InterferenceFunctionHardDisk.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"

HardDiskBuilder::HardDiskBuilder()
    : m_cylinder_height(5 * Units::nanometer), m_cylinder_radius(5 * Units::nanometer),
      m_disk_radius(5 * Units::nanometer), m_density(0.006)
{
}

MultiLayer* HardDiskBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);
    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    InterferenceFunctionHardDisk interference_function(m_disk_radius, m_density);
    particle_layout.setInterferenceFunction(interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
