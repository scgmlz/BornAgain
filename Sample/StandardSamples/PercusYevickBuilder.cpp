//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/PercusYevickBuilder.cpp
//! @brief     Implements class PercusYevickBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/PercusYevickBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/InterferenceFunctionHardDisk.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* HardDiskBuilder::buildSample() const {
    const double m_cylinder_height(5 * Units::nm);
    const double m_cylinder_radius(5 * Units::nm);
    const double m_disk_radius(5 * Units::nm);
    const double m_density(0.006);

    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);
    Particle particle(refMat::Particle, ff_cylinder);
    ParticleLayout particle_layout(particle);

    InterferenceFunctionHardDisk interference_function(m_disk_radius, m_density);
    particle_layout.setInterferenceFunction(interference_function);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
