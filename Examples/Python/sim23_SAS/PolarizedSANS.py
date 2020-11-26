"""
Simple example demonstrating how polarized SANS experiments can be
simulated with BornAgain.
"""

import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t

# Magnetization of the particle's core material (A/m)
magnetization_core = kvector_t(0.0, 0.0, 1e7)


def get_sample():
    """
    Returns a sample with a magnetic core-shell particle in a solvent.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Solvent", 5e-06, 0.0)
    magnetic_field = kvector_t(0, 0, 10000000)
    material_2 = ba.HomogeneousMaterial("Core", 6e-06, 2e-08, magnetic_field)
    material_3 = ba.HomogeneousMaterial("Shell", 1e-07, 2e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)

    # Define form factors
    formFactor_1 = ba.FormFactorFullSphere(10.0*nm)
    formFactor_2 = ba.FormFactorFullSphere(12.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)
    particle_1_position = kvector_t(0.0*nm, 0.0*nm, 2.0*nm)
    particle_1.setPosition(particle_1_position)
    particle_2 = ba.Particle(material_3, formFactor_2)

    # Define core shell particles

    particleCoreShell_1 = ba.ParticleCoreShell(particle_2, particle_1)

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particleCoreShell_1, 1.0)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.01)

    # Add layouts to layers
    layer_1.addLayout(layout_1)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)

    return multiLayer_1


def get_simulation():
    """
    Returns a polarized SANS simulation
    """
    simulation = ba.GISASSimulation()

    # Defining detector
    simulation.setDetectorParameters(200, -3.0*deg, 3.0*deg, 200, -3.0*deg,
                                     3.0*deg)

    # Defining beam parameters
    simulation.setBeamParameters(0.5*nm, 0.0*deg, 0.0*deg)
    simulation.setBeamIntensity(1e12)

    # Defining beam polarization and polarization analysis for spin-flip channel
    analyzer_dir = kvector_t(0.0, 0.0, -1.0)
    beampol = kvector_t(0.0, 0.0, 1.0)
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
    ba.plot_simulation_result(result,
                              cmap='jet',
                              units=ba.Axes.QSPACE,
                              aspect='auto')
