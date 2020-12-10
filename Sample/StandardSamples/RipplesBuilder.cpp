//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/RipplesBuilder.cpp
//! @brief     Implement classes to build various ripples.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/RipplesBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCosineRipple.h"
#include "Sample/HardParticle/FormFactorSawtoothRipple.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* CosineRippleBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    FormFactorCosineRippleBox ff_ripple1(100.0, 20.0, 4.0);
    Particle ripple(refMat::Particle, ff_ripple1);

    ParticleLayout particle_layout;
    particle_layout.addParticle(ripple, 1.0);
    InterferenceFunctionRadialParaCrystal interference_function(20.0, 1e7);
    FTDistribution1DGauss pdf(4.0);
    interference_function.setProbabilityDistribution(pdf);
    particle_layout.setInterferenceFunction(interference_function);

    vacuum_layer.addLayout(particle_layout);

    Layer substrate_layer(refMat::Substrate);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------

TriangularRippleBuilder::TriangularRippleBuilder() : m_d(0.0 * Units::nm) {
    registerParameter("asymmetry", &m_d);
}

MultiLayer* TriangularRippleBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    FormFactorSawtoothRippleBox ff_ripple2(100.0, 20.0, 4.0, m_d);
    Particle ripple(refMat::Particle, ff_ripple2);

    ParticleLayout particle_layout;
    particle_layout.addParticle(ripple, 1.0);
    InterferenceFunctionRadialParaCrystal interference_function(20.0, 1e7);
    FTDistribution1DGauss pdf(4.0);
    interference_function.setProbabilityDistribution(pdf);
    particle_layout.setInterferenceFunction(interference_function);

    vacuum_layer.addLayout(particle_layout);
    Layer substrate_layer(refMat::Substrate);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------

MultiLayer* AsymRippleBuilder::buildSample() const {
    TriangularRippleBuilder builder;
    builder.setParameterValue("asymmetry", -3.0);
    return builder.buildSample();
}
