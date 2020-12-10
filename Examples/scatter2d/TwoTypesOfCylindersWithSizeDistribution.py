"""
Mixture cylinder particles with different size distribution
"""
import numpy, sys
import bornagain as ba
from bornagain import angstrom, deg, micrometer, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with cylinders in a homogeneous medium ("Vacuum").
    The cylinders are a 95:5 mixture of two different size distributions.
    """

    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff_1 = ba.FormFactorCylinder(5.0*nm, 5.0*nm)
    ff_2 = ba.FormFactorCylinder(10.0*nm, 10.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_Particle, ff_1)
    particle_2 = ba.Particle(material_Particle, ff_2)

    # Define particles with parameter following a distribution
    distr_1 = ba.DistributionGaussian(5.0*nm, 1.0*nm)
    par_distr_1 = ba.ParameterDistribution("/Particle/Cylinder/Radius",
                                           distr_1, 150, 3.0,
                                           ba.RealLimits.nonnegative())
    particle_distrib_1 = ba.ParticleDistribution(particle_1, par_distr_1)
    distr_2 = ba.DistributionGaussian(10.0*nm, 0.2*nm)
    par_distr_2 = ba.ParameterDistribution("/Particle/Cylinder/Radius",
                                           distr_2, 150, 3.0,
                                           ba.RealLimits.nonnegative())
    particle_distrib_2 = ba.ParticleDistribution(particle_2, par_distr_2)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle_distrib_1, 0.95)
    layout.addParticle(particle_distrib_2, 0.05)
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
