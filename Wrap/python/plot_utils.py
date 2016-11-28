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
from bornagain import deg as deg
from bornagain import IFitObserver as IFitObserver
import bornagain as ba

def standardIntensityPlot(result):
    """
    Plots intensity map.
    """
    import matplotlib
    import sys
    from matplotlib import pyplot as plt

    zmin, zmax = 1.0, result.getMaximum()
    if zmin >= zmax:
        zmax = 1.0
        zmin = 1e-6*zmax

    im = plt.imshow(
        result.getArray(),
        norm=matplotlib.colors.LogNorm(zmin, zmax),
        extent=[result.getXmin()/deg, result.getXmax()/deg,
                result.getYmin()/deg, result.getYmax()/deg],
        aspect='auto',
    )
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.show()


def exoticIntensityPlot(result):
    """
    Plots intensity map.
    """
    import matplotlib
    import sys
    from matplotlib import pyplot as plt
    from matplotlib import rc
    rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
    rc('text', usetex=True)
    im = plt.imshow(
        result.getArray(),
        norm=matplotlib.colors.LogNorm(1.0, result.getMaximum()),
        extent=[result.getXmin()/deg, result.getXmax()/deg,
                result.getYmin()/deg, result.getYmax()/deg],
        aspect='auto',
    )
    cb = plt.colorbar(im)
    cb.set_label(r'Intensity (arb. u.)', size=16)
    plt.xlabel(r'$\phi_f (^{\circ})$', fontsize=16)
    plt.ylabel(r'$\alpha_f (^{\circ})$', fontsize=16)
    plt.title(sys.argv[0])
    plt.show()


def standardIntensitySave(filename, result):
    """
    Saves simulation result, which must be in an intensity map,
    or a dictionary of such maps.
    """
    ba.IntensityDataIOFactory.writeIntensityData(result, filename+".int")

class FlowSeq( list ):
    pass

def yamlDump(filename, data):
    """
    Saves an arbitrary hierarchical data set as YAML-formatted text file.
    """
    import yaml
    global yaml
    from collections import OrderedDict
    class ImprovedDumper(yaml.Dumper):
        pass
    def odict_representer(dumper, data):
        return dumper.represent_mapping(
            yaml.resolver.BaseResolver.DEFAULT_MAPPING_TAG,
            data.items())
    def flowseq_representer(dumper, data):
        return dumper.represent_sequence(
            yaml.resolver.BaseResolver.DEFAULT_SEQUENCE_TAG,
            data,
            flow_style=True )
    ImprovedDumper.add_representer(OrderedDict, odict_representer)
    ImprovedDumper.add_representer(FlowSeq, flowseq_representer)
    with open(filename+".yaml", "w") as f:
        f.write(yaml.dump(data, None, ImprovedDumper,
                          allow_unicode=True, encoding='utf-8',
                          default_flow_style=False, indent=4, width=70).decode('utf-8'))


def getFilenameOrPlotflag():
    """
    Used at beginning of main program, this function returns a filename or a flag
    obtained from the command-line argument, or prints a help message and exit.
    """
    import sys
    # if len(sys.argv)<=1:
    #     print("Usage:")
    #     print("  " + sys.argv[0] + " -p                           # to plot results")
    #     print("  " + sys.argv[0] + " <filename without extension> # to save results")
    #     sys.exit()
    # return sys.argv[1]
    if len(sys.argv)<=1:
        return '-p'
    else:
        return sys.argv[1]


def simulateThenPlotOrSave(
        simulate, plot=standardIntensityPlot, save=standardIntensitySave):
    """
    Runs a simulation. Then plots the function or saves the result,
    depending on the command-line argument argv[1].
    """
    arg = getFilenameOrPlotflag()
    result = simulate()
    if arg == '-p':
        plot(result)
        return
    # save result
    if type(result) is dict:
        for name, subresult in result.items(): # inefficient under Py2, but good enough
            save(arg+"."+str(name), subresult)
    else:
        save(arg+".ref", result)


def plot_intensity_data(intensity_data, plot=standardIntensityPlot, save=standardIntensitySave):
    """
    Plots intensity data (if no command line arguments are provided).
    If there is an additional command line arguments, it must be a file name, and
    the data are silently saved to that file. This is used in our persistence tests.
    """
    import sys
    if len(sys.argv) <= 1:
        plot(intensity_data)
    else:
        filename = sys.argv[1]
        # save result
        if type(intensity_data) is dict:
            for name, subresult in intensity_data.items():  # inefficient under Py2, but good enough
                save(filename+"."+str(name), subresult)
        else:
            save(filename+".ref", intensity_data)


class DefaultFitObserver(IFitObserver):
    """
    Draws fit progress every nth iteration. This class has to be attached to
    FitSuite via attachObserver method.
    FitSuite kernel will call DrawObserver's update() method every n'th iteration.
    It is up to the user what to do here.
    """

    def __init__(self, draw_every_nth=10):
        IFitObserver.__init__(self, draw_every_nth)

        import matplotlib
        from matplotlib import pyplot as plt
        global matplotlib, plt

        self.fig = plt.figure(figsize=(10.25, 7.69))
        self.fig.canvas.draw()
        plt.ion()

    def plot(self, data, title, nplot, min=1, max=1e6):
        plt.subplot(2, 2, nplot)
        plt.subplots_adjust(wspace=0.2, hspace=0.2)
        im = plt.imshow(data.getArray(),
                        norm=matplotlib.colors.LogNorm(min, max),
                        extent=[data.getXmin(), data.getXmax(), data.getYmin(), data.getYmax()],
                        aspect='auto')
        plt.colorbar(im)
        plt.title(title)

    def update(self, fit_suite):
        self.fig.clf()
        real_data = fit_suite.getRealData()
        self.plot(real_data, "\"Real\" data", nplot=1, min=1.0, max=real_data.getMaximum())
        self.plot(fit_suite.getSimulationData(), "Simulated data", nplot=2, min=1.0, max=real_data.getMaximum())
        self.plot(fit_suite.getChiSquaredMap(), "Chi2 map", nplot=3, min=0.001, max=10.0)

        plt.subplot(2, 2, 4)
        plt.title('Parameters')
        plt.axis('off')
        plt.text(0.01, 0.85, "Iterations  " + '{:d}     {:s}'.
                 format(fit_suite.numberOfIterations(), fit_suite.minimizer().minimizerName()))
        plt.text(0.01, 0.75, "Chi2       " + '{:8.4f}'.format(fit_suite.getChi2()))
        for index, fitPar in enumerate(fit_suite.fitParameters()):
            plt.text(0.01, 0.55 - index*0.1,  '{:30.30s}: {:6.3f}'.format(fitPar.name(), fitPar.value()))

        plt.draw()
        plt.pause(0.01)

        if fit_suite.isLastIteration():
            plt.ioff()
