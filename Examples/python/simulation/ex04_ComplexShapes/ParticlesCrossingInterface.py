"""
This example demonstrates new experimental feature of release-1.8.0:
particles can now cross interfaces.

Given example is similar to simulation/ex01_BasicParticles/CylindersAndPrisms.py,
with the difference, that z-position of particles is adjusted to move them slightly
down from air layer and to make them cross substrate/air interface.

Note:
1) Simulation kernel automatically detects particles crossing interface and
adjusts calculations accordingly.

2) Particle crossing interface requires more time to simulate.

3) Crossing of interface is possible only for limited number of geometries.
For example, X or Y rotated particles can not yet cross interfaces (exception
will be thrown when trying to simulate such geometries).
"""
import bornagain as ba
from bornagain import deg, angstrom, nm

phi_min, phi_max = -1.0, 1.0
alpha_min, alpha_max = 0.0, 2.0


def get_sample():
    """
    Returns a sample with uncorrelated cylinders and prisms on a substrate.
    """
    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    shift_down = 3*nm

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(5*nm, 5*nm)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    cylinder.setPosition(0, 0, -shift_down)

    prism_ff = ba.FormFactorPrism3(10*nm, 5*nm)
    prism = ba.Particle(m_particle, prism_ff)
    prism.setPosition(0, 0, -shift_down)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 0.5)
    particle_layout.addParticle(prism, 0.5)
    interference = ba.InterferenceFunctionNone()
    particle_layout.setInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    print(multi_layer.treeToString())
    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, phi_min*deg, phi_max*deg,
                                     100, alpha_min*deg, alpha_max*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def run_simulation():
    """
    Runs simulation and returns resulting intensity map.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.mpl_settings()
    ba.plot_simulation_result(result)
