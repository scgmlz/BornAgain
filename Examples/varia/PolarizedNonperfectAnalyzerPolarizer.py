#!/usr/bin/env python3
"""
An example that shows how to simulate
a non-perfect polarizer and analyzer
following Devishvili et al., Rev. Sci. Instrum. 84, 025112 (2013)
"""
import numpy
import matplotlib.pyplot as plt

import bornagain as ba
from bornagain import deg, angstrom

sldFe = (8.0241e-06, 6.0448e-10)
sldPd = (4.0099e-6, 1.3019e-09)
sldMgO = (5.9803e-06, 9.3996e-12)

magnetizationMagnitude = 1.6e6
angle = 0
magnetizationVector = ba.kvector_t(magnetizationMagnitude*numpy.sin(angle*deg),
                                   magnetizationMagnitude*numpy.cos(angle*deg),
                                   0)


def get_sample(*, magnetization=magnetizationVector):
    """
    Define sample and returns it
    """

    # create materials
    mat_vacuum = ba.MaterialBySLD("Vacuum", 0.0, 0.0)
    mat_Pd = ba.MaterialBySLD("Pd", *sldPd)
    mat_Fe = ba.MaterialBySLD("Fe", *sldFe, magnetizationVector)
    mat_substrate = ba.MaterialBySLD("MgO", *sldMgO)

    # create layers
    layer_vacuum = ba.Layer(mat_vacuum)
    layer_Pd = ba.Layer(mat_Pd, 120*angstrom)
    layer_Fe = ba.Layer(mat_Fe, 1000*angstrom)
    layer_substrate = ba.Layer(mat_substrate)

    roughness = ba.LayerRoughness()
    roughness.setSigma(20*angstrom)

    # create sample
    multi_layer = ba.MultiLayer()

    multi_layer.addLayer(layer_vacuum)
    multi_layer.addLayerWithTopRoughness(layer_Pd, roughness)
    multi_layer.addLayerWithTopRoughness(layer_Fe, roughness)
    multi_layer.addLayerWithTopRoughness(layer_substrate, roughness)

    return multi_layer


def get_simulation(sample, scan_size=1500):
    """
    Defines and returns a specular simulation.
    """
    simulation = ba.SpecularSimulation()
    qzs = numpy.linspace(0.1, 1.5, scan_size)

    n_sig = 4.0
    n_samples = 25
    distr = ba.RangedDistributionGaussian(n_samples, n_sig)

    scan = ba.QSpecScan(qzs)
    scan.setAbsoluteQResolution(distr, 0.008)

    simulation.setScan(scan)
    simulation.setSample(sample)
    return simulation


def run_simulation(*,
                   polarization=ba.kvector_t(0, 1, 0),
                   polarizer_efficiency=1,
                   analyzer=ba.kvector_t(0, 1, 0),
                   analyzer_efficiency=1):
    """
    Runs simulation and returns its result.
    """
    sample = get_sample()
    simulation = get_simulation(sample)

    simulation.beam().setPolarization(polarization*polarizer_efficiency)
    simulation.detector().setAnalyzerProperties(analyzer, analyzer_efficiency, 0.5)

    simulation.setBackground(ba.ConstantBackground(1e-7))

    simulation.runSimulation()
    return simulation.result()


def plot(data, labels):

    plt.figure()
    for d, l in zip(data, labels):
        plt.semilogy(numpy.array(d.axis(ba.Axes.QSPACE)),
                     d.array(ba.Axes.QSPACE),
                     label=l,
                     linewidth=1)

    plt.legend(loc='upper right')
    plt.gca().yaxis.set_ticks_position('both')
    plt.gca().xaxis.set_ticks_position('both')

    plt.xlabel("$Q$ [nm${}^{-1}$]")
    plt.ylabel("Reflectivity")

    plt.tight_layout()
    plt.show()


if __name__ == '__main__':

    polarizer_efficiency = 0.986
    analyzer_efficiency = 0.970

    results_pp = run_simulation(polarization=ba.kvector_t(0, 1, 0),
                                analyzer=ba.kvector_t(0, 1, 0),
                                polarizer_efficiency=polarizer_efficiency,
                                analyzer_efficiency=analyzer_efficiency)
    results_mm = run_simulation(polarization=ba.kvector_t(0, -1, 0),
                                analyzer=ba.kvector_t(0, -1, 0),
                                polarizer_efficiency=polarizer_efficiency,
                                analyzer_efficiency=analyzer_efficiency)

    results_pm = run_simulation(polarization=ba.kvector_t(0, 1, 0),
                                analyzer=ba.kvector_t(0, -1, 0),
                                polarizer_efficiency=polarizer_efficiency,
                                analyzer_efficiency=analyzer_efficiency)
    results_mp = run_simulation(polarization=ba.kvector_t(0, -1, 0),
                                analyzer=ba.kvector_t(0, 1, 0),
                                polarizer_efficiency=polarizer_efficiency,
                                analyzer_efficiency=analyzer_efficiency)

    plot([results_pp, results_mm, results_pm, results_mp],
         ["$++$", "$--$", "$+-$", "$-+$"])
