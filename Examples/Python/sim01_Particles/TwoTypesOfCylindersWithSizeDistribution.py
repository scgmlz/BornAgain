"""
Mixture cylinder particles with different size distribution
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Returns a sample with cylinders in a homogeneous medium ("Vacuum").
    The cylinders are a 95:5 mixture of two different size distributions.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)

    # Define form factors
    formFactor_1 = ba.FormFactorCylinder(5.0*nm, 5.0*nm)
    formFactor_2 = ba.FormFactorCylinder(10.0*nm, 10.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)
    particle_2 = ba.Particle(material_2, formFactor_2)

    # Define particles with parameter following a distribution
    distr_1 = ba.DistributionGaussian(5.0*nm, 1.0*nm)
    par_distr_1 = ba.ParameterDistribution("/Particle/Cylinder/Radius",
                                           distr_1, 150, 3.0,
                                           ba.RealLimits.nonnegative())
    particleDistribution_1 = ba.ParticleDistribution(particle_1, par_distr_1)
    distr_2 = ba.DistributionGaussian(10.0*nm, 0.2*nm)
    par_distr_2 = ba.ParameterDistribution("/Particle/Cylinder/Radius",
                                           distr_2, 150, 3.0,
                                           ba.RealLimits.nonnegative())
    particleDistribution_2 = ba.ParticleDistribution(particle_2, par_distr_2)

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particleDistribution_1, 0.95)
    layout_1.addParticle(particleDistribution_2, 0.05)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.01)

    # Add layouts to layers
    layer_1.addLayout(layout_1)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    return multiLayer_1


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, 0.0*deg, 2.0*deg, 200, 0.0*deg,
                                     2.0*deg)
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
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
