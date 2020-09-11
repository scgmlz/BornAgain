# Functional test: Magnetic cylinders in DWBA with zero magnetic field
from __future__ import print_function
import sys
import os
import numpy
import gzip
from utils import get_difference

from bornagain import *

REFERENCE_DIR = "@TEST_REFERENCE_DIR@/Python"

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def getSimulationIntensity(rho_beam, efficiency):
    print("- simulate", flush=True)
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
    mSubstrate = HomogeneousMaterial("Substrate", 15e-6, 0.0)

    magnetization = kvector_t(0, 1e6, 0)

    magParticle = HomogeneousMaterial("magParticle", 5e-6, 0.0, magnetization )
    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(magParticle, cylinder_ff)

    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)
    interference = InterferenceFunctionNone()
    particle_layout.setInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -1*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree)
    zplus = kvector_t(0.0, 0.0, 1.0)
    simulation.setAnalyzerProperties(zplus, efficiency, 0.5)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    simulation.setBeamPolarization(rho_beam)
    simulation.setSample(multi_layer)
    simulation.setBeamIntensity(1e9)
    simulation.runSimulation()
    print("- - simulation done", flush=True)
    return simulation.result()


# TODO: revert to some standard solution. For other tests, get_reference_data comes from utils.py.
def get_reference_data(filename):
    """
    read and return reference data from file
    """
    path = os.path.join(REFERENCE_DIR,filename)
    print("- read reference from", path, flush=True)
    ret = IntensityDataIOFactory.readIntensityData(path)
    print("- - reference read", flush=True)
    return ret

# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def run_test():
    print("run test", flush=True)
    zplus = kvector_t(0.0, 0.0, 1.0)
    zmin = kvector_t(0.0, 0.0, -1.0)

    # IntensityDataIOFactory.writeIntensityData(getSimulationIntensity(zplus, 1.0), 'polmagcylinders2_reference_00.int')
    # IntensityDataIOFactory.writeIntensityData(getSimulationIntensity(zplus, -1.0), 'polmagcylinders2_reference_01.int')
    # IntensityDataIOFactory.writeIntensityData(getSimulationIntensity(zmin, 1.0), 'polmagcylinders2_reference_10.int')
    # IntensityDataIOFactory.writeIntensityData(getSimulationIntensity(zmin, -1.0), 'polmagcylinders2_reference_11.int')
    diff = 0.0
    diff += get_difference(getSimulationIntensity(zplus, 1.0).array(),
                           get_reference_data('polmagcylinders2_reference_00.int.gz').getArray())
    diff += get_difference(getSimulationIntensity(zplus, -1.0).array(),
                           get_reference_data('polmagcylinders2_reference_01.int.gz').getArray())
    diff += get_difference(getSimulationIntensity(zmin, 1.0).array(),
                           get_reference_data('polmagcylinders2_reference_10.int.gz').getArray())
    diff += get_difference(getSimulationIntensity(zmin, -1.0).array(),
                           get_reference_data('polmagcylinders2_reference_11.int.gz').getArray())

    diff /= 4.0
    status = "OK"
    if diff > 2e-10:
        status = "FAILED"
    return "PolarizedDWBAZeroMag", "functional test: polarized DWBA with non-zero magnetic field", diff, status


if __name__ == '__main__':
    name, description, diff, status = run_test()
    print(name, description, diff, status)
    if("FAILED" in status):
        exit(1)
