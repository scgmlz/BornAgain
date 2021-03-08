#!/usr/bin/env python3
"""
Spherical particles embedded in the middle of the layer on top of substrate.
"""
import bornagain as ba
from bornagain import deg, nm, kvector_t


def get_sample():
    """
    Returns a sample with spherical particles in a layer
    between vacuum and substrate.
    """

    # Define materials
    material_IntermLayer = ba.HomogeneousMaterial("IntermLayer", 3.45e-06,
                                                  5.24e-09)
    material_Particle = ba.HomogeneousMaterial("Particle", 0, 0)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 7.43e-06,
                                                1.72e-07)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0, 0)

    # Define form factors
    ff = ba.FormFactorFullSphere(10.2*nm)

    # Define particles
    particle = ba.Particle(material_Particle, ff)
    particle_position = kvector_t(0, 0, -25.2*nm)
    particle.setPosition(particle_position)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle, 1)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer_1 = ba.Layer(material_Vacuum)
    layer_2 = ba.Layer(material_IntermLayer, 30*nm)
    layer_2.addLayout(layout)
    layer_3 = ba.Layer(material_Substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)
    sample.addLayer(layer_3)

    return sample


def get_simulation(sample):
    beam = ba.Beam(1, 0.15*nm, ba.Direction(0.15*deg, 0))
    detector = ba.SphericalDetector(200, 2*deg, 0, 1*deg)
    simulation = ba.GISASSimulation(beam, sample, detector)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
