//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/MagneticParticlesBuilder.cpp
//! @brief     Implements classes to build magnetic samples
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/MagneticParticlesBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/HardParticle/FormFactorFullSphere.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Slice/LayerInterface.h"
#include "Sample/Slice/LayerRoughness.h"

// ----------------------------------------------------------------------------
// Magnetic cylinders and zero magnetic field
// ----------------------------------------------------------------------------

MultiLayer* MagneticParticleZeroFieldBuilder::buildSample() const {
    const double m_cylinder_radius(5 * Units::nm);
    const double m_cylinder_height(5 * Units::nm);

    Material vacuum_material = HomogeneousMaterial("Vacuum", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    Material particle_material = HomogeneousMaterial("MagParticle", 6e-4, 2e-8, magnetic_field);

    Layer vacuum_layer(vacuum_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------
// Magnetic cylinders and non-zero magnetization
// ----------------------------------------------------------------------------

MultiLayer* MagneticCylindersBuilder::buildSample() const {
    const double m_cylinder_radius(5 * Units::nm);
    const double m_cylinder_height(5 * Units::nm);

    Material vacuum_material = HomogeneousMaterial("Vacuum", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 15e-6, 0.0);
    kvector_t magnetization(0.0, 1e6, 0.0);
    Material particle_material = HomogeneousMaterial("MagParticle2", 5e-6, 0.0, magnetization);

    Layer vacuum_layer(vacuum_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------
// Magnetic spheres inside substrate
// ----------------------------------------------------------------------------

MultiLayer* MagneticSpheresBuilder::buildSample() const {
    const double m_sphere_radius(5 * Units::nm);

    kvector_t magnetization(0.0, 0.0, 1e7);
    Material particle_material = HomogeneousMaterial("Particle", 2e-5, 4e-7, magnetization);
    Material vacuum_material = HomogeneousMaterial("Vacuum", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 7e-6, 1.8e-7);

    FormFactorFullSphere ff_sphere(m_sphere_radius);
    Particle particle(particle_material, ff_sphere);
    kvector_t position(0.0, 0.0, -2.0 * m_sphere_radius);

    ParticleLayout particle_layout;
    particle_layout.addParticle(particle, 1.0, position);

    Layer vacuum_layer(vacuum_material);
    Layer substrate_layer(substrate_material);
    substrate_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
