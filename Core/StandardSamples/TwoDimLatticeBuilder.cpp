// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/TwoDimLatticeBuilder.cpp
//! @brief     Implements class IsGISAXS06Builder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/TwoDimLatticeBuilder.h"
#include "Core/Aggregate/InterferenceFunction2DLattice.h"
#include "Core/Aggregate/InterferenceFunction2DSuperLattice.h"
#include "Core/Aggregate/InterferenceFunctionFinite2DLattice.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleComposition.h"

MultiLayer* Basic2DLatticeBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    std::unique_ptr<InterferenceFunction2DLattice> P_interference_function(
        new InterferenceFunction2DLattice(5.0 * Units::nanometer, 10.0 * Units::nanometer,
                                          30.0 * Units::deg, 10.0 * Units::deg));

    FTDecayFunction2DCauchy pdf(300.0 * Units::nanometer / 2.0 / M_PI,
                                100.0 * Units::nanometer / 2.0 / M_PI, 0);
    P_interference_function->setDecayFunction(pdf);

    // particles
    ParticleLayout particle_layout;
    FormFactorCylinder ff_cyl(5.0 * Units::nanometer, 5.0 * Units::nanometer);
    Particle particle(particle_material, ff_cyl);
    particle_layout.addParticle(particle, 1.0);

    particle_layout.setInterferenceFunction(*P_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

// -----------------------------------------------------------------------------
// lattice #1:
// -----------------------------------------------------------------------------
MultiLayer* SquareLatticeBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    std::unique_ptr<InterferenceFunction2DLattice> P_interference_function{
        InterferenceFunction2DLattice::createSquare(10.0 * Units::nanometer, 0)};
    FTDecayFunction2DCauchy pdf(300.0 * Units::nanometer / 2.0 / M_PI,
                                100.0 * Units::nanometer / 2.0 / M_PI, 0);
    P_interference_function->setDecayFunction(pdf);

    // particles
    ParticleLayout particle_layout;
    FormFactorCylinder ff_cyl(5.0 * Units::nanometer, 5.0 * Units::nanometer);
    Particle particle(particle_material, ff_cyl);
    particle_layout.addParticle(particle, 1.0);

    particle_layout.setInterferenceFunction(*P_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

// -----------------------------------------------------------------------------
// lattice #2: centered
// -----------------------------------------------------------------------------
MultiLayer* CenteredSquareLatticeBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction2DLattice interference_function(10.0 * Units::nanometer,
                                                        10.0 * Units::nanometer, M_PI / 2.0, 0);
    FTDecayFunction2DCauchy pdf(300.0 * Units::nanometer / 2.0 / M_PI,
                                100.0 * Units::nanometer / 2.0 / M_PI, 0);
    interference_function.setDecayFunction(pdf);

    FormFactorCylinder ff_cyl(5.0 * Units::nanometer, 5.0 * Units::nanometer);
    Particle cylinder(particle_material, ff_cyl);
    std::vector<kvector_t> positions;
    kvector_t position_1(0.0, 0.0, 0.0);
    kvector_t position_2(5.0 * Units::nanometer, -5.0 * Units::nanometer, 0.0);
    positions.push_back(position_1);
    positions.push_back(position_2);
    ParticleComposition basis;
    basis.addParticles(cylinder, positions);

    ParticleLayout particle_layout;
    particle_layout.addParticle(basis);
    particle_layout.setInterferenceFunction(interference_function);
    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

// -----------------------------------------------------------------------------
// lattice #3: rotated
// -----------------------------------------------------------------------------
MultiLayer* RotatedSquareLatticeBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    std::unique_ptr<InterferenceFunction2DLattice> P_interference_function{
        InterferenceFunction2DLattice::createSquare(10.0 * Units::nanometer, 30.0 * Units::degree)};
    FTDecayFunction2DCauchy pdf(300.0 * Units::nanometer / 2.0 / M_PI,
                                100.0 * Units::nanometer / 2.0 / M_PI, 30.0 * Units::degree);
    P_interference_function->setDecayFunction(pdf);

    ParticleLayout particle_layout;
    // particle
    FormFactorCylinder ff_cyl(5.0 * Units::nanometer, 5.0 * Units::nanometer);
    kvector_t position(0.0, 0.0, 0.0);
    Particle p(particle_material, ff_cyl);
    p.setPosition(position);
    particle_layout.addParticle(p);
    particle_layout.setInterferenceFunction(*P_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

// -----------------------------------------------------------------------------
// lattice #4: finite square
// -----------------------------------------------------------------------------
MultiLayer* FiniteSquareLatticeBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    std::unique_ptr<InterferenceFunctionFinite2DLattice> P_interference_function{
        InterferenceFunctionFinite2DLattice::createSquare(10.0 * Units::nanometer, 0.0, 40, 40)};
    P_interference_function->setPositionVariance(1.0);

    // particles
    ParticleLayout particle_layout;
    FormFactorCylinder ff_cyl(5.0 * Units::nanometer, 5.0 * Units::nanometer);
    Particle particle(particle_material, ff_cyl);
    particle_layout.addParticle(particle, 1.0);

    particle_layout.setInterferenceFunction(*P_interference_function);

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

// -----------------------------------------------------------------------------
// lattice #5: superlattice
// -----------------------------------------------------------------------------
MultiLayer* SuperLatticeBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    std::unique_ptr<InterferenceFunction2DSuperLattice> P_interference_function{
        InterferenceFunction2DSuperLattice::createSquare(200.0 * Units::nanometer, 0.0, 40, 40)};
    std::unique_ptr<InterferenceFunctionFinite2DLattice> P_substructure{
        InterferenceFunctionFinite2DLattice::createSquare(10.0 * Units::nanometer, 0.0, 10, 10)};
    P_interference_function->setSubstructureIFF(*P_substructure);
    P_interference_function->setPositionVariance(1.0);

    // particles
    ParticleLayout particle_layout;
    FormFactorCylinder ff_cyl(5.0 * Units::nanometer, 10.0 * Units::nanometer);
    Particle particle(air_material, ff_cyl);
    particle_layout.addParticle(particle, 1.0, kvector_t(0.0, 0.0, -10.0 * Units::nanometer));

    particle_layout.setInterferenceFunction(*P_interference_function);
    particle_layout.setTotalParticleSurfaceDensity(100.0 / 4e4);

    substrate_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}
