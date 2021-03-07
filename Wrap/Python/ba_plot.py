#  **************************************************************************  #
"""
#   BornAgain: simulate and fit reflection and scattering
#
#   @file      Wrap/Python/ba_plot.py
#   @brief     Python extensions of the SWIG-generated Python module bornagain.
#
#   @homepage  http://apps.jcns.fz-juelich.de/BornAgain
#   @license   GNU General Public License v3 or higher (see COPYING)
#   @copyright Forschungszentrum Juelich GmbH 2016
#   @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
"""
#  **************************************************************************  #

import os
import bornagain as ba
try:  # workaround for build servers
    import numpy as np
    from matplotlib import pyplot as plt
    from matplotlib import gridspec, colors
except Exception as e:
    print("In ba_plot.py: {:s}".format(str(e)))

label_fontsize = 16

# default values from environment variables
CMAP = "CMAP" in os.environ and os.environ["CMAP"] or 'inferno'
NOSHOW = "NOSHOW" in os.environ


def get_axes_limits(result, units):
    """
    Returns axes range as expected by pyplot.imshow.
    :param result: SimulationResult object from a Simulation
    :param units: units to use
    :return: axes ranges as a flat list
    """
    axis_infos = result.axisInfo(units)
    limits = [[axis_infos[i].m_min, axis_infos[i].m_max]
              for i in range(len(axis_infos))]
    flat_limits = [v for sublist in limits for v in sublist]

    return flat_limits


def translate_axis_label(label):
    """
    Formats an axis label into a LaTeX representation
    :param label: text representation of the axis label
    :return: LaTeX representation
    """
    label_dict = {
        'X [nbins]': r'$X \; $(bins)',
        'X [mm]': r'$X \; $(mm)',
        'Y [nbins]': r'$Y \; $(bins)',
        'Y [mm]': r'$Y \; $(mm)',
        'phi_f [rad]': r'$\varphi_f \; $(rad)',
        'phi_f [deg]': r'$\varphi_f \; $(deg)',
        'alpha_i [rad]': r'$\alpha_i \; $(rad)',
        'alpha_i [deg]': r'$\alpha_i \; $(deg)',
        'alpha_f [rad]': r'$\alpha_f \; $(rad)',
        'alpha_f [deg]': r'$\alpha_f \; $(deg)',
        'Qx [1/nm]': r'$Q_x \; $(nm$^{-1}$)',
        'Qy [1/nm]': r'$Q_y \; $(nm$^{-1}$)',
        'Qz [1/nm]': r'$Q_z \; $(nm$^{-1}$)',
        'Q [1/nm]': r'$Q \; $(nm$^{-1}$)',
        'Position [nm]': r'$Position \; $(nm)'
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
    labels = [
        translate_axis_label(axis_infos[i].m_name)
        for i in range(len(axis_infos))
    ]

    return labels


def plot_array(array, axes_limits=None, **kwargs):
    """
    Plots numpy array as a colormap in log scale.
    """

    zmax = kwargs.pop('intensity_max', np.amax(array))
    zmin = kwargs.pop('intensity_min', 1e-6*zmax)

    if zmin == zmax == 0.0:
        norm = colors.Normalize(0, 1)
    else:
        norm = colors.LogNorm(zmin, zmax)

    xlabel = kwargs.pop('xlabel', None)
    ylabel = kwargs.pop('ylabel', None)
    zlabel = kwargs.pop('zlabel', "Intensity")
    title = kwargs.pop('title', None)
    aspect = kwargs.pop('aspect', 'auto')
    cmap = kwargs.pop('cmap', CMAP)

    im = plt.imshow(array, cmap=cmap, norm=norm, aspect=aspect, extent=axes_limits, **kwargs)
    cb = plt.colorbar(im, pad=0.025)

    if xlabel:
        plt.xlabel(xlabel, fontsize=label_fontsize)
    if ylabel:
        plt.ylabel(ylabel, fontsize=label_fontsize)
    if zlabel:
        cb.set_label(zlabel, size=label_fontsize)

    if title:
        plt.title(title)


def plot_histogram(hist, **kwargs):
    """
    Plots intensity data as color map
    :param intensity: Histogram2D object obtained from GISASSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """

    if not 'xlabel' in kwargs:
        kwargs['xlabel'] = translate_axis_label(hist.xAxis().getName())
    if not 'ylabel' in kwargs:
        kwargs['ylabel'] = translate_axis_label(hist.yAxis().getName())

    axes_limits = [
        hist.getXmin(),
        hist.getXmax(),
        hist.getYmin(),
        hist.getYmax()
    ]

    title = kwargs.pop('title', None)

    plot_array(hist.array(), title=title, axes_limits=axes_limits, **kwargs)


def plot_colormap(result, **kwargs):
    """
    Plots intensity data as color map
    :param result: SimulationResult from GISAS/OffSpecularSimulation
    :param zmin: Min value on amplitude's color bar
    :param zmax: Max value on amplitude's color bar
    """

    units = kwargs.pop('units', ba.Axes.DEFAULT)
    axes_limits = get_axes_limits(result, units)
    axes_labels = get_axes_labels(result, units)

    if not 'xlabel' in kwargs:
        kwargs['xlabel'] = axes_labels[0]
    if not 'ylabel' in kwargs:
        kwargs['ylabel'] = axes_labels[1]

    plot_array(result.array(), axes_limits=axes_limits, **kwargs)


def plot_specular_simulation_result(result, **kwargs):
    """
    Plots intensity data for specular simulation result
    :param result: SimulationResult from SpecularSimulation
    :param ymin: minimal y-axis value to show
    :param ymax: maximum y-axis value to show
    :param units: units on the x-axis
    """

    units = kwargs.pop('units', ba.Axes.DEFAULT)
    intensity = result.array(units)
    x_axis = result.axis(units)

    ymax = kwargs.pop('intensity_max', np.amax(np.amax(intensity)*2))
    ymin = kwargs.pop('intensity_min', max(np.amin(intensity)*0.5, 1e-18*ymax))

    xlabel = kwargs.pop('xlabel', get_axes_labels(result, units)[0])
    ylabel = kwargs.pop('ylabel', "Intensity")
    title = kwargs.pop('title', None)

    plt.semilogy(x_axis, intensity, **kwargs)

    plt.ylim([ymin, ymax])

    if xlabel:
        plt.xlabel(xlabel, fontsize=label_fontsize)
    if ylabel:
        plt.ylabel(ylabel, fontsize=label_fontsize)

    if title:
        plt.title(title)


def plot_simulation_result(result, **kwargs):
    """
    Draws simulation result and (optionally) shows the plot.
    :param result_: SimulationResult object obtained from GISAS/OffSpecular/SpecularSimulation
    :param intensity_min: Min value on amplitude's axis or color bar
    :param intensity_max: Max value on amplitude's axis or color bar
    :param units: units for plot axes
    :param noshow: don't plot to interactive device
    """
    noshow = kwargs.pop('noshow', NOSHOW)

    if len(result.array().shape) == 1:  # 1D data, specular simulation assumed
        plot_specular_simulation_result(result, **kwargs)
    else:
        plot_colormap(result, **kwargs)
    plt.tight_layout()
    if not (noshow):
        plt.show()
    else:
        print("plot_simulation_result: noshow")

def run_and_plot(simulation, **kwargs):
    simulation.runSimulation()
    plot_simulation_result(simulation.result(), **kwargs)
