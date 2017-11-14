"""
R and T coefficients in multilayer, ba.Specular simulation.
"""
import numpy
import bornagain as ba
from bornagain import deg, angstrom, nm

alpha_i_min, alpha_i_max = 0.0*deg, 2.0*deg  # incoming beam


def get_sample():
    """
    Returns a sample with two layers on a substrate, with correlated roughnesses.
    """
    m_ambience = ba.HomogeneousMaterial("ambience", 0.0, 0.0)
    m_part_a = ba.HomogeneousMaterial("PartA", 5e-6, 0.0)
    m_part_b = ba.HomogeneousMaterial("PartB", 10e-6, 0.0)
    m_substrate = ba.HomogeneousMaterial("substrate", 15e-6, 0.0)

    l_ambience = ba.Layer(m_ambience)
    l_part_a = ba.Layer(m_part_a, 5.0*nm)
    l_part_b = ba.Layer(m_part_b, 10.0*nm)
    l_substrate = ba.Layer(m_substrate)

    roughness = ba.LayerRoughness()
    roughness.setSigma(1.0*nm)

    my_sample = ba.MultiLayer()

    # adding layers
    my_sample.addLayer(l_ambience)

    n_repetitions = 10
    for i in range(n_repetitions):
        my_sample.addLayerWithTopRoughness(l_part_a, roughness)
        my_sample.addLayerWithTopRoughness(l_part_b, roughness)

    my_sample.addLayerWithTopRoughness(l_substrate, roughness)

    return my_sample


def get_simulation():
    """
    Returns a specular simulation with beam and detector defined.
    """
    simulation = ba.SpecularSimulation()
    simulation.setBeamParameters(
        1.54*angstrom, 500, alpha_i_min, alpha_i_max)
    return simulation


def run_simulation():
    """
    Runs simulation and returns it.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation


def rt_coefficients(simulation):
    """
    Returns refraction/transmission coefficients for all layers
    """
    rf2 = [simulation.reflectivity(i) for i in range(22)]
    tf2 = [simulation.transmissivity(i) for i in range(22)]
    return rf2, tf2


def plot(simulation):
    """
    Plots results for several selected layers
    """
    from matplotlib import pyplot as plt
    plt.figure(figsize=(12.80, 10.24))

    rf2, tf2 = rt_coefficients(simulation)

    selected_layers = [0, 1, 20, 21]
    nplot = 1
    for layer_index in selected_layers:
        plt.subplot(2, 2, nplot)
        plt.ylim(ymax=50.0, ymin=1e-10)
        plt.xlabel(r'$\alpha_f$ (rad)', fontsize=16)
        plt.semilogy(rf2[layer_index].getBinCenters(), rf2[layer_index].getArray())
        plt.semilogy(tf2[layer_index].getBinCenters(), tf2[layer_index].getArray())
        plt.legend(['$|R|^2$ layer #'+str(layer_index),
                    '$|T|^2$ layer #'+str(layer_index)],
                   loc='upper right')
        nplot += 1

    plt.show()


if __name__ == '__main__':
    results = run_simulation()
    plot(results)
