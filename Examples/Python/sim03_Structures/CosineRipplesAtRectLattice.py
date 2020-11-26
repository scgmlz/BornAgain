"""
Cosine ripple on a 2D lattice
"""
import numpy
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with cosine ripples on a substrate.
    The structure is modelled as a 2D Lattice.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_3 = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_3)

    # Define form factors
    formFactor_1 = ba.FormFactorCosineRippleBox(100.0*nm, 20.0*nm, 4.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)

    # Define 2D lattices
    lattice2D_1 = ba.BasicLattice2D(200.0*nm, 50.0*nm, 90.0*deg, 0.0*deg)

    # Define interference functions
    interference_1 = ba.InterferenceFunction2DLattice(lattice2D_1)
    interference_1_pdf = ba.FTDecayFunction2DCauchy(160.0*nm, 16.0*nm, 0.0*deg)
    interference_1.setDecayFunction(interference_1_pdf)

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particle_1, 1.0)
    layout_1.setInterferenceFunction(interference_1)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.0001)

    # Add layouts to layers
    layer_1.addLayout(layout_1)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    multiLayer_1.addLayer(layer_2)

    return multiLayer_1


def get_simulation():
    """
    characterizing the input beam and output detector
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.5*deg, 1.5*deg, 100, 0.0*deg,
                                     2.5*deg)
    simulation.setBeamParameters(1.6*angstrom, 0.3*deg, 0.0*deg)
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
