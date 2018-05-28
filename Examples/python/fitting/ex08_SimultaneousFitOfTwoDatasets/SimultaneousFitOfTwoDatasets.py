"""
Fitting example: demonstrates how to fit two datasets simultaneously.
"""

import numpy as np
import matplotlib
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(radius_a=4.0*nm, radius_b=4.0*nm, height=4.0*nm):
    """
    Returns a sample with uncorrelated cylinders and pyramids.
    """
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    formFactor = ba.FormFactorHemiEllipsoid(radius_a, radius_b, height)
    hemiEllipsoid = ba.Particle(m_particle, formFactor)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(hemiEllipsoid)

    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)

    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(incident_alpha=0.2):
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(50, -1.5*deg, 1.5*deg,
                                     50, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, incident_alpha, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    return simulation


def create_real_data(incident_alpha):
    """
    Generating "real" data by adding noise to the simulated data.
    """
    sample = get_sample(
        radius_a=5.0*nm, radius_b=6.0*nm, height=8.0*nm)
    simulation = get_simulation(incident_alpha)
    simulation.setSample(sample)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


class DrawObserver(ba.IFitObserver):
    """
    Draws fit progress every nth iteration. Real data, simulated data
    and chi2 map will be shown for both datasets.
    """
    def __init__(self, draw_every_nth=10):
        import matplotlib
        from matplotlib import pyplot as plt
        global matplotlib, plt

        ba.IFitObserver.__init__(self, draw_every_nth)
        self.fig = plt.figure(figsize=(12.8, 10.24))
        self.fig.canvas.draw()
        plt.ion()

    def plot_datasets(self, fit_suite, canvas):
        for i_dataset in range(0, fit_suite.numberOfFitObjects()):
            real_data = fit_suite.experimentalData(i_dataset)
            simul_data = fit_suite.simulationResult(i_dataset)
            chi2_map = fit_suite.relativeDifference(i_dataset)

            zmax = real_data.histogram2d().getMaximum()

            plt.subplot(canvas[i_dataset*3])
            ba.plot_colormap(real_data, title="\"Real\" data - #"+str(i_dataset+1),
                               zmin=1.0, zmax=zmax, zlabel="")
            plt.subplot(canvas[1+i_dataset*3])
            ba.plot_colormap(simul_data, title="Simulated data - #"+str(i_dataset+1),
                               zmin=1.0, zmax=zmax, zlabel="")
            plt.subplot(canvas[2+i_dataset*3])
            ba.plot_colormap(chi2_map, title="Chi2 map - #"+str(i_dataset+1),
                               zmin=0.001, zmax=10.0, zlabel="")

    def plot_fit_parameters(self, fit_suite, canvas):
        # fit parameters
        plt.subplot(canvas[6:])
        plt.axis('off')
        plt.text(0.01, 0.95, "Iterations  " + '{:d}     {:s}'.
                 format(fit_suite.numberOfIterations(),
                        fit_suite.minimizer().minimizerName()))
        plt.text(0.01, 0.70, "Chi2       " + '{:8.4f}'.format(fit_suite.getChi2()))
        for index, fitPar in enumerate(fit_suite.fitParameters()):
            plt.text(0.01, 0.30 - index*0.3,
                     '{:40.40s}: {:6.3f}'.format(fitPar.name(), fitPar.value()))

    def update(self, fit_suite):
        self.fig.clf()

        # we divide figure to have 3x3 subplots, with two first rows occupying
        # most of the space
        canvas = matplotlib.gridspec.GridSpec(
            3, 3, width_ratios=[1, 1, 1], height_ratios=[4, 4, 1])
        canvas.update(left=0.05, right=0.95, hspace=0.5, wspace=0.2)

        self.plot_datasets(fit_suite, canvas)
        self.plot_fit_parameters(fit_suite, canvas)

        plt.draw()
        plt.pause(0.01)

        if fit_suite.isLastIteration():
            plt.ioff()


def run_fitting():
    """
    main function to run fitting
    """

    incident_alpha_angles = [0.1*deg, 0.4*deg]
    fit_suite = ba.FitSuite()
    sample = get_sample()

    for alpha in incident_alpha_angles:
        real_data = create_real_data(incident_alpha=alpha)
        simulation = get_simulation(incident_alpha=alpha)
        simulation.setSample(sample)
        fit_suite.addSimulationAndRealData(simulation, real_data)

    fit_suite.initPrint(10)
    draw_observer = DrawObserver(draw_every_nth=10)
    fit_suite.attachObserver(draw_observer)

    # setting fitting parameters with starting values
    fit_suite.addFitParameter("*/HemiEllipsoid/RadiusX", 4.*nm).setLimited(2., 10.)
    fit_suite.addFitParameter("*/HemiEllipsoid/RadiusY", 6.*nm).setFixed()
    fit_suite.addFitParameter("*/HemiEllipsoid/Height", 4.*nm).setLimited(2., 10.)

    print(fit_suite.treeToString())
    print(fit_suite.parametersToString())

    # running fit
    fit_suite.runFit()

    print("Fitting completed.")
    print("chi2:", fit_suite.getChi2())
    for fitPar in fit_suite.fitParameters():
        print(fitPar.name(), fitPar.value(), fitPar.error())


if __name__ == '__main__':
    run_fitting()
    plt.show()
