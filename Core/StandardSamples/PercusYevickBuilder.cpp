// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/PercusYevickBuilder.cpp
//! @brief     Implements class PercusYevickBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/PercusYevickBuilder.h"
#include "Base/Const/Units.h"
#include "Core/Aggregate/InterferenceFunctionHardDisk.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"
#include "Core/StandardSamples/ReferenceMaterials.h"

MultiLayer* HardDiskBuilder::buildSample() const
{
    const double m_cylinder_height(5 * Units::nanometer);
    const double m_cylinder_radius(5 * Units::nanometer);
    const double m_disk_radius(5 * Units::nanometer);
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
