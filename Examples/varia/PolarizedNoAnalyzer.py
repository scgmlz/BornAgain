#!/usr/bin/env python3
"""
An example of computing splin-flip reflectivity from
a magnetized sample.
"""
import numpy
import matplotlib.pyplot as plt

import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t


def get_sample():
    """
    Defines sample and returns it
    """

    # Define materials
    material_Ambient = ba.MaterialBySLD("Ambient", 0.0, 0.0)
    magnetic_field = kvector_t(50000000, 86602540.3784, 0)
    material_Layer = ba.MaterialBySLD("Layer", 0.0001, 1e-08, magnetic_field)
    material_Substrate = ba.MaterialBySLD("Substrate", 7e-05, 2e-06)

    # Define layers
    layer_1 = ba.Layer(material_Ambient)
    layer_2 = ba.Layer(material_Layer, 10.0*nm)
    layer_3 = ba.Layer(material_Substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)
    sample.addLayer(layer_3)

    return sample


def get_simulation(sample, scan_size=500):
    """
    Defines and returns a specular simulation.
    """
    simulation = ba.SpecularSimulation()
    scan = ba.AngularSpecScan(1.54*angstrom, scan_size, 0.0*deg, 5.0*deg)
    simulation.setScan(scan)
    simulation.setSample(sample)
    return simulation


def run_simulation(polarization=ba.kvector_t(0.0, 1.0, 0.0), analyzer=None):
    """
    Runs simulation and returns its result.
    """
    sample = get_sample()
    simulation = get_simulation(sample)

    # adding polarization and analyzer operator
    simulation.beam().setPolarization(polarization)
    if analyzer:
        simulation.detector().setAnalyzerProperties(analyzer, 1.0, 0.5)

    simulation.runSimulation()
    result = simulation.result()
    return result.axis(), result.array()


def plot(axis, data, labels):

    plt.figure()
    for d, l in zip(data, labels):
        plt.semilogy(axis, d, label=l, linewidth=1)

    plt.legend(loc='upper right')
    plt.gca().yaxis.set_ticks_position('both')
    plt.gca().xaxis.set_ticks_position('both')

    plt.xlabel(r"$\alpha_i$ [deg]")
    plt.ylabel("Reflectivity")

    plt.tight_layout()


if __name__ == '__main__':
    q, results_pp = run_simulation(ba.kvector_t(0, 1, 0), ba.kvector_t(0, 1, 0))
    q, results_mm = run_simulation(ba.kvector_t(0, -1, 0),
                                   ba.kvector_t(0, -1, 0))

    q, results_pm = run_simulation(ba.kvector_t(0, 1, 0),
                                   ba.kvector_t(0, -1, 0))
    q, results_mp = run_simulation(ba.kvector_t(0, -1, 0),
                                   ba.kvector_t(0, 1, 0))

    r_plus = results_pp + results_pm
    r_minus = results_mm + results_mp
    plot(q, [r_plus, r_minus], ["$+$", "$-$"])

    # same result, but need half the computational time
    q, results_p = run_simulation(ba.kvector_t(0, 1, 0))
    q, results_m = run_simulation(ba.kvector_t(0, -1, 0))

    plot(q, [results_p, results_m], ["$+$", "$-$"])

    plt.show()
