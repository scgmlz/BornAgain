// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CoreShellParticleBuilder.cpp
//! @brief     Implements class CoreShellParticleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/CoreShellParticleBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorBox.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleCoreShell.h"

// --- CoreShellParticleBuilder ---

MultiLayer* CoreShellParticleBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);

    complex_t n_particle_shell(1.0 - 1e-4, 2e-8);
    complex_t n_particle_core(1.0 - 6e-5, 2e-8);

    Material shell_material = HomogeneousMaterial("Shell", n_particle_shell);
    Material core_material = HomogeneousMaterial("Core", n_particle_core);

    Layer air_layer(air_material);

    FormFactorBox ff_box1(16 * Units::nanometer, 16 * Units::nanometer, 8 * Units::nanometer);
    Particle shell_particle(shell_material, ff_box1);

    FormFactorBox ff_box2(12 * Units::nanometer, 12 * Units::nanometer, 7 * Units::nanometer);
    Particle core_particle(core_material, ff_box2);

    kvector_t core_position(0.0, 0.0, 0.0);
    ParticleCoreShell particle(shell_particle, core_particle, core_position);
    ParticleLayout particle_layout(particle);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    return multi_layer;
}

// --- CoreShellBoxRotateZandYBuilder ---

MultiLayer* CoreShellBoxRotateZandYBuilder::buildSample() const
{
    const double layer_thickness(100.0 * Units::nanometer);

    Material mAmbience = HomogeneousMaterial("Air", 0.0, 0.0);
    Material mMiddle = HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9);
    Material mSubstrate = HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8);
    Material mCore = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7);
    Material mShell = HomogeneousMaterial("AgO2", 8.600e-6, 3.442e-7);

    // core shell particle
    const double shell_length(50.0 * Units::nanometer);
    const double shell_width(20.0 * Units::nanometer);
    const double shell_height(10.0 * Units::nanometer);
    double core_length = shell_length / 2.0;
    double core_width = shell_width / 2.0;
    double core_height = shell_height / 2.0;

    Particle core(mCore, FormFactorBox(core_length, core_width, core_height));
    Particle shell(mShell, FormFactorBox(shell_length, shell_width, shell_height));
    ParticleCoreShell coreshell(shell, core,
                                kvector_t(0.0, 0.0, (shell_height - core_height) / 2.0));
    coreshell.setRotation(RotationZ(90.0 * Units::degree));
    coreshell.rotate(RotationY(90.0 * Units::degree));
    coreshell.setPosition(kvector_t(0.0, 0.0, -layer_thickness / 2.0));

    ParticleLayout layout;
    layout.addParticle(coreshell);

    Layer air_layer(mAmbience);
    Layer middle_layer(mMiddle, layer_thickness);
    middle_layer.addLayout(layout);
    Layer substrate(mSubstrate);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);

    return multi_layer;
}
