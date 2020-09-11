"""
An example of taking into account beam angular divergence
and beam footprint correction in reflectometry calculations
with BornAgain.

"""
import numpy as np
import bornagain as ba
from os import path

# input parameters
wavelength = 1.54 * ba.angstrom
alpha_i_min = 0.0 * ba.deg  # min incident angle, deg
alpha_i_max = 2.0 * ba.deg  # max incident angle, rad
beam_sample_ratio = 0.01  # beam-to-sample size ratio

# convolution parameters
d_ang = 0.01 * ba.deg  # spread width for incident angle
n_sig = 3  # number of sigmas to convolve over
n_points = 25  # number of points to convolve over

# substrate (Si)
si_sld_real = 2.0704e-06  # \AA^{-2}
# layer parameters
n_repetitions = 10
# Ni
ni_sld_real = 9.4245e-06  # \AA^{-2}
d_ni = 70 * ba.angstrom
# Ti
ti_sld_real = -1.9493e-06  # \AA^{-2}
d_ti = 30 * ba.angstrom


def get_sample():
    # defining materials
    m_air = ba.MaterialBySLD("Air", 0.0, 0.0)
    m_ni = ba.MaterialBySLD("Ni", ni_sld_real, 0.0)
    m_ti = ba.MaterialBySLD("Ti", ti_sld_real, 0.0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", si_sld_real, 0.0)

    air_layer = ba.Layer(m_air)
    ni_layer = ba.Layer(m_ni, d_ni)
    ti_layer = ba.Layer(m_ti, d_ti)
    substrate_layer = ba.Layer(m_substrate)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    for i in range(n_repetitions):
        multi_layer.addLayer(ti_layer)
        multi_layer.addLayer(ni_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def create_real_data():
    """
    Loading data from genx_angular_divergence.dat
    """
    filepath = path.join(path.dirname(path.realpath(__file__)),
                                      "genx_angular_divergence.dat.gz")
    ax_values, real_data = np.loadtxt(filepath,
                                      usecols=(0, 1), skiprows=3, unpack=True)

    # translating axis values from double incident angle # to incident angle
    ax_values *= 0.5

    return ax_values, real_data


def get_simulation(scan_size=500):
    """
    Returns a specular simulation with beam and detector defined.
    """
    footprint = ba.FootprintSquare(beam_sample_ratio)
    alpha_distr = ba.RangedDistributionGaussian(n_points, n_sig)

    scan = ba.AngularSpecScan(wavelength, scan_size, alpha_i_min, alpha_i_max)
    scan.setFootprintFactor(footprint)
    scan.setAbsoluteAngularResolution(alpha_distr, d_ang)

    simulation = ba.SpecularSimulation()
    simulation.setScan(scan)

    return simulation


def run_simulation():
    """
    Runs simulation and returns it.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


def plot(results):
    """

    :param results:
    :return:
    """
    from matplotlib import pyplot as plt

    ba.plot_simulation_result(results, postpone_show=True)

    genx_axis, genx_values = create_real_data()

    plt.semilogy(genx_axis, genx_values, 'ko', markevery=300)
    plt.legend(['BornAgain',
                'GenX'],
               loc='upper right')

    plt.show()


if __name__ == '__main__':
    results = run_simulation()
    plot(results)
