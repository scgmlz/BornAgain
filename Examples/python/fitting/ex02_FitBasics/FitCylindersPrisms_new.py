"""
Fitting example: 4 parameters fit with simple output
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(params):
    """
    Returns a sample with uncorrelated cylinders and prisms on a substrate.
    """
    cylinder_height = params["cylinder_height"].value
    cylinder_radius = params["cylinder_radius"].value
    prism_length = params["prism_height"].value
    prism_height = params["prism_base_edge"].value

    # defining materials
    m_air = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = ba.FormFactorCylinder(cylinder_radius, cylinder_height)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    prism_ff = ba.FormFactorPrism3(prism_length, prism_height)
    prism = ba.Particle(m_particle, prism_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 0.5)
    particle_layout.addParticle(prism, 0.5)
    interference = ba.InterferenceFunctionNone()
    particle_layout.setInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = ba.Layer(m_air)
    air_layer.addLayout(particle_layout)
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


def run_fitting():
    """
    run fitting
    """
    real_data = ba.IntensityDataIOFactory.readIntensityData(
        'refdata_fitcylinderprisms.int.gz')

    fit_objective = ba.FitObjective()
    fit_objective.addSimulationAndData(get_simulation, real_data.array(), 1.0)

    params = ba.Parameters()
    params.add(ba.Parameter("cylinder_height",
                            4.*nm, ba.AttLimits.lowerLimited(0.01)))
    params.add(ba.Parameter("cylinder_radius",
                            6.*nm, ba.AttLimits.lowerLimited(0.01)))
    params.add(ba.Parameter("prism_height",
                            4.*nm, ba.AttLimits.lowerLimited(0.01)))
    params.add(ba.Parameter("prism_base_edge",
                            12.*nm, ba.AttLimits.lowerLimited(0.01)))

    minimizer = ba.Minimizer()
    result = minimizer.minimize(fit_objective.evaluate, params)

    print(result.toString())


if __name__ == '__main__':
    run_fitting()
