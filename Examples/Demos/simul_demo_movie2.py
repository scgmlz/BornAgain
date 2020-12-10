"""
Simulation demo: make movie
"""

import os, sys
import numpy
import matplotlib
import math
from bornagain import *

radius = 1
layer_thickness = 1
Nframes = 100
Ngrowframes = 30


# ----------------------------------
# describe sample and run simulation
# ----------------------------------
def RunSimulation():
    # defining materials
    mVacuum = HomogeneousMaterial("Vacuum", 0.0, 0.0)
    mSubstrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    mParticle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    semisphere_ff = FormFactorTruncatedSphere(radius, radius, 0)
    semisphere = Particle(mParticle, semisphere_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(semisphere)

    # interference function
    interference = InterferenceFunctionRadialParaCrystal(6*nm)
    pdf = FTDistribution1DGauss(1*nm)
    interference.setProbabilityDistribution(pdf)
    particle_layout.setInterferenceFunction(interference)

    # vacuum layer with particles and substrate form multi layer
    vacuum_layer = Layer(mVacuum)
    vacuum_layer.addLayout(particle_layout)
    film_layer = Layer(mParticle, layer_thickness)
    substrate_layer = Layer(mSubstrate)
    multi_layer = MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    multi_layer.addLayer(film_layer)
    multi_layer.addLayer(substrate_layer)

    # build and run experiment
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -4.0*deg, 4.0*deg, 100, 0.0*deg,
                                     8.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setSample(multi_layer)
    simulation.runSimulation()
    # intensity data
    return simulation.result().array()


def SetParameters(i):
    global radius
    global layer_thickness
    if i < Ngrowframes:
        radius = (1. + (3.0/Ngrowframes)*i)*nm
        layer_thickness = 0.01*nm
    else:
        radius = 4.*nm
        layer_thickness = (0.01 + (0.5/(Nframes - Ngrowframes))*
                           (i - Ngrowframes))*nm


#-------------------------------------------------------------
# main()
#-------------------------------------------------------------
if __name__ == '__main__':
    files = []
    fig = plt.figure(figsize=(5, 5))
    ax = fig.add_subplot(111)
    for i in range(Nframes):
        SetParameters(i)
        result = RunSimulation() + 1  # for log scale
        ax.cla()
        im = ax.imshow(result,
                       vmax=1e3,
                       norm=matplotlib.colors.LogNorm(),
                       extent=[-4.0, 4.0, 0, 8.0])
        plt.xlabel(r'$\phi_f$', fontsize=20)
        plt.ylabel(r'$\alpha_f$', fontsize=20)
        if i == 0:
            plt.colorbar(im)
        fname = '_tmp%03d.png' % i
        print 'Saving frame', fname
        try:
            fig.savefig(fname)
        except IOError as e:
            print "Frame cannot be saved. I/O error({0}): {1}".format(
                e.errno, e.strerror)
            print "Copy these examples to the directory where you have a write permission and enough free space to save the movie."
            sys.exit()
        except:
            print "Frame cannot be saved. Error:", sys.exc_info()[0]
            sys.exit()
        else:
            files.append(fname)
    try:
        os.system(
            "mencoder 'mf://_tmp*.png' -mf type=png:fps=10 -ovc lavc -lavcopts vcodec=wmv2 -oac copy -o animation2.mpg"
        )
        print 'Removing temporary files'
        os.system("rm _tmp*")
    except:
        print "Movie cannot be saved. Error:", sys.exc_info()[0]
        sys.exit()
