"""
Minimal working fit examples: finds radius of sphere in Born approximation.
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_simulation(params):
    """
    Returns GISAS simulation for given set of parameters.
    """
    radius = params["radius"]

    sphere = ba.Particle(ba.HomogeneousMaterial("Particle", 6e-4, 2e-8),
                         ba.FormFactorFullSphere(radius))

    layer = ba.Layer(ba.HomogeneousMaterial("Vacuum", 0.0, 0.0))
    layer.addLayout(ba.ParticleLayout(sphere))
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(layer)

    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -1.0*deg, 1.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.setSample(multi_layer)

    return simulation


def real_data():
    """
    Generating "experimental" data by running simulation with default parameters.
    """
    simulation = get_simulation({'radius': 5.0*nm})
    simulation.runSimulation()
    return simulation.result().array()


def run_fitting():
    """
    Setups and runs fit.
    """
    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(get_simulation, real_data())
    fit_objective.initPrint(10)

    params = ba.Parameters()
    params.add("radius", 4.*nm, min=0.01)

    minimizer = ba.Minimizer()
    result = minimizer.minimize(fit_objective.evaluate, params)
    fit_objective.finalize(result)


if __name__ == '__main__':
    run_fitting()
