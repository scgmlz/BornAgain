"""
Real life example: reflectometry experiment at XRD
"""
from matplotlib import pyplot as plt
import numpy as np
from os import path
import bornagain as ba
from XRDSampleBuilder import SiAgNPSampleBuilder

# fixed parameters
beam_intensity = 1e7
wavelength = 1.54*ba.angstrom
beam_divergence = 0.04 * ba.deg

# starting values
beam_to_sample_ratio = 0.05
layer_roughness = 0.1 * ba.nm
np_thickness = 1 * ba.nm
np_concentration = 1.0
oxide_thickness = 1 * ba.nm
oxide_concentration = 1.0


def make_axis(ax_values):
    """
    Create BornAgain axis from given axis values
    :param ax_values: ndarray, values on axis
    :return: BornAgain.IAxis
    """
    name = "inclination_angles"
    nbins = ax_values.size
    boundaries = np.array([(ax_values[i] + ax_values[i+1])/2
                           for i in range(nbins-1)])
    boundaries = np.insert(boundaries, 0, 2 * boundaries[0] - boundaries[1])
    boundaries = np.insert(boundaries, nbins, 2 * boundaries[-1] - boundaries[-2])
    return ba.VariableBinAxis(name, nbins, boundaries)


def create_simulation(axis):
    """
    Creates and returns specular simulation
    """
    simulation = ba.SpecularSimulation()
    alpha_distr = ba.DistributionGaussian(0.0, beam_divergence)
    footprint = ba.FootprintFactorGaussian(beam_to_sample_ratio)
    simulation.setBeamParameters(wavelength, axis, footprint)
    simulation.setBeamIntensity(beam_intensity)
    simulation.addParameterDistribution("*/Beam/InclinationAngle", alpha_distr,
                                        30, 3)
    bg = ba.PoissonNoiseBackground()
    simulation.setBackground(bg)
    return simulation


def init_real_data(filename="mg6a_Merged.txt.gz"):
    """
    Loads real data and crops it to the region we are interested in.
    Return values are inclination angles (in radians) and
    signal intensities
    """
    filepath = path.join(path.dirname(path.realpath(__file__)),
                         filename)
    ax_values, real_data = np.loadtxt(filepath,
                                      usecols=(0, 1), skiprows=1, unpack=True)

    # translating axis values from double incident angle (degrees)
    # to incident angle (radians)
    ax_values *= np.pi / 360

    # first 10 points of data are not taken into account
    # since they contain the direct beam
    return ax_values[10:], real_data[10:]


def create_chi2_module():
    """
    Creates chi2 module to calculate fitting error
    Enables logarithmic error estimate
    :return: chi2 module
    """
    intensity_log = ba.IntensityFunctionLog()
    chi2 = ba.ChiSquaredModule()
    chi2.setIntensityFunction(intensity_log)

    return chi2


def init_fit_parameters(fit_suite):
    """
    initializes fitting parameters
    in fit_suite with starting values
    and limits
    :param fit_suite: fitting suite
    :return: None
    """

    fit_par1 = fit_suite.addFitParameter(
        "*BeamToSampleWidthRatio", beam_to_sample_ratio,
        ba.AttLimits.limited(0.0, 0.1),
        0.01)
    fit_par1.setName("BeamToSampleRatio")

    fit_par2 = fit_suite.addFitParameter(
        "*roughness", layer_roughness, ba.AttLimits.limited(0.0, 2.0 * ba.nm),
                      0.01 * ba.nm)
    fit_par2.setName("Roughness")

    fit_par3 = fit_suite.addFitParameter(
        "*np_thickness", np_thickness, ba.AttLimits.limited(0.0, 2.0 * ba.nm),
                         0.01 * ba.nm)
    fit_par3.setName("np_thick")

    fit_par4 = fit_suite.addFitParameter(
        "*np_concentration", np_concentration, ba.AttLimits.limited(0.0, 1.0),
        0.01)
    fit_par4.setName("np_dens")

    fit_par5 = fit_suite.addFitParameter(
        "*oxide_thickness", oxide_thickness, ba.AttLimits.limited(0.0, 2.0 * ba.nm),
                            0.01 * ba.nm)
    fit_par5.setName("sio2_thick")

    fit_par6 = fit_suite.addFitParameter(
        "*oxide_concentration", oxide_concentration, ba.AttLimits.limited(0.0, 1.0),
        0.01)
    fit_par6.setName("sio2_dens")


def run_fitting():

    axis_values, real_data = init_real_data()
    axis = make_axis(axis_values)

    simulation = create_simulation(axis)
    sample_builder = SiAgNPSampleBuilder()
    simulation.setSampleBuilder(sample_builder)

    fit_suite = ba.FitSuite()
    draw_observer = ba.DefaultFitObserver(draw_every_nth=10,
                                          SimulationType='Specular')
    fit_suite.attachObserver(draw_observer)
    fit_suite.initPrint(10)
    fit_suite.addSimulationAndRealData(simulation, real_data)

    # adjust figure of merit
    chi2_module = create_chi2_module()
    fit_suite.setChiSquaredModule(chi2_module)

    # set fitting parameters with starting values
    init_fit_parameters(fit_suite)

    # set fitting strategies
    strategy1 = ba.AdjustMinimizerStrategy("Genetic", "",
                                           "PopSize=80;MaxIterations=100")
    fit_suite.addFitStrategy(strategy1)
    strategy2 = ba.AdjustMinimizerStrategy("Minuit2", "Migrad")
    fit_suite.addFitStrategy(strategy2)

    # running fit
    fit_suite.runFit()

    plt.show()


if __name__ == '__main__':
    run_fitting()
