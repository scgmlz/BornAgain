"""
MultiLayer with correlated roughness
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Returns a sample with two layers on a substrate, with correlated roughnesses.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("ambience", 0.0, 0.0)
    m_part_a = ba.HomogeneousMaterial("PartA", 5e-6, 0.0)
    m_part_b = ba.HomogeneousMaterial("PartB", 10e-6, 0.0)
    m_substrate = ba.HomogeneousMaterial("substrate", 15e-6, 0.0)

    # defining layers
    l_ambience = ba.Layer(m_ambience)
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

    print(my_sample.treeToString())

    return my_sample


def get_simulation():
    """
    Characterizing the input beam and output detector
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(200, -0.5*deg, 0.5*deg,
                                     200, 0.0*deg, 1.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(5e11)
    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    simulation = get_simulation()
    simulation.setSample(get_sample())
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.mpl_settings()
    ba.plot_simulation_result(result)
