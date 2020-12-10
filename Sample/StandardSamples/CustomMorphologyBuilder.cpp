//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/CustomMorphologyBuilder.cpp
//! @brief     Implements class CustomMorphologyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/CustomMorphologyBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorBox.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* CustomMorphologyBuilder::buildSample() const {

    Material mat_vacuum = refMat::Vacuum;
    Material mat_particle = refMat::Particle;

    Layer vacuum_layer(mat_vacuum);
    ParticleLayout particle_layout;

    // add particle number 1:
    FormFactorBox ff1(2.0 * Units::nm, 2.0 * Units::nm, 1.0 * Units::nm);
    kvector_t pos1(0.0 * Units::nm, 0.0 * Units::nm, 0.0);
    Particle p1(mat_particle, ff1);
    p1.setPosition(pos1);
    particle_layout.addParticle(p1, 0.5);
    // add particle number 2:
    FormFactorBox ff2(2.0 * Units::nm, 4.0 * Units::nm, 1.0 * Units::nm);
    kvector_t pos2(5.0 * Units::nm, 5.0 * Units::nm, 0.0);
    RotationZ m2(10 * Units::deg);
    Particle p2(mat_particle, ff2, m2);
    p2.setPosition(pos2);
    particle_layout.addParticle(p2, 0.5);
    // add particle number 3:
    FormFactorBox ff3(2.0 * Units::nm, 6.0 * Units::nm, 1.0 * Units::nm);
    kvector_t pos3(-5.0 * Units::nm, -5.0 * Units::nm, 0.0);
    RotationZ m3(20 * Units::deg);
    Particle p3(mat_particle, ff3, m3);
    p3.setPosition(pos3);
    particle_layout.addParticle(p3, 0.5);
    // add particle number 4:
    FormFactorBox ff4(2.0 * Units::nm, 8.0 * Units::nm, 1.0 * Units::nm);
    kvector_t pos4(5.0 * Units::nm, -5.0 * Units::nm, 0.0);
    RotationZ m4(30 * Units::deg);
    Particle p4(mat_particle, ff4, m4);
    p4.setPosition(pos4);
    particle_layout.addParticle(p4, 0.5);
    // add particle number 5:
    FormFactorBox ff5(2.0 * Units::nm, 10.0 * Units::nm, 1.0 * Units::nm);
    kvector_t pos5(-5.0 * Units::nm, 5.0 * Units::nm, 0.0);
    RotationZ m5(40 * Units::deg);
    Particle p5(mat_particle, ff5, m5);
    p5.setPosition(pos5);
    particle_layout.addParticle(p5, 0.5);
    // add particle number 6:
    FormFactorBox ff6(2.0 * Units::nm, 2.0 * Units::nm, 1.0 * Units::nm);
    kvector_t pos6(0.0 * Units::nm, 0.0 * Units::nm, 0.0);
    RotationZ m6(50 * Units::deg);
    Particle p6(mat_particle, ff6, m6);
    p6.setPosition(pos6);
    particle_layout.addParticle(p6, 0.5);
    // add particle number 7:
    FormFactorBox ff7(2.0 * Units::nm, 4.0 * Units::nm, 1.0 * Units::nm);
    kvector_t pos7(5.0 * Units::nm, 5.0 * Units::nm, 0.0);
    RotationZ m7(60 * Units::deg);
    Particle p7(mat_particle, ff7, m7);
    p7.setPosition(pos7);
    particle_layout.addParticle(p7, 0.5);
    // add particle number 8:
    FormFactorBox ff8(2.0 * Units::nm, 6.0 * Units::nm, 1.0 * Units::nm);
    kvector_t pos8(-5.0 * Units::nm, -5.0 * Units::nm, 0.0);
    RotationZ m8(70 * Units::deg);
    Particle p8(mat_particle, ff8, m8);
    p8.setPosition(pos8);
    particle_layout.addParticle(p8, 0.5);
    // add particle number 9:
    FormFactorBox ff9(2.0 * Units::nm, 8.0 * Units::nm, 1.0 * Units::nm);
    kvector_t pos9(5.0 * Units::nm, -5.0 * Units::nm, 0.0);
    RotationZ m9(80 * Units::deg);
    Particle p9(mat_particle, ff9, m9);
    p9.setPosition(pos9);
    particle_layout.addParticle(p9, 0.5);
    // add particle number 10:
    FormFactorBox ff10(2.0 * Units::nm, 10.0 * Units::nm, 1.0 * Units::nm);
    kvector_t pos10(-5.0 * Units::nm, 5.0 * Units::nm, 0.0);
    RotationZ m10(90 * Units::deg);
    Particle p10(mat_particle, ff10, m10);
    p10.setPosition(pos10);
    particle_layout.addParticle(p10, 0.5);
    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    return multi_layer;
}
