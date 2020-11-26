"""
Simulation demo: magnetic spheres in substrate
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t

# Magnetization of the particle's material (A/m)
magnetization_particle = ba.kvector_t(0.0, 0.0, 1e7)


def get_sample():
    """
    Returns a sample with magnetic spheres in the substrate.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Substrate", 7e-06, 1.8e-07)
    magnetic_field = kvector_t(0, 0, 10000000)
    material_3 = ba.HomogeneousMaterial("Particle", 2e-05, 4e-07,
                                        magnetic_field)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_2)

    # Define form factors
    formFactor_1 = ba.FormFactorFullSphere(5.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_3, formFactor_1)
    particle_1_position = kvector_t(0.0*nm, 0.0*nm, -10.0*nm)
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

    return multiLayer_1


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, -3.0*deg, 3.0*deg, 200, 0.0*deg,
                                     6.0*deg)
    simulation.setBeamParameters(1.*angstrom, 0.5*deg, 0.0*deg)
    simulation.setBeamIntensity(1e12)

    analyzer_dir = ba.kvector_t(0.0, 0.0, -1.0)
    beampol = ba.kvector_t(0.0, 0.0, 1.0)
    simulation.setBeamPolarization(beampol)
    simulation.setAnalyzerProperties(analyzer_dir, 1.0, 0.5)

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
