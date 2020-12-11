"""
An example of defining reflectometry instrument
for time of flight experiment. In this example
we will use purely qz-defined beam,
without explicitly specifying
incident angle or a wavelength.
Additionally we will set pointwise resolution
to the scan.
Note that these approaches work with SLD-based
materials only.
"""
import numpy as np
import bornagain as ba
from bornagain import angstrom


def get_sample():
    """
    Defines sample and returns it. Note that SLD-based materials are used.
    """

    # creating materials
    m_ambient = ba.MaterialBySLD("Ambient", 0.0, 0.0)
    m_ti = ba.MaterialBySLD("Ti", -1.9493e-06, 0.0)
    m_ni = ba.MaterialBySLD("Ni", 9.4245e-06, 0.0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", 2.0704e-06, 0.0)

    # creating layers
    ambient_layer = ba.Layer(m_ambient)
    ti_layer = ba.Layer(m_ti, 30*angstrom)
    ni_layer = ba.Layer(m_ni, 70*angstrom)
    substrate_layer = ba.Layer(m_substrate)

    # creating multilayer
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(ambient_layer)
    for i in range(10):
        multi_layer.addLayer(ti_layer)
        multi_layer.addLayer(ni_layer)
    multi_layer.addLayer(substrate_layer)

    return multi_layer


def get_simulation(scan_size=500):
    """
    Defines and returns specular simulation
    with a qz-defined beam
    """
    qzs = np.linspace(0.01, 1.0, scan_size)  # qz-values
    dq = 0.03*qzs
    n_sig = 2.0
    n_samples = 25

    distr = ba.RangedDistributionGaussian(n_samples, n_sig)

    scan = ba.QSpecScan(qzs)
    scan.setAbsoluteQResolution(distr, dq)

    simulation = ba.SpecularSimulation()
    simulation.setScan(scan)

    return simulation


def run_simulation():
    """
    Runs simulation and returns its result.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result)
