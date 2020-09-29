'''
Simulation demo: Size Space Coupling Approximation
'''

import os, sys
import numpy
import matplotlib
import math
from bornagain import *

Nframes = 50

kappa = 0.

# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mVacuum = HomogeneousMaterial("Vacuum", 0.0, 0.0)
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8)
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
    interference = InterferenceFunctionRadialParaCrystal(6 * nanometer)
    pdf = FTDistribution1DGauss(.5 * nanometer)
    interference.setProbabilityDistribution(pdf)
    # set coupling between size and space
    interference.setKappa(kappa)
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


def SetParameters(i):
    global kappa
    kappa = 0.01 + (2.0/Nframes)*i

#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    files = []
    fig = plt.figure(figsize=(5,5))
    ax = fig.add_subplot(111)
    for i in range(Nframes):
        SetParameters(i)
        result = RunSimulation() + 1  # for log scale
        ax.cla()
        im = ax.imshow(result, vmax=1e3,
                 norm=matplotlib.colors.LogNorm(),
                 extent=[-4.0, 4.0, 0, 8.0])
        plt.xlabel(r'$\phi_f$', fontsize=20)
        plt.ylabel(r'$\alpha_f$', fontsize=20)
        if i==0:
            plt.colorbar(im)
        fname = '_tmp%03d.png'%i
        print 'Saving frame', fname
        try:
            fig.savefig(fname)
        except IOError as e:
            print "Frame cannot be saved. I/O error({0}): {1}".format(e.errno, e.strerror)
            print "Copy these examples to the directory where you have a write permission and enough free space to save the movie."
            sys.exit()
        except:
            print "Frame cannot be saved. Error:", sys.exc_info()[0]
            sys.exit()
        else:
            files.append(fname)

    try:
        os.system("mencoder 'mf://_tmp*.png' -mf type=png:fps=10 -ovc lavc -lavcopts vcodec=wmv2 -oac copy -o animation3.mpg")
        print 'Removing temporary files'
        os.system("rm _tmp*")
    except:
        print "Movie cannot be saved. Error:", sys.exc_info()[0]
        sys.exit()

