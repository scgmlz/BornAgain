// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParticleInVacuumBuilder.cpp
//! @brief     Implements class ParticleInVacuumBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/ParticleInVacuumBuilder.h"
#include "Base/Const/Units.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"
#include "Core/SampleBuilderEngine/SampleComponents.h"
#include "Core/StandardSamples/ReferenceMaterials.h"

namespace
{
FormFactorComponents ff_components;
}

ParticleInVacuumBuilder::ParticleInVacuumBuilder()
    : m_ff(new FormFactorFullSphere(5.0 * Units::nanometer))
{
}

MultiLayer* ParticleInVacuumBuilder::buildSample() const
{
    Layer vacuum_layer(refMat::Vacuum);

    Particle particle(refMat::Particle, *m_ff);
    ParticleLayout particle_layout(particle);
    vacuum_layer.addLayout(particle_layout);

    MultiLayer* result = new MultiLayer;
    result->addLayer(vacuum_layer);
    return result;
}

MultiLayer* ParticleInVacuumBuilder::createSampleByIndex(size_t index)
{
    auto name = ff_components.keys().at(index);
    m_ff.reset(ff_components.getItem(name)->clone());
    setName(name);
    return buildSample();
}

size_t ParticleInVacuumBuilder::size()
{
    return ff_components.size();
}
