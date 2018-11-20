"""
Fitting example: fit along slices
"""

from matplotlib import pyplot as plt
import bornagain as ba
from bornagain import deg, angstrom, nm

phi_slice_value = 0.0  # position of vertical slice in deg
alpha_slice_value = 0.2  # position of horizontal slice in deg


def get_sample(params):
    """
    Returns a sample with uncorrelated cylinders on a substrate.
    """
    radius = params["radius"]
    height = params["height"]

    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    cylinder_ff = ba.FormFactorCylinder(radius, height)
    cylinder = ba.Particle(m_particle, cylinder_ff)

    layout = ba.ParticleLayout()
    layout.addParticle(cylinder)

    air_layer = ba.Layer(m_air)
    air_layer.addLayout(layout)

    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(params, add_masks=True):
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg, 100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    simulation.setSample(get_sample(params))
    if add_masks:
        """
        At this point we mask all the detector and then unmask two areas
        corresponding to the vertical and horizontal lines. This will make
        simulation/fitting to be performed along slices only.
        """
        simulation.maskAll()
        simulation.addMask(ba.HorizontalLine(alpha_slice_value*deg), False)
        simulation.addMask(ba.VerticalLine(phi_slice_value*deg), False)
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    """
    # initial values which we will have to find later during the fit
    params = {'radius': 5.0*nm, 'height': 10.0*nm}

    # retrieving simulated data in the form of numpy array
    simulation = get_simulation(params, add_masks=False)
    simulation.setBackground(ba.PoissonNoiseBackground())
    simulation.runSimulation()

    return simulation.result().array()


class PlotObserver:
    """
    Draws fit progress every nth iteration. Here we plot slices along real
    and simulated images to see fit progress.
    """

    def __init__(self):
        self.fig = plt.figure(figsize=(10.25, 7.69))
        self.fig.canvas.draw()

    def __call__(self, fit_objective):
        self.update(fit_objective)

    @staticmethod
    def plot_real_data(data):
        """
        Plot experimental data as colormap with horizontal/vertical lines
        representing slices on top.
        """
        plt.subplots_adjust(wspace=0.2, hspace=0.2)
        ba.plot_histogram(data, title="Experimental data")
        # line representing vertical slice
        plt.plot([phi_slice_value, phi_slice_value],
                 [data.getYmin(), data.getYmax()],
                 color='gray', linestyle='-', linewidth=1)
        # line representing horizontal slice
        plt.plot([data.getXmin(), data.getXmax()],
                 [alpha_slice_value, alpha_slice_value],
                 color='gray', linestyle='-', linewidth=1)

    @staticmethod
    def plot_slices(slices, title):
        """
        Plots vertical and horizontal projections.
        """
        plt.subplots_adjust(wspace=0.2, hspace=0.3)
        for label, slice in slices:
            plt.semilogy(slice.getBinCenters(),
                         slice.getBinValues(), label=label)
            plt.xlim(slice.getXmin(), slice.getXmax())
            plt.ylim(1.0, slice.getMaximum()*10.0)
        plt.legend(loc='upper right')
        plt.title(title)

    @staticmethod
    def display_fit_parameters(fit_objective):
        """
        Displays fit parameters, chi and iteration number.
        """
        plt.title('Parameters')
        plt.axis('off')

        iteration_info = fit_objective.iterationInfo()

        plt.text(0.01, 0.85, "Iterations  " + '{:d}'.
                 format(iteration_info.iterationCount()))
        plt.text(0.01, 0.75, "Chi2       " + '{:8.4f}'.format(iteration_info.chi2()))
        for index, params in enumerate(iteration_info.parameters()):
            plt.text(0.01, 0.55 - index * 0.1,
                     '{:30.30s}: {:6.3f}'.format(params.name(), params.value))


        plt.tight_layout()
        plt.draw()
        plt.pause(0.01)

    def update(self, fit_objective):
        """
        Callback to access fit_objective on every n'th iteration.
        """
        self.fig.clf()

        real_data = fit_objective.experimentalData().histogram2d()
        simul_data = fit_objective.simulationResult().histogram2d()

        # plot real data
        plt.subplot(2, 2, 1)
        self.plot_real_data(real_data)

        # horizontal slices
        slices = [
            ("real", real_data.projectionX(alpha_slice_value)),
            ("simul", simul_data.projectionX(alpha_slice_value))
            ]
        title = ("Horizontal slice at alpha =" + '{:3.1f}'.format(alpha_slice_value))
        plt.subplot(2, 2, 2)
        self.plot_slices(slices, title)

        # vertical slices
        slices = [
            ("real", real_data.projectionY(phi_slice_value)),
            ("simul", simul_data.projectionY(phi_slice_value))
            ]
        title = "Vertical slice at phi =" + '{:3.1f}'.format(phi_slice_value)
        plt.subplot(2, 2, 3)
        self.plot_slices(slices, title)

        # display fit parameters
        plt.subplot(2, 2, 4)
        self.display_fit_parameters(fit_objective)


def run_fitting():
    """
    main function to run fitting
    """

    real_data = create_real_data()

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(get_simulation, real_data, 1.0)
    fit_objective.initPrint(10)

    # creating custom observer which will draw fit progress
    plotter = PlotObserver()
    fit_objective.initPlot(10, plotter)

    params = ba.Parameters()
    params.add("radius", 6.*nm, min=4.0, max=8.0)
    params.add("height", 9.*nm, min=8.0, max=12.0)

    minimizer = ba.Minimizer()
    result = minimizer.minimize(fit_objective.evaluate, params)
    fit_objective.finalize(result)


if __name__ == '__main__':
    run_fitting()
    plt.show()
