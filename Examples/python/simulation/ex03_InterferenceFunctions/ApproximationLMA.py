"""
Cylinders of two different sizes in Local Monodisperse Approximation
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Returns a sample with cylinders of two different sizes on a substrate.
    The cylinder positions are modelled in Local Monodisperse Approximation.
    """
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # cylindrical particle 1
    radius1 = 5*nm
    height1 = radius1
    cylinder_ff1 = ba.FormFactorCylinder(radius1, height1)
    cylinder1 = ba.Particle(m_particle, cylinder_ff1)

    # cylindrical particle 2
    radius2 = 8*nm
    height2 = radius2
    cylinder_ff2 = ba.FormFactorCylinder(radius2, height2)
    cylinder2 = ba.Particle(m_particle, cylinder_ff2)

    # interference function1
    interference1 = ba.InterferenceFunctionRadialParaCrystal(
        16.8*nm, 1e3*nm)
    pdf = ba.FTDistribution1DGauss(3 * nm)
    interference1.setProbabilityDistribution(pdf)

    # interference function2
    interference2 = ba.InterferenceFunctionRadialParaCrystal(
        22.8*nm, 1e3*nm)
    interference2.setProbabilityDistribution(pdf)

    # assembling the sample
    particle_layout1 = ba.ParticleLayout()
    particle_layout1.addParticle(cylinder1, 0.8)
    particle_layout1.setInterferenceFunction(interference1)

    particle_layout2 = ba.ParticleLayout()
    particle_layout2.addParticle(cylinder2, 0.2)
    particle_layout2.setInterferenceFunction(interference2)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout1)
    air_layer.addLayout(particle_layout2)
    substrate_layer = ba.Layer(m_substrate)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
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
