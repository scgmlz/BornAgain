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
    magnetic_field = kvector_t(0, 0, 10000000)
    material_Core = ba.HomogeneousMaterial("Core", 6e-06, 2e-08, magnetic_field)
    material_Shell = ba.HomogeneousMaterial("Shell", 1e-07, 2e-08)
    material_Solvent = ba.HomogeneousMaterial("Solvent", 5e-06, 0.0)

    # Define form factors
    ff_1 = ba.FormFactorFullSphere(10.0*nm)
    ff_2 = ba.FormFactorFullSphere(12.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_Core, ff_1)
    particle_1_position = kvector_t(0.0*nm, 0.0*nm, 2.0*nm)
    particle_1.setPosition(particle_1_position)
    particle_2 = ba.Particle(material_Shell, ff_2)

    # Define core shell particles
    particle_3 = ba.ParticleCoreShell(particle_2, particle_1)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle_3, 1.0)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer = ba.Layer(material_Solvent)
    layer.addLayout(layout)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer)

    return sample


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
    simulation.beam().setIntensity(1e12)

    # Defining beam polarization and polarization analysis for spin-flip channel
    analyzer_dir = kvector_t(0.0, 0.0, -1.0)
    beampol = kvector_t(0.0, 0.0, 1.0)
    simulation.beam().setPolarization(beampol)
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
