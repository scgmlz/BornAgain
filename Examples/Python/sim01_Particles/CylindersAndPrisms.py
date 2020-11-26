"""
Mixture of cylinders and prisms without interference
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Returns a sample with uncorrelated cylinders and prisms on a substrate.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_3 = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_3)

    # Define form factors
    formFactor_1 = ba.FormFactorCylinder(5.0*nm, 5.0*nm)
    formFactor_2 = ba.FormFactorPrism3(10.0*nm, 5.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)
    particle_2 = ba.Particle(material_2, formFactor_2)

    # Define interference functions
    interference_1 = ba.InterferenceFunctionNone()

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particle_1, 0.5)
    layout_1.addParticle(particle_2, 0.5)
    layout_1.setInterferenceFunction(interference_1)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.01)

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
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg, 100, 0.0*deg,
                                     2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def run_simulation():
    """
    Runs simulation and returns resulting intensity map.
    """
    simulation = get_simulation()
    simulation.setSample(get_sample())
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
