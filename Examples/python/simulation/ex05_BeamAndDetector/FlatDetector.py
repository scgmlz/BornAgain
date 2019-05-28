"""
Simulation with flat detector. Pilatus3-1M detector is used as an example.
Results will be compared against simulation with spherical detector.
"""
import numpy
import bornagain as ba
from bornagain import deg, angstrom, nm
import matplotlib
from matplotlib import pyplot as plt

detector_distance = 1000.0  # in mm
pilatus_pixel_size = 0.172  # in mm
pilatus_npx, pilatus_npy = 981, 1043  # number of pixels


def get_sample():
    """
    Returns a sample with cylindrical particles on a substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    edge = 40*nm
    ff = ba.FormFactorBox(edge, edge, edge)
    cylinder = ba.Particle(m_particle, ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


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
    return ba.SphericalDetector(
        n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max)


def get_flat_detector():
    """
    Returns a flat detector representing our PILATUS detector
    """
    width = pilatus_npx*pilatus_pixel_size
    height = pilatus_npy*pilatus_pixel_size
    detector = ba.FlatDetector(pilatus_npx, width, pilatus_npy, height)
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
    ba.plot_colormap(results['spherical'], title="Spherical detector",
                     xlabel=r'$\phi_f ^{\circ}$', ylabel=r'$\alpha_f ^{\circ}$',
                     zlabel="")

    # showing  result of flat detector simulation
    plt.subplot(1, 3, 2)
    ba.plot_colormap(results['rectangular'], title="Flat detector",
                     xlabel='X, mm', ylabel='Y, mm', zlabel="")

    # show relative difference between two plots (sph[i]-rect[i])/rect[i]
    # for every detector pixel
    sph_array = results['spherical'].array()
    rect_array = results['rectangular'].array()
    rel_diff = 2.0 * numpy.abs(sph_array - rect_array)/(sph_array + rect_array)
    plt.subplot(1, 3, 3)
    im = plt.imshow(rel_diff, norm=colors.LogNorm(1e-6, 1.0), aspect='auto')
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

    # runs simulation for flat detector
    simulation.setDetector(get_flat_detector())
    simulation.runSimulation()
    results['rectangular'] = simulation.result()

    return results


if __name__ == '__main__':
    results = run_simulation()
    plot(results)
