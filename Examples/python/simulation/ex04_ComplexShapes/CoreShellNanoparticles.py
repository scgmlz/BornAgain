"""
Core shell nanoparticles
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Returns a sample with box-shaped core-shell particles on a substrate.
    """
    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0 )
    m_shell = ba.HomogeneousMaterial("Shell", 1e-4, 2e-8 )
    m_core = ba.HomogeneousMaterial("Core", 6e-5, 2e-8 )

    # collection of particles
    parallelepiped1_ff = ba.FormFactorBox(16*nm, 16*nm, 8*nm)
    parallelepiped2_ff = ba.FormFactorBox(12*nm, 12*nm, 7*nm)
    shell_particle = ba.Particle(m_shell, parallelepiped1_ff)
    core_particle = ba.Particle(m_core, parallelepiped2_ff)
    core_position = ba.kvector_t(0.0, 0.0, 0.0)

    particle = ba.ParticleCoreShell(shell_particle, core_particle, core_position)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(particle)
    interference = ba.InterferenceFunctionNone()
    particle_layout.setInterferenceFunction(interference)

    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)

    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, -1.0*deg, 1.0*deg,
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
