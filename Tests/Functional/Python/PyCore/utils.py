"""
Collection of utils for testing
"""

import gzip, numpy, sys, os
import bornagain as ba
from bornagain import deg, angstrom

REFERENCE_DIR = "@TEST_REFERENCE_DIR_PY_CORE@"


def get_difference(data, reference):
    """
    calculate numeric difference between result and reference data
    """
    reference = reference.reshape(data.shape)
    data -= reference
    diff = 0.0
    epsilon = sys.float_info.epsilon
    for x, y in numpy.ndindex(data.shape):
        v1 = data[x][y]
        v2 = reference[x][y]
        if v1 <= epsilon and v2 <= epsilon:
            diff += 0.0
        elif v2 <= epsilon:
            diff += abs(v1/epsilon)
        else:
            diff += abs(v1/v2)
    diff = diff/data.size
    if numpy.isnan(diff):
        raise ba.Exception("get_difference", "isnan")
    return diff


def get_reference_data(filename):
    """
    read and return reference data from file
    """
    return ba.IntensityDataIOFactory.readIntensityData(
        os.path.join(REFERENCE_DIR, filename))


def get_simulation_MiniGISAS(sample):
    detector = ba.SphericalDetector(25, -2*deg, 2*deg, 25, 0*deg, 2*deg)
    beam = ba.Beam(1., 1*angstrom, ba.Direction(0.2*deg, 0))
    return ba.GISASSimulation(beam, sample, detector)
