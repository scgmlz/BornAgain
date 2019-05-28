"""
In this example we demonstrate how to plot simulation results with
axes in different units (nbins, mm, degs and QyQz).
"""
import bornagain as ba
from bornagain import deg, angstrom, nm
from matplotlib import pyplot as plt


def get_sample():
    """
    Returns a sample with uncorrelated cylinders on a substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(5*nm, 5*nm)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_flat_detector():
    """
    Returns flat detector representing our PILATUS detector
    """

    detector_distance = 2000.0  # in mm
    pilatus_pixel_size = 0.172  # in mm
    pilatus_npx, pilatus_npy = 981, 1043  # number of pixels

    width = pilatus_npx*pilatus_pixel_size
    height = pilatus_npy*pilatus_pixel_size
    detector = ba.FlatDetector(pilatus_npx, width, pilatus_npy, height)
    detector.setPerpendicularToSampleX(detector_distance, width/2., 0.0)
    return detector


def get_simulation():
    """
    Returns a GISAXS simulation with beam defined
    """
    simulation = ba.GISASSimulation()
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setDetector(get_flat_detector())
    return simulation


def run_simulation():
    """
    Run simulation and returns results for different detector units.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()

    result = simulation.result()

    return result


def plot(result):
    """
    Plots simulation results for different detectors.
    """
    fig = plt.figure(figsize=(12.80, 10.24))

    plt.subplot(2, 2, 1)
    # default units for flat detector are millimeters

    ba.plot_colormap(result, title="In default units",
                     xlabel=r'$X_{mm}$', ylabel=r'$Y_{mm}$', zlabel=None)

    plt.subplot(2, 2, 2)
    ba.plot_colormap(result, units=ba.AxesUnits.NBINS, title="In number of bins",
                     xlabel=r'$X_{nbins}$', ylabel=r'$Y_{nbins}$', zlabel=None)

    plt.subplot(2, 2, 3)
    ba.plot_colormap(result, units=ba.AxesUnits.DEGREES, title="In degs",
                     xlabel=r'$\phi_f ^{\circ}$', ylabel=r'$\alpha_f ^{\circ}$',
                     zlabel=None)

    plt.subplot(2, 2, 4)
    ba.plot_colormap(result, units=ba.AxesUnits.QSPACE, title="Q-space",
                     xlabel=r'$Q_{y} [1/nm]$', ylabel=r'$Q_{z} [1/nm]$', zlabel=None)

    plt.subplots_adjust(left=0.07, right=0.97, top=0.9, bottom=0.1, hspace=0.25)
    plt.show()


if __name__ == '__main__':
    result = run_simulation()
    plot(result)
