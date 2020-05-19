// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/RipplesBuilder.cpp
//! @brief     Implement classes to build various ripples.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RipplesBuilder.h"
#include "BornAgainNamespace.h"
#include "FormFactorRipple1.h"
#include "FormFactorRipple2.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

CosineRippleBuilder::CosineRippleBuilder() {}

MultiLayer* CosineRippleBuilder::buildSample() const
{
    MultiLayer* p_multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    FormFactorRipple1Box ff_ripple1(100.0, 20.0, 4.0);
    Particle ripple(particle_material, ff_ripple1);

    ParticleLayout particle_layout;
    particle_layout.addParticle(ripple, 1.0);
    InterferenceFunctionRadialParaCrystal interference_function(20.0, 1e7);
    FTDistribution1DGauss pdf(4.0);
    interference_function.setProbabilityDistribution(pdf);
    particle_layout.setInterferenceFunction(interference_function);

    air_layer.addLayout(particle_layout);

    p_multi_layer->addLayer(air_layer);

    Layer substrate_layer(substrate_material);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}

// ----------------------------------------------------------------------------

TriangularRippleBuilder::TriangularRippleBuilder() : m_d(0.0 * Units::nanometer)
{
    init_parameters();
}

MultiLayer* TriangularRippleBuilder::buildSample() const
{
    MultiLayer* p_multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    FormFactorRipple2 ff_ripple2(100.0, 20.0, 4.0, m_d);
    Particle ripple(particle_material, ff_ripple2);

    ParticleLayout particle_layout;
    particle_layout.addParticle(ripple, 1.0);
    InterferenceFunctionRadialParaCrystal interference_function(20.0, 1e7);
    FTDistribution1DGauss pdf(4.0);
    interference_function.setProbabilityDistribution(pdf);
    particle_layout.setInterferenceFunction(interference_function);

    air_layer.addLayout(particle_layout);

    p_multi_layer->addLayer(air_layer);

    Layer substrate_layer(substrate_material);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}

void TriangularRippleBuilder::init_parameters()
{
    registerParameter("asymetry", &m_d);
}

// ----------------------------------------------------------------------------

MultiLayer* AsymRippleBuilder::buildSample() const
{
    TriangularRippleBuilder builder;
    builder.setParameterValue("asymetry", -3.0);
    return builder.buildSample();
}
