//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/ParticleDistributionsBuilder.cpp
//! @brief     Implements classes of with different types of particle distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/ParticleDistributionsBuilder.h"
#include "Base/Const/Units.h"
#include "Param/Distrib/Distributions.h"
#include "Param/Varia/ParameterPattern.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorBox.h"
#include "Sample/HardParticle/FormFactorCone.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/HardParticle/FormFactorFullSphere.h"
#include "Sample/HardParticle/FormFactorPyramid.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleDistribution.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* CylindersWithSizeDistributionBuilder::buildSample() const {
    const double height(5 * Units::nm);
    const double radius(5 * Units::nm);

    Layer vacuum_layer(refMat::Vacuum);

    ParticleLayout particle_layout;
    // preparing prototype of nano particle
    double sigma = 0.2 * radius;
    FormFactorCylinder p_ff_cylinder(radius, height);
    Particle nano_particle(refMat::Particle, p_ff_cylinder);
    // radius of nanoparticles will be sampled with gaussian probability
    int n_samples(100);
    // to get radius_min = average - 2.0*FWHM:
    double n_sigma = 2.0 * 2.0 * std::sqrt(2.0 * std::log(2.0));
    DistributionGaussian gauss(radius, sigma);
    ParameterPattern pattern;
    pattern.add("Particle").add("Cylinder").add("Radius");
    ParameterDistribution par_distr(pattern.toStdString(), gauss, static_cast<size_t>(n_samples),
                                    n_sigma);
    ParticleDistribution particle_collection(nano_particle, par_distr);
    particle_layout.addParticle(particle_collection);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------

TwoTypesCylindersDistributionBuilder::TwoTypesCylindersDistributionBuilder()
    : m_radius1(5 * Units::nm)
    , m_radius2(10 * Units::nm)
    , m_height1(5 * Units::nm)
    , m_height2(10 * Units::nm)
    , m_sigma1_ratio(0.2)
    , m_sigma2_ratio(0.02) {}

MultiLayer* TwoTypesCylindersDistributionBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);

    ParticleLayout particle_layout;

    // preparing nano particles prototypes for seeding layer's particle_layout
    FormFactorCylinder p_ff_cylinder1(m_radius1, m_height1);
    Particle cylinder1(refMat::Particle, p_ff_cylinder1);

    FormFactorCylinder p_ff_cylinder2(m_radius2, m_height2);
    Particle cylinder2(refMat::Particle, p_ff_cylinder2);

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins = 150;
    double sigma1 = m_radius1 * m_sigma1_ratio;
    double sigma2 = m_radius2 * m_sigma2_ratio;
    // to have xmin=average-3*sigma
    double n_sigma = 3.0;
    DistributionGaussian gauss1(m_radius1, sigma1);
    DistributionGaussian gauss2(m_radius2, sigma2);

    // building distribution of nano particles
    ParameterPattern pattern1;
    pattern1.add("Particle").add("Cylinder").add("Radius");
    ParameterDistribution par_distr1(pattern1.toStdString(), gauss1, nbins, n_sigma);
    ParticleDistribution particle_collection1(cylinder1, par_distr1);
    particle_layout.addParticle(particle_collection1, 0.95);
    ParameterPattern pattern2;
    pattern2.add("Particle").add("Cylinder").add("Radius");
    ParameterDistribution par_distr2(pattern2.toStdString(), gauss2, static_cast<size_t>(nbins),
                                     n_sigma);
    ParticleDistribution particle_collection2(cylinder2, par_distr2);
    particle_layout.addParticle(particle_collection2, 0.05);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------

RotatedPyramidsDistributionBuilder::RotatedPyramidsDistributionBuilder()
    : m_length(10 * Units::nm)
    , m_height(5 * Units::nm)
    , m_alpha(Units::deg2rad(54.73))
    , m_zangle(45. * Units::deg) {}

MultiLayer* RotatedPyramidsDistributionBuilder::buildSample() const {
    // particle
    FormFactorPyramid ff_pyramid(m_length, m_height, m_alpha);
    Particle pyramid(refMat::Particle, ff_pyramid);
    pyramid.setRotation(RotationZ(m_zangle));

    // particle collection
    DistributionGate gate(35.0 * Units::deg, 55.0 * Units::deg);
    ParameterDistribution parameter_distr("/Particle/ZRotation/Angle", gate, 10, 2.0);

    ParticleDistribution collection(pyramid, parameter_distr);

    ParticleLayout particle_layout;
    particle_layout.addParticle(collection);

    // Multi layer
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------

MultiLayer* SpheresWithLimitsDistributionBuilder::buildSample() const {
    // particle
    FormFactorFullSphere ff(3.0 * Units::nm);
    Particle sphere(refMat::Particle, ff);

    // particle collection
    DistributionGaussian gauss(3.0 * Units::nm, 1.0 * Units::nm);
    ParameterDistribution parameter_distr("/Particle/FullSphere/Radius", gauss, 10, 20.0,
                                          RealLimits::limited(2.0, 4.0));

    ParticleDistribution collection(sphere, parameter_distr);

    ParticleLayout particle_layout;
    particle_layout.addParticle(collection);

    // Multi layer
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

// ----------------------------------------------------------------------------

MultiLayer* ConesWithLimitsDistributionBuilder::buildSample() const {
    // particle
    FormFactorCone ff(10.0 * Units::nm, 13.0 * Units::nm, 60.0 * Units::deg);
    Particle cone(refMat::Particle, ff);

    // particle collection
    DistributionGaussian gauss(60.0 * Units::deg, 6.0 * Units::deg);
    ParameterDistribution parameter_distr(
        "/Particle/Cone/Alpha", gauss, 5, 20.0,
        RealLimits::limited(55.0 * Units::deg, 65.0 * Units::deg));

    ParticleDistribution collection(cone, parameter_distr);

    ParticleLayout particle_layout;
    particle_layout.addParticle(collection);

    // Multi layer
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

MultiLayer* LinkedBoxDistributionBuilder::buildSample() const {
    // particle
    FormFactorBox ff(40.0 * Units::nm, 30.0 * Units::nm, 10.0 * Units::nm);
    Particle box(refMat::Particle, ff);

    // particle collection
    DistributionGate gate(10.0 * Units::nm, 70.0 * Units::nm);
    ParameterDistribution parameter_distr("/Particle/Box/Length", gate, 3, 0.0,
                                          RealLimits::limited(1.0 * Units::nm, 200.0 * Units::nm));
    parameter_distr.linkParameter("/Particle/Box/Width").linkParameter("/Particle/Box/Height");

    ParticleDistribution collection(box, parameter_distr);

    ParticleLayout particle_layout;
    particle_layout.addParticle(collection);
    particle_layout.setTotalParticleSurfaceDensity(1e-4);

    // Multi layer
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
