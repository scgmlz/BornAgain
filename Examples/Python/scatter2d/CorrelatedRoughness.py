"""
MultiLayer with correlated roughness
"""
import numpy, sys
import bornagain as ba
from bornagain import angstrom, deg, micrometer, nm, nm2, kvector_t


def get_sample():
    """
    Returns a sample with two layers on a substrate, with correlated roughnesses.
    """
    # defining materials
    m_vacuum = ba.HomogeneousMaterial("ambience", 0.0, 0.0)
    m_part_a = ba.HomogeneousMaterial("PartA", 5e-6, 0.0)
    m_part_b = ba.HomogeneousMaterial("PartB", 10e-6, 0.0)
    m_substrate = ba.HomogeneousMaterial("substrate", 15e-6, 0.0)

    # defining layers
    l_ambience = ba.Layer(m_vacuum)
    l_part_a = ba.Layer(m_part_a, 2.5*nm)
    l_part_b = ba.Layer(m_part_b, 5.0*nm)
    l_substrate = ba.Layer(m_substrate)

    roughness = ba.LayerRoughness()
    roughness.setSigma(1.0*nm)
    roughness.setHurstParameter(0.3)
    roughness.setLatteralCorrLength(5.0*nm)

    my_sample = ba.MultiLayer()

    # adding layers
    my_sample.addLayer(l_ambience)

    n_repetitions = 5
    for i in range(n_repetitions):
        my_sample.addLayerWithTopRoughness(l_part_a, roughness)
        my_sample.addLayerWithTopRoughness(l_part_b, roughness)

    my_sample.addLayerWithTopRoughness(l_substrate, roughness)
    my_sample.setCrossCorrLength(10*nm)

    return my_sample


def get_simulation():
    beam = ba.Beam(500000000000.0, 0.1*nm, ba.Direction(0.2*deg, 0.0*deg))
    nbin = 200
    detector = ba.SphericalDetector(nbin, 1.0*deg, 0.0*deg, 0.5*deg)

    simulation = ba.GISASSimulation(beam, get_sample(), detector)
    return simulation


def run_simulation():
    simulation = get_simulation()
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
