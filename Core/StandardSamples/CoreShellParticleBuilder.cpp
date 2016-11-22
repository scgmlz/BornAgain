// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CoreShellParticleBuilder.cpp
//! @brief     Implements class CoreShellParticleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreShellParticleBuilder.h"
#include "FormFactorBox.h"
#include "Layer.h"
#include "HomogeneousMaterial.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleCoreShell.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

// --- CoreShellParticleBuilder ---

MultiLayer* CoreShellParticleBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);

    complex_t n_particle_shell(1.0-1e-4, 2e-8);
    complex_t n_particle_core(1.0-6e-5, 2e-8);

    HomogeneousMaterial shell_material("Shell", n_particle_shell);
    HomogeneousMaterial core_material("Core", n_particle_core);

    Layer air_layer(air_material);

    FormFactorBox ff_box1(16*Units::nanometer, 16*Units::nanometer, 8*Units::nanometer);
    Particle shell_particle(shell_material, ff_box1);

    FormFactorBox ff_box2(12*Units::nanometer, 12*Units::nanometer, 7*Units::nanometer);
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
    const double layer_thickness(100.0*Units::nanometer);

    HomogeneousMaterial mAmbience("Air", 0.0, 0.0);
    HomogeneousMaterial mMiddle("Teflon", 2.900e-6, 6.019e-9);
    HomogeneousMaterial mSubstrate("Substrate", 3.212e-6, 3.244e-8);
    HomogeneousMaterial mCore("Ag", 1.245e-5, 5.419e-7);
    HomogeneousMaterial mShell("AgO2", 8.600e-6, 3.442e-7);

    // core shell particle
    const double shell_length(50.0*Units::nanometer);
    const double shell_width(20.0*Units::nanometer);
    const double shell_height(10.0*Units::nanometer);
    double core_length = shell_length/2.0;
    double core_width = shell_width/2.0;
    double core_height = shell_height/2.0;

    Particle core(mCore, FormFactorBox(core_length, core_width, core_height));
    Particle shell(mShell, FormFactorBox(shell_length, shell_width, shell_height));
    ParticleCoreShell coreshell(shell, core, kvector_t(0.0, 0.0, (shell_height-core_height)/2.0));
    coreshell.setRotation(RotationZ(90.0*Units::degree));
    coreshell.applyRotation(RotationY(90.0*Units::degree));
    coreshell.setPosition(kvector_t(0.0, 0.0, -layer_thickness/2.0));

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
