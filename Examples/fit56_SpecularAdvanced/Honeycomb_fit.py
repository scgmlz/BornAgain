#!/usr/bin/env python3
"""
This example demonstrates how to fit a complex experimental setup using BornAgain.
It is based on real data published in  https://doi.org/10.1002/advs.201700856
by A. Glavic et al.
In this example we utilize the scalar reflectometry  engine to fit polarized 
data without spin-flip for performance reasons.
"""

import sys
import numpy
import matplotlib.pyplot as plt

from scipy.optimize import differential_evolution

import bornagain as ba
from bornagain import angstrom

from zipfile import ZipFile

# number of points on which the computed result is plotted
scan_size = 1500

# restrict the Q-range of the data used for fitting
qmin = 0.08
qmax = 1.4

####################################################################
#                  Create Sample and Simulation                    #
####################################################################


def get_sample(parameters, sign, ms150=1):

    m_Air = ba.MaterialBySLD("Air", 0, 0)
    m_PyOx  = ba.MaterialBySLD("PyOx",
                               (parameters["sld_PyOx_real"] + \
                                 sign * ms150 * parameters["msld_PyOx"] )* 1e-6,
                               parameters["sld_PyOx_imag"] * 1e-6)
    m_Py2   = ba.MaterialBySLD("Py2",
                               ( parameters["sld_Py2_real"] + \
                                 sign * ms150 * parameters["msld_Py2"] ) * 1e-6,
                               parameters["sld_Py2_imag"] * 1e-6)
    m_Py1   = ba.MaterialBySLD("Py1",
                               ( parameters["sld_Py1_real"] + \
                                 sign * ms150 * parameters["msld_Py1"] ) * 1e-6,
                               parameters["sld_Py1_imag"] * 1e-6)
    m_SiO2 = ba.MaterialBySLD("SiO2", parameters["sld_SiO2_real"]*1e-6,
                              parameters["sld_SiO2_imag"]*1e-6)
    m_Si = ba.MaterialBySLD("Substrate", parameters["sld_Si_real"]*1e-6,
                            parameters["sld_Si_imag"]*1e-6)

    l_Air = ba.Layer(m_Air)
    l_PyOx = ba.Layer(m_PyOx, parameters["t_PyOx"]*angstrom)
    l_Py2 = ba.Layer(m_Py2, parameters["t_Py2"]*angstrom)
    l_Py1 = ba.Layer(m_Py1, parameters["t_Py1"]*angstrom)
    l_SiO2 = ba.Layer(m_SiO2, parameters["t_SiO2"]*angstrom)
    l_Si = ba.Layer(m_Si)

    r_PyOx = ba.LayerRoughness()
    r_Py2 = ba.LayerRoughness()
    r_Py1 = ba.LayerRoughness()
    r_SiO2 = ba.LayerRoughness()
    r_Si = ba.LayerRoughness()

    r_PyOx.setSigma(parameters["r_PyOx"]*angstrom)
    r_Py2.setSigma(parameters["r_Py2"]*angstrom)
    r_Py1.setSigma(parameters["r_Py1"]*angstrom)
    r_SiO2.setSigma(parameters["r_SiO2"]*angstrom)
    r_Si.setSigma(parameters["r_Si"]*angstrom)

    sample = ba.MultiLayer()

    sample.addLayer(l_Air)
    sample.addLayerWithTopRoughness(l_PyOx, r_PyOx)
    sample.addLayerWithTopRoughness(l_Py2, r_Py2)
    sample.addLayerWithTopRoughness(l_Py1, r_Py1)
    sample.addLayerWithTopRoughness(l_SiO2, r_SiO2)
    sample.addLayerWithTopRoughness(l_Si, r_Si)

    sample.setRoughnessModel(ba.RoughnessModel.NEVOT_CROCE)

    return sample


