"""
Fitting example: simultaneous fit of two datasets
"""

import numpy as np
import matplotlib
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(params):
    """
    Returns a sample with uncorrelated cylinders and pyramids.
    """
    radius_a = params["radius_a"]
    radius_b = params["radius_b"]
    height = params["height"]

    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    formfactor = ba.FormFactorHemiEllipsoid(radius_a, radius_b, height)
    particle = ba.Particle(m_particle, formfactor)

    layout = ba.ParticleLayout()
    layout.addParticle(particle)

    air_layer = ba.Layer(m_air)
    air_layer.addLayout(layout)

    substrate_layer = ba.Layer(m_substrate)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(params):
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    incident_angle = params["incident_angle"]

    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(50, -1.5*deg, 1.5*deg,
                                     50, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, incident_angle, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    simulation.setSample(get_sample(params))
    return simulation


def simulation1(params):
    params["incident_angle"] = 0.1*deg
    return get_simulation(params)


def simulation2(params):
    params["incident_angle"] = 0.4*deg
    return get_simulation(params)


def create_real_data(incident_alpha):
    """
    Generating "real" data by adding noise to the simulated data.
    """
    params = {'radius_a': 5.0*nm, 'radius_b': 6.0*nm,
              'height': 8.0*nm, "incident_angle": incident_alpha}

    simulation = get_simulation(params)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


class PlotObserver():
    """
    Draws fit progress every nth iteration. Real data, simulated data
    and chi2 map will be shown for both datasets.
    """
    def __init__(self):
        self.fig = plt.figure(figsize=(12.8, 10.24))
        self.fig.canvas.draw()

    def __call__(self, fit_objective):
        self.update(fit_objective)

    @staticmethod
    def plot_dataset(fit_objective, canvas):
        for i_dataset in range(0, fit_objective.fitObjectCount()):
            real_data = fit_objective.experimentalData(i_dataset)
            simul_data = fit_objective.simulationResult(i_dataset)
            chi2_map = fit_objective.relativeDifference(i_dataset)

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

    @staticmethod
    def display_fit_parameters(fit_objective):
        """
        Displays fit parameters, chi and iteration number.
        """
        plt.title('Parameters')
        plt.axis('off')

        iteration_info = fit_objective.iterationInfo()

        plt.text(0.01, 0.85, "Iterations  " + '{:d}'.
                 format(iteration_info.iterationCount()))
        plt.text(0.01, 0.75, "Chi2       " + '{:8.4f}'.format(iteration_info.chi2()))
        for index, params in enumerate(iteration_info.parameters()):
            plt.text(0.01, 0.55 - index * 0.1,
                     '{:30.30s}: {:6.3f}'.format(params.name(), params.value))

    @staticmethod
    def plot_fit_parameters(fit_objective):
        """
        Displays fit parameters, chi and iteration number.
        """
        plt.axis('off')

        iteration_info = fit_objective.iterationInfo()

        plt.text(0.01, 0.95, "Iterations  " + '{:d}'.
                 format(iteration_info.iterationCount()))
        plt.text(0.01, 0.70, "Chi2       " + '{:8.4f}'.format(iteration_info.chi2()))
        for index, params in enumerate(iteration_info.parameters()):
            plt.text(0.01, 0.30 - index * 0.3,
                     '{:30.30s}: {:6.3f}'.format(params.name(), params.value))

    def update(self, fit_objective):
        self.fig.clf()

        # we divide figure to have 3x3 subplots, with two first rows occupying
        # most of the space
        canvas = matplotlib.gridspec.GridSpec(
            3, 3, width_ratios=[1, 1, 1], height_ratios=[4, 4, 1])
        canvas.update(left=0.05, right=0.95, hspace=0.5, wspace=0.2)

        self.plot_dataset(fit_objective, canvas)
        plt.subplot(canvas[6:])
        self.plot_fit_parameters(fit_objective)

        plt.draw()
        plt.pause(0.01)


def run_fitting():
    """
    main function to run fitting
    """

    data1 = create_real_data(0.1 * deg)
    data2 = create_real_data(0.4 * deg)

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(simulation1, data1, 1.0)
    fit_objective.addSimulationAndData(simulation2, data2, 1.0)
    fit_objective.initPrint(10)

    # creating custom observer which will draw fit progress
    plotter = PlotObserver()
    fit_objective.initPlot(10, plotter.update)

    params = ba.Parameters()
    params.add("radius_a", 4.*nm, min=2.0, max=10.0)
    params.add("radius_b", 6.*nm, vary=False)
    params.add("height", 4.*nm, min=2.0, max=10.0)

    minimizer = ba.Minimizer()
    result = minimizer.minimize(fit_objective.evaluate, params)
    fit_objective.finalize(result)


if __name__ == '__main__':
    run_fitting()
    plt.show()
