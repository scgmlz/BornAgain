"""
Utilities to plot form factors of particles in Born approximation
"""
import numpy
import matplotlib as mpl
import matplotlib.pyplot as plt
import bornagain as ba
from bornagain import nanometer, degree, angstrom, deg2rad


class BinRange:
    def __init__(self, vmin, vmax, n):
        self.vmin = vmin
        self.vmax = vmax
        self.n = n

    def origin_index(self):
        return int((0.-self.vmin)/(self.vmax-self.vmin)*self.n)

    def range(self):
        return self.vmax - self.vmin


class DetPars:
    def __init__(self, bins_per_dimension, y_min, y_max, z_min, z_max):
        self.y = BinRange(y_min, y_max, bins_per_dimension)
        self.z = BinRange(z_min, z_max, bins_per_dimension)

    def rectangle(self):
        return self.y.vmin, self.y.vmax, self.z.vmin, self.z.vmax


class Result:
    def __init__(self, idx, data, title=""):
        self.idx = idx
        self.data = data
        self.title = title


def make_plot(results, detPars, name, nrow=1):
    """Make a plot consisting of one detector image for each Result in results,
    plus one common color scale.

    :param results: List of simulation results
    :param detPars: Detector limits
    :param name: Filename for plot during save
    :param nrow: Number of rows for different plots
    """
    mpl.rcParams['image.interpolation'] = 'none'
    n = len(results)
    ncol = 1+(n-1)//nrow
    # Parameters as fraction of subfig size.
    yskip = 0.2  # +ncol*0.02
    bottomskip = yskip
    topskip = yskip/2
    xskip = 0.21
    leftskip = xskip
    rightskip = 0.28+ncol*0.03
    xtot = ncol*1.0 + (ncol-1)*xskip + leftskip + rightskip
    ytot = nrow*1.0 + (nrow-1)*yskip + bottomskip + topskip
    # We need parameters as fraction of total fig size.
    xskip /= xtot
    leftskip /= xtot
    rightskip /= xtot
    yskip /= ytot
    bottomskip /= ytot
    topskip /= ytot
    # Set total figure dimensions.
    ftot = 5
    fontsize = 18+36.0/(ncol+2)
    # Create the figure 'fig' and its subplots axes ('tmp'->'axes').
    fig, tmp = plt.subplots(nrow, ncol, figsize=(ftot*xtot, ftot*ytot))
    if n > 1:
        axes = tmp.flat
    else:
        axes = [tmp]
    # Always the same color scale, to facilitate comparisons between figures.
    norm = mpl.colors.LogNorm(1e-10, 1)
    # Plot the subfigures.
    for res in results:
        ax = axes[res.idx]
        im = ax.imshow(res.data,
                       norm=norm,
                       extent=detPars.rectangle(),
                       aspect=1)
        ax.set_xlabel(r'$k_y/k_x$', fontsize=fontsize)
        if res.idx % ncol == 0:
            ax.set_ylabel(r'$k_z/k_x$', fontsize=fontsize)
        if res.title != "":
            ax.set_title(res.title, fontsize=fontsize)
        ax.tick_params(axis='both', which='major', labelsize=fontsize*21/24)
    # Adjust whitespace around and between subfigures.
    plt.subplots_adjust(wspace=xskip, hspace=yskip,
                        left=leftskip, right=1-rightskip,
                        bottom=bottomskip, top=1-topskip)
    # Plot the color scale.
    cbar_ax = fig.add_axes([1-rightskip+0.4*xskip, bottomskip,
                            0.25*xskip, 1-bottomskip-topskip])
    cb = fig.colorbar(im, cax=cbar_ax)
    cb.set_label(r'$\left|F(q)\right|^2/V^{\,2}$', fontsize=fontsize)
    # Output to file or display.
    plt.savefig(name+".pdf", format="pdf", bbox_inches='tight')
    plt.show()


def get_sample(ff, trafo):
    """Build and return a sample consisting of uncorrelated particles with given
    form factor and transformation operator

    :param ff: Form factor
    :param trafo: Optional rotation
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_particle = ba.HomogeneousMaterial("Particle", 1e-5, 0)

    # collection of particles
    particle = ba.Particle(m_particle, ff)
    particle_layout = ba.ParticleLayout()
    if trafo is not None:
        particle.setRotation(trafo)
        particle_layout.addParticle(particle)
    else:
        particle_layout.addParticle(particle)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    return multi_layer


def get_simulation(detPars, ff, trafo=None):
    """Create and return GISAXS simulation

    :param detPars: Detector limits
    :param sample
    """
    simulation = ba.GISASSimulation()
    detector = ba.RectangularDetector(detPars.y.n, detPars.y.range(), detPars.z.n, detPars.z.range())
    detector.setPerpendicularToSampleX(1., -detPars.y.vmin, -detPars.z.vmin)
    simulation.setDetector(detector)
    simulation.setBeamParameters(1.0*nanometer, 0, 0)
    sample = get_sample(ff, trafo)
    simulation.setSample(sample)
    return simulation


def run_sim(simulation, detPars):
    """Run simulation and return plottable results
    """
    simulation.runSimulation()
    data = simulation.result().array()
    nor = data[detPars.z.n - detPars.z.origin_index() - 1, detPars.y.origin_index()]
    data /= nor
    return data + 1e-80  # for log scale


def run_simulation(detPars, ff, trafo=None):
    """Create simulation, run it, and return plottable results

    :param detPars: Detector limits
    :param ff: Form factor
    :param trafo: Optional rotation
    """
    return run_sim( get_simulation(detPars, tt, trafo), detPars )
