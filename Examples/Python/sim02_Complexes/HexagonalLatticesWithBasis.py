"""
Spheres on two hexagonal close packed layers
"""
import numpy
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with spheres on a substrate,
    forming two hexagonal close packed layers.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_3 = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_3)

    # Define form factors
    formFactor_1 = ba.FormFactorFullSphere(10.0*nm)
    formFactor_2 = ba.FormFactorFullSphere(10.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)
    particle_2 = ba.Particle(material_2, formFactor_2)
    particle_2_position = kvector_t(10.0*nm, 10.0*nm, 17.3205080757*nm)
    particle_2.setPosition(particle_2_position)

    # Define composition of particles at specific positions
    particleComposition_1 = ba.ParticleComposition()
    particleComposition_1.addParticle(particle_1)
    particleComposition_1.addParticle(particle_2)

    # Define 2D lattices
    lattice2D_1 = ba.BasicLattice2D(20.0*nm, 20.0*nm, 120.0*deg, 0.0*deg)

    # Define interference functions
    interference_1 = ba.InterferenceFunction2DLattice(lattice2D_1)
    interference_1_pdf = ba.FTDecayFunction2DCauchy(10.0*nm, 10.0*nm, 0.0*deg)
    interference_1.setDecayFunction(interference_1_pdf)

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particleComposition_1, 1.0)
    layout_1.setInterferenceFunction(interference_1)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.00288675134595)

    # Add layouts to layers
    layer_1.addLayout(layout_1)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    multiLayer_1.addLayer(layer_2)

    return multiLayer_1


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, -1.0*deg, 1.0*deg, 200, 0.0*deg,
                                     1.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    simulation = get_simulation()
    simulation.setSample(get_sample())
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='inferno', aspect='auto')
