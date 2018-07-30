"""
Turns a Python example into a functional persistence test via CMake machinery.
"""

import sys
import os
import glob

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba

REFERENCE_DIR = "@PYPERSIST_REFERENCE_DIR@"
EXAMPLE_DIR = "@EXAMPLE_DIR@"
EXAMPLE_NAME = "@EXAMPLE_NAME@"
OUTPUT_DIR = "@OUTPUT_DIR@"
TOLERANCE = @PYPERSIST_TOLERANCE@

sys.path.append(EXAMPLE_DIR)
example = __import__(EXAMPLE_NAME)

simulationObject = None


def get_simulation_SpecularSimulation():
    """
    Returns custom simulation for SpecularSimulation.py.
    """
    simulation = example.get_simulation()
    beam = simulation.getInstrument().getBeam()
    wavelength = beam.getWavelength()
    axis = simulation.getAlphaAxis()
    footprint = beam.footprintFactor()
    simulation.setBeamParameters(
        wavelength, 10, axis.getMin(), axis.getMax(), footprint)
    return simulation


def get_simulation_DepthProbe():
    """
    Returns custom simulation in the case of depth probe.
    """
    simulation = example.get_simulation()
    beam = simulation.getInstrument().getBeam()
    wavelength = beam.getWavelength()
    incl_axis = simulation.getAlphaAxis()
    z_axis = simulation.getZAxis()
    footprint = beam.footprintFactor()
    simulation.setBeamParameters(
        wavelength, 10, incl_axis.getMin(), incl_axis.getMax(), footprint)
    simulation.setZSpan(10, z_axis.getMin(), z_axis.getMax())
    return simulation


def get_simulation_RectangularGrating():
    """
    Returns custom simulation for RectangularGrating.py.
    Contains smaller detector to make MC integration happy on all platforms
    """
    simulation = example.get_simulation()
    simulation.setDetectorParameters(5, -0.01*ba.deg, 0.01*ba.deg, 6, 0.0, 0.02*ba.deg)
    return simulation


def get_simulation_GenericExample():
    """
    Returns minified simulation for majority of examples. Detector size is adjusted.
    The idea is that all other example's setting related to the simulation (MC integration flags,
    threads settings etc) remains intact.
    """
    simulation = example.get_simulation()
    detector = simulation.getInstrument().getDetector()

    # preserving axes range, making less bins
    ax = detector.getAxis(0)
    ay = detector.getAxis(1)
    xmin, xmax = ax.getMin(), ax.getMax()
    ymin, ymax = ay.getMin(), ay.getMax()
    simulation.setDetectorParameters(5, xmin, xmax, 6, ymin, ymax)

    return simulation


def get_minified_simulation():
    """
    Returns a simulation constructed from example simulation with smaller detector.
    """
    if "ex06_Reflectometry" in EXAMPLE_DIR:
        return get_simulation_SpecularSimulation()

    elif EXAMPLE_NAME == "RectangularGrating":
        return get_simulation_RectangularGrating()

    elif EXAMPLE_NAME == "DepthProbe":
        return get_simulation_DepthProbe()

    else:
        return get_simulation_GenericExample()


def adjusted_simulation():
    """
    Returns pre-calculated minified simulation. Function is intended for
    injection into python example file.
    """
    global simulationObject
    return simulationObject


def run_simulation():
    """
    Runs simulation and returns resulting intensity map.
    """

    # create minified simulation object
    global simulationObject
    simulationObject = get_minified_simulation()

    # INJECTION HERE: replacing get_simulation() method of example with local method
    example.get_simulation = adjusted_simulation
    return example.run_simulation()


def save(result, filename):

    filename += ".ref.int.gz"
    ba.IntensityDataIOFactory.writeSimulationResult(result, filename)

    print("example_template.py -> Writing results in '{0}'".format(filename))


def get_reffile_name(example_name):
    """
    Returns full name of reference file for given basename
    """
    reffiles = glob.glob(os.path.join(REFERENCE_DIR, example_name+"*"))
    if len(reffiles) != 1:
        print("Can't find reference file in '{0}' for name '{1}'".format(REFERENCE_DIR, example_name))
        print("Possible candidates", reffiles)
        return None
    return reffiles[0]


def save_result(result, filename):
    """
    Writing result to the file with given name into test output directory.
    """
    fullname = os.path.join(OUTPUT_DIR, filename)
    print("Writing results in '{0}'".format(fullname))
    try:
        ba.IntensityDataIOFactory.writeSimulationResult(result, fullname)
    except Exception as err:
        print("Exception caught, failed to write file", err)



def check_result(result, example_name):
    print("Checking results for '{}'".format(example_name))
    reffile = get_reffile_name(example_name)

    if not reffile:
        save_result(result, example_name+".int.gz")
        raise Exception("Absent reference file")

    print("Loading reference file '{}'".format(reffile))
    reference = ba.IntensityDataIOFactory.readIntensityData(reffile)

    diff = ba.getRelativeDifference(result.histogram(), reference)

    if diff > TOLERANCE:
        print("Failure - Difference {0} is above tolerance level {1}".format(diff, TOLERANCE))
        reffile_basename = os.path.basename(reffile)
        save_result(result, reffile_basename)
        raise Exception("Tolerance exceeded")
    else:
        print("Success - Difference {0} is below tolerance level{1}".format(diff, TOLERANCE))


def process_result(result, example_name):
    try:
        check_result(result, example_name)
        return 0
    except Exception:
        return 1


def process_example():
    result = run_simulation()

    nfailures = 0
    if type(result) is dict:
        for dict_key, subresult in result.items():
            nfailures += process_result(subresult, EXAMPLE_NAME + "." + str(dict_key))
    else:
        nfailures += process_result(result, EXAMPLE_NAME)

    return nfailures


if __name__ == '__main__':
    sys.exit(process_example())

