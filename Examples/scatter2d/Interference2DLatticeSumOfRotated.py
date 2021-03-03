#!/usr/bin/env python3
import bornagain as ba
from bornagain import deg, nm


def get_sample():
    """
    Returns a sample with cylinders on a substrate,
    forming a 2D lattice with different disorder rotated lattice
    """
    m_vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    vacuum_layer = ba.Layer(m_vacuum)
    substrate_layer = ba.Layer(m_substrate)

    p_interference_function = \
        ba.InterferenceFunction2DLattice(ba.SquareLattice2D(25.0*nm, 0))
    pdf = ba.FTDecayFunction2DCauchy(48*nm, 16*nm, 0)
    p_interference_function.setDecayFunction(pdf)

    particle_layout = ba.ParticleLayout()
    ff = ba.FormFactorCylinder(3.0*nm, 3.0*nm)
    position = ba.kvector_t(0.0, 0.0, 0.0)
    cylinder = ba.Particle(m_particle, ff.clone())
    cylinder.setPosition(position)
    particle_layout.addParticle(cylinder, 1.0)
    particle_layout.setInterferenceFunction(p_interference_function)

    vacuum_layer.addLayout(particle_layout)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(sample):
    beam = ba.Beam(1.0, 0.1*nm, ba.Direction(0.2*deg, 0*deg))
    detector = ba.SphericalDetector(100, 2*deg, 1*deg, 1*deg)
    simulation = ba.GISASSimulation(beam, sample, detector)
    distr_1 = ba.DistributionGate(0*deg, 240*deg)
    simulation.addParameterDistribution("*/SquareLattice2D/Xi", distr_1, 3, 0.0)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
