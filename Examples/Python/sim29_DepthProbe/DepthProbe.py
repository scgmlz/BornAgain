"""
Basic example of depth-probe simulation with BornAgain.
Sample structure:
----------------------- inf

                        Si

----------------------- 0 nm
                        Ti
----------------------- -13 nm
                        Pt
----------------------- -45 nm
                        Ti
----------------------- -55 nm
                        TiO2
----------------------- -58 nm

                        D2O

----------------------- -inf
Beam comes from silicon side.
z axis is directed up and perpendicularly
to the sample, z = 0 corresponding to the sample
surface
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t

# layer thicknesses in angstroms
t_Ti = 130.0*angstrom
t_Pt = 320.0*angstrom
t_Ti_top = 100.0*angstrom
t_TiO2 = 30.0*angstrom

#  beam data
ai_min = 0.0*deg  # minimum incident angle
ai_max = 1.0*deg  # maximum incident angle
n_ai_bins = 5000  # number of bins in incident angle axis
beam_sample_ratio = 0.01  # beam-to-sample size ratio
wl = 10*angstrom  # wavelength in angstroms

# convolution parameters
d_ang = 0.01*ba.deg  # spread width for incident angle
n_points = 25  # number of points to convolve over
n_sig = 3  # number of sigmas to convolve over

#  depth position span
z_min = -100*nm
z_max = 100*nm
n_z_bins = 500


def get_sample():
    """
    Constructs a sample with one resonating Ti/Pt layer
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Si", 3.3009e-05, 0.0)
    material_2 = ba.HomogeneousMaterial("Ti", -3.0637e-05, 1.5278e-08)
    material_3 = ba.HomogeneousMaterial("Pt", 0.00010117, 3.01822e-08)
    material_4 = ba.HomogeneousMaterial("TiO2", 4.1921e-05, 8.1293e-09)
    material_5 = ba.HomogeneousMaterial("D2O", 0.00010116, 1.809e-12)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_2, 13.0*nm)
    layer_3 = ba.Layer(material_3, 32.0*nm)
    layer_4 = ba.Layer(material_2, 10.0*nm)
    layer_5 = ba.Layer(material_4, 3.0*nm)
    layer_6 = ba.Layer(material_5)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    multiLayer_1.addLayer(layer_2)
    multiLayer_1.addLayer(layer_3)
    multiLayer_1.addLayer(layer_4)
    multiLayer_1.addLayer(layer_5)
    multiLayer_1.addLayer(layer_6)

    return multiLayer_1


def get_simulation():
    """
    Returns a depth-probe simulation.
    """
    alpha_distr = ba.DistributionGaussian(0.0, d_ang)
    footprint = ba.FootprintSquare(beam_sample_ratio)
    simulation = ba.DepthProbeSimulation()
    simulation.setBeamParameters(wl, n_ai_bins, ai_min, ai_max, footprint)
    simulation.setZSpan(n_z_bins, z_min, z_max)
    simulation.addParameterDistribution("*/Beam/InclinationAngle", alpha_distr,
                                        n_points, n_sig)
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
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
