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
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_3 = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_3)

    # Define form factors
    formFactor_1 = ba.FormFactorBox(1000.0*nm, 20.0*nm, 10.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)
    particle_1_rotation = ba.RotationZ(90.0*deg)
    particle_1.setRotation(particle_1_rotation)

    # Define interference functions
    interference_1 = ba.InterferenceFunction1DLattice(100.0*nm, 0.0*deg)
    interference_1_pdf = ba.FTDecayFunction1DCauchy(1000000.0*nm)
    interference_1.setDecayFunction(interference_1_pdf)

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particle_1, 1.0)
    layout_1.setInterferenceFunction(interference_1)
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
    Returns an off-specular simulation with beam and detector defined.
    """
    simulation = ba.OffSpecSimulation()
    simulation.setDetectorParameters(20, phi_f_min*deg, phi_f_max*deg, 200,
                                     alpha_f_min*deg, alpha_f_max*deg)
    # define the beam with alpha_i varied between alpha_i_min and alpha_i_max
    alpha_i_axis = ba.FixedBinAxis("alpha_i", 200, alpha_i_min*deg,
                                   alpha_i_max*deg)
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
    ba.plot_simulation_result(result,
                              intensity_min=1.0,
                              cmap='jet',
                              aspect='auto')
