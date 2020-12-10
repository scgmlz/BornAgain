//  ************************************************************************************************
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
//  ************************************************************************************************

#include "Base/Const/Units.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Device/Histo/Histogram2D.h"
#include "Device/Histo/IntensityDataIOFactory.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/HardParticle/FormFactorPrism3.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Particle.h"

int main() {
    // Define the sample
    Material vacuum_material = HomogeneousMaterial("Vacuum", 0., 0.);
    Material substrate_material = HomogeneousMaterial("Substrate", 6e-6, 2e-8);

    Layer vacuum_layer(vacuum_material);
    Layer substrate_layer(substrate_material);

    ParticleLayout particle_layout;
    Material particle_material = HomogeneousMaterial("Particle", 6e-4, 2e-8);

    Particle cylinder(particle_material, FormFactorCylinder(5 * Units::nm, 5 * Units::nm));
    particle_layout.addParticle(cylinder, 0.5);

    Particle prism(particle_material, FormFactorPrism3(10 * Units::nm, 5 * Units::nm));
    particle_layout.addParticle(prism, 0.5);

    vacuum_layer.addLayout(particle_layout);

    MultiLayer sample;
    sample.addLayer(vacuum_layer);
    sample.addLayer(substrate_layer);

    // Define the simulation
    GISASSimulation simulation;
    simulation.setDetectorParameters(400, -1.0 * Units::deg, 1.0 * Units::deg, 400,
                                     0.0 * Units::deg, 2.0 * Units::deg);
    simulation.setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    simulation.setSample(sample);

    // Run the simulation, and store the result
    simulation.runSimulation();
    auto result = simulation.result();
    IntensityDataIOFactory::writeSimulationResult(result, "result.int");
    return 0;
}
