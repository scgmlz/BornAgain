"""
Square lattice of half spheres on substrate with usage of average material
and slicing
"""
import bornagain as ba
from bornagain import deg, angstrom, nm

sphere_radius = 5*nm
n_slices = 10


def get_sample():
    """
    Returns a sample with cylinders on a substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_layer = ba.HomogeneousMaterial("Layer", 3e-6, 2e-8)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 3e-5, 2e-8)

    # cylindrical particle
    half_sphere_ff = ba.FormFactorTruncatedSphere(sphere_radius, sphere_radius, 0)
    half_sphere = ba.Particle(m_particle, half_sphere_ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(half_sphere)

    # interference function
    interference = ba.InterferenceFunction2DLattice.createSquare(10*nm, 0*deg)
    pdf = ba.FTDecayFunction2DCauchy(100*nm, 100*nm, 0)
    interference.setDecayFunction(pdf)
    particle_layout.setInterferenceFunction(interference)

    air_layer = ba.Layer(m_ambience)
    air_layer.addLayout(particle_layout)
    air_layer.setNumberOfSlices(n_slices)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, -2.0*deg, 2.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)
    simulation.getOptions().setUseAvgMaterials(True)
    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    sample = get_sample()
    simulation = get_simulation()
    simulation.setSample(sample)
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
