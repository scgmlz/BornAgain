"""
This simulation example demonstrates how to replicate the
fitting example "Magnetically Dead Layers in Spinel Films"
given at the Nist website:
https://www.nist.gov/ncnr/magnetically-dead-layers-spinel-films

For simplicity, here we only reproduce the first part of that 
demonstration without the magnetically dead layer.
"""

# import boranagain
import bornagain as ba
from bornagain import deg, angstrom, nm

import numpy
import matplotlib.pyplot as plt

# import more libs needed for data processing
from re import match, DOTALL
from sys import argv
from io import BytesIO
from urllib.request import urlopen
from zipfile import ZipFile
from os.path import isfile

# q-range on which the simulation and fitting are to be performed
qmin = 0.05997
qmax = 1.96

# number of points on which the computed result is plotted
scan_size = 1500

# The SLD of the substrate is kept constant
sldMao = (5.377e-06, 0)

# constant to convert between magnetization and magnetic SLD
RhoMconst = 2.910429812376859e-12

####################################################################
#                  Create Sample and Simulation                    #
####################################################################


def get_sample(params):
    """
    construct the sample with the given parameters
    """
    magnetizationMagnitude = params["rhoM_Mafo"]*1e-6/RhoMconst
    angle = 0
    magnetizationVector = ba.kvector_t(
        magnetizationMagnitude*numpy.sin(angle*deg),
        magnetizationMagnitude*numpy.cos(angle*deg), 0)

    mat_vacuum = ba.MaterialBySLD("Vacuum", 0.0, 0.0)
    mat_layer = ba.MaterialBySLD("(Mg,Al,Fe)3O4", params["rho_Mafo"]*1e-6, 0,
                                 magnetizationVector)
    mat_substrate = ba.MaterialBySLD("MgAl2O4", *sldMao)

    ambient_layer = ba.Layer(mat_vacuum)
    layer = ba.Layer(mat_layer, params["t_Mafo"]*angstrom)
    substrate_layer = ba.Layer(mat_substrate)

    r_Mafo = ba.LayerRoughness()
    r_Mafo.setSigma(params["r_Mafo"]*angstrom)

    r_substrate = ba.LayerRoughness()
    r_substrate.setSigma(params["r_Mao"]*angstrom)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(ambient_layer)
    multi_layer.addLayerWithTopRoughness(layer, r_Mafo)
    multi_layer.addLayerWithTopRoughness(substrate_layer, r_substrate)

    return multi_layer


def get_simulation(q_axis, parameters, polarization, analyzer):
    """
    Returns a simulation object.
    Polarization, analyzer and resolution are set
    from given parameters
    """
    simulation = ba.SpecularSimulation()
    q_axis = q_axis + parameters["q_offset"]
    scan = ba.QSpecScan(q_axis)

    dq = parameters["q_res"]*q_axis
    n_sig = 4.0
    n_samples = 25

    distr = ba.RangedDistributionGaussian(n_samples, n_sig)
    scan.setAbsoluteQResolution(distr, parameters["q_res"])
    simulation.setScan(scan)

    simulation.beam().setPolarization(polarization)
    simulation.setAnalyzerProperties(analyzer, 1.0, 0.5)

    return simulation


def run_simulation(q_axis, fitParams, *, polarization, analyzer):
    """
    Run a simulation on the given q-axis, where the sample is 
    constructed with the given parameters.
    Vectors for polarization and analyzer need to be provided
    """
    parameters = dict(fitParams, **fixedParams)

    sample = get_sample(parameters)
    simulation = get_simulation(q_axis, parameters, polarization, analyzer)

    simulation.setSample(sample)
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


def plot(qs, rs, exps, labels, filename):
    """
    Plot the simulated result together with the experimental data
    """
    fig = plt.figure()
    ax = fig.add_subplot(111)

    for q, r, exp, l in zip(qs, rs, exps, labels):

        ax.errorbar(exp[0],
                    exp[1],
                    xerr=exp[3],
                    yerr=exp[2],
                    fmt='.',
                    markersize=0.75,
                    linewidth=0.5)

        ax.plot(q, r, label=l)

    ax.set_yscale('log')
    plt.legend()

    plt.xlabel("Q [nm${}^{-1}$]")
    plt.ylabel("R")

    plt.tight_layout()
    plt.savefig(filename)


