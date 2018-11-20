"""
Fitting example: fit with masks
"""

import numpy as np
from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(params):
    """
    Build the sample representing cylinders on top of
    substrate without interference.
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


def get_simulation(params, add_masks=True):
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    simulation.setSample(get_sample(params))

    if add_masks:
        add_mask_to_simulation(simulation)

    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    params = {'radius': 5.0*nm, 'height': 10.0*nm}

    # retrieving simulated data in the form of numpy array
    simulation = get_simulation(params, add_masks=False)
    simulation.runSimulation()
    real_data = simulation.result().array()

    # spoiling simulated data with the noise to produce "real" data
    noise_factor = 0.1
    noisy = np.random.normal(real_data, noise_factor*np.sqrt(real_data))
    noisy[noisy < 0.1] = 0.1
    return noisy


def add_mask_to_simulation(simulation):
    """
    Here we demonstrate how to add masks to the simulation.
    Only unmasked areas will be simulated and then used during the fit.

    Masks can have different geometrical shapes (ba.Rectangle, ba.Ellipse, Line)
    with the mask value either "True" (detector bin is excluded from the simulation)
    or False (will be simulated).

    Every subsequent mask overrides previously defined mask in this area.

    In the code below we put masks in such way that simulated image will look like
    a Pac-Man from ancient arcade game.
    """
    # mask all detector (put mask=True to all detector channels)
    simulation.maskAll()

    # set mask to simulate pacman's head
    simulation.addMask(
        ba.Ellipse(0.0*deg, 1.0*deg, 0.5*deg, 0.5*deg), False)

    # set mask for pacman's eye
    simulation.addMask(
        ba.Ellipse(0.11*deg, 1.25*deg, 0.05*deg, 0.05*deg), True)

    # set mask for pacman's mouth
    points = [[0.0*deg, 1.0*deg], [0.5*deg, 1.2*deg],
              [0.5*deg, 0.8*deg], [0.0*deg, 1.0*deg]]
    simulation.addMask(ba.Polygon(points), True)

    # giving pacman something to eat
    simulation.addMask(
        ba.Rectangle(0.45*deg, 0.95*deg, 0.55*deg, 1.05*deg), False)
    simulation.addMask(
        ba.Rectangle(0.61*deg, 0.95*deg, 0.71*deg, 1.05*deg), False)
    simulation.addMask(
        ba.Rectangle(0.75*deg, 0.95*deg, 0.85*deg, 1.05*deg), False)

    # other mask's shapes are possible too
    # simulation.removeMasks()
    # # rotated ellipse:
    # simulation.addMask(ba.Ellipse(0.11*deg, 1.25*deg,
    #                    1.0*deg, 0.5*deg, 45.0*deg), True)
    # simulation.addMask(Line(-1.0*deg, 0.0*deg, 1.0*deg, 2.0*deg), True)
    # simulation.addMask(ba.HorizontalLine(1.0*deg), False)
    # simulation.addMask(ba.VerticalLine(0.0*deg), False)


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
    params.add("radius", 6.*nm, min=4.0, max=8.0)
    params.add("height", 9.*nm, min=8.0, max=12.0)

    minimizer = ba.Minimizer()
    result = minimizer.minimize(fit_objective.evaluate, params)
    fit_objective.finalize(result)


if __name__ == '__main__':
    run_fitting()
    plt.show()