def get_simulation(q_axis, fitParams, sign, ms150=False):

    n_points = 25
    n_sig = 3.0

    parameters = dict(fitParams, **fixedParams)

    q_distr = ba.RangedDistributionGaussian(n_points, n_sig)

    dq = parameters["dq"]*q_axis
    scan = ba.QSpecScan(q_axis)
    scan.setAbsoluteQResolution(q_distr, dq)

    simulation = ba.SpecularSimulation()
    simulation.setScan(scan)
    simulation.beam().setIntensity(parameters["intensity"])

    if ms150:
        sample = get_sample(parameters=parameters,
                            sign=sign,
                            ms150=parameters["ms150"])
    else:
        sample = get_sample(parameters=parameters, sign=sign, ms150=1)

    simulation.setSample(sample)
    simulation.setBackground(ba.ConstantBackground(5e-7))

    return simulation


def run_simulation(q_axis, fitParams, *, sign, ms150=False):
    simulation = get_simulation(q_axis, fitParams, sign, ms150)
    simulation.runSimulation()

    return simulation


def qr(result):
    """
    Returns two arrays that hold the q-values as well as the
    reflectivity from a given simulation result
    """
    q = numpy.array(result.result().axis(ba.Axes.QSPACE))
    r = numpy.array(result.result().array(ba.Axes.QSPACE))

    return q, r


####################################################################
#                         Plot Handling                            #
####################################################################


def plot(qs, rs, exps, shifts, labels, filename):
    """
    Plot the simulated result together with the experimental data
    """
    fig = plt.figure()
    ax = fig.add_subplot(111)

    for q, r, exp, shift, l in zip(qs, rs, exps, shifts, labels):

        ax.errorbar(exp[0],
                    exp[1]/shift,
                    yerr=exp[2]/shift,
                    fmt='.',
                    markersize=0.75,
                    linewidth=0.5)

        ax.plot(q, r/shift, label=l)

    ax.set_yscale('log')
    plt.legend()

    plt.xlabel("Q [nm${}^{-1}$]")
    plt.ylabel("R")

    plt.tight_layout()
    plt.savefig(filename)


def plot_sld_profile(fitParams, filename):

    plt.figure()
    parameters = dict(fitParams, **fixedParams)

    z_300_p, sld_300_p = ba.MaterialProfile(get_sample(parameters, 1))
    z_300_m, sld_300_m = ba.MaterialProfile(get_sample(parameters, -1))

    z_150_p, sld_150_p = ba.MaterialProfile(
        get_sample(parameters, 1, ms150=parameters["ms150"]))
    z_150_m, sld_150_m = ba.MaterialProfile(
        get_sample(parameters, -1, ms150=parameters["ms150"]))

    plt.figure()
    nsld = plt.plot(z_300_p, numpy.real(sld_300_p)*1e6, label=r"300K $+$")
    nsld = plt.plot(z_300_m, numpy.real(sld_300_m)*1e6, label=r"300K $-$")

    nsld = plt.plot(z_150_p, numpy.real(sld_150_p)*1e6, label=r"150K $+$")
    nsld = plt.plot(z_150_m, numpy.real(sld_150_m)*1e6, label=r"150K $-$")

    plt.xlabel(r"$z$ [A]")
    plt.ylabel(r"$\delta(z) \cdot 10^6$")

    plt.legend()
    plt.tight_layout()
    plt.savefig(filename)
    plt.close()


####################################################################
#                          Data Handling                           #
####################################################################


def normalizeData(data):
    """
    Removes duplicate q values from the input data,
    normalizes it such that the maximum of the reflectivity is
    unity and rescales the q-axis to inverse nm
    """
    # delete repeated data
    r0 = numpy.where(data[0] - numpy.roll(data[0], 1) == 0)
    data = numpy.delete(data, r0, 1)

    data[0] = data[0]/angstrom
    norm = numpy.max(data[1])
    data[1] = data[1]/norm
    data[2] = data[2]/norm

    # sort by q axis
    so = numpy.argsort(data[0])
    data = data[:, so]

    return data


def get_Experimental_data(filename, qmin, qmax):

    if not hasattr(get_Experimental_data, "zipfile"):
        get_Experimental_data.zipfile = ZipFile("honeycomb_data.zip")

    input_Data = numpy.genfromtxt(
        get_Experimental_data.zipfile.open(filename),
        unpack=True,
        usecols=(0, 2, 3))
    data = normalizeData(input_Data)

    minIndex = numpy.argmin(numpy.abs(data[0] - qmin))
    maxIndex = numpy.argmin(numpy.abs(data[0] - qmax))

    return data[:, minIndex:maxIndex + 1]


