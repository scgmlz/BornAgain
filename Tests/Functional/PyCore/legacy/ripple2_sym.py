# Functional test: triangular ripple formfactor within the 1D-paracrystal model

from __future__ import print_function
import numpy, os, sys

import utils
from libBornAgainCore import *


# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0)
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    ripple2_ff = FormFactorRipple2(100 * nanometer, 20 * nanometer, 4 * nanometer, 0 * nanometer)
    ripple = Particle(mParticle, ripple2_ff)

    particle_layout = ParticleLayout()
    particle_layout.addParticle(ripple, 1.0)

    interference = InterferenceFunctionRadialParaCrystal(20 * nanometer, 1e7 * nanometer)
    pdf = FTDistribution1DGauss(4 * nanometer)
    interference.setProbabilityDistribution(pdf)
    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    substrate_layer = Layer(mSubstrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -1.5 * degree, 1.5 * degree, 100, 0.0 * degree, 2.0 * degree)
    simulation.setBeamParameters(1.6 * angstrom, 0.3 * degree, 0.0 * degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()

    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result = RunSimulation()

    reference = utils.get_reference_data("ripple2_sym_reference.int.gz")

    diff = getRelativeDifference(result, reference)

    status = "OK"
    if (diff > 1e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "Ripple2", "Triangular ripple within the 1D-paracrystal model", diff, status


# -------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name, description, diff, status = runTest()
    print(name, description, diff, status)
    if("FAILED" in status):
        exit(1)
