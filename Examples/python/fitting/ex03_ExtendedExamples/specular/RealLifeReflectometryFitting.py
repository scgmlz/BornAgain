"""
Real life example:
Fitting data from an X-ray reflectometer

The sample is composed of a thin
silver nano-particle layer on a silicon
substrate. The substrate is covered with
SiO2 layer. The nano-particle layer has negligible density
and does not considerably affect
the observed reflectometry picture.

The following parameters of the experiment
are fitted:
1. beam intensity
2. footprint correction factor
3. beam angular divergence
4. Material concentration in the SiO2 layer
5. Thickness of SiO2 layer
6. Sample roughness

Fitting is done in two steps:
First the whole range of experimental data is fitted,
then the data related to the instrument is fixed and
on the second step only the right-hand part of
experimental data (i.e. the part of the reflectometry curve
associated with bigger incident angles)
is concerned for fitting. At the second
stage only the sample parameters are fitted,
since only they affect the shape of the reflectometry
curve at bigger incident angles.
"""
from matplotlib import pyplot as plt
import numpy as np
from os import path
import bornagain as ba
from scipy.optimize import differential_evolution


def get_real_data(filename="mg6a_Merged.txt.gz"):
    """
    Loads real data files and merges them once.
    Returns a Nx3 array (N - the number of experimental data entries)
    with first column being coordinates,
    second one being values,
    and the third one being weights to restore intensity values from experiment
    """
    if not hasattr(get_real_data, "data"):
        filepath = path.join(path.dirname(path.realpath(__file__)), filename)
        real_data = np.loadtxt(filepath, usecols=(0, 1, 3), skiprows=1)

        # translating axis values from double incident angle (degrees)
        # to incident angle (radians)
        real_data[:, 0] *= np.pi / 360
        get_real_data.data = real_data
    return get_real_data.data.copy()


def get_real_data_axis(start, end):
    """
    Get axis coordinates of the experimental data
    :param start: first bin to extract
    :param end: last bin to extract
    :return: 1D array with axis coordinates
    """
    return get_real_data()[start:end, 0]


def get_real_data_values(start, end):
    """
    Get experimental data values as a 1D array
    :param start: first bin to extract
    :param end: last bin to extract
    :return: 1D array with experimental data values
    """
    return get_real_data()[start:end, 1]


def get_weights(start, end):
    """
    Get weights to restore genuine intensity of experimental instrument
    :param start: first bin to extract
    :param end: last bin to extract
    :return: 1D array with weights to restore beam intensity
    """
    return get_real_data()[start:end, 2]


def create_simulation(arg_dict, bin_start, bin_end):
    """
    Creates and returns specular simulation
    """
    simulation = ba.SpecularSimulation()
    alpha_distr = ba.DistributionGaussian(0.0, arg_dict["divergence"])
    footprint = ba.FootprintFactorGaussian(arg_dict["footprint_factor"])
    simulation.setBeamParameters(1.54 * ba.angstrom,
                                 get_real_data_axis(bin_start, bin_end), footprint)
    simulation.setBeamIntensity(arg_dict["intensity"])
    simulation.addParameterDistribution("*/Beam/InclinationAngle", alpha_distr,
                                         30, 3)
    return simulation


def buildSample(arg_dict):
    """
    Creates sample and returns it
    """
    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_si_o2 = ba.HomogeneousMaterial("SiO2",
        8.57040868e-06 * arg_dict["concentration"],
        1.11016654e-07 * arg_dict["concentration"])
    m_si = ba.HomogeneousMaterial("Si", 7.57211137e-06, 1.72728178e-07)

    # roughness
    r_si = ba.LayerRoughness(arg_dict["roughness"], 0, 0)

    # layers
    air_layer = ba.Layer(m_air)
    oxide_layer = ba.Layer(m_si_o2, arg_dict["thickness"])
    substrate_layer = ba.Layer(m_si)

    # assembling multilayer
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayerWithTopRoughness(oxide_layer, r_si)
    multi_layer.addLayerWithTopRoughness(substrate_layer, r_si)

    return multi_layer


def run_simulation(arg_dict, bin_start=0, bin_end=-1):
    """
    Runs simulation and returns its result
    """

    simulation = create_simulation(arg_dict, bin_start, bin_end)
    simulation.setSample(buildSample(arg_dict))

    simulation.runSimulation()
    return simulation.result()


