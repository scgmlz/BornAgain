"""
Fitting example: running one fit after another using different minimizers.

During the first fit Genetic minimizer will be used to scan large parameter
space and roughly find local minimum. The second Minuit2 minimizer will continue
after that to find precise minimum location.
"""

import numpy as np
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(params):
    """
    Returns a sample with uncorrelated cylinders and pyramids on a substrate.
    """
    radius = params["radius"]
    height = params["height"]

    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    cylinder_ff = ba.FormFactorCylinder(radius, height)
    cylinder = ba.Particle(m_particle, cylinder_ff)

    layout = ba.ParticleLayout()
    layout.addParticle(cylinder)

    air_layer = ba.Layer(m_air)
    air_layer.addLayout(layout)

    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(params):
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, 0.0*deg, 2.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    simulation.setSample(get_sample(params))
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    params = {'radius': 5.0*nm, 'height': 5.0*nm}

    simulation = get_simulation(params)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    real_data = simulation.result().array()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


def run_fitting():
    """
    main function to run fitting
    """
    real_data = create_real_data()

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(get_simulation, real_data, 1.0)
    fit_objective.initPrint(10)
    fit_objective.initPlot(10)

    """
    Setting fitting parameters with starting values.
    Here we select starting values being quite far from true values
    to puzzle our minimizer's as much as possible.
    """
    params = ba.Parameters()
    params.add("height", 1.*nm, min=0.01, max=30.0, step=0.05*nm)
    params.add("radius", 20.*nm, min=0.01, max=30.0, step=0.05*nm)

    """
    Now we run first minimization round using the Genetic minimizer.
    The Genetic minimizer is able to explore large parameter space
    without being trapped by some local minimum.
    """
    minimizer = ba.Minimizer()
    minimizer.setMinimizer("Genetic", "", "MaxIterations=2;RandomSeed=1")
    result = minimizer.minimize(fit_objective.evaluate, params)
    fit_objective.finalize(result)

    best_params_so_far = result.parameters()

    """
    Second fit will use another minimizer.
    It starts from best parameters found in previous minimization
    and then continues until fit converges.
    """
    minimizer.setMinimizer("Minuit2", "Migrad")
    result = minimizer.minimize(fit_objective.evaluate, best_params_so_far)

    fit_objective.finalize(result)


if __name__ == '__main__':
    run_fitting()
    plt.show()
