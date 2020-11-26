"""
An example of computing reflectivity on a
magnetized sample.
"""

import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t

import matplotlib.pyplot as plt


def get_sample():
    """
    Defines sample and returns it
    """

    # Define materials
    material_1 = ba.MaterialBySLD("Ambient", 0.0, 0.0)
    magnetic_field = kvector_t(0, 100000000, 0)
    material_2 = ba.MaterialBySLD("Layer", 0.0001, 1e-08, magnetic_field)
    material_3 = ba.MaterialBySLD("Substrate", 7e-05, 2e-06)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_2, 10.0*nm)
    layer_3 = ba.Layer(material_3)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    multiLayer_1.addLayer(layer_2)
    multiLayer_1.addLayer(layer_3)

    return multiLayer_1


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
