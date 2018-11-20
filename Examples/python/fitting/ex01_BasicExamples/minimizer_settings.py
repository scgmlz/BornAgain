"""
Fitting example: running same fit using various minimizer and their settings.
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(params):
    """
    Returns a sample with uncorrelated cylinders and prisms on a substrate.
    """
    cylinder_height = params["cylinder_height"]
    cylinder_radius = params["cylinder_radius"]
    prism_height = params["prism_height"]
    prism_base_edge = params["prism_base_edge"]

    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(cylinder_radius, cylinder_height)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    prism_ff = ba.FormFactorPrism3(prism_base_edge, prism_height)
    prism = ba.Particle(m_particle, prism_ff)
    layout = ba.ParticleLayout()
    layout.addParticle(cylinder, 0.5)
    layout.addParticle(prism, 0.5)
    interference = ba.InterferenceFunctionNone()
    layout.setInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = ba.Layer(m_air)
    air_layer.addLayout(layout)
    substrate_layer = ba.Layer(m_substrate, 0)
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(params):
    """
    Returns a GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setBeamIntensity(1e+08)
    simulation.setSample(get_sample(params))
    return simulation


def create_real_data():
    """
    Generating "real" data by adding noise to the simulated data.
    This function has been used once to generate refdata_fitcylinderprisms.int
    located in same directory.
    """
    # creating sample with set of parameters we will later try to find during the fit

    params = {'cylinder_height': 5.0*nm, 'cylinder_radius': 5.0*nm,
              'prism_height': 5.0*nm, 'prism_base_edge': 5.0*nm}

    simulation = get_simulation(params)
    simulation.runSimulation()

    return simulation.result().array()


def run_fitting():
    """
    main function to run fitting
    """

    real_data = create_real_data()

    # prints info about available minimizers
    print(ba.MinimizerFactory().catalogueToString())

    # prints detailed info about available minimizers and their options
    print(ba.MinimizerFactory().catalogueDetailsToString())

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(get_simulation, real_data, 1.0)
    fit_objective.initPrint(10)

    params = ba.Parameters()
    params.add("cylinder_height", 4.*nm, min=0.01)
    params.add("cylinder_radius", 6.*nm, min=0.01)
    params.add("prism_height", 4.*nm, min=0.01)
    params.add("prism_base_edge", 12.*nm, min=0.01)

    minimizer = ba.Minimizer()

    # Uncomment one of the line below to adjust minimizer settings

    """
    Setting Minuit2 minimizer with Migrad algorithm, limiting number of iterations.
    Minimization will try to respect MaxFunctionCalls value.
    """
    # minimizer.setMinimizer("Minuit2", "Migrad", "MaxFunctionCalls=50")

    """
    Setting two options at once.
    Strategy=2 promises more accurate fit.    
    """
    # minimizer.setMinimizer("Minuit2", "Migrad", "MaxFunctionCalls=500;Strategy=2")

    """
    Setting Minuit2 minimizer with Fumili algorithm.
    """
    # minimizer.setMinimizer("Minuit2", "Fumili")

    """
    Setting Levenberg-Marquardt algorithm.
    """
    # minimizer.setMinimizer("GSLLMA")

    result = minimizer.minimize(fit_objective.evaluate_residuals, params)

    fit_objective.finalize(result)

    print("Fitting completed.")
    print("chi2:", result.minValue())
    for fitPar in result.parameters():
        print(fitPar.name(), fitPar.value, fitPar.error)


if __name__ == '__main__':
    run_fitting()
