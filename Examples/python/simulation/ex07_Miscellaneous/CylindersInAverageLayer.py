"""
Square lattice of cylinders inside finite layer with usage of average material
"""
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample(cyl_height=5*nm):
    """
    Returns a sample with cylinders on a substrate.
    """
    # defining materials
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_layer = ba.HomogeneousMaterial("Layer", 3e-6, 2e-8)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 3e-5, 2e-8)

    # cylindrical particle
    cylinder_ff = ba.FormFactorCylinder(5*nm, cyl_height)
    cylinder = ba.Particle(m_particle, cylinder_ff)
    position = ba.kvector_t(0.0, 0.0, -cyl_height)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(cylinder, 1.0, position)

    # interference function
    interference = ba.InterferenceFunction2DLattice.createSquare(15*nm, 0*deg)
    pdf = ba.FTDecayFunction2DCauchy(300*nm, 300*nm, 0)
    interference.setDecayFunction(pdf)
    particle_layout.setInterferenceFunction(interference)

    air_layer = ba.Layer(m_ambience)
    intermediate_layer = ba.Layer(m_layer, 5*nm)
    intermediate_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(intermediate_layer)
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
    simulation = get_simulation()
    simulation.setSample(get_sample())
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
