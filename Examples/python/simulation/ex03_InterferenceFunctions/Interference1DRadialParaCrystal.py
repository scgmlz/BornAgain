"""
radial paracrystal
"""
import bornagain as ba
from bornagain import deg, angstrom, nm

phi_min, phi_max = -2.0, 2.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Returns a sample with cylinders on a substrate that form a radial paracrystal.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(5*nm, 5*nm)
    cylinder = ba.Particle(m_particle, cylinder_ff)

    interference = ba.InterferenceFunctionRadialParaCrystal(
        20.0*nm, 1e3*nm)
    pdf = ba.FTDistribution1DGauss(7 * nm)
    interference.setProbabilityDistribution(pdf)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)
    particle_layout.setInterferenceFunction(interference)

    # assembling the sample
    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    # print(multi_layer.treeToString())
    return multi_layer


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, -2.0*deg, 2.0*deg,
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
