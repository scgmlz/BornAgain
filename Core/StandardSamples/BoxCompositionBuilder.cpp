// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/BoxCompositionBuilder.cpp
//! @brief     Implements class BoxCompositionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/BoxCompositionBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorBox.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleComposition.h"

BoxCompositionBuilder::BoxCompositionBuilder()
    : m_particleMaterial(HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7)),
      m_layer_thickness(100.0 * Units::nanometer), m_length(50.0 * Units::nanometer),
      m_width(20.0 * Units::nanometer), m_height(10.0 * Units::nanometer)
{
}

BoxCompositionBuilder::~BoxCompositionBuilder() {}

MultiLayer* BoxCompositionBuilder::createMultiLayer(const ParticleComposition& composition) const
{
    Material mAmbience = HomogeneousMaterial("Air", 0.0, 0.0);
    Material mMiddle = HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9);
    Material mSubstrate = HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8);

    ParticleLayout layout;
    layout.addParticle(composition);

    Layer air_layer(mAmbience);
    Layer middle_layer(mMiddle, m_layer_thickness);
    middle_layer.addLayout(layout);
    Layer substrate(mSubstrate);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);
    return multi_layer;
}

// --- BoxCompositionRotateXBuilder ---

MultiLayer* BoxCompositionRotateXBuilder::buildSample() const
{
    Particle box(m_particleMaterial, FormFactorBox(m_length / 2.0, m_width, m_height));
    ParticleComposition composition;
    composition.addParticle(box, kvector_t(0.0, 0.0, 0.0));
    composition.addParticle(box, kvector_t(m_length / 2.0, 0.0, 0.0));
    composition.setRotation(RotationX(90.0 * Units::degree));
    composition.setPosition(kvector_t(0.0, 0.0, -m_layer_thickness / 2.0));
    return createMultiLayer(composition);
}

// --- BoxCompositionRotateYBuilder ---

MultiLayer* BoxCompositionRotateYBuilder::buildSample() const
{
    Particle box(m_particleMaterial, FormFactorBox(m_length / 2.0, m_width, m_height));
    ParticleComposition composition;
    composition.addParticle(box, kvector_t(0.0, 0.0, 0.0));
    composition.addParticle(box, kvector_t(m_length / 2.0, 0.0, 0.0));
    composition.setRotation(RotationY(90.0 * Units::degree));
    composition.setPosition(kvector_t(0.0, 0.0, -m_layer_thickness / 2.0 + m_length / 4.0));
    return createMultiLayer(composition);
}

// --- BoxCompositionRotateZBuilder ---

MultiLayer* BoxCompositionRotateZBuilder::buildSample() const
{
    Particle box(m_particleMaterial, FormFactorBox(m_length / 2.0, m_width, m_height));
    ParticleComposition composition;
    composition.addParticle(box, kvector_t(0.0, 0.0, 0.0));
    composition.addParticle(box, kvector_t(m_length / 2.0, 0.0, 0.0));
    composition.setRotation(RotationZ(90.0 * Units::degree));
    composition.setPosition(kvector_t(0.0, 0.0, -m_layer_thickness / 2.0 - m_height / 2.0));
    return createMultiLayer(composition);
}

// --- BoxCompositionRotateZandYBuilder ---

MultiLayer* BoxCompositionRotateZandYBuilder::buildSample() const
{
    Particle box(m_particleMaterial, FormFactorBox(m_length / 2.0, m_width, m_height));
    ParticleComposition composition;
    composition.addParticle(box, kvector_t(0.0, 0.0, 0.0));
    composition.addParticle(box, kvector_t(m_length / 2.0, 0.0, 0.0));
    composition.setRotation(RotationZ(90.0 * Units::degree));
    composition.rotate(RotationY(90.0 * Units::degree));
    composition.setPosition(kvector_t(0.0, 0.0, -m_layer_thickness / 2.0));
    return createMultiLayer(composition);
}

// --- BoxStackCompositionBuilder ---

// Composition of two boxes which gives you the box (10,20,50) with reference point as usual.
MultiLayer* BoxStackCompositionBuilder::buildSample() const
{
    ParticleComposition composition;

    // box1 (20,50,5), rotatedZ
    const double box1_length = 20;
    const double box1_width = 50;
    const double box1_height = 5;
    Particle box1(m_particleMaterial, FormFactorBox(box1_length, box1_width, box1_height));
    box1.setRotation(RotationZ(90. * Units::degree));

    // box2 (5,20,50), rotatedY
    const double box2_length = 5.0;
    const double box2_width = 20.0;
    const double box2_height = 50.0;
    Particle box2(m_particleMaterial, FormFactorBox(box2_length, box2_width, box2_height));
    box2.setRotation(RotationY(90. * Units::degree));
    box2.setPosition(kvector_t(-box2_height / 2.0, 0.0, box2_length / 2.0));

    composition.addParticle(box1, kvector_t(0.0, 0.0, 0.0));
    composition.addParticle(box2, kvector_t(0.0, 0.0, box1_height));
    composition.setRotation(RotationY(90.0 * Units::degree));
    composition.setPosition(kvector_t(0.0, 0.0, -m_layer_thickness / 2.));

    return createMultiLayer(composition);
}
