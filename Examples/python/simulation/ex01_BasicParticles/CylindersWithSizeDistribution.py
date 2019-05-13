"""
Cylinders with size distribution
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Return a sample with cylinders on a substrate.
    The cylinders have a Gaussian size distribution.
    """
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # cylindrical particle
    radius = 5*nm
    height = radius
    cylinder_ff = ba.FormFactorCylinder(radius, height)
    cylinder = ba.Particle(m_particle, cylinder_ff)

    # collection of particles with size distribution
    nparticles = 100
    sigma = 0.2*radius

    gauss_distr = ba.DistributionGaussian(radius, sigma)

    sigma_factor = 2.0
    par_distr = ba.ParameterDistribution(
        "/Particle/Cylinder/Radius", gauss_distr, nparticles, sigma_factor)
    # by uncommenting the line below, the height of the cylinders
    #   can be scaled proportionally to the radius:
    # par_distr.linkParameter("/Particle/Cylinder/Height")
    part_coll = ba.ParticleDistribution(cylinder, par_distr)

    # assembling the sample
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(part_coll)

    air_layer = ba.Layer(m_ambience)
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
