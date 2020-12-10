#!/usr/bin/env python3
"""
Plots intensity data difference stored in BornAgain "*.int" or "*.int.gz" format
Usage: python plot_diff_int.py reference.int.gz new.int.gz
"""

import numpy as np
import bornagain as ba
import plot_int as pid
import sys


def plot_diff_int(filename1, filename2):
    intensity_ref = ba.IntensityDataIOFactory.readIntensityData(filename1)
    intensity_other = ba.IntensityDataIOFactory.readIntensityData(filename2)
    data = 2 * np.abs(intensity_ref.array() - intensity_other.array()) \
           / (np.abs(intensity_ref.array()) + np.abs(intensity_other.array()))
    if data.max() == 0:
        exit("Both data sets are equal, there is nothing to plot.")
    rank = intensity_ref.rank()
    if rank == 2:
        pid.plot_raw_data_2d(data, [
            intensity_ref.getXmin()/ba.deg,
            intensity_ref.getXmax()/ba.deg,
            intensity_ref.getYmin()/ba.deg,
            intensity_ref.getYmax()/ba.deg
        ], data.max())
    elif rank == 1:
        axis_values = np.asarray(intensity_ref.xAxis().binCenters())/ba.deg
        pid.plot_raw_data_1d(axis_values, data, log_y=False)
    else:
        exit("Error in plot_diff_int: wrong data rank")


if __name__ == '__main__':
    if len(sys.argv) != 3:
        exit("Usage: plot_diff_int.py reference.int.gz other.int.gz")

    plot_diff_int(sys.argv[1], sys.argv[2])
