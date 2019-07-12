"""
Simple example demonstrating how polarized SANS experiments can be
simulated with BornAgain.
"""

import bornagain as ba
from bornagain import deg, nm, kvector_t

# Magnetization of the particle's core material (A/m)
magnetization_core = kvector_t(0.0, 0.0, 1e7)


def get_sample():
    """
    Returns a sample with a magnetic core-shell particle in a solvent.
    """
    # Defining Materials
    mat_solvent = ba.HomogeneousMaterial("Solvent", 5e-6, 0.0)
    mat_core = ba.HomogeneousMaterial("Core", 6e-6, 2e-8,
                                      magnetization_core)
    mat_shell = ba.HomogeneousMaterial("Shell", 1e-7, 2e-8)

    # Defining Layer
    solvent_layer = ba.Layer(mat_solvent)

    # Defining particle layout with a core-shell particle
    layout = ba.ParticleLayout()
    core_sphere_ff = ba.FormFactorFullSphere(10*nm)
    shell_sphere_ff = ba.FormFactorFullSphere(12*nm)
    core = ba.Particle(mat_core, core_sphere_ff)
    shell = ba.Particle(mat_shell, shell_sphere_ff)
    position = kvector_t(0.0, 0.0, 2.0)
    particleCoreShell = ba.ParticleCoreShell(shell, core, position)
    layout.addParticle(particleCoreShell)

    # Adding layout to layer
    solvent_layer.addLayout(layout)

    # Defining Multilayer with single layer
    multiLayer = ba.MultiLayer()
    multiLayer.addLayer(solvent_layer)
    return multiLayer


def get_simulation():
    """
    Returns a polarized SANS simulation
    """
    simulation = ba.GISASSimulation()

    # Defining detector
    simulation.setDetectorParameters(200, -3.0*deg, 3.0*deg, 200, -3.0*deg, 3.0*deg)

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
    ba.plot_simulation_result(result, cmap='jet', units=ba.AxesUnits.QSPACE,
                              aspect='auto')
