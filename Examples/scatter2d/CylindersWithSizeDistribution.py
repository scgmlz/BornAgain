"""
Cylinders with size distribution
"""
import numpy, sys
import bornagain as ba
from bornagain import angstrom, deg, micrometer, nm, nm2, kvector_t


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


def get_simulation():
    beam = ba.Beam(1.0, 0.1*nm, ba.Direction(0.2*deg, 0.0*deg))
    nbin = 200
    detector = ba.SphericalDetector(nbin, 2.0*deg, 1.0*deg, 1.0*deg)

    simulation = ba.GISASSimulation(beam, get_sample(), detector)
    return simulation


def run_simulation():
    simulation = get_simulation()
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, *sys.argv[1:])
