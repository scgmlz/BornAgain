#  **************************************************************************  #
"""
#   BornAgain: simulate and fit reflection and scattering
#
#   @file      Wrap/Python/ba_fitmonitor.py
#   @brief     Plotter classes for monitoring fit progress.
#
#   @homepage  http://apps.jcns.fz-juelich.de/BornAgain
#   @license   GNU General Public License v3 or higher (see COPYING)
#   @copyright Forschungszentrum Juelich GmbH 2019
#   @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
"""
#  **************************************************************************  #

import bornagain as ba
import ba_plot
try:  # workaround for build servers
    import numpy as np
    from matplotlib import pyplot as plt
    from matplotlib import gridspec, colors
except Exception as e:
    print("In ba_fitmonitor.py: {:s}".format(str(e)))

label_fontsize = 16


class Plotter:
    """
    Draws fit progress. Base class for simulation-specific classes (PlotterGISAS etc).
    """
    def __init__(self,
                 zmin=None,
                 zmax=None,
                 xlabel=None,
                 ylabel=None,
                 units=ba.Axes.DEFAULT,
                 aspect=None):

        self._fig = plt.figure(figsize=(10.25, 7.69))
        self._fig.canvas.draw()
        self._zmin = zmin
        self._zmax = zmax
        self._xlabel = xlabel
        self._ylabel = ylabel
        self._units = units
        self._aspect = aspect

    def reset(self):
        self._fig.clf()

    def plot(self):
        self._fig.tight_layout()
        plt.pause(0.03)


class PlotterGISAS(Plotter):
    """
    Draws fit progress, for GISAS simulation.
    """
    def __init__(self,
                 zmin=None,
                 zmax=None,
                 xlabel=None,
                 ylabel=None,
                 units=ba.Axes.DEFAULT,
                 aspect=None):
        Plotter.__init__(self, zmin, zmax, xlabel, ylabel, units, aspect)

    @staticmethod
    def make_subplot(nplot):
        plt.subplot(2, 2, nplot)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)

    def plot(self, fit_objective):
        Plotter.reset(self)

        real_data = fit_objective.experimentalData()
        sim_data = fit_objective.simulationResult()
        diff = fit_objective.absoluteDifference()

        self.make_subplot(1)

        # same limits for both plots
        arr = real_data.array()
        zmax = np.amax(arr) if self._zmax is None else self._zmax
        zmin = zmax*1e-6 if self._zmin is None else self._zmin

        ba.plot_colormap(real_data,
                         title="Experimental data",
                         zmin=zmin,
                         zmax=zmax,
                         units=self._units,
                         xlabel=self._xlabel,
                         ylabel=self._ylabel,
                         zlabel='',
                         aspect=self._aspect)

        self.make_subplot(2)
        ba.plot_colormap(sim_data,
                         title="Simulated data",
                         zmin=zmin,
                         zmax=zmax,
                         units=self._units,
                         xlabel=self._xlabel,
                         ylabel=self._ylabel,
                         zlabel='',
                         aspect=self._aspect)

        self.make_subplot(3)
        ba.plot_colormap(diff,
                         title="Difference",
                         zmin=zmin,
                         zmax=zmax,
                         units=self._units,
                         xlabel=self._xlabel,
                         ylabel=self._ylabel,
                         zlabel='',
                         aspect=self._aspect)

        self.make_subplot(4)
        plt.title('Parameters')
        plt.axis('off')

        iteration_info = fit_objective.iterationInfo()

        plt.text(
            0.01, 0.85, "Iterations  " +
            '{:d}'.format(iteration_info.iterationCount()))
        plt.text(0.01, 0.75,
                 "Chi2       " + '{:8.4f}'.format(iteration_info.chi2()))
        index = 0
        params = iteration_info.parameterMap()
        for key in params:
            plt.text(0.01, 0.55 - index*0.1,
                     '{:30.30s}: {:6.3f}'.format(key, params[key]))
            index = index + 1

        Plotter.plot(self)


class PlotterSpecular(Plotter):
    """
    Draws fit progress, for specular simulation.
    """
    def __init__(self, units=ba.Axes.DEFAULT):
        Plotter.__init__(self)
        self.gs = gridspec.GridSpec(1, 2, width_ratios=[2.5, 1], wspace=0)
        self.units = units

    def __call__(self, fit_objective):
        self.plot(fit_objective)

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
        return (token[:length - 2] +
                '..') if len(token) > length else token

    def plot_table(self, fit_objective):

        iteration_info = fit_objective.iterationInfo()

        trunc_length = 9  # max string field width in the table
        n_digits = 1  # number of decimal digits to print

        n_iterations = iteration_info.iterationCount(
        )  # current number of iterations passed
        rel_dif = fit_objective.relativeDifference().array().max(
        )  # maximum relative difference
        fitted_parameters = iteration_info.parameterMap()

        # creating table content
        labels = ("Parameter", "Value")
        table_data = [["Iteration", '${:d}$'.format(n_iterations)],
                      [
                          "$d_{r, max}$",
                          '${:s}$'.format(self.as_si(rel_dif, n_digits))
                      ]]
        for key, value in fitted_parameters.iteritems():
            table_data.append([
                '{:s}'.format(self.trunc_str(key, trunc_length)),
                '${:s}$'.format(self.as_si(value, n_digits))
            ])

        # creating table
        axs = plt.subplot(self.gs[1])
        axs.axis('tight')
        axs.axis('off')
        table = plt.table(cellText=table_data,
                          colLabels=labels,
                          cellLoc='center',
                          loc='bottom left',
                          bbox=[0, 0, 1, 1.0])

    def plot_graph(self, fit_objective):
        # retrieving data from fit suite
        real_data = fit_objective.experimentalData()
        sim_data = fit_objective.simulationResult()
        unc_data = fit_objective.uncertaintyData()

        # data values
        sim_values = sim_data.array(self.units)
        real_values = real_data.array(self.units)
        unc_values = None if unc_data is None else unc_data.array(
            self.units)

        # default font properties dictionary to use
        font = {
            'family': 'serif',
            'weight': 'normal',
            'size': label_fontsize
        }

        plt.subplot(self.gs[0])
        plt.semilogy(sim_data.axis(), sim_values, 'b', real_data.axis(),
                     real_values, 'k--')
        if unc_values is not None:
            plt.semilogy(real_data.axis(),
                         real_values - unc_values,
                         'xkcd:grey',
                         alpha=0.6)
            plt.semilogy(real_data.axis(),
                         real_values + unc_values,
                         'xkcd:grey',
                         alpha=0.6)
        plt.ylim((0.5*np.min(real_values), 5*np.max(real_values)))

        xlabel = ba_plot.get_axes_labels(real_data, self.units)[0]
        legend = ['BornAgain', 'Data']
        if unc_values is not None:
            legend = ['BornAgain', 'Data', r'Data $\pm \sigma$']
        plt.legend(legend, loc='upper right', prop=font)
        plt.xlabel(xlabel, fontdict=font)
        plt.ylabel("Intensity", fontdict=font)
        plt.title("Specular data fitting", fontdict=font)

    def plot(self, fit_objective):
        Plotter.reset(self)

        self.plot_graph(fit_objective)
        self.plot_table(fit_objective)

        Plotter.plot(self)
