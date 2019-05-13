"""
Simulation demo: magnetic spheres in substrate
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


# Magnetization of the particle's material (A/m)
magnetization_particle = ba.kvector_t(0.0, 0.0, 1e7)


def get_sample():
    """
    Returns a sample with magnetic spheres in the substrate.
    """
    # defining materials
    particle_material = ba.HomogeneousMaterial("Particle", 2e-5, 4e-7,
                                               magnetization_particle)
    air_material = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    substrate_material = ba.HomogeneousMaterial("Substrate", 7e-6, 1.8e-7)

    # spherical magnetic particle
    sphere_ff = ba.FormFactorFullSphere(5*nm)
    sphere = ba.Particle(particle_material, sphere_ff)
    position = ba.kvector_t(0.0, 0.0, -10.0*nm)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(sphere, 1.0, position)

    # defining layers
    air_layer = ba.Layer(air_material)
    substrate_layer = ba.Layer(substrate_material)
    substrate_layer.addLayout(particle_layout)

    # defining the multilayer
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, -3.0*deg, 3.0*deg, 200, 0.0*deg, 6.0*deg)
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
    ba.mpl_settings()
    ba.plot_simulation_result(result)
