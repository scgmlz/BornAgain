#!/usr/bin/env python3
"""
Basic example of a DWBA simulation of a GISAS experiment:
Scattering by a dilute random assembly of cylinders on a substrate.
"""
import bornagain as ba
from bornagain import deg, nm


def get_sample():
    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0, 0)

    # Define particles
    ff = ba.FormFactorCylinder(5*nm, 5*nm)
    particle = ba.Particle(material_Particle, ff)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle)
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
    # Define beam
    wavelength = 0.1*nm
    alpha_i = 0.2*deg
    beam = ba.Beam(1, wavelength, ba.Direction(alpha_i, 0))

    # Define detector
    nPix = 200  # pixels per direction
    detector = ba.SphericalDetector(nPix, -2*deg, 2*deg, nPix, 0, 3*deg)

    return ba.GISASSimulation(beam, sample, detector)


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
