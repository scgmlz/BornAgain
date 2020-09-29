// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SlicedCompositionBuilder.cpp
//! @brief     Defines classes to build various particles crossing interfaces.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/SlicedCompositionBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorTruncatedSphere.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleComposition.h"
#include "Core/StandardSamples/ReferenceMaterials.h"

MultiLayer* SlicedCompositionBuilder::buildSample() const
{
    const double sphere_radius = 10.0;
    const double bottom_cup_height = 4.0;
    const double composition_shift = bottom_cup_height;

    Particle topCup(refMat::Ag, FormFactorTruncatedSphere(
                                    sphere_radius, sphere_radius * 2 - bottom_cup_height, 0));
    Particle bottomCup(refMat::Teflon,
                       FormFactorTruncatedSphere(sphere_radius, bottom_cup_height, 0));
    bottomCup.setRotation(RotationX(180 * Units::deg));

    ParticleComposition composition;
    composition.addParticle(topCup, kvector_t(0.0, 0.0, bottom_cup_height));
    composition.addParticle(bottomCup, kvector_t(0.0, 0.0, bottom_cup_height));
    composition.setPosition(0, 0, -composition_shift);

    ParticleLayout particle_layout;
    particle_layout.addParticle(composition);

    Layer vacuum_layer(refMat::Vacuum);
    vacuum_layer.addLayout(particle_layout);

    Layer substrate_layer(refMat::Substrate2);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
