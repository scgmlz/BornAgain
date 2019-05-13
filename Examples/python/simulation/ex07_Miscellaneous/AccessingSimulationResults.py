"""
Extended example for simulation results treatment (cropping, slicing, exporting)
The standard "Cylinders in DWBA" sample is used to setup the simulation.
"""
import math
import random
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


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(201, -2.0*deg, 2.0*deg,
                                     201, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+05)
    return simulation


def get_noisy_image(hist):
    """
    Returns clone of input histogram filled with additional noise
    """
    result = hist.clone()
    noise_factor = 2.0
    for i in range(0, result.getTotalNumberOfBins()):
        amplitude = result.getBinContent(i)
        sigma = noise_factor*math.sqrt(amplitude)
        noisy_amplitude = random.gauss(amplitude, sigma)
        result.setBinContent(i, noisy_amplitude)
    return result


def plot_histogram(hist, zmin=None, zmax=None):
    ba.plot_histogram(hist, xlabel=r'$\varphi_f ^{\circ}$',
                      ylabel=r'$\alpha_f ^{\circ}$',
                      zlabel="", zmin=zmin, zmax=zmax)


def get_relative_difference(hist):
    """
    Creates noisy histogram made of original histogram,
    then creates and plots a relative difference histogram: (noisy-hist)/hist
    """
    noisy = get_noisy_image(hist)
    return noisy.relativeDifferenceHistogram(hist)


def plot_slices(hist):
    """
    Plot 1D slices along y-axis at certain x-axis values.
    """
    noisy = get_noisy_image(hist)

    # projection along Y, slice at fixed x-value
    proj1 = noisy.projectionY(0.0)
    plt.semilogy(proj1.getBinCenters(),
                 proj1.getBinValues(),
                 label=r'$\phi=0.0^{\circ}$')

    # projection along Y, slice at fixed x-value
    proj2 = noisy.projectionY(0.5)  # slice at fixed value
    plt.semilogy(proj2.getBinCenters(),
                 proj2.getBinValues(),
                 label=r'$\phi=0.5^{\circ}$')

    # projection along Y for all X values between [xlow, xup], averaged
    proj3 = noisy.projectionY(0.41, 0.59)
    plt.semilogy(proj3.getBinCenters(),
                 proj3.array(ba.IHistogram.AVERAGE),
                 label=r'$<\phi>=0.5^{\circ}$')

    plt.xlim(proj1.getXmin(), proj1.getXmax())
    plt.ylim(proj2.getMinimum(), proj1.getMaximum()*10.0)
    plt.xlabel(r'$\alpha_f ^{\circ}$', fontsize=16)
    plt.legend(loc='upper right')
    plt.tight_layout()


def plot(hist):
    """
    Runs different plotting functions one by one
    to demonstrate trivial data presentation tasks.
    """

    plt.figure(figsize=(12.80, 10.24))

    plt.subplot(2, 2, 1)
    plot_histogram(hist)
    plt.title("Intensity as colormap")

    plt.subplot(2, 2, 2)
    crop = hist.crop(-1.0, 0.5, 1.0, 1.0)
    plot_histogram(crop)
    plt.title("Cropping")

    plt.subplot(2, 2, 3)
    reldiff_hist = get_relative_difference(hist)
    plot_histogram(reldiff_hist, zmin=1e-03, zmax=10)
    plt.title("Relative difference")

    plt.subplot(2, 2, 4)
    plot_slices(hist)
    plt.title("Various slicing of 2D into 1D")

    # save to file
    # result.save("result.int")
    # result.save("result.tif")
    # result.save("result.txt")
    # result.save("result.int.gz")
    # result.save("result.tif.gz")
    # result.save("result.txt.gz")
    # result.save("result.int.bz2")
    # result.save("result.tif.bz2")
    # result.save("result.txt.bz2")

    plt.tight_layout()
    plt.show()


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result().histogram2d()


if __name__ == '__main__':
    result = run_simulation()
    ba.mpl_settings()
    plot(result)
