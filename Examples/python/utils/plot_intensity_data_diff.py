#!/usr/bin/env python
'''
Plots intensity data difference stored in BornAgain "*.int" or "*.int.gz" format
Usage: python plot_intensity_data_diff.py intensity_reference.int.gz intensity_other.int.gz
'''

import numpy as np
import bornagain as ba
import plot_intensity_data as pid
import sys


def plot_intensity_data_diff(filename1, filename2):
    intensity_ref = ba.IntensityDataIOFactory.readIntensityData(filename1)
    intensity_other = ba.IntensityDataIOFactory.readIntensityData(filename2)
    data = 2 * np.abs(intensity_ref.getArray() - intensity_other.getArray()) \
           / (np.abs(intensity_ref.getArray()) + np.abs(intensity_other.getArray()))
    if data.max() == 0:
        exit("Both data sets are equal, there is nothing to plot.")
    rank = intensity_ref.getRank()
    if rank == 2:
        pid.plot_raw_data_2d(data,
                             [intensity_ref.getXmin() / ba.deg, intensity_ref.getXmax() / ba.deg,
                              intensity_ref.getYmin() / ba.deg, intensity_ref.getYmax() / ba.deg],
                             data.max())
    elif rank == 1:
        axis_values = np.asarray(intensity_ref.getXaxis().getBinCenters()) / ba.deg
        pid.plot_raw_data_1d(axis_values, data, log_y=False)
    else:
        exit("Error in plot_intensity_data_diff: wrong data rank")


if __name__ == '__main__':
    if len(sys.argv)!=3:
        exit("Usage: plot_intensity_data_diff.py reference.int.gz other.int.gz")

    plot_intensity_data_diff(sys.argv[1], sys.argv[2])
