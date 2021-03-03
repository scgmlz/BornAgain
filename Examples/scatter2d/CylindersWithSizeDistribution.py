#!/usr/bin/env python3
"""
Cylinders with size distribution
"""
import bornagain as ba
from bornagain import deg, nm


def get_sample():
    """
    Return a sample with cylinders on a substrate.
    The cylinders have a Gaussian size distribution.
    """

    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff = ba.FormFactorCylinder(5.0*nm, 5.0*nm)

    # Define particles
    particle = ba.Particle(material_Particle, ff)

    # Define particles with parameter following a distribution
    distr_1 = ba.DistributionGaussian(5.0*nm, 1.0*nm)
    par_distr_1 = ba.ParameterDistribution("/Particle/Cylinder/Radius", distr_1,
                                           100, 2.0)
    particle_distrib = ba.ParticleDistribution(particle, par_distr_1)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle_distrib, 1.0)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer = ba.Layer(material_Vacuum)
    layer.addLayout(layout)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer)

    return sample


def get_simulation(sample):
    beam = ba.Beam(1.0, 0.1*nm, ba.Direction(0.2*deg, 0*deg))
    detector = ba.SphericalDetector(200, 2*deg, 1*deg, 1*deg)
    simulation = ba.GISASSimulation(beam, sample, detector)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
