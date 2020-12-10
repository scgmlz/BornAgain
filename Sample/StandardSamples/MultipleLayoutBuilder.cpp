//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/MultipleLayoutBuilder.cpp
//! @brief     Implements class MultipleLayoutBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/MultipleLayoutBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/HardParticle/FormFactorPrism3.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* MultipleLayoutBuilder::buildSample() const {
    const double cylinder_height(5 * Units::nm);
    const double cylinder_radius(5 * Units::nm);
    const double prisheight(5 * Units::nm);
    const double prislength(10 * Units::nm);
    const double cylinder_weight(0.5);

    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    ParticleLayout particle_layout_1;
    ParticleLayout particle_layout_2;

    FormFactorCylinder ff_cylinder(cylinder_radius, cylinder_height);
    Particle cylinder(refMat::Particle, ff_cylinder);

    FormFactorPrism3 ff_prism3(prislength, prisheight);
    Particle prism3(refMat::Particle, ff_prism3);

    particle_layout_1.addParticle(cylinder, cylinder_weight);
    particle_layout_2.addParticle(prism3, 1.0 - cylinder_weight);

    vacuum_layer.addLayout(particle_layout_1);
    vacuum_layer.addLayout(particle_layout_2);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
