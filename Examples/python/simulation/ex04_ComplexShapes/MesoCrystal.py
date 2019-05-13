"""
Cylindrical mesocrystal on a substrate
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Returns a sample with a cylindrically shaped mesocrystal on a substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # mesocrystal lattice
    lattice_basis_1 = ba.kvector_t(5.0, 0.0, 0.0)
    lattice_basis_2 = ba.kvector_t(0.0, 5.0, 0.0)
    lattice_basis_3 = ba.kvector_t(0.0, 0.0, 5.0)
    lattice = ba.Lattice(lattice_basis_1, lattice_basis_2, lattice_basis_3)

    # spherical particle that forms the base of the mesocrystal
    sphere_ff = ba.FormFactorFullSphere(2*nm)
    sphere = ba.Particle(m_particle, sphere_ff)

    # crystal structure
    crystal = ba.Crystal(sphere, lattice)

    # mesocrystal
    meso_ff = ba.FormFactorCylinder(20 * nm, 50 * nm)
    meso = ba.MesoCrystal(crystal, meso_ff)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(meso)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined
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
