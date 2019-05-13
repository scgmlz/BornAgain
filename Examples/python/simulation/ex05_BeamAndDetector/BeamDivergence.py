"""
Cylinder form factor in DWBA with beam divergence
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Returns a sample with uncorrelated cylinders on a substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(5*nm, 5*nm)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    # assembling the sample
    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam (+ divergence) and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, 0.0*deg, 2.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    wavelength_distr = ba.DistributionLogNormal(1.0*angstrom, 0.1)
    alpha_distr = ba.DistributionGaussian(0.2*deg, 0.1*deg)
    phi_distr = ba.DistributionGaussian(0.0*deg, 0.1*deg)
    simulation.addParameterDistribution("*/Beam/Wavelength", wavelength_distr, 5)
    simulation.addParameterDistribution("*/Beam/InclinationAngle", alpha_distr, 5)
    simulation.addParameterDistribution("*/Beam/AzimuthalAngle", phi_distr, 5)
    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    simulation = get_simulation()
    simulation.setSample(get_sample())
    print(simulation.treeToString())
    print(simulation.parametersToString())
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.mpl_settings()
    ba.plot_simulation_result(result)
