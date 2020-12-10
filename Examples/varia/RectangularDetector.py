"""
Simulation with rectangular detector. Pilatus3-1M detector is used as an example.
Results will be compared against simulation with spherical detector.
"""
import numpy
import bornagain as ba
from bornagain import angstrom, deg, nm, nm2, kvector_t
import matplotlib
from matplotlib import pyplot as plt

detector_distance = 1000.0  # in mm
pilatus_pixel_size = 0.172  # in mm
pilatus_npx, pilatus_npy = 981, 1043  # number of pixels


def get_sample():
    """
    Returns a sample with cylindrical particles on a substrate.
    """

    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)

    # Define form factors
    ff = ba.FormFactorBox(40.0*nm, 40.0*nm, 40.0*nm)

    # Define particles
    particle = ba.Particle(material_Particle, ff)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle, 1.0)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

    # Define layers
    layer_1 = ba.Layer(material_Vacuum)
    layer_1.addLayout(layout)
    layer_2 = ba.Layer(material_Substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)

    return sample


def get_spherical_detector():
    """
    Returns a spherical detector roughly approximating our PILATUS detector
    """
    n_phi = pilatus_npx
    n_alpha = pilatus_npy
    width = pilatus_npx*pilatus_pixel_size
    height = pilatus_npy*pilatus_pixel_size
    phi_min = numpy.arctan(-width/2./detector_distance)
    phi_max = numpy.arctan(width/2./detector_distance)
    alpha_min = 0.0
    alpha_max = numpy.arctan(height/detector_distance)
    return ba.SphericalDetector(n_phi, phi_min, phi_max, n_alpha, alpha_min,
                                alpha_max)


def get_rectangular_detector():
    """
    Returns a rectangular detector representing our PILATUS detector
    """
    width = pilatus_npx*pilatus_pixel_size
    height = pilatus_npy*pilatus_pixel_size
    detector = ba.RectangularDetector(pilatus_npx, width, pilatus_npy, height)
    detector.setPerpendicularToSampleX(detector_distance, width/2., 0.0)
    return detector


def get_simulation():
    """
    Return a GISAXS simulation with defined beam
    """
    simulation = ba.GISASSimulation()
    simulation.setBeamParameters(10*angstrom, 0.2*deg, 0.0*deg)
    return simulation


def plot(results):
    """
    Plots results of two simulations and their relative difference on one canvas
    """
    from matplotlib import colors
    fig = plt.figure(figsize=(13.6, 5.12))

    # showing  result of spherical detector simulation
    plt.subplot(1, 3, 1)
    ba.plot_colormap(results['spherical'],
                     title="Spherical detector",
                     xlabel=r'$\phi_f ^{\circ}$',
                     ylabel=r'$\alpha_f ^{\circ}$',
                     zlabel="",
                     *sys.argv[1:])

    # showing  result of rectangular detector simulation
    plt.subplot(1, 3, 2)
    ba.plot_colormap(results['rectangular'],
                     title="Rectangular detector",
                     xlabel='X, mm',
                     ylabel='Y, mm',
                     zlabel="",
                     *sys.argv[1:])

    # show relative difference between two plots (sph[i]-rect[i])/rect[i]
    # for every detector pixel
    sph_array = results['spherical'].array()
    rect_array = results['rectangular'].array()
    rel_diff = 2.0*numpy.abs(sph_array - rect_array)/(sph_array + rect_array)
    plt.subplot(1, 3, 3)
    im = plt.imshow(rel_diff,
                    norm=colors.LogNorm(1e-6, 1.0),
                    aspect='auto',
                    cmap='jet')
    cb = plt.colorbar(im, pad=0.025)
    plt.xlabel('X, bins', fontsize=14)
    plt.ylabel('Y, bins', fontsize=14)
    plt.title("Relative difference")

    plt.subplots_adjust(left=0.05, right=0.92, top=0.88, bottom=0.12)
    plt.tight_layout()
    plt.show()


def run_simulation():
    """
    Run two simulations for two different detectors and plot results
    """
    results = {}

    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)

    # runs simulation for spherical detector
    simulation.setDetector(get_spherical_detector())
    simulation.runSimulation()
    results['spherical'] = simulation.result()

    # runs simulation for rectangular detector
    simulation.setDetector(get_rectangular_detector())
    simulation.runSimulation()
    results['rectangular'] = simulation.result()

    return results


if __name__ == '__main__':
    results = run_simulation()
    plot(results)
