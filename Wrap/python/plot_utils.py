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
try:  # workaround for build servers
    import numpy as np
    from matplotlib import pyplot as plt
    from matplotlib import gridspec, colors
except Exception as e:
    print("In plot_utils.py: {:s}".format(str(e)))


label_fontsize = 16


def get_axes_limits(result, units):
    """
    Returns axes range as expected by pyplot.imshow.
    :param result: SimulationResult object from a Simulation
    :param units: units to use
    :return: axes ranges as a flat list
    """
    axis_infos = result.axisInfo(units)
    limits = [ [axis_infos[i].m_min, axis_infos[i].m_max] for i in range(len(axis_infos)) ]
    flat_limits = [ v for sublist in limits for v in sublist ]

    return flat_limits


def translate_axis_label(label):
    """
    Formats an axis label into a LaTeX representation
    :param label: text representation of the axis label
    :return: LaTeX representation
    """
    label_dict = {
                 'X [nbins]'     : r'$X \; $(bins)',
                 'phi_f [rad]'   : r'$\varphi_f \; $(rad)',
                 'phi_f [deg]'   : r'$\varphi_f \; $(deg)',
                 'alpha_i [rad]' : r'$\alpha_i \; $(rad)',
                 'alpha_i [deg]' : r'$\alpha_i \; $(deg)',
                 'X [mm]'        : r'$X \; $(mm)',
                 'Qx [1/nm]'     : r'$Q_x \; $(nm$^{-1}$)',
                 'Qy [1/nm]'     : r'$Q_y \; $(nm$^{-1}$)',
                 'Q [1/nm]'      : r'$Q \; $(nm$^{-1}$)',

                 'Y [nbins]'     : r'$Y \; $(bins)',
                 'alpha_f [rad]' : r'$\alpha_f \; $(rad)',
                 'alpha_f [deg]' : r'$\alpha_f \; $(deg)',
                 'Y [mm]'        : r'$Y \; $(mm)',
                 'Qz [1/nm]'     : r'$Q_z \; $(nm$^{-1}$)',
                 'Position [nm]' : r'$Position \; $(nm)'
                 }
    if label in label_dict.keys():
        return label_dict[label]
    else:
        return label


def get_axes_labels(result, units):
    """
    Returns axes range as expected by pyplot.imshow.
    :param result: SimulationResult object from a Simulation
    :param units: units to use
    :return: axes ranges as a flat list
    """
    axis_infos = result.axisInfo(units)
    labels = [ translate_axis_label(axis_infos[i].m_name) for i in range(len(axis_infos)) ]

    return labels


def plot_array(array, zmin=None, zmax=None, xlabel=None, ylabel=None, zlabel=None,
               title=None, axes_limits=None, **kwargs):
    """
    Plots numpy array as a colormap in log scale.
    """

    zlabel = "Intensity" if zlabel is None else zlabel

    zmax = np.amax(array) if zmax is None else zmax
    zmin = 1e-6*zmax if zmin is None else zmin

    if zmin == zmax == 0.0:
        norm = colors.Normalize(0, 1)
    else:
        norm = colors.LogNorm(zmin, zmax)

    im = plt.imshow(array, norm=norm, extent=axes_limits, **kwargs)
    cb = plt.colorbar(im, pad=0.025)

    if xlabel:
        plt.xlabel(xlabel, fontsize=label_fontsize)

    if ylabel:
        plt.ylabel(ylabel, fontsize=label_fontsize)

    if zlabel:
        cb.set_label(zlabel, size=label_fontsize)

    if title:
        plt.title(title)


def plot_histogram(hist, zmin=None, zmax=None, xlabel=None, ylabel=None, zlabel=None,
                  title=None, **kwargs):
    """
    Plots intensity data as color map
    :param intensity: Histogram2D object obtained from GISASSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """

    if not xlabel:
        xlabel = translate_axis_label(hist.getXaxis().getName())

    if not ylabel:
        ylabel = translate_axis_label(hist.getYaxis().getName())

    axes_limits = [hist.getXmin(), hist.getXmax(),
                   hist.getYmin(), hist.getYmax()]

    plot_array(hist.array(), zmin=zmin, zmax=zmax, xlabel=xlabel, ylabel=ylabel,
               zlabel=zlabel, title=title, axes_limits=axes_limits, **kwargs)


def plot_colormap(result, zmin=None, zmax=None, units=ba.Axes.DEFAULT,
                  xlabel=None, ylabel=None, zlabel=None,
                  title=None, **kwargs):
    """
    Plots intensity data as color map
    :param result: SimulationResult from GISAS/OffSpecSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """

    axes_limits = get_axes_limits(result, units)
    axes_labels = get_axes_labels(result, units)
    xlabel = axes_labels[0] if xlabel is None else xlabel
    ylabel = axes_labels[1] if ylabel is None else ylabel

    plot_array(result.array(), zmin=zmin, zmax=zmax, xlabel=xlabel, ylabel=ylabel,
               zlabel=zlabel, title=title, axes_limits=axes_limits, **kwargs)


def plot_specular_simulation_result(result, ymin=None, ymax=None, units=ba.Axes.DEFAULT,
              xlabel=None, ylabel=None, title=None, **kwargs):
    """
    Plots intensity data for specular simulation result
    :param result: SimulationResult from SpecularSimulation
    :param ymin: minimal y-axis value to show
    :param ymax: maximum y-axis value to show
    :param units: units on the x-axis
    """

    intensity = result.array(units)
    x_axis = result.axis(units)
    ymax = np.amax(intensity) * 2.0 if ymax is None else ymax
    ymin = max(np.amin(intensity) * 0.5, 1e-18 * ymax) if ymin is None else ymin

    xlabel = get_axes_labels(result, units)[0] if xlabel is None else xlabel
    ylabel = "Intensity" if ylabel is None else ylabel

    plt.semilogy(x_axis, intensity, **kwargs)

    plt.ylim([ymin, ymax])

    if xlabel:
        plt.xlabel(xlabel, fontsize=label_fontsize)

    if ylabel:
        plt.ylabel(ylabel, fontsize=label_fontsize)

    if title:
        plt.title(title)


