// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParticleDistributionsBuilder.cpp
//! @brief     Implements classes of with different types of particle distributions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleDistributionsBuilder.h"
#include "BornAgainNamespace.h"
#include "Distributions.h"
#include "FormFactorCylinder.h"
#include "HomogeneousMaterial.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "ParameterPattern.h"
#include "Particle.h"
#include "ParticleDistribution.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"

CylindersWithSizeDistributionBuilder::CylindersWithSizeDistributionBuilder()
    : m_height(5*Units::nanometer)
    , m_radius(5*Units::nanometer)
{
    init_parameters();
}


void CylindersWithSizeDistributionBuilder::init_parameters()
{
    registerParameter(BornAgain::Radius, &m_radius).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
}


MultiLayer* CylindersWithSizeDistributionBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    ParticleLayout particle_layout;
    // preparing prototype of nano particle
    double sigma = 0.2*m_radius;
    FormFactorCylinder p_ff_cylinder( m_radius, m_height);
    Particle nano_particle(particle_material, p_ff_cylinder);
    // radius of nanoparticles will be sampled with gaussian probability
    int n_samples(100);
    // to get radius_min = average - 2.0*FWHM:
    double n_sigma = 2.0*2.0*std::sqrt(2.0*std::log(2.0));
    DistributionGaussian gauss(m_radius, sigma);
    ParameterPattern pattern;
    pattern.add(BornAgain::ParticleType).add(BornAgain::FFCylinderType).add(BornAgain::Radius);
    ParameterDistribution par_distr(pattern.toStdString(), gauss, n_samples, n_sigma);
    ParticleDistribution particle_collection(nano_particle, par_distr);
    particle_layout.addParticle(particle_collection);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);

    return multi_layer;
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------

TwoTypesCylindersDistributionBuilder::TwoTypesCylindersDistributionBuilder()
    : m_radius1(5*Units::nanometer)
    , m_radius2(10*Units::nanometer)
    , m_height1(5*Units::nanometer)
    , m_height2(10*Units::nanometer)
    , m_sigma1_ratio(0.2)
    , m_sigma2_ratio(0.02)
{
    init_parameters();
}


void TwoTypesCylindersDistributionBuilder::init_parameters()
{
    registerParameter("radius1", &m_radius1).setUnit("nm").setNonnegative();
    registerParameter("radius2", &m_radius2).setUnit("nm").setNonnegative();
    registerParameter("height1", &m_height1).setUnit("nm").setNonnegative();
    registerParameter("height2", &m_height2).setUnit("nm").setNonnegative();
    registerParameter("sigma1_ratio", &m_sigma1_ratio).setNonnegative();
    registerParameter("sigma2_ratio", &m_sigma2_ratio).setNonnegative();
}


MultiLayer* TwoTypesCylindersDistributionBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);

    ParticleLayout particle_layout;

    // preparing nano particles prototypes for seeding layer's particle_layout
    FormFactorCylinder p_ff_cylinder1(m_radius1, m_height1);
    Particle cylinder1(particle_material, p_ff_cylinder1 );

    FormFactorCylinder p_ff_cylinder2(m_radius2, m_height2);
    Particle cylinder2(particle_material, p_ff_cylinder2 );

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins=150;
    double sigma1 = m_radius1*m_sigma1_ratio;
    double sigma2 = m_radius2*m_sigma2_ratio;
    // to have xmin=average-3*sigma
    double n_sigma = 3.0;
    DistributionGaussian gauss1(m_radius1, sigma1);
    DistributionGaussian gauss2(m_radius2, sigma2);

    // building distribution of nano particles
    ParameterPattern pattern1;
    pattern1.add(BornAgain::ParticleType).add(BornAgain::FFCylinderType).add(BornAgain::Radius);
    ParameterDistribution par_distr1(pattern1.toStdString(), gauss1, nbins, n_sigma);
    ParticleDistribution particle_collection1(cylinder1, par_distr1);
    particle_layout.addParticle(particle_collection1, 0.95);
    ParameterPattern pattern2;
    pattern2.add(BornAgain::ParticleType).add(BornAgain::FFCylinderType).add(BornAgain::Radius);
    ParameterDistribution par_distr2(pattern2.toStdString(), gauss2, nbins, n_sigma);
    ParticleDistribution particle_collection2(cylinder2, par_distr2);
    particle_layout.addParticle(particle_collection2, 0.05);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);

    return multi_layer;
}
