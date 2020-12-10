//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/SizeDistributionModelsBuilder.cpp
//! @brief     Implements class ParticlesInSSCABuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/SizeDistributionModelsBuilder.h"
#include "Base/Const/Units.h"
#include "Param/Distrib/Distributions.h"
#include "Param/Varia/ParameterPattern.h"
#include "Sample/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleDistribution.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* SizeDistributionDAModelBuilder::buildSample() const {
    // cylindrical particle 1
    double radius1(5 * Units::nm);
    double height1 = radius1;
    FormFactorCylinder cylinder_ff1(radius1, height1);
    Particle cylinder1(refMat::Particle, cylinder_ff1);

    // cylindrical particle 2
    double radius2(8 * Units::nm);
    double height2(radius2);
    FormFactorCylinder cylinder_ff2(radius2, height2);
    Particle cylinder2(refMat::Particle, cylinder_ff2);

    // interference function
    InterferenceFunctionRadialParaCrystal interference(18.0 * Units::nm, 1e3 * Units::nm);
    FTDistribution1DGauss pdf(3 * Units::nm);
    interference.setProbabilityDistribution(pdf);

    // assembling the sample
    ParticleLayout particle_layout;
    particle_layout.addParticle(cylinder1, 0.8);
    particle_layout.addParticle(cylinder2, 0.2);
    particle_layout.setInterferenceFunction(interference);

    Layer vacuum_layer(refMat::Vacuum);
    vacuum_layer.addLayout(particle_layout);
    Layer substrate_layer(refMat::Substrate);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------

MultiLayer* SizeDistributionLMAModelBuilder::buildSample() const {
    // cylindrical particle 1
    double radius1(5 * Units::nm);
    double height1 = radius1;
    FormFactorCylinder cylinder_ff1(radius1, height1);
    Particle cylinder1(refMat::Particle, cylinder_ff1);

    // cylindrical particle 2
    double radius2(8 * Units::nm);
    double height2(radius2);
    FormFactorCylinder cylinder_ff2(radius2, height2);
    Particle cylinder2(refMat::Particle, cylinder_ff2);

    // interference function1
    InterferenceFunctionRadialParaCrystal interference1(16.8 * Units::nm, 1e3 * Units::nm);
    FTDistribution1DGauss pdf(3 * Units::nm);
    interference1.setProbabilityDistribution(pdf);

    // interference function2
    InterferenceFunctionRadialParaCrystal interference2(22.8 * Units::nm, 1e3 * Units::nm);
    interference2.setProbabilityDistribution(pdf);

    // assembling the sample
    ParticleLayout particle_layout1;
    particle_layout1.addParticle(cylinder1, 0.8);
    particle_layout1.setInterferenceFunction(interference1);

    ParticleLayout particle_layout2;
    particle_layout2.addParticle(cylinder2, 0.2);
    particle_layout2.setInterferenceFunction(interference2);

    Layer vacuum_layer(refMat::Vacuum);
    vacuum_layer.addLayout(particle_layout1);
    vacuum_layer.addLayout(particle_layout2);
    Layer substrate_layer(refMat::Substrate);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------

MultiLayer* SizeDistributionSSCAModelBuilder::buildSample() const {
    // cylindrical particle 1
    double radius1(5 * Units::nm);
    double height1 = radius1;
    FormFactorCylinder cylinder_ff1(radius1, height1);
    Particle cylinder1(refMat::Particle, cylinder_ff1);

    // cylindrical particle 2
    double radius2(8 * Units::nm);
    double height2(radius2);
    FormFactorCylinder cylinder_ff2(radius2, height2);
    Particle cylinder2(refMat::Particle, cylinder_ff2);

    // interference function
    InterferenceFunctionRadialParaCrystal interference(18.0 * Units::nm, 1e3 * Units::nm);
    FTDistribution1DGauss pdf(3 * Units::nm);
    interference.setProbabilityDistribution(pdf);
    interference.setKappa(1.0);

    // assembling the sample
    ParticleLayout particle_layout;
    particle_layout.addParticle(cylinder1, 0.8);
    particle_layout.addParticle(cylinder2, 0.2);
    particle_layout.setInterferenceFunction(interference);

    Layer vacuum_layer(refMat::Vacuum);
    vacuum_layer.addLayout(particle_layout);
    Layer substrate_layer(refMat::Substrate);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// ----------------------------------------------------------------------------

MultiLayer* CylindersInSSCABuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);

    InterferenceFunctionRadialParaCrystal interference_function(15.0 * Units::nm, 1e3 * Units::nm);
    FTDistribution1DGauss pdf(5 * Units::nm);
    interference_function.setProbabilityDistribution(pdf);
    interference_function.setKappa(4.02698);
    ParticleLayout particle_layout;

    FormFactorCylinder ff_cylinder(5.0 * Units::nm, 5.0 * Units::nm);
    Particle particle_prototype(refMat::Particle, ff_cylinder);

    DistributionGaussian gauss(5.0 * Units::nm, 1.25 * Units::nm);
    ParameterPattern pattern_radius;
    pattern_radius.add("Particle").add("Cylinder").add("Radius");
    ParameterDistribution par_distr(pattern_radius.toStdString(), gauss, 30, 3.0);
    ParameterPattern pattern_height;
    pattern_height.add("Particle").add("Cylinder").add("Height");
    par_distr.linkParameter(pattern_height.toStdString());
    ParticleDistribution particle_collection(particle_prototype, par_distr);
    particle_layout.addParticle(particle_collection);

    particle_layout.setInterferenceFunction(interference_function);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    return multi_layer;
}