def plot_simulation_result(result, intensity_min=None, intensity_max=None, units=ba.Axes.DEFAULT,
                           xlabel=None, ylabel=None, postpone_show=False, title=None, **kwargs):
    """
    Draws simulation result and (optionally) shows the plot.
    :param result_: SimulationResult object obtained from GISAS/OffSpec/SpecularSimulation
    :param intensity_min: Min value on amplitude's axis or color bar
    :param intensity_max: Max value on amplitude's axis or color bar
    :param units: units for plot axes
    :param postpone_show: postpone showing the plot for later tuning (False by default)
    """
    if len(result.array().shape) == 1:  # 1D data, specular simulation assumed
        plot_specular_simulation_result(result, intensity_min, intensity_max, units, **kwargs)
    else:
        plot_colormap(result, intensity_min, intensity_max, units, xlabel, ylabel,
                      title=title, **kwargs)
    plt.tight_layout()
    if not postpone_show:
        plt.show()


class Plotter:
    def __init__(self, zmin=None, zmax=None, xlabel=None, ylabel=None,
                 units=ba.Axes.DEFAULT, aspect=None):

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
    def __init__(self, zmin=None, zmax=None, xlabel=None, ylabel=None,
                 units=ba.Axes.DEFAULT, aspect=None):
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

        ba.plot_colormap(real_data, title="Experimental data", zmin=zmin, zmax=zmax,
                         units=self._units, xlabel=self._xlabel, ylabel=self._ylabel,
                         zlabel='', aspect=self._aspect)

        self.make_subplot(2)
        ba.plot_colormap(sim_data, title="Simulated data", zmin=zmin, zmax=zmax,
                         units=self._units, xlabel=self._xlabel, ylabel=self._ylabel,
                         zlabel='', aspect=self._aspect)

        self.make_subplot(3)
        ba.plot_colormap(diff, title="Difference", zmin=zmin, zmax=zmax,
                         units=self._units, xlabel=self._xlabel, ylabel=self._ylabel,
                         zlabel='', aspect=self._aspect)

        self.make_subplot(4)
        plt.title('Parameters')
        plt.axis('off')

        iteration_info = fit_objective.iterationInfo()

        plt.text(0.01, 0.85, "Iterations  " + '{:d}'.
                 format(iteration_info.iterationCount()))
        plt.text(0.01, 0.75, "Chi2       " + '{:8.4f}'.format(iteration_info.chi2()))
        index = 0
        params = iteration_info.parameterMap()
        for key in params:
            plt.text(0.01, 0.55 - index * 0.1, '{:30.30s}: {:6.3f}'.format(key, params[key]))
            index = index + 1

        Plotter.plot(self)


class PlotterSpecular(Plotter):
    """
    Draws fit progress. Intended specifically for observing
    specular data fit.
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
        return (token[:length - 2] + '..') if len(token) > length else token

    def plot_table(self, fit_objective):

        iteration_info = fit_objective.iterationInfo()

        trunc_length = 9  # max string field width in the table
        n_digits = 1  # number of decimal digits to print

        n_iterations = iteration_info.iterationCount()  # current number of iterations passed
        rel_dif = fit_objective.relativeDifference().array().max()  # maximum relative difference
        fitted_parameters = iteration_info.parameterMap()

        # creating table content
        labels = ("Parameter", "Value")
        table_data = [["Iteration", '${:d}$'.format(n_iterations)],
                      ["$d_{r, max}$", '${:s}$'.format(self.as_si(rel_dif, n_digits))]]
        for key, value in fitted_parameters.iteritems():
            table_data.append(['{:s}'.format(self.trunc_str(key, trunc_length)),
                               '${:s}$'.format(self.as_si(value, n_digits))])

        # creating table
        axs = plt.subplot(self.gs[1])
        axs.axis('tight')
        axs.axis('off')
        table = plt.table(cellText=table_data, colLabels=labels, cellLoc='center',
                          loc='bottom left', bbox=[0.0, 0.0, 1.0, 1.0])

    def plot_graph(self, fit_objective):
        # retrieving data from fit suite
        real_data = fit_objective.experimentalData()
        sim_data = fit_objective.simulationResult()
        unc_data = fit_objective.uncertaintyData()

        # data values
        sim_values = sim_data.array(self.units)
        real_values = real_data.array(self.units)
        unc_values = None if unc_data is None else unc_data.array(self.units)

        # default font properties dictionary to use
        font = {'family': 'serif',
                'weight': 'normal',
                'size': label_fontsize}

        plt.subplot(self.gs[0])
        plt.semilogy(sim_data.axis(), sim_values, 'b',
                     real_data.axis(), real_values, 'k--')
        if unc_values is not None:
            plt.semilogy(real_data.axis(), real_values - unc_values, 'xkcd:grey', alpha=0.6)
            plt.semilogy(real_data.axis(), real_values + unc_values, 'xkcd:grey', alpha=0.6)
        plt.ylim((0.5 * np.min(real_values), 5 * np.max(real_values)))

        xlabel = get_axes_labels(real_data, self.units)[0]
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