####################################################################
#                          Fit Function                            #
####################################################################


def relative_difference(sim, exp):
    result = (exp - sim)/(exp + sim)
    return numpy.sum(result*result)/len(sim)


def create_Parameter_dictionary(parameterNames, *args):
    return {name: value for name, value in zip(parameterNames, *args)}


class FitObjective:
    def __init__(self, q_axis, rdata, simulationFactory, parameterNames):
        if isinstance(q_axis, list) and isinstance(rdata, list) and \
                                    isinstance(simulationFactory, list):
            self._q = q_axis
            self._r = rdata
            self._simulationFactory = simulationFactory

        elif not isinstance(q_axis, list) and not isinstance(rdata, list) \
                              and not isinstance(simulationFactory, list):
            self._q = [q_axis]
            self._r = [rdata]
            self._simulationFactory = [simulationFactory]

        else:
            raise Exception("Inconsistent parameters")

        self._parameterNames = parameterNames

    def __call__(self, *args):
        fitParameters = create_Parameter_dictionary(self._parameterNames,
                                                    *args)
        print(f"FitParamters = {fitParameters}")

        result_metric = 0

        for q, r, sim in zip(self._q, self._r, self._simulationFactory):
            sim_result = sim(q, fitParameters).result().array()
            result_metric += relative_difference(sim_result, r)

        return result_metric


def run_fit_differential_evolution(q_axis, rdata, simulationFactory,
                                   startParams):

    bounds = [(par[1], par[2]) for n, par in startParams.items()]
    parameters = [par[0] for n, par in startParams.items()]
    parameterNames = [n for n, par in startParams.items()]
    print(f"Bounds = {bounds}")

    objective = FitObjective(q_axis, rdata, simulationFactory,
                             parameterNames)

    chi2_initial = objective(parameters)

    result = differential_evolution(objective,
                                    bounds,
                                    maxiter=200,
                                    popsize=len(bounds)*10,
                                    mutation=(0.5, 1.5),
                                    disp=True,
                                    tol=1e-2)

    resultParameters = create_Parameter_dictionary(parameterNames,
                                                   result.x)
    chi2_final = objective(resultParameters.values())

    print(f"Initial chi2: {chi2_initial}")
    print(f"Final chi2: {chi2_final}")
    return resultParameters


####################################################################
#                          Main Function                           #
####################################################################

