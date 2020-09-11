'''
Simulation demo: Cylinder form factor without interference
'''

import numpy
import matplotlib
import math
from bornagain import *

M_PI = numpy.pi

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mAmbience = HomogeneousMaterial("Air", 0.0, 0.0 )
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8 )
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8 )

    # particle 1
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(mParticle, cylinder_ff)
    position = kvector_t(0.0, 0.0, 0.0)
    cylinder.setPosition(position)
    particle_layout1 = ParticleLayout()
    particle_layout1.addParticle(cylinder, 1.0)
    # particle 2
    position_2 = kvector_t(5.0*nanometer, 5.0*nanometer, 0.0)
    cylinder.setPosition(position_2)
    particle_layout2 = ParticleLayout()
    particle_layout2.addParticle(cylinder, 1.0)

    # interference function
    interference = InterferenceFunction2DLattice.createSquare(10.0*nanometer)
    pdf = FTDecayFunction2DCauchy(300.0*nanometer/2.0/M_PI, 100.0*nanometer/2.0/M_PI, 0)
    interference.setDecayFunction(pdf)
    particle_layout1.setInterferenceFunction(interference)
    particle_layout2.setInterferenceFunction(interference)

    # top air layer
    air_layer = Layer(mAmbience)
    air_layer.addLayout(particle_layout1)
    air_layer.addLayout(particle_layout2)

    # substrate layer
    substrate_layer = Layer(mSubstrate, 0)

    # multilayer
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -2.0*degree, 2.0*degree, 100, 0.0*degree, 4.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)

    # run simulation
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    return simulation.result().array()


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    result = RunSimulation()
    im = plt.imshow(result+1,
                 norm=matplotlib.colors.LogNorm(),
                 extent=[-2.0, 2.0, 0, 4.0])
    plt.colorbar(im)
    plt.xlabel(r'$\phi_f$', fontsize=20)
    plt.ylabel(r'$\alpha_f$', fontsize=20)
    plt.show()




