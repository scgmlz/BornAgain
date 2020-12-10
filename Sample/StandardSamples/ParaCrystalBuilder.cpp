//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/ParaCrystalBuilder.cpp
//! @brief     Implements class ParaCrystalBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/ParaCrystalBuilder.h"
#include "Base/Const/Units.h"
#include "Base/Utils/Assert.h"
#include "Sample/Aggregate/InterferenceFunction2DParaCrystal.h"
#include "Sample/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/SampleBuilderEngine/SampleComponents.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* RadialParaCrystalBuilder::buildSample() const {
    const double m_corr_peak_distance(20.0 * Units::nm);
    const double m_corr_width(7 * Units::nm);
    const double m_corr_length(1e3 * Units::nm);
    const double m_cylinder_height(5 * Units::nm);
    const double m_cylinder_radius(5 * Units::nm);

    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunctionRadialParaCrystal iff(m_corr_peak_distance, m_corr_length);
    FTDistribution1DGauss pdf(m_corr_width);
    iff.setProbabilityDistribution(pdf);
    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    Particle particle(refMat::Particle, ff_cylinder);
    ParticleLayout particle_layout(particle);
    particle_layout.setInterferenceFunction(iff);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// -----------------------------------------------------------------------------
// Basic2DParaCrystalBuilder
// -----------------------------------------------------------------------------

Basic2DParaCrystalBuilder::Basic2DParaCrystalBuilder()
    : m_pdf1(new FTDistribution2DCauchy(0.1 * Units::nm, 0.2 * Units::nm, 0))
    , m_pdf2(new FTDistribution2DCauchy(0.3 * Units::nm, 0.4 * Units::nm, 0)) {}

Basic2DParaCrystalBuilder::~Basic2DParaCrystalBuilder() = default;

MultiLayer* Basic2DParaCrystalBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunction2DParaCrystal iff(
        BasicLattice2D(10.0 * Units::nm, 20.0 * Units::nm, 30.0 * Units::deg, 45.0 * Units::deg),
        1000.0 * Units::nm, 20.0 * Units::micrometer, 40.0 * Units::micrometer);

    iff.setProbabilityDistributions(*m_pdf1, *m_pdf2);

    FormFactorCylinder ff_cylinder(5.0 * Units::nm, 5.0 * Units::nm);

    Particle particle(refMat::Particle, ff_cylinder);
    ParticleLayout particle_layout(particle);
    particle_layout.setInterferenceFunction(iff);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

MultiLayer* Basic2DParaCrystalBuilder::createSampleByIndex(size_t index) {
    ASSERT(index < FTDistribution2DComponents().size());

    auto names = FTDistribution2DComponents().keys();
    m_pdf2.reset(FTDistribution2DComponents().getItem(names.at(index))->clone());

    setName(names.at(index));

    return buildSample();
}

// -----------------------------------------------------------------------------
// HexParaCrystalBuilder
// -----------------------------------------------------------------------------

MultiLayer* HexParaCrystalBuilder::buildSample() const {
    const double m_peak_distance(20.0 * Units::nm);
    const double m_corr_length(0.0);
    const double m_domain_size_1(20.0 * Units::micrometer);
    const double m_domain_size_2(20.0 * Units::micrometer);
    const double m_cylinder_height(5 * Units::nm);
    const double m_cylinder_radius(5 * Units::nm);

    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunction2DParaCrystal iff(HexagonalLattice2D(m_peak_distance, 0.0), m_corr_length,
                                          m_domain_size_1, m_domain_size_2);
    iff.setIntegrationOverXi(true);
    FTDistribution2DCauchy pdf(1.0 * Units::nm, 1.0 * Units::nm, 0);
    iff.setProbabilityDistributions(pdf, pdf);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);
    Particle cylinder(refMat::Particle, ff_cylinder);

    ParticleLayout particle_layout(cylinder);
    particle_layout.setInterferenceFunction(iff);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// -----------------------------------------------------------------------------
// RectParaCrystalBuilder
// -----------------------------------------------------------------------------

MultiLayer* RectParaCrystalBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunction2DParaCrystal iff(SquareLattice2D(10 * Units::nm), 0, 0, 0);
    iff.setIntegrationOverXi(true);
    iff.setDomainSizes(20.0 * Units::micrometer, 20.0 * Units::micrometer);
    FTDistribution2DCauchy pdf1(0.5 * Units::nm, 2.0 * Units::nm, 0);
    FTDistribution2DCauchy pdf2(0.5 * Units::nm, 2.0 * Units::nm, 0);
    iff.setProbabilityDistributions(pdf1, pdf2);

    FormFactorCylinder ff_cylinder(5.0 * Units::nm, 5.0 * Units::nm);

    Particle particle(refMat::Particle, ff_cylinder);
    ParticleLayout particle_layout(particle);
    particle_layout.setInterferenceFunction(iff);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
