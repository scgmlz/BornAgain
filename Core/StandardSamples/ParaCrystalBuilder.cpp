// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParaCrystalBuilder.cpp
//! @brief     Implements class ParaCrystalBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/ParaCrystalBuilder.h"
#include "Core/Aggregate/InterferenceFunction2DParaCrystal.h"
#include "Core/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Assert.h"
#include "Core/Basics/Units.h"
#include "Core/Correlations/FTDistributions2D.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"
#include "Core/StandardSamples/SampleComponents.h"

RadialParaCrystalBuilder::RadialParaCrystalBuilder()
    : m_corr_peak_distance(20.0 * Units::nanometer), m_corr_width(7 * Units::nanometer),
      m_corr_length(1e3 * Units::nanometer), m_cylinder_height(5 * Units::nanometer),
      m_cylinder_radius(5 * Units::nanometer)
{
}

MultiLayer* RadialParaCrystalBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunctionRadialParaCrystal interference_function(m_corr_peak_distance,
                                                                m_corr_length);
    FTDistribution1DGauss pdf(m_corr_width);
    interference_function.setProbabilityDistribution(pdf);
    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);
    particle_layout.setInterferenceFunction(interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

// -----------------------------------------------------------------------------
// Basic2DParaCrystalBuilder
// -----------------------------------------------------------------------------

Basic2DParaCrystalBuilder::Basic2DParaCrystalBuilder()
    : m_pdf1(new FTDistribution2DCauchy(0.1 * Units::nanometer, 0.2 * Units::nanometer, 0)),
      m_pdf2(new FTDistribution2DCauchy(0.3 * Units::nanometer, 0.4 * Units::nanometer, 0))
{
}

Basic2DParaCrystalBuilder::~Basic2DParaCrystalBuilder() = default;

MultiLayer* Basic2DParaCrystalBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction2DParaCrystal interference_function(
        10.0 * Units::nanometer, 20.0 * Units::nanometer, 30.0 * Units::degree,
        45.0 * Units::degree, 1000.0 * Units::nanometer);

    interference_function.setDomainSizes(20.0 * Units::micrometer, 40.0 * Units::micrometer);

    interference_function.setProbabilityDistributions(*m_pdf1, *m_pdf2);

    FormFactorCylinder ff_cylinder(5.0 * Units::nanometer, 5.0 * Units::nanometer);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);
    particle_layout.setInterferenceFunction(interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

MultiLayer* Basic2DParaCrystalBuilder::createSample(size_t index)
{
    ASSERT(index < FTDistribution2DComponents().size());

    auto names = FTDistribution2DComponents().keys();
    m_pdf2.reset(FTDistribution2DComponents().getItem(names[index])->clone());

    setName(names[index]);

    return buildSample();
}

// -----------------------------------------------------------------------------
// HexParaCrystalBuilder
// -----------------------------------------------------------------------------

HexParaCrystalBuilder::HexParaCrystalBuilder()
    : m_peak_distance(20.0 * Units::nanometer), m_corr_length(0.0),
      m_domain_size_1(20.0 * Units::micrometer), m_domain_size_2(20.0 * Units::micrometer),
      m_cylinder_height(5 * Units::nanometer), m_cylinder_radius(5 * Units::nanometer)
{
}

MultiLayer* HexParaCrystalBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    std::unique_ptr<InterferenceFunction2DParaCrystal> P_interference_function{
        InterferenceFunction2DParaCrystal::createHexagonal(m_peak_distance, m_corr_length,
                                                           m_domain_size_1, m_domain_size_2)};
    FTDistribution2DCauchy pdf(1.0 * Units::nanometer, 1.0 * Units::nanometer, 0);
    P_interference_function->setProbabilityDistributions(pdf, pdf);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);
    Particle cylinder(particle_material, ff_cylinder);

    ParticleLayout particle_layout(cylinder);
    particle_layout.setInterferenceFunction(*P_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

// -----------------------------------------------------------------------------
// RectParaCrystalBuilder
// -----------------------------------------------------------------------------

MultiLayer* RectParaCrystalBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    std::unique_ptr<InterferenceFunction2DParaCrystal> P_interference_function{
        InterferenceFunction2DParaCrystal::createSquare(10 * Units::nanometer, 0 * Units::nanometer,
                                                        0, 0)};

    P_interference_function->setDomainSizes(20.0 * Units::micrometer, 20.0 * Units::micrometer);
    FTDistribution2DCauchy pdf1(0.5 * Units::nanometer, 2.0 * Units::nanometer, 0);
    FTDistribution2DCauchy pdf2(0.5 * Units::nanometer, 2.0 * Units::nanometer, 0);
    P_interference_function->setProbabilityDistributions(pdf1, pdf2);

    FormFactorCylinder ff_cylinder(5.0 * Units::nanometer, 5.0 * Units::nanometer);

    Particle particle(particle_material, ff_cylinder);
    ParticleLayout particle_layout(particle);
    particle_layout.setInterferenceFunction(*P_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
