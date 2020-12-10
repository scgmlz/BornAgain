//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/CoreShellParticleBuilder.cpp
//! @brief     Implements class CoreShellParticleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/CoreShellParticleBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorBox.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleCoreShell.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

// --- CoreShellParticleBuilder ---

MultiLayer* CoreShellParticleBuilder::buildSample() const {
    complex_t n_particle_shell(1.0 - 1e-4, 2e-8);
    complex_t n_particle_core(1.0 - 6e-5, 2e-8);

    Material shell_material = HomogeneousMaterial("Shell", n_particle_shell);
    Material core_material = HomogeneousMaterial("Core", n_particle_core);

    Layer vacuum_layer(refMat::Vacuum);

    FormFactorBox ff_box1(16 * Units::nm, 16 * Units::nm, 8 * Units::nm);
    Particle shell_particle(shell_material, ff_box1);

    FormFactorBox ff_box2(12 * Units::nm, 12 * Units::nm, 7 * Units::nm);
    Particle core_particle(core_material, ff_box2);

    kvector_t core_position(0.0, 0.0, 0.0);
    ParticleCoreShell particle(shell_particle, core_particle, core_position);
    ParticleLayout particle_layout(particle);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    return multi_layer;
}

// --- CoreShellBoxRotateZandYBuilder ---

MultiLayer* CoreShellBoxRotateZandYBuilder::buildSample() const {
    const double layer_thickness(100.0 * Units::nm);

    // core shell particle
    const double shell_length(50.0 * Units::nm);
    const double shell_width(20.0 * Units::nm);
    const double shell_height(10.0 * Units::nm);
    double core_length = shell_length / 2.0;
    double core_width = shell_width / 2.0;
    double core_height = shell_height / 2.0;

    Particle core(refMat::Ag, FormFactorBox(core_length, core_width, core_height));
    Particle shell(refMat::AgO2, FormFactorBox(shell_length, shell_width, shell_height));
    ParticleCoreShell coreshell(shell, core,
                                kvector_t(0.0, 0.0, (shell_height - core_height) / 2.0));
    coreshell.setRotation(RotationZ(90.0 * Units::deg));
    coreshell.rotate(RotationY(90.0 * Units::deg));
    coreshell.setPosition(kvector_t(0.0, 0.0, -layer_thickness / 2.0));

    ParticleLayout layout;
    layout.addParticle(coreshell);

    Layer vacuum_layer(refMat::Vacuum);
    Layer middle_layer(refMat::Teflon, layer_thickness);
    middle_layer.addLayout(layout);
    Layer substrate(refMat::Substrate2);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);

    return multi_layer;
}
