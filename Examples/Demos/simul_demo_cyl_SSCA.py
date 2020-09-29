'''
Simulation demo: Size Space Coupling Approximation
'''

import numpy
import matplotlib
import math
from bornagain import *

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mVacuum = HomogeneousMaterial("Vacuum", 0.0, 0.0)
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    mParticle =HomogeneousMaterial("Particle", 6e-4, 2e-8)
    mLayer = HomogeneousMaterial("Layer", 2e-5, 2e-8)

    # collection of particles
    cylinder_ff1 = FormFactorCylinder(2 * nanometer, 5 * nanometer)
    cylinder_ff2 = FormFactorCylinder(3 * nanometer, 6 * nanometer)
    cylinder_ff3 = FormFactorCylinder(4 * nanometer, 7 * nanometer)
    cylinder1 = Particle(mParticle, cylinder_ff1)
    cylinder2 = Particle(mParticle, cylinder_ff2)
    cylinder3 = Particle(mParticle, cylinder_ff3)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder1)
    particle_layout.addParticle(cylinder2)
    particle_layout.addParticle(cylinder3)
    interference = InterferenceFunctionRadialParaCrystal(5 * nanometer)
    pdf = FTDistribution1DGauss(1 * nanometer)
    interference.setProbabilityDistribution(pdf)
    # set coupling between size and space
    interference.setKappa(2)
    particle_layout.setInterferenceFunction(interference)

    # vacuum layer with particles and substrate form multi layer
    vacuum_layer = Layer(mVacuum)
    vacuum_layer.addLayout(particle_layout)
    substrate_layer = Layer(mSubstrate)
    multi_layer = MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    roughness = LayerRoughness(10 * nanometer, 3, 20 * nanometer)
    multi_layer.addLayerWithTopRoughness(substrate_layer, roughness)

    # build and run experiment
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -4.0 * degree, 4.0 * degree, 100, 0.0 * degree, 8.0 * degree)
    simulation.setBeamParameters(1.0 * angstrom, 0.2 * degree, 0.0 * degree)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # intensity data
    return simulation.result().array()


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation() + 1 # for log scale
    im = plt.imshow(result, norm=matplotlib.colors.LogNorm(),
                 extent=[-4.0, 4.0, 0, 8.0])
    plt.colorbar(im)
    plt.xlabel(r'$\phi_f$', fontsize=20)
    plt.ylabel(r'$\alpha_f$', fontsize=20)
    plt.show()
