// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SlicedParticleBuilder.cpp
//! @brief     Defines classes to build various particles crossing interfaces.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/SlicedParticleBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/HardParticle/FormFactorTruncatedSphere.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleComposition.h"
#include "Core/Vector/Transform3D.h"

MultiLayer* SlicedCompositionBuilder::buildSample() const
{
    MultiLayer* p_multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 3.212e-6, 3.244e-8);
    Material topCupMaterial = HomogeneousMaterial("Ag", 1.245e-5, 5.419e-7);
    Material bottomCupMaterial = HomogeneousMaterial("Teflon", 2.900e-6, 6.019e-9);

    const double sphere_radius = 10.0;
    const double bottom_cup_height = 4.0;
    const double composition_shift = bottom_cup_height;

    Particle topCup(topCupMaterial, FormFactorTruncatedSphere(
                                        sphere_radius, sphere_radius * 2 - bottom_cup_height, 0));
    Particle bottomCup(bottomCupMaterial,
                       FormFactorTruncatedSphere(sphere_radius, bottom_cup_height, 0));
    bottomCup.setRotation(RotationX(180 * Units::deg));

    ParticleComposition composition;
    composition.addParticle(topCup, kvector_t(0.0, 0.0, bottom_cup_height));
    composition.addParticle(bottomCup, kvector_t(0.0, 0.0, bottom_cup_height));
    composition.setPosition(0, 0, -composition_shift);

    ParticleLayout particle_layout;
    particle_layout.addParticle(composition);

    Layer air_layer(air_material);
    air_layer.addLayout(particle_layout);

    Layer substrate_layer(substrate_material);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}
