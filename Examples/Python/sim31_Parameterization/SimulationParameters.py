"""
Working with sample parameters.

This example shows how to create a simulation with fixed parameters, and then change
these parameters on the fly during runtime.
"""

from __future__ import print_function
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with uncorrelated cylinders and prisms on a substrate.
    Parameter set is fixed.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_3 = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_3)

    # Define form factors
    formFactor_1 = ba.FormFactorCylinder(5.0*nm, 5.0*nm)
    formFactor_2 = ba.FormFactorPrism3(5.0*nm, 5.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)
    particle_2 = ba.Particle(material_2, formFactor_2)

    # Define interference functions
    interference_1 = ba.InterferenceFunctionNone()

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particle_1, 0.5)
    layout_1.addParticle(particle_2, 0.5)
    layout_1.setInterferenceFunction(interference_1)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.01)

    # Add layouts to layers
    layer_1.addLayout(layout_1)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    multiLayer_1.addLayer(layer_2)

    return multiLayer_1


def get_simulation():
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg, 100, 0.0*deg,
                                     2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def run_simulation():
    """
    Runs simulations for the sample with different sample parameters.
    """

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    print("The tree structure of the simulation")
    print(simulation.treeToString())

    print("The simulation contains following parameters ('name':value)")
    print(simulation.parametersToString())

    results = {}

    # simulation #1
    # initial simulation is used
    simulation.runSimulation()
    results[0] = simulation.result()

    # simulation #2
    # one sample parameter (cylinder height) is changed using exact parameter name
    simulation.setParameterValue(
        "/GISASSimulation/MultiLayer/Layer0/ParticleLayout"
        "/Particle0/Cylinder/Height", 10.0*nm)
    simulation.runSimulation()
    results[1] = simulation.result()

    # simulation #3
    # all parameters matching criteria will be changed (cylinder height in this case)
    simulation.setParameterValue("*/Cylinder/Height", 100.0*nm)
    simulation.runSimulation()
    results[2] = simulation.result()

    # simulation #4
    # all parameters which are matching criteria will be changed
    simulation.setParameterValue("*/Cylinder/Height", 10.0*nm)
    simulation.setParameterValue("*/Prism3/*", 10.0*nm)
    simulation.runSimulation()
    results[3] = simulation.result()

    return results


def plot(results):
    """
    Draw results of several simulations on canvas
    """

    from matplotlib import pyplot as plt
    plt.figure(figsize=(12.80, 10.24))

    for nplot, hist in results.items():
        plt.subplot(2, 2, nplot + 1)
        ba.plot_colormap(hist, zlabel="", cmap='jet', aspect='auto')
    plt.tight_layout()
    plt.show()


if __name__ == '__main__':
    results = run_simulation()
    plot(results)
