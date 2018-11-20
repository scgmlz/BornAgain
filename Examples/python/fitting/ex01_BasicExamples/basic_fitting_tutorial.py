"""
Fitting example: 4 parameters fit for mixture of cylinders and prisms on top
of substrate.
"""

import bornagain as ba
import numpy as np
from matplotlib import pyplot as plt
from bornagain import deg, angstrom, nm


def get_sample(params):
    """
    Returns a sample with uncorrelated cylinders and prisms on a substrate.
    """
    cylinder_height = params["cylinder_height"]
    cylinder_radius = params["cylinder_radius"]
    prism_height = params["prism_height"]
    prism_base_edge = params["prism_base_edge"]

    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(cylinder_radius, cylinder_height)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    prism_ff = ba.FormFactorPrism3(prism_base_edge, prism_height)
    prism = ba.Particle(m_particle, prism_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 0.5)
    particle_layout.addParticle(prism, 0.5)
    interference = ba.InterferenceFunctionNone()
    particle_layout.setInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def create_real_data():
    """
    Generating "experimental" data by running simulation with certain parameters.
    The data is saved on disk in the form of numpy array.
    """

    # default sample parameters
    params = {'cylinder_height': 5.0*nm, 'cylinder_radius': 5.0*nm,
              'prism_height': 5.0*nm, 'prism_base_edge': 5.0*nm}

    # retrieving simulated data in the form of numpy array
    simulation = get_simulation(params)
    simulation.runSimulation()
    real_data = simulation.result().array()

    # spoiling simulated data with noise to produce "real" data
    np.random.seed(0)
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1

    np.savetxt("basic_fitting_tutorial_data.txt.gz", real_data)


def load_real_data():
    """
    Loads experimental data from file
    """
    return np.loadtxt("basic_fitting_tutorial_data.txt.gz", dtype=float)


def get_simulation(params):
    """
    Returns a GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    simulation.setSample(get_sample(params))
    return simulation


def run_fitting():
    """
    Setup simulation and fit
    """

    real_data = load_real_data()

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(get_simulation, real_data, 1.0)

    # Print fit progress on every n-th iteration.
    fit_objective.initPrint(10)

    # Plot fit progress on every n-th iteration. Will slow down fit.
    fit_objective.initPlot(10)

    params = ba.Parameters()
    params.add("cylinder_height", 4.*nm, min=0.01)
    params.add("cylinder_radius", 6.*nm, min=0.01)
    params.add("prism_height", 4.*nm, min=0.01)
    params.add("prism_base_edge", 12.*nm, min=0.01)

    minimizer = ba.Minimizer()
    result = minimizer.minimize(fit_objective.evaluate, params)

    fit_objective.finalize(result)

    print("Fitting completed.")
    print("chi2:", result.minValue())
    for fitPar in result.parameters():
        print(fitPar.name(), fitPar.value, fitPar.error)

    # saving simulation image corresponding to the best fit parameters
    # np.savetxt("data.txt", fit_objective.simulationResult().array())


if __name__ == '__main__':
    # uncomment line below to regenerate "experimental" data file
    create_real_data()

    run_fitting()
    plt.show()
