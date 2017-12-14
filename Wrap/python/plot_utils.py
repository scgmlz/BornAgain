#  **************************************************************************  #
'''
#   BornAgain: simulate and fit scattering at grazing incidence
#
#   @file      Wrap/python.plot_utils
#   @brief     Python extensions of the SWIG-generated Python module bornagain.
#
#   @homepage  http://apps.jcns.fz-juelich.de/BornAgain
#   @license   GNU General Public License v3 or higher (see COPYING)
#   @copyright Forschungszentrum Juelich GmbH 2016
#   @authors   Scientific Computing Group at MLZ Garching
#   @authors   J. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
'''
#  **************************************************************************  #
from __future__ import print_function
import bornagain as ba
from bornagain import deg as deg
from bornagain import IFitObserver as IFitObserver
from matplotlib import pyplot as plt
from matplotlib import gridspec, colors


def get_axes_limits(intensity):
    """
    Returns axes range as expected by pyplot.imshow.
    :param intensity: Histogram2D object from GISAS simulation
    :return:axes range
    """
    result = [intensity.getXmin(), intensity.getXmax(),
              intensity.getYmin(), intensity.getYmax()]

    # We show radians as degrees. If no units defined in histogram object,
    # we assume radians.
    if "rad" in intensity.axesUnits() or len(intensity.axesUnits()) == 0:
        result = [x / deg for x in result]

    return result


def get_xlabel(intensity):
    """
    Returns the label for x-axis
    :param intensity: Histogram2D object from GISAS simulation
    :return:label for x-axis
    """
    if "mm" in intensity.axesUnits():
        return r'$X_{mm}$'

    if "deg" in intensity.axesUnits() or "rad" in intensity.axesUnits():
        return r'$\phi_f ^{\circ}$'

    if "qyqz" in intensity.axesUnits():
        return r'$Q_{y} [1/nm]$'


def get_ylabel(intensity):
    """
    Returns the label for y-axis
    :param intensity: Histogram2D object from GISAS simulation
    :return:label for y-axis
    """
    if "mm" in intensity.axesUnits():
        return r'$X_{mm}$'

    if "deg" in intensity.axesUnits() or "rad" in intensity.axesUnits():
        return r'$\alpha_f ^{\circ}$'

    if "qyqz" in intensity.axesUnits():
        return r'$Q_{z} [1/nm]$'


def plot_colormap(intensity, zmin=None, zmax=None,
                  xlabel=None, ylabel=None, zlabel=None,
                  title=None):
    """
    Plots intensity data as color map
    :param intensity: Histogram2D object obtained from GISASSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """
    zmin = 1.0 if zmin is None else zmin
    zmax = intensity.getMaximum() if zmax is None else zmax

    xlabel = get_xlabel(intensity) if xlabel is None else xlabel
    ylabel = get_ylabel(intensity) if ylabel is None else ylabel
    zlabel = "Intensity" if zlabel is None else zlabel

    im = plt.imshow(
        intensity.getArray(),
        norm=colors.LogNorm(zmin, zmax),
        extent=get_axes_limits(intensity),
        aspect='auto',
    )
    cb = plt.colorbar(im, pad=0.025)

    if xlabel:
        plt.xlabel(xlabel, fontsize=14)

    if ylabel:
        plt.ylabel(ylabel, fontsize=14)

    if zlabel:
        cb.set_label(zlabel, size=14)

    if title:
        plt.title(title)


def plot_intensity_data(intensity, zmin=None, zmax=None):
    """
    Plots intensity data as color map and hold the plot.
    If command line parameter was provided, save image instead of plotting.
    :param intensity: Histogram2D object obtained from GISASSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """
    plot_colormap(intensity, zmin, zmax)
    plt.show()


class Plotter:
    def __init__(self):

        self._fig = plt.figure(figsize=(10.25, 7.69))
        self._fig.canvas.draw()

    def reset(self):
        self._fig.clf()

    def plot(self, fit_suite):
        plt.pause(0.03)



class PlotterGISAS(Plotter):
    def __init__(self):
        Plotter.__init__(self)

    @staticmethod
    def make_subplot(nplot):
        plt.subplot(2, 2, nplot)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)

    def plot(self, fit_suite):
        Plotter.reset(self)

        self.make_subplot(1)
        real_data = fit_suite.getRealData()
        plot_colormap(real_data, title="\"Real\" data",
                      zmin=1.0, zmax=real_data.getMaximum(),
                      xlabel='', ylabel='', zlabel='')

        self.make_subplot(2)
        sim_data = fit_suite.getSimulationData()
        plot_colormap(sim_data, title="Simulated data",
                      zmin=1.0, zmax=real_data.getMaximum(),
                      xlabel='', ylabel='', zlabel='')

        self.make_subplot(3)
        chi_data = fit_suite.getChiSquaredMap()
        plot_colormap(chi_data, title="Chi2 map",
                      zmin=0.001, zmax=10.0,
                      xlabel='', ylabel='', zlabel='')

        self.make_subplot(4)
        plt.title('Parameters')
        plt.axis('off')
        plt.text(0.01, 0.85, "Iterations  " + '{:d}     {:s}'.
                 format(fit_suite.numberOfIterations(), fit_suite.minimizer().minimizerName()))
        plt.text(0.01, 0.75, "Chi2       " + '{:8.4f}'.format(fit_suite.getChi2()))
        for index, fitPar in enumerate(fit_suite.fitParameters()):
            plt.text(0.01, 0.55 - index * 0.1, '{:30.30s}: {:6.3f}'.format(fitPar.name(), fitPar.value()))

        Plotter.plot(self, fit_suite)


