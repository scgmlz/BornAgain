"""
Example for producing a profile of SLD of a multilayer with particles
and slicing.
"""

import bornagain as ba
from bornagain import deg, angstrom, nm
import numpy as np
import matplotlib.pyplot as plt


def get_sample():
    """
    Defines sample and returns it
    """

    # creating materials
    m_ambient = ba.MaterialBySLD("Ambient", 0.0, 0.0)
    m_ti = ba.MaterialBySLD("Ti", -1.9493e-06, 0.0)
    m_ni = ba.MaterialBySLD("Ni", 9.4245e-06, 0.0)
    m_particle = ba.MaterialBySLD("Particle", 5e-6, 0.0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", 2.0704e-06, 0.0)

    # creating layers
    ambient_layer = ba.Layer(m_ambient)
    ti_layer = ba.Layer(m_ti, 30 * angstrom)
    ni_layer = ba.Layer(m_ni, 70 * angstrom)
    substrate_layer = ba.Layer(m_substrate)

    # create roughness
    roughness = ba.LayerRoughness(5 * angstrom, 0.5, 10 * angstrom)

    # create particle layout
    ff = ba.FormFactorCone(5 * nm, 10 * nm, 75 * deg)
    particle = ba.Particle(m_particle, ff)
    layout = ba.ParticleLayout()
    layout.addParticle(particle)
    iff = ba.InterferenceFunction2DLattice.createSquare(10 * nm, 0)
    layout.setInterferenceFunction(iff)
    ambient_layer.addLayout(layout)
    ambient_layer.setNumberOfSlices(20)

    # creating multilayer
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(ambient_layer)
    for i in range(2):
        multi_layer.addLayerWithTopRoughness(ti_layer, roughness)
        multi_layer.addLayerWithTopRoughness(ni_layer, roughness)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


if __name__ == '__main__':
    sample = get_sample()
    zpoints, slds = ba.MaterialProfile(sample)

    plt.figure()
    plt.plot(zpoints, np.real(slds))
    plt.show()
