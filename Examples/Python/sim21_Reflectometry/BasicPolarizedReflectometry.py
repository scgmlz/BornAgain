"""
An example of computing reflectivity on a
magnetized sample.
"""

import bornagain as ba
from bornagain import deg, angstrom

import matplotlib.pyplot as plt


def get_sample():
    """
    Defines sample and returns it
    """

    # creating materials
    m_ambient = ba.MaterialBySLD("Ambient", 0.0, 0.0)
    m_layer_mat = ba.MaterialBySLD("Layer", 1e-4, 1e-8,
                                   ba.kvector_t(0.0, 1e8, 0.0))
    m_substrate = ba.MaterialBySLD("Substrate", 7e-5, 2e-6)

    # creating layers
    ambient_layer = ba.Layer(m_ambient)
    layer = ba.Layer(m_layer_mat, 10)
    substrate_layer = ba.Layer(m_substrate)

    # creating multilayer
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(ambient_layer)
    multi_layer.addLayer(layer)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


def get_simulation(scan_size=500):
    """
    Defines and returns a specular simulation.
    """
    simulation = ba.SpecularSimulation()
    scan = ba.AngularSpecScan(1.54*angstrom, scan_size, 0.0*deg, 5.0*deg)
    simulation.setScan(scan)
    return simulation


def run_simulation(polarization=ba.kvector_t(0, 1, 0),
                   analyzer=ba.kvector_t(0, 1, 0)):
    """
    Runs simulation and returns its result.
    """
    sample = get_sample()
    simulation = get_simulation()

    # adding polarization and analyzer operator
    simulation.setBeamPolarization(polarization)
    simulation.setAnalyzerProperties(analyzer, 1.0, 0.5)

    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


def plot(data, labels):

    plt.figure()
    for d, l in zip(data, labels):
        plt.semilogy(d.axis(), d.array(), label=l, linewidth=1)

    plt.legend(loc='upper right')
    plt.gca().yaxis.set_ticks_position('both')
    plt.gca().xaxis.set_ticks_position('both')

    plt.xlabel(r"$\alpha_i$ [deg]")
    plt.ylabel("Reflectivity")

    plt.tight_layout()
    plt.show()


if __name__ == '__main__':
    results_pp = run_simulation(ba.kvector_t(0, 1, 0), ba.kvector_t(0, 1, 0))
    results_mm = run_simulation(ba.kvector_t(0, -1, 0), ba.kvector_t(0, -1, 0))
    plot([results_pp, results_mm], ["$++$", "$--$"])