class PlotterSpecular(Plotter):
    """
    Draws fit progress every nth iteration. This class has to be attached to
    FitSuite via attachObserver method. Intended specifically for observing
    specular data fit.
    FitSuite kernel will call DrawObserver's update() method every n'th iteration.
    """

    def __init__(self, draw_every_nth=10):
        Plotter.__init__(self)
        self.gs = gridspec.GridSpec(1, 2, width_ratios=[2.5, 1], wspace=0)

    @staticmethod
    def as_si(val, ndp):
        """
        Fancy print of scientific-formatted values
        :param val: numeric value
        :param ndp: number of decimal digits to print
        :return: a string corresponding to the _val_
        """
        s = '{x:0.{ndp:d}e}'.format(x=val, ndp=ndp)
        m, e = s.split('e')
        return r'{m:s}\times 10^{{{e:d}}}'.format(m=m, e=int(e))

    @staticmethod
    def trunc_str(token, length):
        """
        Truncates token if it is longer than length.

        Example:
            trunc_str("123456789", 8) returns "123456.."

            trunc_str("123456789", 9) returns "123456789"

        :param token: input string
        :param length: max non-truncated length
        :return:
        """
        return (token[:length - 2] + '..') if len(token) > length else token

    def plot_table(self, fit_suite):

        # definitions and values
        trunc_length = 9  # max string field width in the table
        n_digits = 1  # number of decimal digits to print
        n_iterations = fit_suite.numberOfIterations()  # number of iterations
        minimizer = fit_suite.minimizer().minimizerName()
        fom_max = fit_suite.getChiSquaredMap().getArray().max()  # max Figure Of Merit (FOM) value
        fitted_parameters = fit_suite.fitParameters()

        # creating table content
        labels = ("Parameter", "Value")
        table_data = [["Minimizer", '{:s}'.format(self.trunc_str(minimizer, trunc_length))],
                      ["Iteration", '${:d}$'.format(n_iterations)],
                      ["$\chi^2$", '${:s}$'.format(self.as_si(fom_max, n_digits))]]
        for fitPar in fitted_parameters:
            table_data.append(['{:s}'.format(self.trunc_str(fitPar.name(), trunc_length)),
                               '${:s}$'.format(self.as_si(fitPar.value(), n_digits))])

        # creating table
        axs = plt.subplot(self.gs[1])
        axs.axis('tight')
        axs.axis('off')
        table = plt.table(cellText=table_data, colLabels=labels, cellLoc='center',
                          loc='bottom left', bbox=[0.0, 0.0, 1.0, 1.0])

        # # setting alignment to center in 0th column
        # for key, cell in table.get_celld().items():
        #     col = key[1]
        #     if col == 0:
        #         cell._loc = 'center'  # accessing private member is the only option to change alignment for one cell

    def plot_graph(self, fit_suite):
        # retrieving data from fit suite
        real_data = fit_suite.getRealData()
        sim_data = fit_suite.getSimulationData()

        # normalizing axis coordinates
        axis = real_data.getXaxis().getBinCenters()
        norm = 1
        if "rad" in real_data.axesUnits():
            norm = ba.deg
        axis_values = [value / norm for value in axis]

        # default font properties dictionary to use
        font = {'family': 'serif',
                'weight': 'normal',
                'size': 16}

        plt.subplot(self.gs[0])
        plt.semilogy(axis_values, sim_data.getArray(), 'b',
                     axis_values, real_data.getArray(), 'k--')
        plt.ylim((0.5 * real_data.getMinimum(), 5 * real_data.getMaximum()))
        plt.legend(['BornAgain', 'Reference'], loc='upper right', prop=font)
        plt.xlabel("Incident angle, deg", fontdict=font)
        plt.ylabel("Intensity", fontdict=font)
        plt.title("Specular data fitting", fontdict=font)

    def plot(self, fit_suite):
        Plotter.reset(self)

        self.plot_graph(fit_suite)
        self.plot_table(fit_suite)

        plt.tight_layout()

        Plotter.plot(self, fit_suite)


class DefaultFitObserver(IFitObserver):
    """
    Draws fit progress every nth iteration. This class has to be attached to
    FitSuite via attachObserver method.
    FitSuite kernel will call DrawObserver's update() method every n'th iteration.
    It is up to the user what to do here.
    """
    import sys
    import traceback

    def __init__(self, draw_every_nth=10, SimulationType='GISAS'):
        """
        Initializes observer
        :param draw_every_nth: specifies when to output data, defaults to each 10th iteration
        :param SimulationType: simulation type underlying fitting:
            'GISAS' - GISAS simulation, default

            'Specular' - specular simulation

        """
        IFitObserver.__init__(self, draw_every_nth)
        if SimulationType is 'GISAS':
            self._plotter = PlotterGISAS()
        elif SimulationType is 'Specular':
            self._plotter = PlotterSpecular()
        else:
            raise Exception("Unknown simulation type {:s}.".format(SimulationType))

    def update(self, fit_suite):
        self._plotter.plot(fit_suite)

