// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParticleInTheAirBuilder.cpp
//! @brief     Implements class ParticleInTheAirBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/ParticleInTheAirBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/Units.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"
#include "Core/StandardSamples/SampleComponents.h"
#include "Core/includeIncludes/FormFactors.h"

ParticleInTheAirBuilder::ParticleInTheAirBuilder()
    : m_ff(new FormFactorFullSphere(5.0 * Units::nanometer))
{
}

ParticleInTheAirBuilder::~ParticleInTheAirBuilder() = default;

MultiLayer* ParticleInTheAirBuilder::buildSample() const
{
    MultiLayer* result = new MultiLayer;

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    Particle particle(particle_material, *m_ff);
    ParticleLayout particle_layout(particle);
    air_layer.addLayout(particle_layout);

    result->addLayer(air_layer);

    return result;
}

MultiLayer* ParticleInTheAirBuilder::createSample(size_t index)
{
    if (index >= size())
        throw std::runtime_error("ParticleInTheAirBuilder::createSample() -> Error. "
                                 "Sample index is out of range.");

    auto ff_names = ff_components().keys();
    m_ff.reset(ff_components().getItem(ff_names[index])->clone());

    setName(ff_names[index]);

    return buildSample();
}

size_t ParticleInTheAirBuilder::size()
{
    return ff_components().size();
}

FormFactorComponents& ParticleInTheAirBuilder::ff_components()
{
    static FormFactorComponents result = {};
    return result;
}
