"""
Fitting example
(This is more detailed version of FitCylindersPrisms.py.
We show how to generate "real" data and how to draw fit progress.
Take a note, that performance here is determined by poor performance of matplotlib drawing routines.)

In this example we use a simple geometry: cylinders and prisms in
air layer, deposited on a substrate layer, with no interference.
There are 4 fitting parameters:
1) radius of cylinders
2) height of cylinders
3) length of prisms
4) height of prisms

Our reference data is 2D intensity map obtained from the simulation of
the same geometry with fixed values cylinder_height = prism3_height
 = cylinder_radius = prism3_length/2 = 1nm.

Then we run our minimization consequently using default
minimization engine, with starting values cylinder_height = prism3_height = 4nm,
cylinder_radius = prism3_length/2 = 6nm as initial fit parameter values.
"""


import numpy
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.path import Path
import math
import random
from bornagain import *

fig = plt.figure(1)
max_line_length = 30


def get_sample(cylinder_height=1.0*nanometer,
               cylinder_radius=1.0*nanometer,
               prism_length=2.0*nanometer,
               prism_height=1.0*nanometer):
    """
    Build the sample representing cylinders and pyramids on top of
    substrate without interference.
    """
    # defining materials
    m_vacuum = HomogeneousMaterial("Vacuum", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(cylinder_radius, cylinder_height)
    cylinder = Particle(m_particle, cylinder_ff)
    prism_ff = FormFactorPrism3(prism_length, prism_height)
    prism = Particle(m_particle, prism_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 0.5)
    particle_layout.addParticle(prism, 0.5)
    interference = InterferenceFunctionNone()
    particle_layout.setInterferenceFunction(interference)

    # vacuum layer with particles and substrate form multi layer
    vacuum_layer = Layer(m_vacuum)
    vacuum_layer.addLayout(particle_layout)
    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    This function has been used once to generate refdata_fitcylinderprisms.int
    """
    # creating sample with set of parameters we will later try to find during the fit
    sample = get_sample(5.0*nanometer, 5.0*nanometer, 5.0*nanometer, 5.0*nanometer)
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    real_data = simulation.result().array()

    # spoiling simulated data with noise to produce "real" data
    # random seed made as in FitSPheresInHexLattice_builder.py example
    np.random.seed(0)
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    IntensityDataIOFactory.writeIntensityData(ba.Histogram2D(noisy),
                                              'refdata_fitcylinderprisms.int')


def get_simulation():
    """
    Create GISAXS simulation with beam and detector defined
    """
    simulation = GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*degree, 1.0*degree, 100, 0.0*degree, 2.0*degree)
    simulation.setBeamParameters(1.0*angstrom, 0.2*degree, 0.0*degree)
    return simulation


class DrawObserver(IFitObserver):
    """
    class which draws fit progress every nth iteration.
    It has to be attached to fit_suite via AttachObserver command
    """
    def __init__(self, draw_every_nth=1):
        IFitObserver.__init__(self, draw_every_nth)
        print "MySampleBuilder ctor"
        self.cyl_points = []
        self.prism_points = []
        self.draw_codes = []

    def update(self, fit_suite):
        fig.clf()
        # plotting real data
        real_data = fit_suite.getFitObjects().getRealData().getArray()
        simulated_data = fit_suite.getFitObjects().getSimulationData().getArray()
        plt.subplot(2, 2, 1)
        im = plt.imshow(real_data + 1, norm=matplotlib.colors.LogNorm(),extent=[-1.0, 1.0, 0, 2.0])
        plt.colorbar(im)
        plt.title('\"Real\" data')
        # plotting real data
        plt.subplot(2, 2, 2)
        im = plt.imshow(simulated_data + 1, norm=matplotlib.colors.LogNorm(),extent=[-1.0, 1.0, 0, 2.0])
        plt.colorbar(im)
        plt.title('Simulated data')
        # plotting parameter space
        if fit_suite.getNumberOfIterations() == 0:
            self.draw_codes.append(Path.MOVETO)
        # elif fit_suite.getNCalls() < max_line_length:
        else:
            self.draw_codes.append(Path.LINETO)
        fitpars = fit_suite.getFitParameters()
        self.cyl_points.append((fitpars[0].getValue(), fitpars[1].getValue()))
        self.prism_points.append((fitpars[2].getValue(), fitpars[3].getValue()))
        # if fit_suite.getNCalls() >= max_line_length:
        #     self.cyl_points.pop(0)
        #     self.prism_points.pop(0)
        # cylinder parameter space
        path_cyl = Path(self.cyl_points, self.draw_codes)
        ax = plt.subplot(2, 2, 3)
        patch = patches.PathPatch(path_cyl, facecolor='none', lw=2)
        ax.add_patch(patch)
        ax.set_xlim(0, 10)
        ax.set_ylim(0, 10)
        # prism parameter space
        path_prism = Path(self.prism_points, self.draw_codes)
        ax = plt.subplot(2, 2, 4)
        patch = patches.PathPatch(path_prism, facecolor='none', lw=2)
        ax.add_patch(patch)
        ax.set_xlim(0, 10)
        ax.set_ylim(0, 10)
        # # plotting difference map
        # diff_map = (real_data - simulated_data)/numpy.sqrt(real_data + 1)
        # pylab.subplot(2, 2, 3)
        # im = pylab.imshow(diff_map, norm=matplotlib.colors.LogNorm(), extent=[-1.0, 1.0, 0, 2.0], vmin = 0.001, vmax = 1.0)
        # pylab.colorbar(im)
        # pylab.title('Difference map')
        # # plotting parameters info
        # pylab.subplot(2, 2, 4)
        # pylab.title('Parameters')
        # pylab.axis('off')
        # pylab.text(0.01, 0.85, "Iteration  " + str(fit_suite.getNCalls()))
        # pylab.text(0.01, 0.75, "Chi2       " + str(fit_suite.getFitObjects().getChiSquaredValue()))
        # fitpars = fit_suite.getFitParameters()
        # for i in range(0, fitpars.size()):
        #     pylab.text(0.01, 0.55 - i*0.1, str(fitpars[i].getName()) + " " + str(fitpars[i].getValue())[0:5] )
        fname = '_tmp%03d.png' % fit_suite.getNumberOfIterations()
        print 'Saving frame', fname
        fig.savefig(fname)


def run_fitting():
    """
    main function to run fitting
    """

    # uncomment to regenerate "real" data
    #create_real_data()

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    real_data = IntensityDataIOFactory.readIntensityData('refdata_fitcylinderprisms.int.gz')

    fit_suite = FitSuite()
    fit_suite.addSimulationAndRealData(simulation, real_data)
    fit_suite.initPrint(10)

    draw_observer = DrawObserver()
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*Cylinder/Height", 2.*nanometer, Limits.limited(0.01, 10.0))
    fit_suite.addFitParameter("*Cylinder/Radius", 2.*nanometer, Limits.limited(0.01, 10.0))
    fit_suite.addFitParameter("*Prism3/Height", 2.*nanometer, Limits.limited(0.01, 10.0))
    fit_suite.addFitParameter("*Prism3/Length", 2.*nanometer, Limits.limited(0.01, 10.0))

    # # Now we create first fig strategy which will run first minimization round using Genetic minimizer.
    # # Genetic minimizer is able to explore large parameter space without being trapped by some local minima.
    # strategy1 = FitStrategyAdjustMinimizer()
    # strategy1.setMinimizer(MinimizerFactory.createMinimizer("Genetic"))
    # strategy1.getMinimizer().getOptions().setMaxIterations(0)
    # fit_suite.addFitStrategy(strategy1)

    # Second fit strategy will use another algorithm. It will use best parameters found from previous minimization round.
    strategy2 = FitStrategyAdjustMinimizer("Minuit2", "Migrad")
    fit_suite.addFitStrategy(strategy2)

    # running fit
    fit_suite.runFit()

    print "Fitting completed."
    fit_suite.printResults()
    print "chi2:", fit_suite.getMinimizer().getMinValue()
    fitpars = fit_suite.getFitParameters()
    for i in range(0, fitpars.size()):
        print fitpars[i].getName(), fitpars[i].getValue(), fitpars[i].getError()
    os.system("mencoder 'mf://_tmp*.png' -mf type=png:fps=10 -ovc lavc -lavcopts vcodec=wmv2 -oac copy -o fit_movie.mpg")
    print 'Removing temporary files'
    os.system("rm _tmp*")


if __name__ == '__main__':
    run_fitting()
    # pylab.ioff()
    # pylab.show()