def chi_2(real_data, sim_data, weights):
    """
    Computes chi_2 metrics and returns its value
    """
    sim_data_upsc = np.multiply(weights, sim_data)
    sim_data_upsc[sim_data_upsc is 0] = 1e-30
    real_data_upsc = np.multiply(weights, real_data)
    diff = real_data_upsc - sim_data_upsc
    return np.sum(np.divide(np.multiply(diff,diff), sim_data_upsc))


def create_par_dict(*arg):
    """
    Creates a dictionary with parameter names and values
    and returns it
    """
    return {'intensity': arg[0],
            'footprint_factor': arg[1],
            'divergence':arg[2],
            'concentration': arg[3],
            'thickness': arg[4],
            'roughness': arg[5]
            }


def objective_primary(args):
    """
    Objective function for preliminary stage of optimization
    """

    bin_start = 15  # first bin in the experimental data to calculate
    bin_end = -1  # last bin in the experimental data to calculate
    arg_dict = create_par_dict(*args)

    sim_result = run_simulation(arg_dict, bin_start, bin_end)
    sim_data = sim_result.data().getArray()
    return chi_2(get_real_data_values(bin_start, bin_end),
                 sim_data, get_weights(bin_start, bin_end))


def objective_fine(args, intensity, footprint_factor, divergence):
    """
    Objective function for tuning the right-hand side of experimental data
    """

    bin_start = 404  # first bin in the experimental data to calculate
    bin_end = -1  # last bin in the experimental data to calculate
    arg_dict = create_par_dict(intensity, footprint_factor, divergence, *args)

    sim_result = run_simulation(arg_dict, bin_start, bin_end)
    sim_data = sim_result.data().getArray()
    return chi_2(get_real_data_values(bin_start, bin_end),
                 sim_data, get_weights(bin_start, bin_end))


def run_fitting():
    """
    Runs fitting and returns its result
    """
    # running preliminary optimization on the total range of experimental data.
    bounds = [(1e6, 1e8),   # beam intensity
              (0.0, 0.1),   # beam-to-sample width ratio
              (0.0, 0.08 * ba.deg),  # beam_divergence
              (0.0, 1.0),  # oxide_concentration
              (0.0, 2.0 * ba.nm),  # oxide_thickness
              (0.0, 2.0 * ba.nm)]    # roughness

    print("Start preliminary fitting of experimental data:\n")

    preliminary_result = differential_evolution(objective_primary, bounds,
                                                maxiter=20, popsize=10,
                                                mutation=(0.5, 1.5),
                                                disp=True, tol=1e-5)

    bounds = [(0.0, 1.0),  # oxide_concentration
              (0.0, 2.0 * ba.nm),  # oxide_thickness
              (0.0, 2.0 * ba.nm)]    # roughness

    fixed_args = (preliminary_result.x[0],  # beam intensity
                  preliminary_result.x[1],  # beam-to-sample width ratio
                  preliminary_result.x[2]  # beam divergence
                  )

    print("\nStart fitting big incident angle part of experimental data:\n")

    fine_tuning_result = differential_evolution(objective_fine, bounds,
                                                fixed_args, maxiter=20,
                                                popsize=10, mutation=(0.5, 1.5),
                                                disp=True, tol=1e-5)

    result = create_par_dict(*fixed_args, *fine_tuning_result.x)
    print("\nFitting result:")
    print(result,"\n")

    return result


def plot_result(sim_result, ref_result, bin_start=0, bin_end=-1):
    """
    Plots the graphs of obtained simulation data
    """
    sim_data = sim_result.data()
    ref_data = ref_result.data()

    plt.semilogy(get_real_data_axis(bin_start, bin_end) * 180 / np.pi,
                 get_real_data_values(bin_start, bin_end),
                 sim_data.getAxis(0).getBinCenters(), sim_data.getArray(),
                 ref_data.getAxis(0).getBinCenters(), ref_data.getArray())

    xlabel = ba.get_axes_labels(sim_result, ba.AxesUnits.DEFAULT)[0]
    ylabel = "Intensity"
    plt.xlabel(xlabel, fontsize=16)
    plt.ylabel(ylabel, fontsize=16)
    plt.legend(['Experimental data', 'Simulation', 'Reference'],
               loc='upper right', fontsize=16)

    plt.show()


if __name__ == '__main__':
    fit_data = run_fitting()
    ref_data = create_par_dict(3.78271438e+06,  # beam intensity
                               9.58009763e-04,  # beam-to-sample width ratio
                               2.30471294e-04,  # beam angular divergence
                               0.58721753,  # oxide concentration
                               1.25559347,  # oxide thickness
                               0.19281863)  # roughness
    plot_result(run_simulation(fit_data), run_simulation(ref_data))
