#!/usr/bin/env python3
"""
Long boxes at 1D lattice, ba.OffSpecular simulation
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t

phi_f_min, phi_f_max = -1, 1.0
alpha_f_min, alpha_f_max = 0, 10.0
alpha_i_min, alpha_i_max = 0, 10.0  # incoming beam


def get_sample():
    """
    Returns a sample with a grating on a substrate,
    modelled by infinitely long boxes forming a 1D lattice.
    """

    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0, 0)

    # Define form factors
    ff = ba.FormFactorBox(1000*nm, 20*nm, 10*nm)

    # Define particles
    particle = ba.Particle(material_Particle, ff)
    particle_rotation = ba.RotationZ(90*deg)
    particle.setRotation(particle_rotation)

    # Define interference functions
    iff = ba.InterferenceFunction1DLattice(100*nm, 0)
    iff_pdf = ba.FTDecayFunction1DCauchy(1000000*nm)
    iff.setDecayFunction(iff_pdf)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle, 1)
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


def get_simulation(sample):
    """
    Returns an off-specular simulation with beam and detector defined.
    """
    simulation = ba.OffSpecularSimulation()
    simulation.setDetectorParameters(20, phi_f_min*deg, phi_f_max*deg, 200,
                                     alpha_f_min*deg, alpha_f_max*deg)
    # define the beam with alpha_i varied between alpha_i_min and alpha_i_max
    alpha_i_axis = ba.FixedBinAxis("alpha_i", 200, alpha_i_min*deg,
                                   alpha_i_max*deg)
    simulation.setBeamParameters(1*angstrom, alpha_i_axis, 0)
    simulation.beam().setIntensity(1e9)
    simulation.setSample(sample)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation, intensity_min=1)
