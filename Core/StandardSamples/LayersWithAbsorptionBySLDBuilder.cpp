// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/LayersWithAbsorptionBySLDBuilder.cpp
//! @brief     Implements class LayersWithAbsorptionBySLDBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/LayersWithAbsorptionBySLDBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"
#include "Core/includeIncludes/FormFactors.h"

const double middle_layer_thickness(60.0 * Units::nanometer);

LayersWithAbsorptionBySLDBuilder::LayersWithAbsorptionBySLDBuilder() {}

LayersWithAbsorptionBySLDBuilder::~LayersWithAbsorptionBySLDBuilder() = default;

MultiLayer* LayersWithAbsorptionBySLDBuilder::buildSample() const
{
    Material ambience_mat = MaterialBySLD("Air", 0.0, 0.0);
    Material middle_mat = MaterialBySLD("Teflon", 4.7573e-6, 1.6724e-12);
    Material substrate_mat = MaterialBySLD("Substrate", 2.0728e-06, 2.3747e-11);
    Material particle_mat = MaterialBySLD("Ag", 3.4682e-06, 1.0309e-08);

    FormFactorFullSphere ff(5.0 * Units::nanometer);

    Particle particle(particle_mat, ff);
    particle.setRotation(RotationZ(10.0 * Units::degree));
    particle.rotate(RotationY(10.0 * Units::degree));
    particle.rotate(RotationX(10.0 * Units::degree));
    particle.setPosition(kvector_t(0.0, 0.0, -middle_layer_thickness / 2.0));

    ParticleLayout layout;
    layout.addParticle(particle);

    Layer air_layer(ambience_mat);
    Layer middle_layer(middle_mat, middle_layer_thickness);
    Layer substrate(substrate_mat);

    middle_layer.addLayout(layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(middle_layer);
    multi_layer->addLayer(substrate);
    return multi_layer;
}
