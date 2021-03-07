#!/usr/bin/env python3
"""
Rotated pyramids on top of substrate
"""
import bornagain as ba
from bornagain import deg, nm


def get_sample():
    """
    Returns a sample with rotated pyramids on top of a substrate.
    """

    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0, 0)

    # Define form factors
    ff = ba.FormFactorPyramid(10*nm, 5*nm, 54.73*deg)

    # Define particles
    particle = ba.Particle(material_Particle, ff)
    particle_rotation = ba.RotationZ(45*deg)
    particle.setRotation(particle_rotation)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle, 1)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer_1 = ba.Layer(material_Vacuum)
    layer_1.addLayout(layout)
    layer_2 = ba.Layer(material_Substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)

    return sample


def get_simulation(sample):
    beam = ba.Beam(1, 0.1*nm, ba.Direction(0.2*deg, 0*deg))
    detector = ba.SphericalDetector(200, -2*deg, 2*deg, 200, 0*deg, 2*deg)
    simulation = ba.GISASSimulation(beam, sample, detector)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
