"""
Core shell nanoparticles
"""
import numpy, sys
import bornagain as ba
from bornagain import angstrom, deg, micrometer, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with box-shaped core-shell particles on a substrate.
    """

    # Define materials
    material_Core = ba.HomogeneousMaterial("Core", 6e-05, 2e-08)
    material_Shell = ba.HomogeneousMaterial("Shell", 0.0001, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff_1 = ba.FormFactorBox(12.0*nm, 12.0*nm, 7.0*nm)
    ff_2 = ba.FormFactorBox(16.0*nm, 16.0*nm, 8.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_Core, ff_1)
    particle_2 = ba.Particle(material_Shell, ff_2)

    # Define core shell particles
    particle_3 = ba.ParticleCoreShell(particle_2, particle_1)

    # Define interference functions
    iff = ba.InterferenceFunctionNone()

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle_3, 1.0)
    layout.setInterferenceFunction(iff)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer = ba.Layer(material_Vacuum)
    layer.addLayout(layout)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer)

    return sample


def get_simulation():
    beam = ba.Beam(1.0, 0.1*nm, ba.Direction(0.2*deg, 0.0*deg))
    nbin = 200
    detector = ba.SphericalDetector(nbin, 2.0*deg, 0.0*deg, 1.0*deg)

    simulation = ba.GISASSimulation(beam, get_sample(), detector)
    return simulation


def run_simulation():
    simulation = get_simulation()
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
