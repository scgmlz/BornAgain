//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/CylindersBuilder.cpp
//! @brief     Implements classes of CylindersBuilder family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/CylindersBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Slice/LayerInterface.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

// -----------------------------------------------------------------------------
// Cylinders in DWBA
// -----------------------------------------------------------------------------
CylindersInDWBABuilder::CylindersInDWBABuilder()
    : m_height(5 * Units::nm), m_radius(5 * Units::nm) {}

MultiLayer* CylindersInDWBABuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    FormFactorCylinder ff_cylinder(m_radius, m_height);

    Particle particle(refMat::Particle, ff_cylinder);
    ParticleLayout particle_layout(particle);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// -----------------------------------------------------------------------------
// Cylinders in BA
// -----------------------------------------------------------------------------
CylindersInBABuilder::CylindersInBABuilder() : m_height(5 * Units::nm), m_radius(5 * Units::nm) {
    registerParameter("height", &m_height);
    registerParameter("radius", &m_radius);
}

MultiLayer* CylindersInBABuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);

    FormFactorCylinder ff_cylinder(m_radius, m_height);
    Particle cylinder(refMat::Particle, ff_cylinder);

    ParticleLayout particle_layout(cylinder);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    return multi_layer;
}

// -----------------------------------------------------------------------------
// Large cylinders in DWBA
// -----------------------------------------------------------------------------
LargeCylindersInDWBABuilder::LargeCylindersInDWBABuilder()
    : m_height(1000 * Units::nm), m_radius(500 * Units::nm) {}

MultiLayer* LargeCylindersInDWBABuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    FormFactorCylinder ff_cylinder(m_radius, m_height);

    Particle particle(refMat::Particle, ff_cylinder);
    ParticleLayout particle_layout(particle);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// -----------------------------------------------------------------------------
// Rotated cylinders in DWBA
// -----------------------------------------------------------------------------
RotatedCylindersBuilder::RotatedCylindersBuilder()
    : m_height(5 * Units::nm), m_radius(5 * Units::nm) {}

MultiLayer* RotatedCylindersBuilder::buildSample() const {
    FormFactorCylinder ff_cylinder(m_radius, m_height);

    Particle particle(refMat::Particle, ff_cylinder);
    ParticleLayout particle_layout;
    particle_layout.addParticle(particle, 1.0, kvector_t(), RotationY(M_PI));

    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);
    substrate_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
