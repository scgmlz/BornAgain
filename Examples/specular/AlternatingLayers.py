#!/usr/bin/env python3
"""
Basic example of specular reflectometry simulation with BornAgain.
The sample consists of 20 alternating Ti and Ni layers.
"""
import bornagain as ba
from bornagain import deg, angstrom


def get_sample():
    # Define materials
    m_ambient = ba.MaterialBySLD("Vacuum", 0, 0)
    m_ti = ba.MaterialBySLD("Ti", -1.9493e-06, 0)
    m_ni = ba.MaterialBySLD("Ni", 9.4245e-06, 0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", 2.0704e-06, 0)

    # Define layers
    ambient_layer = ba.Layer(m_ambient)
    ti_layer = ba.Layer(m_ti, 30*angstrom)
    ni_layer = ba.Layer(m_ni, 70*angstrom)
    substrate_layer = ba.Layer(m_substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(ambient_layer)
    for i in range(10):
        sample.addLayer(ti_layer)
        sample.addLayer(ni_layer)
    sample.addLayer(substrate_layer)

    return sample


def get_simulation(sample, scan_size=500):
    simulation = ba.SpecularSimulation()
    scan = ba.AngularSpecScan(1.54*angstrom, scan_size, 0, 2*deg)
    simulation.setScan(scan)
    simulation.setSample(sample)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
