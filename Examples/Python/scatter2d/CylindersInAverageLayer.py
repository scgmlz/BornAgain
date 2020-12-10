"""
Square lattice of cylinders inside finite layer with usage of average material
"""
import numpy, sys
import bornagain as ba
from bornagain import angstrom, deg, micrometer, nm, nm2, kvector_t


def get_sample(cyl_height=5*nm):
    """
    Returns a sample with cylinders on a substrate.
    """
    # defining materials
    m_vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
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
    interference = ba.InterferenceFunction2DLattice(
        ba.SquareLattice2D(15*nm, 0*deg))
    pdf = ba.FTDecayFunction2DCauchy(300*nm, 300*nm, 0)
    interference.setDecayFunction(pdf)
    particle_layout.setInterferenceFunction(interference)

    vacuum_layer = ba.Layer(m_vacuum)
    intermediate_layer = ba.Layer(m_layer, 5*nm)
    intermediate_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    multi_layer.addLayer(intermediate_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    beam = ba.Beam(1.0, 0.1*nm, ba.Direction(0.2*deg, 0.0*deg))
    nx = 100
    ny = 100
    detector = ba.SphericalDetector(nx, -2.0*deg, 2.0*deg, ny, 0.0*deg, 2.0*deg)

    simulation = ba.GISASSimulation(beam, get_sample(), detector)
    simulation.getOptions().setUseAvgMaterials(True)
    return simulation


def run_simulation():
    simulation = get_simulation()
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
