"""
Fitting experimental data: spherical nanoparticles with size distribution
in 3 layers system (experiment at GALAXI).
"""
import bornagain as ba
from bornagain import nm as nm
from sample_builder import SampleBuilder

wavelength = 1.34*ba.angstrom
alpha_i = 0.463*ba.deg

# detector setup as given from instrument responsible
pilatus_npx, pilatus_npy = 981, 1043
pilatus_pixel_size = 0.172  # in mm
detector_distance = 1730.0  # in mm
beam_xpos, beam_ypos = 597.1, 323.4  # in pixels


def create_detector():
    """
    Returns a model of the GALAXY detector
    """
    u0 = beam_xpos*pilatus_pixel_size  # in mm
    v0 = beam_ypos*pilatus_pixel_size  # in mm
    detector = ba.RectangularDetector(pilatus_npx, pilatus_npx*pilatus_pixel_size,
                                      pilatus_npy, pilatus_npy*pilatus_pixel_size)
    detector.setPerpendicularToDirectBeam(detector_distance, u0, v0)
    return detector


def create_simulation(params):
    """
    Creates and returns GISAS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetector(create_detector())
    simulation.setBeamParameters(wavelength, alpha_i, 0.0)
    simulation.setBeamIntensity(1.2e7)
    simulation.setRegionOfInterest(85.0, 70.0, 120.0, 92.)
    simulation.addMask(ba.Rectangle(101.9, 82.1, 103.7, 85.2), True)  # mask on reflected beam

    sample_builder = SampleBuilder()
    sample = sample_builder.create_sample(params)
    simulation.setSample(sample)

    return simulation


def load_real_data(filename="galaxi_data.tif.gz"):
    """
    Loads experimental data and returns numpy array.
    """
    return ba.IntensityDataIOFactory.readIntensityData(filename).array()


def run_fitting():
    real_data = load_real_data()

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(create_simulation, real_data, 1.0)
    fit_objective.initPrint(10)
    fit_objective.initPlot(10)

    params = ba.Parameters()
    params.add("radius", 5.*nm, min=4.0, max=6.0, step=0.1*nm)
    params.add("sigma", 0.55, min=0.2, max=0.8, step=0.01)
    params.add("distance", 27.*nm, min=20.0, max=70.0)

    minimizer = ba.Minimizer()
    result = minimizer.minimize(fit_objective.evaluate, params)
    fit_objective.finalize(result)


if __name__ == '__main__':
    run_fitting()
