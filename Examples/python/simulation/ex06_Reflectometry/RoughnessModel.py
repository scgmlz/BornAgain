"""
Example of simulating a rough sample with a 
tanh and Nevot-Croce roughness model using BornAgain.

"""

from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm

def get_sample(roughness_model):
    """
    Defines sample and returns it
    """

    # creating materials
    m_ambient = ba.MaterialBySLD("Ambient", 0.0, 0.0)
    m_ti = ba.MaterialBySLD("Ti", -1.9493e-06, 0.0)
    m_ni = ba.MaterialBySLD("Ni", 9.4245e-06, 0.0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", 2.0704e-06, 0.0)

    # creating layers
    ambient_layer = ba.Layer(m_ambient)
    ti_layer = ba.Layer(m_ti, 30 * angstrom)
    ni_layer = ba.Layer(m_ni, 70 * angstrom)
    substrate_layer = ba.Layer(m_substrate)

    # defining roughness
    roughness = ba.LayerRoughness()
    roughness.setSigma(1.0 * nm)

    # creating multilayer
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(ambient_layer)
    for i in range(10):
        multi_layer.addLayerWithTopRoughness(ti_layer, roughness)
        multi_layer.addLayerWithTopRoughness(ni_layer, roughness)
    multi_layer.addLayerWithTopRoughness(substrate_layer, roughness)
    
    multi_layer.setRoughnessModel(roughness_model)

    return multi_layer


def get_simulation(scan_size=500):
    """
    Defines and returns a specular simulation.
    """
    simulation = ba.SpecularSimulation()
    scan = ba.AngularSpecScan(1.54 * angstrom, scan_size,
                              0.0 * deg, 2.0 * deg)
    simulation.setScan(scan)
    return simulation


def run_simulation(roughness_model=ba.RoughnessModel.TANH):
    """
    Runs simulation and returns its result.
    """
    sample = get_sample(roughness_model)
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


def plot(result_tanh, result_nevot_croce):
    
    plt.semilogy(result_nevot_croce.axis(), result_nevot_croce.array(),
                 label="Névot-Croce")
    plt.semilogy(result_tanh.axis(), result_tanh.array(), label="Tanh")
    
    plt.xlabel(r'$\alpha_i \; (deg)$', fontsize=12)
    plt.ylabel(r'Intensity', fontsize=12)
    
    plt.legend()
    plt.show()


if __name__ == '__main__':
    result_tanh = run_simulation(roughness_model=ba.RoughnessModel.TANH)
    result_nevot_croce  = run_simulation(
        roughness_model=ba.RoughnessModel.NEVOT_CROCE)
    plot(result_tanh, result_nevot_croce)
