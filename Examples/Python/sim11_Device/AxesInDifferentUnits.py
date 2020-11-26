"""
In this example we demonstrate how to plot simulation results with
axes in different units (nbins, mm, degs and QyQz).
"""
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t
from matplotlib import pyplot as plt
from matplotlib import rcParams


def get_sample():
    """
    Returns a sample with uncorrelated cylinders on a substrate.
    """

    # Define materials
    material_1 = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    material_2 = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_3 = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)

    # Define layers
    layer_1 = ba.Layer(material_1)
    layer_2 = ba.Layer(material_3)

    # Define form factors
    formFactor_1 = ba.FormFactorCylinder(5.0*nm, 5.0*nm)

    # Define particles
    particle_1 = ba.Particle(material_2, formFactor_1)

    # Define particle layouts and adding particles
    layout_1 = ba.ParticleLayout()
    layout_1.addParticle(particle_1, 1.0)
    layout_1.setWeight(1)
    layout_1.setTotalParticleSurfaceDensity(0.01)

    # Add layouts to layers
    layer_1.addLayout(layout_1)

    # Define multilayers
    multiLayer_1 = ba.MultiLayer()
    multiLayer_1.addLayer(layer_1)
    multiLayer_1.addLayer(layer_2)

    return multiLayer_1


def get_rectangular_detector():
    """
    Returns rectangular detector representing our PILATUS detector
    """

    detector_distance = 2000.0  # in mm
    pilatus_pixel_size = 0.172  # in mm
    pilatus_npx, pilatus_npy = 981, 1043  # number of pixels

    width = pilatus_npx*pilatus_pixel_size
    height = pilatus_npy*pilatus_pixel_size
    detector = ba.RectangularDetector(pilatus_npx, width, pilatus_npy, height)
    detector.setPerpendicularToSampleX(detector_distance, width/2., 0.0)
    return detector


def get_simulation():
    """
    Returns a GISAXS simulation with beam defined
    """
    simulation = ba.GISASSimulation()
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setDetector(get_rectangular_detector())
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
    # set plotting parameters
    rcParams['image.cmap'] = 'jet'
    rcParams['image.aspect'] = 'auto'

    fig = plt.figure(figsize=(12.80, 10.24))

    plt.subplot(2, 2, 1)
    # default units for rectangular detector are millimeters

    ba.plot_colormap(result,
                     title="In default units",
                     xlabel=r'$X_{mm}$',
                     ylabel=r'$Y_{mm}$',
                     zlabel=None)

    plt.subplot(2, 2, 2)
    ba.plot_colormap(result,
                     units=ba.Axes.NBINS,
                     title="In number of bins",
                     xlabel=r'$X_{nbins}$',
                     ylabel=r'$Y_{nbins}$',
                     zlabel=None)

    plt.subplot(2, 2, 3)
    ba.plot_colormap(result,
                     units=ba.Axes.DEGREES,
                     title="In degs",
                     xlabel=r'$\phi_f ^{\circ}$',
                     ylabel=r'$\alpha_f ^{\circ}$',
                     zlabel=None)

    plt.subplot(2, 2, 4)
    ba.plot_colormap(result,
                     units=ba.Axes.QSPACE,
                     title="Q-space",
                     xlabel=r'$Q_{y} [1/nm]$',
                     ylabel=r'$Q_{z} [1/nm]$',
                     zlabel=None)

    plt.subplots_adjust(left=0.07, right=0.97, top=0.9, bottom=0.1, hspace=0.25)
    plt.show()


if __name__ == '__main__':
    result = run_simulation()
    plot(result)