if __name__ == '__main__':

    fixedParams = {
        "sld_PyOx_imag": (0, 0, 0),
        "sld_Py2_imag": (0, 0, 0),
        "sld_Py1_imag": (0, 0, 0),
        "sld_SiO2_imag": (0, 0, 0),
        "sld_Si_imag": (0, 0, 0),
        "sld_SiO2_real": (3.47, 3, 4),
        "sld_Si_real": (2.0704, 2, 3),
        "dq": (0.018, 0, 0.1),
    }

    if len(sys.argv) > 1 and sys.argv[1] == "fit":

        # some sensible start parameters for fitting
        startParams = {
            "intensity": (1.04, 0, 3),
            "t_PyOx": (77, 60, 100),
            "t_Py2": (56, 40, 70),
            "t_Py1": (64, 50, 80),
            "t_SiO2": (16, 10, 30),
            "sld_PyOx_real": (1.915, 1.6, 2.2),
            "sld_Py2_real": (5, 3, 6),
            "sld_Py1_real": (4.62, 3, 6),
            "r_PyOx": (27, 5, 35),
            "r_Py2": (12, 5, 20),
            "r_Py1": (12, 5, 20),
            "r_SiO2": (17, 2, 25),
            "r_Si": (18, 2, 25),
            "msld_PyOx": (0.25, 0, 1),
            "msld_Py2": (0.63, 0, 1),
            "msld_Py1": (0.64, 0, 1),
            "ms150": (1, 0.9, 1.1),
        }

        fit = True

    else:
        # result from our own fitting
        startParams = {
            'intensity': 0.9482344993285265,
            't_PyOx': 74.97056190221168,
            't_Py2': 61.75823766477464,
            't_Py1': 54.058310970786316,
            't_SiO2': 23.127048588278402,
            'sld_PyOx_real': 2.199791584033569,
            'sld_Py2_real': 4.980316982224387,
            'sld_Py1_real': 4.612135848532186,
            'r_PyOx': 31.323366207013787,
            'r_Py2': 9.083768897940645,
            'r_Py1': 5,
            'r_SiO2': 14.43455709065263,
            'r_Si': 14.948233893986075,
            'msld_PyOx': 0.292684104601585,
            'msld_Py2': 0.5979447434271339,
            'msld_Py1': 0.56376339230351,
            'ms150': 1.083311702077648
        }

        startParams = {d: (v, ) for d, v in startParams.items()}
        fit = False

    fixedParams = {d: v[0] for d, v in fixedParams.items()}
    paramsInitial = {d: v[0] for d, v in startParams.items()}

    def run_Simulation_300_p(qzs, params):
        return run_simulation(qzs, params, sign=1)

    def run_Simulation_300_m(qzs, params):
        return run_simulation(qzs, params, sign=-1)

    def run_Simulation_150_p(qzs, params):
        return run_simulation(qzs, params, sign=1, ms150=True)

    def run_Simulation_150_m(qzs, params):
        return run_simulation(qzs, params, sign=-1, ms150=True)

    qzs = numpy.linspace(qmin, qmax, scan_size)
    q_300_p, r_300_p = qr(run_Simulation_300_p(qzs, paramsInitial))
    q_300_m, r_300_m = qr(run_Simulation_300_m(qzs, paramsInitial))

    q_150_p, r_150_p = qr(run_Simulation_150_p(qzs, paramsInitial))
    q_150_m, r_150_m = qr(run_Simulation_150_m(qzs, paramsInitial))

    data_300_p = get_Experimental_data("honeycomb_300_p.dat", qmin, qmax)
    data_300_m = get_Experimental_data("honeycomb_300_m.dat", qmin, qmax)

    data_150_p = get_Experimental_data("honeycomb_150_p.dat", qmin, qmax)
    data_150_m = get_Experimental_data("honeycomb_150_m.dat", qmin, qmax)

    plot_sld_profile(paramsInitial,
                     f"Honeycomb_Fit_sld_profile_initial.pdf")
    plot([q_300_p, q_300_m, q_150_p, q_150_m],
         [r_300_p, r_300_m, r_150_p, r_150_m],
         [data_300_p, data_300_m, data_150_p, data_150_m], [1, 1, 10, 10],
         ["300K $+$", "300K $-$", "150K $+$", "150K $-$"],
         f"Honeycomb_Fit_reflectivity_initial.pdf")

    # fit and plot fit
    if fit:
        dataSimTuple = [[
            data_300_p[0], data_300_m[0], data_150_p[0], data_150_m[0]
        ], [data_300_p[1], data_300_m[1], data_150_p[1], data_150_m[1]],
                        [
                            run_Simulation_300_p, run_Simulation_300_m,
                            run_Simulation_150_p, run_Simulation_150_m
                        ]]

        fitResult = run_fit_differential_evolution(*dataSimTuple,
                                                   startParams)

        print("Fit Result:")
        print(fitResult)

        q_300_p, r_300_p = qr(run_Simulation_300_p(qzs, fitResult))
        q_300_m, r_300_m = qr(run_Simulation_300_m(qzs, fitResult))

        q_150_p, r_150_p = qr(run_Simulation_150_p(qzs, fitResult))
        q_150_m, r_150_m = qr(run_Simulation_150_m(qzs, fitResult))

        plot([q_300_p, q_300_m, q_150_p, q_150_m],
             [r_300_p, r_300_m, r_150_p, r_150_m],
             [data_300_p, data_300_m, data_150_p, data_150_m],
             [1, 1, 10, 10],
             ["300K $+$", "300K $-$", "150K $+$", "150K $-$"],
             f"Honeycomb_Fit_reflectivity_fit.pdf")

        plot_sld_profile(fitResult, f"Honeycomb_Fit_sld_profile_fit.pdf")