def plotSpinAsymmetry(data_pp, data_mm, q, r_pp, r_mm, filename):
    """
    Plot the simulated spin asymmetry as well its 
    experimental counterpart with errorbars
    """

    # compute the errorbars of the spin asymmetry
    delta = numpy.sqrt(4 * (data_pp[1]**2 * data_mm[2]**2 + \
            data_mm[1]**2 * data_pp[2]**2 ) /
                ( data_pp[1] + data_mm[1] )**4 )

    fig = plt.figure()
    ax = fig.add_subplot(111)

    ax.errorbar(data_pp[0], (data_pp[1] - data_mm[1])/(data_pp[1] + data_mm[1]),
                xerr=data_pp[3],
                yerr=delta,
                fmt='.',
                markersize=0.75,
                linewidth=0.5)

    ax.plot(q, (r_pp - r_mm)/(r_pp + r_mm))

    plt.gca().set_ylim((-0.3, 0.5))

    plt.xlabel("Q [nm${}^{-1}$]")
    plt.ylabel("Spin asymmetry")

    plt.tight_layout()
    plt.savefig(filename)


####################################################################
#                          Data Handling                           #
####################################################################


def normalizeData(data):
    """
    Removes duplicate q values from the input data,
    normalizes it such that the maximum of the reflectivity is
    unity and rescales the q-axis to inverse nm
    """

    r0 = numpy.where(data[0] - numpy.roll(data[0], 1) == 0)
    data = numpy.delete(data, r0, 1)

    data[0] = data[0]/angstrom
    data[3] = data[3]/angstrom

    norm = numpy.max(data[1])
    data[1] = data[1]/norm
    data[2] = data[2]/norm

    so = numpy.argsort(data[0])
    data = data[:, so]

    return data


def filterData(data, qmin, qmax):
    minIndex = numpy.argmin(numpy.abs(data[0] - qmin))
    maxIndex = numpy.argmin(numpy.abs(data[0] - qmax))

    return data[:, minIndex:maxIndex + 1]


def get_Experimental_data(qmin, qmax):
    if hasattr(get_Experimental_data, "raw_data"):
        data_pp = get_Experimental_data.raw_data_pp
        data_mm = get_Experimental_data.raw_data_mm

    else:
        input_Data = downloadAndExtractData()
        data_pp = normalizeData(input_Data[0])
        data_mm = normalizeData(input_Data[1])

        get_Experimental_data.data_pp = data_pp
        get_Experimental_data.data_mm = data_mm
        get_Experimental_data.raw_data = True

    return (filterData(data_pp, qmin, qmax), filterData(data_mm, qmin, qmax))


def downloadAndExtractData():
    url = "https://www.nist.gov/document/spinelfilmzip"

    if not isfile("spinelfilm.zip"):
        downloadfile = urlopen(url)
        with open("spinelfilm.zip", 'wb') as outfile:
            outfile.write(downloadfile.read())

    zipfile = ZipFile("spinelfilm.zip")
    rawdata = zipfile.open("MAFO_Saturated.refl").\
                  read().decode("utf-8")

    table_pp = match(
        r'.*# "polarization": "\+\+"\n#.*?\n# "units".*?\n(.*?)#.*', rawdata,
        DOTALL).group(1)
    table_mm = match(
        r'.*# "polarization": "\-\-"\n#.*?\n# "units".*?\n(.*?)#.*', rawdata,
        DOTALL).group(1)

    data_pp = numpy.genfromtxt(BytesIO(table_pp.encode()), unpack=True)
    data_mm = numpy.genfromtxt(BytesIO(table_mm.encode()), unpack=True)

    return (data_pp, data_mm)


####################################################################
#                          Main Function                           #
####################################################################

if __name__ == '__main__':

    fixedParams = {
        # parameters from our own fit run
        'q_res': 0.010542945012551425,
        'q_offset': 7.971243487467318e-05,
        'rho_Mafo': 6.370140108715461,
        'rhoM_Mafo': 0.27399566816062926,
        't_Mafo': 137.46913056084736,
        'r_Mao': 8.60487712674644,
        'r_Mafo': 3.7844265311293483
    }

    def run_Simulation_pp(qzs, params):
        return run_simulation(qzs,
                              params,
                              polarization=ba.kvector_t(0, 1, 0),
                              analyzer=ba.kvector_t(0, 1, 0))

    def run_Simulation_mm(qzs, params):
        return run_simulation(qzs,
                              params,
                              polarization=ba.kvector_t(0, -1, 0),
                              analyzer=ba.kvector_t(0, -1, 0))

    qzs = numpy.linspace(qmin, qmax, scan_size)
    q_pp, r_pp = qr(run_Simulation_pp(qzs, fixedParams))
    q_mm, r_mm = qr(run_Simulation_mm(qzs, fixedParams))

    data_pp, data_mm = get_Experimental_data(qmin, qmax)

    plot([q_pp, q_mm], [r_pp, r_mm], [data_pp, data_mm], ["$++$", "$--$"],
         f'MAFO_Saturated.pdf')

    plotSpinAsymmetry(data_pp, data_mm, qzs, r_pp, r_mm,
                      "MAFO_Saturated_spin_asymmetry.pdf")
