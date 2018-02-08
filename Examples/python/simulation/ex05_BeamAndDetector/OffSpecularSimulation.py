"""
Long boxes at 1D lattice, ba.OffSpecular simulation
"""
import bornagain as ba
from bornagain import deg, angstrom, nm

phi_f_min, phi_f_max = -1.0, 1.0
alpha_f_min, alpha_f_max = 0.0, 10.0
alpha_i_min, alpha_i_max = 0.0, 10.0  # incoming beam


def get_sample():
    """
    Returns a sample with a grating on a substrate,
    modelled by infinitely long boxes forming a 1D lattice.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    lattice_length = 100.0*nm
    lattice_rotation_angle = 0.0*deg
    interference = ba.InterferenceFunction1DLattice(
        lattice_length, lattice_rotation_angle)
    pdf = ba.FTDecayFunction1DCauchy(1e+6)
    interference.setDecayFunction(pdf)

    box_ff = ba.FormFactorBox(1000*nm, 20*nm, 10.0*nm)
    box = ba.Particle(m_particle, box_ff)
    transform = ba.RotationZ(90.0*deg)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(box, 1.0, ba.kvector_t(0.0, 0.0, 0.0), transform)
    particle_layout.setInterferenceFunction(interference)

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
    Returns an off-specular simulation with beam and detector defined.
    """
    simulation = ba.OffSpecSimulation()
    simulation.setDetectorParameters(20, phi_f_min*deg, phi_f_max*deg,
                                     200, alpha_f_min*deg, alpha_f_max*deg)
    # define the beam with alpha_i varied between alpha_i_min and alpha_i_max
    alpha_i_axis = ba.FixedBinAxis(
        "alpha_i", 200, alpha_i_min*deg, alpha_i_max*deg)
    simulation.setBeamParameters(1.0*angstrom, alpha_i_axis, 0.0*deg)
    simulation.setBeamIntensity(1e9)
    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, zmin=1.0)
