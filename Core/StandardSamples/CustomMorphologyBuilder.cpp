// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CustomMorphologyBuilder.cpp
//! @brief     Implements class CustomMorphologyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/CustomMorphologyBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorBox.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"

MultiLayer* CustomMorphologyBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    ParticleLayout particle_layout;

    // add particle number 1:
    FormFactorBox ff1(2.0 * Units::nanometer, 2.0 * Units::nanometer, 1.0 * Units::nanometer);
    kvector_t pos1(0.0 * Units::nanometer, 0.0 * Units::nanometer, 0.0);
    Particle p1(particle_material, ff1);
    p1.setPosition(pos1);
    particle_layout.addParticle(p1, 0.5);
    // add particle number 2:
    FormFactorBox ff2(2.0 * Units::nanometer, 4.0 * Units::nanometer, 1.0 * Units::nanometer);
    kvector_t pos2(5.0 * Units::nanometer, 5.0 * Units::nanometer, 0.0);
    RotationZ m2(10 * Units::degree);
    Particle p2(particle_material, ff2, m2);
    p2.setPosition(pos2);
    particle_layout.addParticle(p2, 0.5);
    // add particle number 3:
    FormFactorBox ff3(2.0 * Units::nanometer, 6.0 * Units::nanometer, 1.0 * Units::nanometer);
    kvector_t pos3(-5.0 * Units::nanometer, -5.0 * Units::nanometer, 0.0);
    RotationZ m3(20 * Units::degree);
    Particle p3(particle_material, ff3, m3);
    p3.setPosition(pos3);
    particle_layout.addParticle(p3, 0.5);
    // add particle number 4:
    FormFactorBox ff4(2.0 * Units::nanometer, 8.0 * Units::nanometer, 1.0 * Units::nanometer);
    kvector_t pos4(5.0 * Units::nanometer, -5.0 * Units::nanometer, 0.0);
    RotationZ m4(30 * Units::degree);
    Particle p4(particle_material, ff4, m4);
    p4.setPosition(pos4);
    particle_layout.addParticle(p4, 0.5);
    // add particle number 5:
    FormFactorBox ff5(2.0 * Units::nanometer, 10.0 * Units::nanometer, 1.0 * Units::nanometer);
    kvector_t pos5(-5.0 * Units::nanometer, 5.0 * Units::nanometer, 0.0);
    RotationZ m5(40 * Units::degree);
    Particle p5(particle_material, ff5, m5);
    p5.setPosition(pos5);
    particle_layout.addParticle(p5, 0.5);
    // add particle number 6:
    FormFactorBox ff6(2.0 * Units::nanometer, 2.0 * Units::nanometer, 1.0 * Units::nanometer);
    kvector_t pos6(0.0 * Units::nanometer, 0.0 * Units::nanometer, 0.0);
    RotationZ m6(50 * Units::degree);
    Particle p6(particle_material, ff6, m6);
    p6.setPosition(pos6);
    particle_layout.addParticle(p6, 0.5);
    // add particle number 7:
    FormFactorBox ff7(2.0 * Units::nanometer, 4.0 * Units::nanometer, 1.0 * Units::nanometer);
    kvector_t pos7(5.0 * Units::nanometer, 5.0 * Units::nanometer, 0.0);
    RotationZ m7(60 * Units::degree);
    Particle p7(particle_material, ff7, m7);
    p7.setPosition(pos7);
    particle_layout.addParticle(p7, 0.5);
    // add particle number 8:
    FormFactorBox ff8(2.0 * Units::nanometer, 6.0 * Units::nanometer, 1.0 * Units::nanometer);
    kvector_t pos8(-5.0 * Units::nanometer, -5.0 * Units::nanometer, 0.0);
    RotationZ m8(70 * Units::degree);
    Particle p8(particle_material, ff8, m8);
    p8.setPosition(pos8);
    particle_layout.addParticle(p8, 0.5);
    // add particle number 9:
    FormFactorBox ff9(2.0 * Units::nanometer, 8.0 * Units::nanometer, 1.0 * Units::nanometer);
    kvector_t pos9(5.0 * Units::nanometer, -5.0 * Units::nanometer, 0.0);
    RotationZ m9(80 * Units::degree);
    Particle p9(particle_material, ff9, m9);
    p9.setPosition(pos9);
    particle_layout.addParticle(p9, 0.5);
    // add particle number 10:
    FormFactorBox ff10(2.0 * Units::nanometer, 10.0 * Units::nanometer, 1.0 * Units::nanometer);
    kvector_t pos10(-5.0 * Units::nanometer, 5.0 * Units::nanometer, 0.0);
    RotationZ m10(90 * Units::degree);
    Particle p10(particle_material, ff10, m10);
    p10.setPosition(pos10);
    particle_layout.addParticle(p10, 0.5);

    air_layer.addLayout(particle_layout);
    multi_layer->addLayer(air_layer);

    return multi_layer;
}
