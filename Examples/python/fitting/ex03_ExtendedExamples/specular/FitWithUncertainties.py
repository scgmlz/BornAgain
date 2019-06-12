"""
Example demonstrates how to fit specular data.
Our sample represents twenty interchanging layers of Ti and Ni. We will fit
thicknesses of all Ti layers, assuming them being equal.

Reference data was generated with GENX for ti layers' thicknesses equal to 3 nm

This example uses exactly the same data as in FitSpecularBasics. However this
time we will add artificial uncertainties and use RQ^4 view.
Besides we will set Chi squared with L1-normalization as the objective metric
and use genetic algorithm as the minimizer.
"""

import numpy as np
import bornagain as ba
from matplotlib import pyplot as plt
from os import path


def get_sample(params):
    """
    Creates a sample and returns it
    :param params: a dictionary of optimization parameters
    :return: the sample defined
    """

    # substrate (Si)
    si_sld_real = 2.0704e-06  # \AA^{-2}
    density_si = 0.0499 / ba.angstrom ** 3  # Si atomic number density

    # layers' parameters
    n_repetitions = 10
    # Ni
    ni_sld_real = 9.4245e-06  # \AA^{-2}
    ni_thickness = 70 * ba.angstrom
    # Ti
    ti_sld_real = -1.9493e-06  # \AA^{-2}
    ti_thickness = params["ti_thickness"]

    # defining materials
    m_air = ba.MaterialBySLD()
    m_ni = ba.MaterialBySLD("Ni", ni_sld_real, 0.0)
    m_ti = ba.MaterialBySLD("Ti", ti_sld_real, 0.0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", si_sld_real, 0.0)

    # air layer and substrate form multi layer
    air_layer = ba.Layer(m_air)
    ni_layer = ba.Layer(m_ni, ni_thickness)
    ti_layer = ba.Layer(m_ti, ti_thickness)
    substrate_layer = ba.Layer(m_substrate)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    for i in range(n_repetitions):
        multi_layer.addLayer(ti_layer)
        multi_layer.addLayer(ni_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_real_data():
    """
    Loading data from genx_interchanging_layers.dat
    Returns a Nx2 array (N - the number of experimental data entries)
    with first column being coordinates,
    second one being values.
    """
    if not hasattr(get_real_data, "data"):
        filename = "genx_interchanging_layers.dat.gz"
        filepath = path.join(path.dirname(path.realpath(__file__)), filename)
        real_data = np.loadtxt(filepath, usecols=(0, 1), skiprows=3)

        # translating axis values from double incident angle (degrees)
        # to incident angle (radians)
        real_data[:, 0] *= np.pi / 360
        get_real_data.data = real_data
    return get_real_data.data.copy()


def get_real_data_axis():
    """
    Get axis coordinates of the experimental data
    :return: 1D array with axis coordinates
    """
    return get_real_data()[:, 0]


def get_real_data_values():
    """
    Get experimental data values as a 1D array
    :return: 1D array with experimental data values
    """
    return get_real_data()[:, 1]


def get_simulation(params):
    """
    Create and return specular simulation with its instrument defined
    """
    wavelength = 1.54 * ba.angstrom  # beam wavelength

    simulation = ba.SpecularSimulation()
    scan = ba.AngularSpecScan(wavelength, get_real_data_axis())
    simulation.setScan(scan)
    simulation.setSample(get_sample(params))
    return simulation


def run_fitting():
    """
    Setup simulation and fit
    """

    real_data = get_real_data_values()
    # setting artificial uncertainties (uncertainty sigma equals a half
    # of experimental data value)
    uncertainties = real_data * 0.5

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(get_simulation, real_data, uncertainties)

    plot_observer = ba.PlotterSpecular(units=ba.AxesUnits.RQ4)
    fit_objective.initPrint(10)
    fit_objective.initPlot(10, plot_observer)
    fit_objective.setObjectiveMetric("Chi2", "L1")

    params = ba.Parameters()
    params.add("ti_thickness", 50 * ba.angstrom,
               min=10 * ba.angstrom, max=60 * ba.angstrom)

    minimizer = ba.Minimizer()
    minimizer.setMinimizer("Genetic", "", "MaxIterations=40;PopSize=10")
    result = minimizer.minimize(fit_objective.evaluate, params)

    fit_objective.finalize(result)


if __name__ == '__main__':
    run_fitting()
    plt.show()
