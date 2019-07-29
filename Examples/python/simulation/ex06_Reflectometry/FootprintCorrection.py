"""
Specular simulation with a footprint correction
for a square beam

"""
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom


def get_sample():
    """
    Defines sample and returns it
    """

    # creating materials
    m_ambient = ba.MaterialBySLD("Ambient", 0.0, 0.0)
    m_ti = ba.MaterialBySLD("Ti", -1.9493e-06, 0.0)
    m_ni = ba.MaterialBySLD("Ni", 9.4245e-06, 0.0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", 2.0704e-06, 0.0)

    # creating layers
    ambient_layer = ba.Layer(m_ambient)
    ti_layer = ba.Layer(m_ti, 30 * angstrom)
    ni_layer = ba.Layer(m_ni, 70 * angstrom)
    substrate_layer = ba.Layer(m_substrate)

    # creating multilayer
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(ambient_layer)
    for i in range(10):
        multi_layer.addLayer(ti_layer)
        multi_layer.addLayer(ni_layer)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


def get_simulation(footprint):
    """
    Defines and returns a specular simulation.
    """
    simulation = ba.SpecularSimulation()
    scan = ba.AngularSpecScan(
        1.54 * angstrom, 500 , 0.0 * deg, 0.6 * deg)
    scan.setFootprintFactor(footprint)
    simulation.setScan(scan)
    return simulation


def run_simulation(simulation):
    """
    Runs simulation and returns its result.
    """
    simulation.setSample(get_sample())
    simulation.runSimulation()
    return simulation.result()


def get_plot_data(sim_result):
    data = sim_result.data()
    intensity = data.getArray()
    x_axis = data.getAxis(0).getBinCenters()
    return x_axis, intensity


def plot(sim_result_1, sim_result_2):
    """
    Plots results from two different simulations
    """

    plt.semilogy(*get_plot_data(sim_result_1), *get_plot_data(sim_result_2))

    plt.xlabel(r'$\alpha_i \; (deg)$', fontsize=16)
    plt.ylabel(r'Intensity', fontsize=16)

    plt.legend(['With footprint',
                'Without footprint'],
                loc='upper right')

    plt.show()


if __name__ == '__main__':
    beam_sample_ratio = 0.01  # beam-to-sample size ratio
    result_with_fp = run_simulation(
        get_simulation(
            footprint=ba.FootprintFactorSquare(beam_sample_ratio)
        )
    )
    result_without_fp = run_simulation(get_simulation(footprint=None))
    plot(result_with_fp, result_without_fp)
