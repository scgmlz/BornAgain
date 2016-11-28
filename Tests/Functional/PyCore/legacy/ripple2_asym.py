# Functional test: triangular asymetric ripple formfactor within the 1D-paracrystal model

from __future__ import print_function
import numpy, os, sys

import utils
import libBornAgainCore as ba
from libBornAgainCore import deg, angstrom, nm

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def runSimulation():
    # defining materials
    mAmbience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    mSubstrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    mParticle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    ripple2_ff = ba.FormFactorRipple2(100*nm, 20*nm, 4*nm, -3*nm)
    ripple = ba.Particle(mParticle, ripple2_ff)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(ripple, 1.0)

    interference = ba.InterferenceFunctionRadialParaCrystal(20*nm, 1e7*nm)
    pdf = ba.FTDistribution1DGauss(4*nm)
    interference.setProbabilityDistribution(pdf)
    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = ba.Layer(mAmbience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(mSubstrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.5*deg, 1.5*deg, 100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.6*angstrom, 0.3*deg, 0.0*deg)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # # intensity data
    return simulation.getIntensityData()


# --------------------------------------------------------------
# run test and analyse test results
# --------------------------------------------------------------
def runTest():
    result = runSimulation()
    reference = utils.get_reference_data("ripple2_asym_reference.int.gz")
    diff = ba.getRelativeDifference(result, reference)
    status = "OK"
    if (diff > 1e-10 or numpy.isnan(diff)):
        status = "FAILED"
    return "Ripple2a", "Triangular asymetric ripple within the 1D-paracrystal model", diff, status


# -------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    name, description, diff, status = runTest()
    print(name, description, diff, status)
    if("FAILED" in status):
        exit(1)
