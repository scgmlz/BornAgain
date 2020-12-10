"""
An example of taking into account beam angular and wavelength
divergence in reflectometry calculations with BornAgain.

"""
import bornagain as ba

# input parameters
wavelength = 1.54*ba.angstrom
alpha_i_min = 0.0*ba.deg  # min incident angle, deg
alpha_i_max = 2.0*ba.deg  # max incident angle, rad

# convolution parameters
d_wl = 0.01*wavelength  # spread width for wavelength
d_ang = 0.01*ba.deg  # spread width for incident angle
n_sig = 3  # number of sigmas to convolve over
n_points = 25  # number of points to convolve over

# substrate (Si)
si_sld_real = 2.0704e-06  # \AA^{-2}
# layer parameters
n_repetitions = 10
# Ni
ni_sld_real = 9.4245e-06  # \AA^{-2}
d_ni = 70*ba.angstrom  # ni layer thickness (nm)
# Ti
ti_sld_real = -1.9493e-06  # \AA^{-2}
d_ti = 30*ba.angstrom  # ti layer thickness (nm)


def get_sample():
    # defining materials
    # this example implies beam divergence in the wavelength,
    # thus MaterialBySLD must be used to provide correct result
    m_vacuum = ba.MaterialBySLD("Vacuum", 0.0, 0.0)
    m_ni = ba.MaterialBySLD("Ni", ni_sld_real, 0.0)
    m_ti = ba.MaterialBySLD("Ti", ti_sld_real, 0.0)
    m_substrate = ba.MaterialBySLD("SiSubstrate", si_sld_real, 0.0)

    vacuum_layer = ba.Layer(m_vacuum)
    ni_layer = ba.Layer(m_ni, d_ni)
    ti_layer = ba.Layer(m_ti, d_ti)
    substrate_layer = ba.Layer(m_substrate)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    for i in range(n_repetitions):
        multi_layer.addLayer(ti_layer)
        multi_layer.addLayer(ni_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(scan_size=500):
    """
    Returns a specular simulation with beam and detector defined.
    """

    alpha_distr = ba.RangedDistributionGaussian(n_points, n_sig)
    wavelength_distr = ba.RangedDistributionGaussian(n_points, n_sig)

    scan = ba.AngularSpecScan(wavelength, scan_size, alpha_i_min, alpha_i_max)
    scan.setAbsoluteAngularResolution(alpha_distr, d_ang)
    scan.setAbsoluteWavelengthResolution(wavelength_distr, d_wl)

    simulation = ba.SpecularSimulation()
    simulation.setScan(scan)

    return simulation


def run_simulation():
    """
    Runs simulation and returns it.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    results = run_simulation()
    ba.plot_simulation_result(results)
