//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/TwoDimLatticeBuilder.cpp
//! @brief     Implements class IsGISAXS06Builder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/StandardSamples/TwoDimLatticeBuilder.h"
#include "Base/Const/Units.h"
#include "Sample/Aggregate/InterferenceFunction2DLattice.h"
#include "Sample/Aggregate/InterferenceFunction2DSuperLattice.h"
#include "Sample/Aggregate/InterferenceFunctionFinite2DLattice.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleComposition.h"
#include "Sample/StandardSamples/ReferenceMaterials.h"

MultiLayer* Basic2DLatticeBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunction2DLattice iff(
        BasicLattice2D(5.0 * Units::nm, 10.0 * Units::nm, 30.0 * Units::deg, 10.0 * Units::deg));

    FTDecayFunction2DCauchy pdf(300.0 * Units::nm / 2.0 / M_PI, 100.0 * Units::nm / 2.0 / M_PI, 0);
    iff.setDecayFunction(pdf);

    // particles
    ParticleLayout particle_layout;
    FormFactorCylinder ff_cyl(5.0 * Units::nm, 5.0 * Units::nm);
    Particle particle(refMat::Particle, ff_cyl);
    particle_layout.addParticle(particle, 1.0);

    particle_layout.setInterferenceFunction(iff);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// -----------------------------------------------------------------------------
// lattice #1:
// -----------------------------------------------------------------------------
MultiLayer* SquareLattice2DBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunction2DLattice iff(SquareLattice2D(10.0 * Units::nm, 0));
    FTDecayFunction2DCauchy pdf(300.0 * Units::nm / 2.0 / M_PI, 100.0 * Units::nm / 2.0 / M_PI, 0);
    iff.setDecayFunction(pdf);

    // particles
    ParticleLayout particle_layout;
    FormFactorCylinder ff_cyl(5.0 * Units::nm, 5.0 * Units::nm);
    Particle particle(refMat::Particle, ff_cyl);
    particle_layout.addParticle(particle, 1.0);

    particle_layout.setInterferenceFunction(iff);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// -----------------------------------------------------------------------------
// lattice #2: centered
// -----------------------------------------------------------------------------
MultiLayer* CenteredSquareLattice2DBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunction2DLattice interference_function(
        BasicLattice2D(10.0 * Units::nm, 10.0 * Units::nm, M_PI / 2.0, 0));
    FTDecayFunction2DCauchy pdf(300.0 * Units::nm / 2.0 / M_PI, 100.0 * Units::nm / 2.0 / M_PI, 0);
    interference_function.setDecayFunction(pdf);

    FormFactorCylinder ff_cyl(5.0 * Units::nm, 5.0 * Units::nm);
    Particle cylinder(refMat::Particle, ff_cyl);
    std::vector<kvector_t> positions;
    kvector_t position_1(0.0, 0.0, 0.0);
    kvector_t position_2(5.0 * Units::nm, -5.0 * Units::nm, 0.0);
    positions.push_back(position_1);
    positions.push_back(position_2);
    ParticleComposition basis;
    basis.addParticles(cylinder, positions);

    ParticleLayout particle_layout;
    particle_layout.addParticle(basis);
    particle_layout.setInterferenceFunction(interference_function);
    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// -----------------------------------------------------------------------------
// lattice #3: rotated
// -----------------------------------------------------------------------------
MultiLayer* RotatedSquareLattice2DBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunction2DLattice iff(SquareLattice2D(10.0 * Units::nm, 30.0 * Units::deg));
    FTDecayFunction2DCauchy pdf(300.0 * Units::nm / 2.0 / M_PI, 100.0 * Units::nm / 2.0 / M_PI,
                                30.0 * Units::deg);
    iff.setDecayFunction(pdf);

    ParticleLayout particle_layout;
    // particle
    FormFactorCylinder ff_cyl(5.0 * Units::nm, 5.0 * Units::nm);
    kvector_t position(0.0, 0.0, 0.0);
    Particle p(refMat::Particle, ff_cyl);
    p.setPosition(position);
    particle_layout.addParticle(p);
    particle_layout.setInterferenceFunction(iff);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// -----------------------------------------------------------------------------
// lattice #4: finite square
// -----------------------------------------------------------------------------
MultiLayer* FiniteSquareLattice2DBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunctionFinite2DLattice iff(SquareLattice2D(10.0 * Units::nm, 0.0), 40, 40);
    iff.setPositionVariance(1.0);

    // particles
    ParticleLayout particle_layout;
    FormFactorCylinder ff_cyl(5.0 * Units::nm, 5.0 * Units::nm);
    Particle particle(refMat::Particle, ff_cyl);
    particle_layout.addParticle(particle, 1.0);

    particle_layout.setInterferenceFunction(iff);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

// -----------------------------------------------------------------------------
// lattice #5: superlattice
// -----------------------------------------------------------------------------
MultiLayer* SuperLatticeBuilder::buildSample() const {
    Layer vacuum_layer(refMat::Vacuum);
    Layer substrate_layer(refMat::Substrate);

    InterferenceFunction2DSuperLattice iff(SquareLattice2D(200.0 * Units::nm, 0.0), 40, 40);
    InterferenceFunctionFinite2DLattice substructure(SquareLattice2D(10.0 * Units::nm, 0.0), 10,
                                                     10);
    iff.setSubstructureIFF(substructure);
    iff.setPositionVariance(1.0);

    // particles
    ParticleLayout particle_layout;
    FormFactorCylinder ff_cyl(5.0 * Units::nm, 10.0 * Units::nm);
    Particle particle(refMat::Vacuum, ff_cyl);
    particle_layout.addParticle(particle, 1.0, kvector_t(0.0, 0.0, -10.0 * Units::nm));

    particle_layout.setInterferenceFunction(iff);
    particle_layout.setTotalParticleSurfaceDensity(100.0 / 4e4);

    substrate_layer.addLayout(particle_layout);

    MultiLayer* multi_layer = new MultiLayer();
    multi_layer->addLayer(vacuum_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
