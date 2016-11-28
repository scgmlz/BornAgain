"""
Spherical particles embedded in the middle of the layer on top of substrate.
"""
import numpy
import bornagain as ba
from bornagain import deg, angstrom, nm

def get_sample():
    """
    Returns a sample with spherical particles in an layer between air and substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_interm_layer = ba.HomogeneousMaterial("IntermLayer", 3.45e-6, 5.24e-9)
    m_substrate = ba.HomogeneousMaterial("Substrate", 7.43e-6, 1.72e-7)
    m_particle = ba.HomogeneousMaterial("Particle", 0.0, 0.0)

    # collection of particles
    ff_sphere = ba.FormFactorFullSphere(10.2*nm)
    sphere = ba.Particle(m_particle, ff_sphere)
    sphere.setPosition(0.0, 0.0, -25.2)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(sphere, 1.0)

    # assembling the sample
    air_layer = ba.Layer(m_ambience)
    intermediate_layer = ba.Layer(m_interm_layer, 30.*nm)
    intermediate_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate, 0)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(intermediate_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation.
    """
    simulation = ba.GISASSimulation()
    simulation.setSample(get_sample())
    simulation.setDetectorParameters(200, -1*deg, +1*deg, 200, 0*deg, +2*deg)
    simulation.setBeamParameters(1.5*angstrom, 0.15*deg, 0.0*deg)
    return simulation


if __name__ == '__main__':
    simulation = get_simulation()
    simulation.runSimulation()
    result = simulation.getIntensityData()
    ba.plot_intensity_data(result)
