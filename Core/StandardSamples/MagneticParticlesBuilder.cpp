// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MagneticParticlesBuilder.cpp
//! @brief     Implements classes to build magnetic samples
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MagneticParticlesBuilder.h"
#include "FormFactorCylinder.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "HomogeneousMagneticMaterial.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

// ----------------------------------------------------------------------------
// Magnetic cylinders and zero magnetic field
// ----------------------------------------------------------------------------

MagneticParticleZeroFieldBuilder::MagneticParticleZeroFieldBuilder()
    :  m_cylinder_radius(5*Units::nanometer)
    ,  m_cylinder_height(5*Units::nanometer)
{
    init_parameters();
}

void MagneticParticleZeroFieldBuilder::init_parameters()
{
    registerParameter("cylinder_radius", &m_cylinder_radius).setUnit("nm").setNonnegative();
    registerParameter("cylinder_height", &m_cylinder_height).setUnit("nm").setNonnegative();
}

MultiLayer* MagneticParticleZeroFieldBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    kvector_t magnetic_field(0.0, 0.0, 0.0);
    HomogeneousMagneticMaterial particle_material("MagParticle", 6e-4, 2e-8, magnetic_field);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------
// Magnetic cylinders and non-zero magnetic field
// ----------------------------------------------------------------------------
MagneticCylindersBuilder::MagneticCylindersBuilder()
    :  m_cylinder_radius(5*Units::nanometer)
    ,  m_cylinder_height(5*Units::nanometer)
{
    init_parameters();
}

void MagneticCylindersBuilder::init_parameters()
{

    registerParameter("cylinder_radius", &m_cylinder_radius).setUnit("nm").setNonnegative();
    registerParameter("cylinder_height", &m_cylinder_height).setUnit("nm").setNonnegative();
}

MultiLayer* MagneticCylindersBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 15e-6, 0.0);
    kvector_t magnetic_field(0.0, 1.0, 0.0);
    HomogeneousMagneticMaterial particle_material("MagParticle2", 5e-6, 0.0, magnetic_field);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
