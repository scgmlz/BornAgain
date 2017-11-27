#!/usr/bin/env python
'''
Plots data stored in BornAgain "*.int" or "*.int.gz" format
Can handle both 1D and 2D arrays
Usage: python plot_intensity_data.py intensity_file.int.gz [intensity_max]
'''

import sys
import numpy as np
import bornagain as ba
from matplotlib import pyplot as plt
from matplotlib import rc, colors
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)


def plot_intensity_data(file_name, intensity_max=None):
    data = ba.IntensityDataIOFactory.readIntensityData(file_name)
    if intensity_max is None:
        intensity_max = data.getMaximum()
    if data.getRank() == 1:
        plot_intensity_data_1d(data, intensity_max)
    elif data.getRank() == 2:
        plot_intensity_data_2d(data, intensity_max)
    else:
        exit("Error in plot_intensity_data: wrong data rank")


def plot_intensity_data_2d(histogram, intensity_max):
    plot_raw_data_2d(histogram.getArray(),
                     [histogram.getXmin() / ba.deg, histogram.getXmax() / ba.deg,
                      histogram.getYmin() / ba.deg, histogram.getYmax() / ba.deg],
                     intensity_max)


def plot_raw_data_2d(values, extent_array, intensity_max):
    im = plt.imshow(values,
                    norm=colors.LogNorm(1.0, intensity_max),
                    extent=extent_array,
                    aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


def plot_intensity_data_1d(histogram, intensity_max):
    axis_values = np.asarray(histogram.getXaxis().getBinCenters()) / ba.deg
    array_values = histogram.getArray() * intensity_max / histogram.getMaximum()
    plot_raw_data_1d(axis_values, array_values)


def plot_raw_data_1d(axis, values, log_y=True):
    if log_y:
        plt.semilogy(axis, values)
    else:
        plt.plot(axis, values)
    plt.xlabel(r'$\alpha_i (^{\circ})$', fontsize=16)
    plt.ylabel(r'Value (a.u.)', fontsize=16)
    plt.show()


if __name__ == '__main__':
    if len(sys.argv)<2 or len(sys.argv)>3:
        exit("Usage: plot_intensity_data.py intensity_file.int.gz [intensity_max]")

    if len(sys.argv)==2:
        plot_intensity_data(sys.argv[1])
    else:
        plot_intensity_data(sys.argv[1], float(sys.argv[2]))
