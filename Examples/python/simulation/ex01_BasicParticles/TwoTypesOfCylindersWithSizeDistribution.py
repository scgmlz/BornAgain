"""
Mixture cylinder particles with different size distribution
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Returns a sample with cylinders in a homogeneous medium ("air").
    The cylinders are a 95:5 mixture of two different size distributions.
    """
    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles #1
    radius1 = 5.0*nm
    height1 = radius1
    sigma1 = radius1*0.2

    cylinder_ff1 = ba.FormFactorCylinder(radius1, height1)
    cylinder1 = ba.Particle(m_particle, cylinder_ff1)

    gauss_distr1 = ba.DistributionGaussian(radius1, sigma1)

    nparticles = 150
    sigma_factor = 3.0

    # limits will assure, that generated Radius'es are >=0
    limits = ba.RealLimits.nonnegative()

    par_distr1 = ba.ParameterDistribution(
        "/Particle/Cylinder/Radius", gauss_distr1, nparticles, sigma_factor, limits)
    part_coll1 = ba.ParticleDistribution(cylinder1, par_distr1)

    # collection of particles #2
    radius2 = 10.0*nm
    height2 = radius2
    sigma2 = radius2*0.02

    cylinder_ff2 = ba.FormFactorCylinder(radius2, height2)
    cylinder2 = ba.Particle(m_particle, cylinder_ff2)

    gauss_distr2 = ba.DistributionGaussian(radius2, sigma2)

    par_distr2 = ba.ParameterDistribution(
        "/Particle/Cylinder/Radius", gauss_distr2, nparticles, sigma_factor, limits)
    part_coll2 = ba.ParticleDistribution(cylinder2, par_distr2)

    # assembling the sample
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(part_coll1, 0.95)
    particle_layout.addParticle(part_coll2, 0.05)

    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, 0.0*deg, 2.0*deg,
                                     200, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
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
    ba.mpl_settings()
    ba.plot_simulation_result(result)
