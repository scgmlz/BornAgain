# 2D lattice with different disorder (IsGISAXS example #6), sum of rotated lattices
import numpy
import bornagain as ba
from bornagain import deg, angstrom, nm


def get_sample():
    """
    Returns a sample with cylinders on a substrate,
    forming a 2D lattice with different disorder rotated lattice
    """
    m_ambience = ba.HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    air_layer = ba.Layer(m_ambience)
    substrate_layer = ba.Layer(m_substrate)

    p_interference_function = \
        ba.InterferenceFunction2DLattice.createSquare(25.0*nm, 0)
    pdf = ba.FTDecayFunction2DCauchy(300.0*nm/2.0/numpy.pi,
                                     100.0*nm/2.0/numpy.pi, 0)
    p_interference_function.setDecayFunction(pdf)

    particle_layout = ba.ParticleLayout()
    ff_cyl = ba.FormFactorCylinder(3.0*nm, 3.0*nm)
    position = ba.kvector_t(0.0, 0.0, 0.0)
    cylinder = ba.Particle(m_particle, ff_cyl.clone())
    cylinder.setPosition(position)
    particle_layout.addParticle(cylinder, 1.0)
    particle_layout.setInterferenceFunction(p_interference_function)

    air_layer.addLayout(particle_layout)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation():
    """
    Returns a GISAXS simulation with beam and detector defined.
    Assigns additional distribution to lattice rotation angle.
    """
    simulation = ba.GISASSimulation()
    simulation.setDetectorParameters(100, 0.0*deg, 2.0*deg,
                                     100, 0.0*deg, 2.0*deg)
    simulation.setBeamParameters(1.0*angstrom, 0.2*deg, 0.0*deg)

    simulation.setSample(get_sample())

    xi_min = 0.0*deg
    xi_max = 240.0*deg
    xi_distr = ba.DistributionGate(xi_min, xi_max)

    # assigns distribution with 3 equidistant points to lattice rotation angle
    simulation.addParameterDistribution("*/SquareLattice/Xi", xi_distr, 3)

    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """

    simulation = get_simulation()
    simulation.runSimulation()
    return simulation.result()


if __name__ == '__main__':
    result = run_simulation()
    ba.plot_simulation_result(result, cmap='jet', aspect='auto')
