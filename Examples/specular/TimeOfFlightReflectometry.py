#!/usr/bin/env python3
"""
An example of defining reflectometry instrument
for time of flight experiment. In this example
we will use purely qz-defined beam,
without explicitly specifying
incident angle or a wavelength.
Note that these approaches work with SLD-based
materials only.
"""
import numpy as np
import bornagain as ba
from bornagain import angstrom


def get_sample():
    """
    Defines sample and returns it. Note that SLD-based materials are used.
    """

    # creating materials
    m_ambient = ba.MaterialBySLD("Ambient", 0.0, 0.0)
    m_ti = ba.MaterialBySLD("Ti", -1.9493e-06, 0.0)
    m_ni = ba.MaterialBySLD("Ni", 9.4245e-06, 0.0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", 2.0704e-06, 0.0)

    # creating layers
    ambient_layer = ba.Layer(m_ambient)
    ti_layer = ba.Layer(m_ti, 30*angstrom)
    ni_layer = ba.Layer(m_ni, 70*angstrom)
    substrate_layer = ba.Layer(m_substrate)

    # creating multilayer
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(ambient_layer)
    for i in range(10):
        multi_layer.addLayer(ti_layer)
        multi_layer.addLayer(ni_layer)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


def get_simulation(sample, scan_size=500):
    """
    Defines and returns specular simulation
    with a qz-defined beam
    """
    qzs = np.linspace(0.01, 1.0, scan_size)  # qz-values
    scan = ba.QSpecScan(qzs)
    simulation = ba.SpecularSimulation()
    simulation.setScan(scan)
    simulation.setSample(sample)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
