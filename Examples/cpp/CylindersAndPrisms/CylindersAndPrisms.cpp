// ********************************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Examples/cpp/CylindersAndPrisms/CylindersAndPrisms.cpp
//! @brief     Demonstrates how to run a BornAgain simulation from a C++ main program.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, C. Durniak, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ********************************************************************************************** //

#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/HardParticle/FormFactorPrism3.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Intensity/Histogram2D.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Particle/Particle.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/Simulation.h"

int main()
{
    // Define the sample
    Material air_material = HomogeneousMaterial("Air", 0., 0.);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    ParticleLayout particle_layout;
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Particle cylinder(particle_material,
                      FormFactorCylinder(5 * Units::nanometer, 5 * Units::nanometer));
    particle_layout.addParticle(cylinder, 0.5);

    Particle prism(particle_material,
                   FormFactorPrism3(10 * Units::nanometer, 5 * Units::nanometer));
    particle_layout.addParticle(prism, 0.5);

    air_layer.addLayout(particle_layout);

    MultiLayer sample;
    sample.addLayer(air_layer);
    sample.addLayer(substrate_layer);

    // Define the simulation
    GISASSimulation simulation;
    simulation.setDetectorParameters(400, -1.0 * Units::degree, 1.0 * Units::degree, 400,
                                     0.0 * Units::degree, 2.0 * Units::degree);
    simulation.setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::degree, 0.0 * Units::degree);
    simulation.setSample(sample);

    // Run the simulation, and store the result
    simulation.runSimulation();
    auto result = simulation.result();
    IntensityDataIOFactory::writeSimulationResult(result, "result.int");
    return 0;
}
