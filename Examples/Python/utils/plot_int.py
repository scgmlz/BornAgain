#!/usr/bin/env python3
"""
Plots data stored in BornAgain's .int or .int.gz format.
Can handle both 1D and 2D arrays.
"""

import argparse
import sys
import numpy as np
import bornagain as ba
from matplotlib import pyplot as plt
from matplotlib import rc, colors
rc('font', **{'family': 'sans-serif', 'sans-serif': ['Helvetica']})
rc('text', usetex=True)


def plot_int(args):
    data = ba.IntensityDataIOFactory.readIntensityData(args.file)
    if args.max:
        intensity_max = args.max
    else:
        intensity_max = data.getMaximum()
    if args.min:
        intensity_min = args.min
    else:
        intensity_min = data.getMinimum()
    ylog = not args.ylin
    if ylog and intensity_min <= 0:
        intensity_min = intensity_max/1e6

    if args.verbose:
        print(f'Data extend from {data.getMinimum()} to {data.getMaximum()}')
    if data.rank() == 1:
        # some white space above and below automatically determined y range:
        if not args.max:
            if args.ylin:
                intensity_max = intensity_max + (intensity_max -
                                                 intensity_min)*0.05
            else:
                intensity_max = intensity_max*(intensity_max/
                                               intensity_min)**0.05
        if not args.min:
            if args.ylin:
                intensity_min = intensity_min - (intensity_max -
                                                 intensity_min)*0.05
            else:
                intensity_min = intensity_min/(intensity_max/
                                               intensity_min)**0.05
        plot_int_1d(data, ylog, intensity_min, intensity_max)
    elif data.rank() == 2:
        plot_int_2d(data, ylog, intensity_min, intensity_max)
    else:
        exit("Error in plot_int: wrong data rank")


def plot_int_2d(histogram, ylog, intensity_min, intensity_max):
    plot_raw_data_2d(histogram.array(), [
        histogram.getXmin()/ba.deg,
        histogram.getXmax()/ba.deg,
        histogram.getYmin()/ba.deg,
        histogram.getYmax()/ba.deg
    ], ylog, intensity_min, intensity_max)


def plot_raw_data_2d(values, extent_array, ylog, intensity_min, intensity_max):
    if ylog:
        norm = colors.LogNorm(intensity_min, intensity_max)
    else:
        norm = colors.Normalize(intensity_min, intensity_max)
    im = plt.imshow(values, norm=norm, extent=extent_array, aspect='auto')
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


def plot_int_1d(histogram, ylog, intensity_min, intensity_max):
    axis_values = np.asarray(histogram.xAxis().binCenters())/ba.deg
    array_values = histogram.array()
    plt.ylim(intensity_min, intensity_max)
    plot_raw_data_1d(axis_values, array_values, ylog)


def plot_raw_data_1d(axis, values, ylog):
    if ylog:
        plt.semilogy(axis, values)
    else:
        plt.plot(axis, values)

    plt.xlabel(r'$\alpha_i (^{\circ})$', fontsize=16)
    plt.ylabel(r'Value (a.u.)', fontsize=16)
    plt.show()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-v",
                        "--verbose",
                        action="store_true",
                        help="print some output to the terminal")
    parser.add_argument("file",
                        type=str,
                        help="input data file (.int or .int.gz)")
    parser.add_argument("-l", "--min", type=float, help="upper plot limit")
    parser.add_argument("-u", "--max", type=float, help="lower plot limit")
    parser.add_argument(
        "-y",
        "--ylin",
        action="store_true",
        help="linear y scale",
    )
    args = parser.parse_args()

    plot_int(args)
