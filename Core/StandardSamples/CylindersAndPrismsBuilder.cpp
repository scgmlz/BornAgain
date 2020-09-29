// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CylindersAndPrismsBuilder.cpp
//! @brief     Implements class CylindersAndPrismsBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/CylindersAndPrismsBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/HardParticle/FormFactorPrism3.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"
#include "Core/StandardSamples/ReferenceMaterials.h"

MultiLayer* CylindersAndPrismsBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    ParticleLayout particle_layout;

    FormFactorCylinder ff_cylinder(5.0, 5.0);
    Particle cylinder(refMat::Particle, ff_cylinder);

    FormFactorPrism3 ff_prism3(10.0, 5.0);
    Particle prism3(refMat::Particle, ff_prism3);

    particle_layout.addParticle(cylinder, 0.5);
    particle_layout.addParticle(prism3, 0.5);

    vacuum_layer.addLayout(particle_layout);

    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
