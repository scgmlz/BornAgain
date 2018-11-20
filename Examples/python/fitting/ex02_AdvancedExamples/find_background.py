"""
Fitting example: looking for background and scale factors.

Real data contains some "unknown" background and scale factor.
In the fit we are trying to find cylinder radius and height,
scale and background factors.
"""

import numpy as np
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(params):
    """
    Build the sample representing cylinders on top of substrate without interference.
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
    Create and return GISAXS simulation with beam and detector defined
    """
    background = params["background"]
    scale = params["scale"]

    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e12*scale)
    simulation.setBackground(ba.ConstantBackground(background))
    simulation.setSample(get_sample(params))

    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise, background and scale
    to the simulated data.
    Cylinder radius is set to 5nm, cylinder height to 10nm.
    During the fit we will try to find cylinder height and radius and
    scale, background factors.
    """

    params = {'radius': 5.0*nm, 'height': 10.0*nm, 'scale': 2.0, 'background': 1000}

    simulation = get_simulation(params)
    simulation.runSimulation()

    # retrieving simulated data in the form of numpy array
    return simulation.result().array()


def run_fitting():
    """
    main function to run fitting
    """
    real_data = create_real_data()

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(get_simulation, real_data, 1.0)

    fit_objective.initPrint(10)
    fit_objective.initPlot(10)

    params = ba.Parameters()
    params.add("radius", 5.*nm, vary=False)
    params.add("height", 9.*nm, min=8.*nm, max=12.*nm)
    params.add("scale", 1.5, min=1.0, max=3.0)
    params.add("background", 200, min=100.0, max=2000.0, step=100.0)

    minimizer = ba.Minimizer()
    result = minimizer.minimize(fit_objective.evaluate, params)
    fit_objective.finalize(result)


if __name__ == '__main__':
    run_fitting()
    plt.show()
