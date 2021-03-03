#!/usr/bin/env python3
"""
Simulation of grating using very long boxes and 1D lattice.
Monte-carlo integration is used to get rid of
large-particle form factor oscillations.
"""
import numpy, sys
import bornagain as ba
from bornagain import deg, micrometer, nm, nm2, kvector_t


def get_sample(lattice_rotation_angle=0.0*deg):
    """
    Returns a sample with a grating on a substrate.
    lattice_rotation_angle = 0 - beam parallel to grating lines
    lattice_rotation_angle = 90*deg - beam perpendicular to grating lines
    """
    # defining materials
    m_vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    m_si = ba.HomogeneousMaterial("Si", 5.78164736e-6, 1.02294578e-7)

    box_length, box_width, box_height = 50*micrometer, 70*nm, 50*nm
    lattice_length = 150*nm

    # collection of particles
    interference = ba.InterferenceFunction1DLattice(
        lattice_length, 90.0*deg - lattice_rotation_angle)

    pdf = ba.FTDecayFunction1DGauss(450.0)
    interference.setDecayFunction(pdf)

    box_ff = ba.FormFactorLongBoxLorentz(box_length, box_width, box_height)
    box = ba.Particle(m_si, box_ff)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(box, 1.0, ba.kvector_t(0.0, 0.0, 0.0),
                                ba.RotationZ(lattice_rotation_angle))
    particle_layout.setInterferenceFunction(interference)

    # assembling the sample
    vacuum_layer = ba.Layer(m_vacuum)
    vacuum_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_si)

    roughness = ba.LayerRoughness()
    roughness.setSigma(5.0*nm)
    roughness.setHurstParameter(0.5)
    roughness.setLatteralCorrLength(10.0*nm)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    multi_layer.addLayerWithTopRoughness(substrate_layer, roughness)
    return multi_layer


def get_simulation(sample):
    beam = ba.Beam(100000000.0, 0.134*nm, ba.Direction(0.4*deg, 0*deg))
    detector = ba.SphericalDetector(200, -0.5*deg, 0.5*deg, 200, 0*deg, 0.6*deg)
    simulation = ba.GISASSimulation(beam, sample, detector)
    simulation.getOptions().setMonteCarloIntegration(True, 100)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
