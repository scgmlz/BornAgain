"""
Spherical particles embedded in the middle of the layer on top of substrate.
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with spherical particles in a layer
    between vacuum and substrate.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("IntermLayer", 3.45e-06, 5.24e-09)
    material_3 = ba.HomogeneousMaterial("Particle", 0.0, 0.0)
    material_4 = ba.HomogeneousMaterial("Substrate", 7.43e-06, 1.72e-07)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_2, 30.0*nm)
    layer_3 = ba.Layer(material_4)

    # Define form factors
    formFactor_1 = ba.FormFactorFullSphere(10.2*nm)

    # Define particles
    particle_1 = ba.Particle(material_3, formFactor_1)
    particle_1_position = kvector_t(0.0*nm, 0.0*nm, -25.2*nm)
    particle_1.setPosition(particle_1_position)

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particle_1, 1.0)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.01)

    # Add layouts to layers
    layer_2.addLayout(layout_1)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    multiLayer_1.addLayer(layer_2)
    multiLayer_1.addLayer(layer_3)

    return multiLayer_1


def get_simulation():
    """
    Returns a GISAXS simulation.
    """
    simulation = ba.GISASSimulation()
    simulation.setSample(get_sample())
    simulation.setDetectorParameters(200, -1*deg, +1*deg, 200, 0*deg, +2*deg)
    simulation.setBeamParameters(1.5*angstrom, 0.15*deg, 0.0*deg)
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
