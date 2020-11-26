"""
Cylinder form factor in DWBA with beam divergence
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with uncorrelated cylinders on a substrate.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_3 = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_3)

    # Define form factors
    formFactor_1 = ba.FormFactorCylinder(5.0*nm, 5.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particle_1, 1.0)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.01)

    # Add layouts to layers
    layer_1.addLayout(layout_1)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    multiLayer_1.addLayer(layer_2)

    return multiLayer_1


def get_simulation():
    """
    Returns a GISAXS simulation with beam (+ divergence) and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, 0.0*deg, 2.0*deg, 100, 0.0*deg,
                                     2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    wavelength_distr = ba.DistributionLogNormal(1.0*angstrom, 0.1)
    alpha_distr = ba.DistributionGaussian(0.2*deg, 0.1*deg)
    phi_distr = ba.DistributionGaussian(0.0*deg, 0.1*deg)
    simulation.addParameterDistribution("*/Beam/Wavelength", wavelength_distr,
                                        5)
    simulation.addParameterDistribution("*/Beam/InclinationAngle", alpha_distr,
                                        5)
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
    ba.plot_simulation_result(result, cmap='inferno', aspect='auto')
