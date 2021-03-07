#!/usr/bin/env python3
"""
This example demonstrates how to fit actual experimental data
by M. Fitzsimmons et al. that is published in 
https://doi.org/10.5281/zenodo.4072376
"""

import numpy
import matplotlib.pyplot as plt
from sys import argv

import bornagain as ba
from bornagain import angstrom

# filename of the experimental data to be loaded
filename = 'RvsQ_36563_36662.txt.gz'

# restrict the Q-range of the data used for fitting
qmin = 0.18
qmax = 2.4

# number of points on which the computed result is plotted
scan_size = 1500

# Use fixed values for the SLD of the substrate and Pt layer
sldPt = (6.3568e-06, 1.8967e-09)
sldSi = (2.0728e-06, 2.3747e-11)

####################################################################
#                  Create Sample and Simulation                    #
####################################################################


def get_sample(params):

    mat_ambient = ba.MaterialBySLD("Ambient", 0, 0)
    mat_layer = ba.MaterialBySLD("Pt", *sldPt)
    mat_substrate = ba.MaterialBySLD("Si", *sldSi)

    ambient_layer = ba.Layer(mat_ambient)
    layer = ba.Layer(mat_layer, params["t_pt/nm"])
    substrate_layer = ba.Layer(mat_substrate)

    r_si = ba.LayerRoughness()
    r_si.setSigma(params["r_si/nm"])

    r_pt = ba.LayerRoughness()
    r_pt.setSigma(params["r_pt/nm"])

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(ambient_layer)
    multi_layer.addLayerWithTopRoughness(layer, r_pt)

    multi_layer.addLayerWithTopRoughness(substrate_layer, r_si)

    return multi_layer


def get_simulation(q_axis, parameters):

    scan = ba.QSpecScan(q_axis)
    scan.setOffset(parameters["q_offset"])

    n_sig = 4.0
    n_samples = 25

    distr = ba.RangedDistributionGaussian(n_samples, n_sig)
    scan.setAbsoluteQResolution(distr, parameters["q_res/q"])

    simulation = ba.SpecularSimulation()
    simulation.beam().setIntensity(parameters["intensity"])

    simulation.setScan(scan)
    return simulation


def run_simulation(q_axis, fitParams):
    parameters = dict(fitParams, **fixedParams)

    sample = get_sample(parameters)
    simulation = get_simulation(q_axis, parameters)

    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation  #.result()


def qr(result):
    """
    helper function to return the q axis and 
    reflectivity from simulation result
    """
    q = numpy.array(result.result().axis(ba.Axes.QSPACE))
    r = numpy.array(result.result().array(ba.Axes.QSPACE))

    return q, r


####################################################################
#                         Plot Handling                            #
####################################################################


def plot(q, r, exp, filename, params=None):
    """
    helper function to plot a result
    """
    fig = plt.figure()
    ax = fig.add_subplot(111)

    ax.errorbar(exp[0],
                exp[1],
                xerr=exp[3],
                yerr=exp[2],
                label="R",
                fmt='.',
                markersize=1.,
                linewidth=0.6,
                color='r')

    ax.plot(q, r, label="Simulation", color='C0', linewidth=0.5)

    ax.set_yscale('log')

    ax.set_xlabel("Q [nm$^{^-1}$]")
    ax.set_ylabel("R")

    y = 0.5
    if params is not None:
        for n, v in params.items():
            plt.text(0.7, y, f"{n} = {v:.3g}", transform=ax.transAxes)
            y += 0.05

    plt.tight_layout()
    plt.savefig(filename)


####################################################################
#                          Data Handling                           #
####################################################################


def get_Experimental_data(qmin, qmax):
    """
    read experimental data, remove some duplicate q-values
    recalculate q axis to inverse nm
    """
    data = numpy.genfromtxt(filename, unpack=True)

    r0 = numpy.where(data[0] - numpy.roll(data[0], 1) == 0)
    data = numpy.delete(data, r0, 1)

    data[0] = data[0]/angstrom
    data[3] = data[3]/angstrom

    data[1] = data[1]
    data[2] = data[2]

    so = numpy.argsort(data[0])

    data = data[:, so]

    minIndex = numpy.argmin(numpy.abs(data[0] - qmin))
    maxIndex = numpy.argmin(numpy.abs(data[0] - qmax))

    return data[:, minIndex:maxIndex + 1]


####################################################################
#                          Fit Function                            #
####################################################################


def run_fit_ba(q_axis, r_data, r_uncertainty, simulationFactory, startParams):

    fit_objective = ba.FitObjective()
    fit_objective.setObjectiveMetric("chi2")

    fit_objective.addSimulationAndData(
        lambda params: simulationFactory(q_axis, params), r_data, r_uncertainty,
        1)

    fit_objective.initPrint(10)

    params = ba.Parameters()
    for name, p in startParams.items():
        params.add(name, p[0], min=p[1], max=p[2])

    minimizer = ba.Minimizer()

    result = minimizer.minimize(fit_objective.evaluate, params)
    fit_objective.finalize(result)

    return {r.name(): r.value for r in result.parameters()}


####################################################################
#                          Main Function                           #
####################################################################

if __name__ == '__main__':

    if len(argv) > 1 and argv[1] == "fit":
        fixedParams = {
            # parameters can be moved here to keep them fixed
        }
        fixedParams = {d: v[0] for d, v in fixedParams.items()}

        startParams = {
            # own starting values
            "q_offset": (0, -0.02, 0.02),
            "q_res/q": (0, 0, 0.02),
            "t_pt/nm": (53, 40, 60),
            "r_si/nm": (1.22, 0, 5),
            "r_pt/nm": (0.25, 0, 5),
            "intensity": (1, 0, 2),
        }
        fit = True

    else:
        startParams = {}
        fixedParams = {
            # parameters from our own fit run
            'q_offset': 0.015085985992837999,
            'q_res/q': 0.010156450689003465,
            't_pt/nm': 48.564838355355405,
            'r_si/nm': 1.2857515425763575,
            'r_pt/nm': 0.2868252673771518,
            'intensity': 1.3156374978332654
        }
        fit = False

    paramsInitial = {d: v[0] for d, v in startParams.items()}

    qzs = numpy.linspace(qmin, qmax, scan_size)
    q, r = qr(run_simulation(qzs, paramsInitial))
    data = get_Experimental_data(qmin, qmax)

    plot(q, r, data, f'PtLayerFit_initial.pdf',
         dict(paramsInitial, **fixedParams))

    if fit:
        fitResult = run_fit_ba(data[0], data[1], data[2], run_simulation,
                               startParams)

        print("Fit Result:")
        print(fitResult)

        q, r = qr(run_simulation(qzs, fitParams=fitResult))
        plot(q, r, data, f'PtLayerFit_fit.pdf', dict(fitResult, **fixedParams))
