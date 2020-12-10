//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/BoxCompositionBuilder.cpp
//! @brief     Implements class BoxCompositionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/BoxCompositionBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorBox.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleComposition.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

namespace {

const Material particleMaterial = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7);
const double layer_thickness = 100.0 * Units::nm;
const double length = 50.0 * Units::nm;
const double width = 20.0 * Units::nm;
const double height = 10.0 * Units::nm;

MultiLayer* finalizeMultiLayer(const ParticleComposition& composition) {
    ParticleLayout layout;
    layout.addParticle(composition);

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

} // namespace

// --- BoxCompositionRotateXBuilder ---

MultiLayer* BoxCompositionRotateXBuilder::buildSample() const {
    Particle box(particleMaterial, FormFactorBox(length / 2.0, width, height));
    ParticleComposition composition;
    composition.addParticle(box, kvector_t(0.0, 0.0, 0.0));
    composition.addParticle(box, kvector_t(length / 2.0, 0.0, 0.0));
    composition.setRotation(RotationX(90.0 * Units::deg));
    composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness / 2.0));
    return finalizeMultiLayer(composition);
}

// --- BoxCompositionRotateYBuilder ---

MultiLayer* BoxCompositionRotateYBuilder::buildSample() const {
    Particle box(particleMaterial, FormFactorBox(length / 2.0, width, height));
    ParticleComposition composition;
    composition.addParticle(box, kvector_t(0.0, 0.0, 0.0));
    composition.addParticle(box, kvector_t(length / 2.0, 0.0, 0.0));
    composition.setRotation(RotationY(90.0 * Units::deg));
    composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness / 2.0 + length / 4.0));
    return finalizeMultiLayer(composition);
}

// --- BoxCompositionRotateZBuilder ---

MultiLayer* BoxCompositionRotateZBuilder::buildSample() const {
    Particle box(particleMaterial, FormFactorBox(length / 2.0, width, height));
    ParticleComposition composition;
    composition.addParticle(box, kvector_t(0.0, 0.0, 0.0));
    composition.addParticle(box, kvector_t(length / 2.0, 0.0, 0.0));
    composition.setRotation(RotationZ(90.0 * Units::deg));
    composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness / 2.0 - height / 2.0));
    return finalizeMultiLayer(composition);
}

// --- BoxCompositionRotateZandYBuilder ---

MultiLayer* BoxCompositionRotateZandYBuilder::buildSample() const {
    Particle box(particleMaterial, FormFactorBox(length / 2.0, width, height));
    ParticleComposition composition;
    composition.addParticle(box, kvector_t(0.0, 0.0, 0.0));
    composition.addParticle(box, kvector_t(length / 2.0, 0.0, 0.0));
    composition.setRotation(RotationZ(90.0 * Units::deg));
    composition.rotate(RotationY(90.0 * Units::deg));
    composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness / 2.0));
    return finalizeMultiLayer(composition);
}

// --- BoxStackCompositionBuilder ---

// Composition of two boxes which gives you the box (10,20,50) with reference point as usual.
MultiLayer* BoxStackCompositionBuilder::buildSample() const {
    ParticleComposition composition;

    // box1 (20,50,5), rotatedZ
    const double box1_length = 20;
    const double box1_width = 50;
    const double box1_height = 5;
    Particle box1(particleMaterial, FormFactorBox(box1_length, box1_width, box1_height));
    box1.setRotation(RotationZ(90. * Units::deg));

    // box2 (5,20,50), rotatedY
    const double box2_length = 5.0;
    const double box2_width = 20.0;
    const double box2_height = 50.0;
    Particle box2(particleMaterial, FormFactorBox(box2_length, box2_width, box2_height));
    box2.setRotation(RotationY(90. * Units::deg));
    box2.setPosition(kvector_t(-box2_height / 2.0, 0.0, box2_length / 2.0));

    composition.addParticle(box1, kvector_t(0.0, 0.0, 0.0));
    composition.addParticle(box2, kvector_t(0.0, 0.0, box1_height));
    composition.setRotation(RotationY(90.0 * Units::deg));
    composition.setPosition(kvector_t(0.0, 0.0, -layer_thickness / 2.));

    return finalizeMultiLayer(composition);
}
