"""
Utilities to plot form factors of particles in Born approximation
"""
import math, numpy
import matplotlib as mpl
import matplotlib.pyplot as plt
from matplotlib import rc
rc('font', **{'family': 'sans-serif', 'sans-serif': ['Helvetica']})
rc('text', usetex=True)
rc('image', cmap='inferno')

import bornagain as ba
from bornagain import nm, deg, angstrom, deg2rad


class BinRange:
    def __init__(self, vmin, vmax, n):
        self.vmin = vmin
        self.vmax = vmax
        self.n = n

    def central_index(self):
        return int((0. - self.vmin)/(self.vmax - self.vmin)*self.n)


class Detector:
    def __init__(self, bins_per_dimension, phi_min, phi_max, alpha_min,
                 alpha_max):
        self.phi = BinRange(phi_min, phi_max, bins_per_dimension)
        self.alpha = BinRange(alpha_min, alpha_max, bins_per_dimension)

    def rectangle(self):
        return self.phi.vmin, self.phi.vmax, self.alpha.vmin, self.alpha.vmax


class Result:
    def __init__(self, idx, data, title=""):
        self.idx = idx
        self.data = data
        self.title = title


def make_plot(results, det, name, nrow=1):
    """
    Make a plot consisting of one detector image for each Result in results,
    plus one common color scale.

    :param results: List of simulation results
    :param det: Detector limits
    :param name: Filename for plot during save
    :param nrow: Number of rows for different plots
    """
    mpl.rcParams['image.interpolation'] = 'none'
    n = len(results)
    ncol = 1 + (n - 1) // nrow
    # Parameters as fraction of subfig size.
    yskip = 0.2  # +ncol*0.02
    bottomskip = yskip
    topskip = yskip/2
    xskip = 0.18
    leftskip = xskip
    rightskip = 0.28 + ncol*0.03
    xtot = ncol*1.0 + (ncol - 1)*xskip + leftskip + rightskip
    ytot = nrow*1.0 + (nrow - 1)*yskip + bottomskip + topskip
    # We need parameters as fraction of total fig size.
    xskip /= xtot
    leftskip /= xtot
    rightskip /= xtot
    yskip /= ytot
    bottomskip /= ytot
    topskip /= ytot
    # Set total figure dimensions.
    ftot = 5
    fontsize = 18 + 36.0/(ncol + 2)
    # Create the figure 'fig' and its subplots axes ('tmp'->'axes').
    fig, tmp = plt.subplots(nrow, ncol, figsize=(ftot*xtot, ftot*ytot))
    if n > 1:
        axes = tmp.flat
    else:
        axes = [tmp]
    # Always the same color scale, to facilitate comparisons between figures.
    norm = mpl.colors.LogNorm(1e-8, 1)
    # Plot the subfigures.
    for res in results:
        ax = axes[res.idx]
        im = ax.imshow(res.data, norm=norm, extent=det.rectangle(), aspect=1)
        ax.set_xlabel(r'$\phi_{\rm f} (^{\circ})$', fontsize=fontsize)
        if res.idx % ncol == 0:
            ax.set_ylabel(r'$\alpha_{\rm f} (^{\circ})$', fontsize=fontsize)
        if res.title != "":
            ax.set_title(res.title, fontsize=fontsize)
        ax.tick_params(axis='both', which='major', labelsize=fontsize*21/24)
    # Adjust whitespace around and between subfigures.
    plt.subplots_adjust(wspace=xskip,
                        hspace=yskip,
                        left=leftskip,
                        right=1 - rightskip,
                        bottom=bottomskip,
                        top=1 - topskip)
    # Plot the color scale.
    cbar_ax = fig.add_axes([
        1 - rightskip + 0.4*xskip, bottomskip, 0.25*xskip,
        1 - bottomskip - topskip
    ])
    cb = fig.colorbar(im, cax=cbar_ax)
    cb.set_label(r'$\left|F(q)\right|^2/V^{\,2}$', fontsize=fontsize)
    # Output to data file, image file, and display.
    nDigits = int(math.log10(len(results))) + 1
    formatN = "%" + str(nDigits) + "i"
    for i in range(len(results)):
        fname = name + "." + (formatN % i) + ".int"
        print(fname)
        numpy.savetxt(fname, results[i].data)
    plt.savefig(name + ".pdf", format="pdf", bbox_inches='tight')
    # plt.show()


def get_sample(ff, trafo):
    """Build and return a sample consisting of uncorrelated particles with given
    form factor and transformation operator

    :param ff: Form factor
    :param trafo: Optional rotation
    """
    # defining materials
    m_vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    m_particle = ba.HomogeneousMaterial("Particle", 1e-5, 0)

    # collection of particles
    particle = ba.Particle(m_particle, ff)
    particle_layout = ba.ParticleLayout()
    if trafo is not None:
        particle.setRotation(trafo)
        particle_layout.addParticle(particle)
    else:
        particle_layout.addParticle(particle)

    vacuum_layer = ba.Layer(m_vacuum)
    vacuum_layer.addLayout(particle_layout)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    return multi_layer


def get_simulation(det):
    """Create and return GISAXS simulation with beam and detector defined

    :param det: Detector limits
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(det.phi.n, det.phi.vmin*deg,
                                     det.phi.vmax*deg, det.alpha.n,
                                     det.alpha.vmin*deg, det.alpha.vmax*deg)
    simulation.setBeamParameters(1.0*angstrom, 0, 0)
    return simulation


def run_simulation(det, ff, trafo=None):
    """Run simulation and plot results

    :param det: Detector limits
    :param ff: Form factor
    :param trafo: Optional rotation
    """
    zero = ba.cvector_t(0, 0, 0)
    volume = abs(ff.evaluate_for_q(zero))
    print("Volume: %g" % volume)
    sample = get_sample(ff, trafo)
    simulation = get_simulation(det)
    simulation.setSample(sample)
    simulation.runSimulation()
    data = simulation.result().array()
    nor = data[det.alpha.n - det.alpha.central_index() - 1,
               det.phi.central_index()]
    data /= nor
    return data + 1e-80  # for log scale
