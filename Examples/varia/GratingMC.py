#!/usr/bin/env python3
"""
Simulation of grating using very long boxes and 1D lattice.
Monte-carlo integration is used to get rid of
large-particle form factor oscillations.
"""
import bornagain as ba
from bornagain import deg, angstrom, nm, micrometer
import ba_plot
from matplotlib import pyplot as plt


def get_sample(lattice_rotation_angle=0*deg):
    """
    Returns a sample with a grating on a substrate.
    lattice_rotation_angle = 0 - beam parallel to grating lines
    lattice_rotation_angle = 90*deg - beam perpendicular to grating lines
    """
    # defining materials
    m_vacuum = ba.HomogeneousMaterial("Vacuum", 0, 0)
    m_si = ba.HomogeneousMaterial("Si", 5.78164736e-6, 1.02294578e-7)

    box_length, box_width, box_height = 50*micrometer, 70*nm, 50*nm
    lattice_length = 150*nm

    # collection of particles
    interference = ba.InterferenceFunction1DLattice(
        lattice_length, 90*deg - lattice_rotation_angle)

    pdf = ba.FTDecayFunction1DGauss(450)
    interference.setDecayFunction(pdf)

    box_ff = ba.FormFactorLongBoxLorentz(box_length, box_width, box_height)
    box = ba.Particle(m_si, box_ff)

    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(box, 1, ba.kvector_t(0, 0, 0),
                                ba.RotationZ(lattice_rotation_angle))
    particle_layout.setInterferenceFunction(interference)

    # assembling the sample
    vacuum_layer = ba.Layer(m_vacuum)
    vacuum_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_si)

    roughness = ba.LayerRoughness()
    roughness.setSigma(5*nm)
    roughness.setHurstParameter(0.5)
    roughness.setLatteralCorrLength(10*nm)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    multi_layer.addLayerWithTopRoughness(substrate_layer, roughness)
    return multi_layer


def get_simulation(sample):
    """
    Create and return GISAXS simulation with beam and detector defined
    """
    beam = ba.Beam(1e8, 1.34*angstrom, ba.Direction(0.4*deg, 0*deg))
    det = ba.SphericalDetector(200, -0.5*deg, 0.5*deg, 200, 0*deg, 0.6*deg)
    simulation = ba.GISASSimulation(beam, sample, det)
    simulation.getOptions().setMonteCarloIntegration(True, 100)
    return simulation


def run_simulation():
    """
    Runs simulation and returns intensity map.
    """
    sample = get_sample()
    simulation = get_simulation(sample)
    if not "__no_terminal__" in globals():
        simulation.setTerminalProgressMonitor()
    simulation.runSimulation()
    return simulation.result()


def simulate_and_plot():
    interactive = True
    result = run_simulation().histogram2d()
    ba_plot.plot_histogram(result)

    peaks = ba.FindPeaks(result, 2, "nomarkov", 0.001)
    xpeaks = [peak[0] for peak in peaks]
    ypeaks = [peak[1] for peak in peaks]
    print(peaks)
    plt.plot(xpeaks,
             ypeaks,
             linestyle='None',
             marker='x',
             color='white',
             markersize=10)
    plt.show()


if __name__ == '__main__':
    simulate_and_plot()
