"""
Long boxes at 1D lattice, ba.OffSpecular simulation
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t

phi_f_min, phi_f_max = -1.0, 1.0
alpha_f_min, alpha_f_max = 0.0, 10.0
alpha_i_min, alpha_i_max = 0.0, 10.0  # incoming beam


def get_sample():
    """
    Returns a sample with a grating on a substrate,
    modelled by infinitely long boxes forming a 1D lattice.
    """

    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff = ba.FormFactorBox(1000.0*nm, 20.0*nm, 10.0*nm)

    # Define particles
    particle = ba.Particle(material_Particle, ff)
    particle_rotation = ba.RotationZ(90.0*deg)
    particle.setRotation(particle_rotation)

    # Define interference functions
    iff = ba.InterferenceFunction1DLattice(100.0*nm, 0.0*deg)
    iff_pdf = ba.FTDecayFunction1DCauchy(1000000.0*nm)
    iff.setDecayFunction(iff_pdf)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle, 1.0)
    layout.setInterferenceFunction(iff)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer_1 = ba.Layer(material_Vacuum)
    layer_1.addLayout(layout)
    layer_2 = ba.Layer(material_Substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)

    return sample


def get_simulation():
    """
    Returns an off-specular simulation with beam and detector defined.
    """
    simulation = ba.OffSpecularSimulation()
    simulation.setDetectorParameters(20, phi_f_min*deg, phi_f_max*deg, 200,
                                     alpha_f_min*deg, alpha_f_max*deg)
    # define the beam with alpha_i varied between alpha_i_min and alpha_i_max
    alpha_i_axis = ba.FixedBinAxis("alpha_i", 200, alpha_i_min*deg,
                                   alpha_i_max*deg)
    simulation.setBeamParameters(1.0*angstrom, alpha_i_axis, 0.0*deg)
    simulation.beam().setIntensity(1e9)
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
    ba.plot_simulation_result(result, intensity_min=1.0, *sys.argv[1:])
