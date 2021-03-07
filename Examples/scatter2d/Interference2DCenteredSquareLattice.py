#!/usr/bin/env python3
"""
2D lattice with disorder, centered square lattice
"""
import bornagain as ba
from bornagain import deg, nm, kvector_t


def get_sample():
    """
    Returns a sample with cylinders on a substrate,
    forming a 2D centered square lattice
    """

    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0, 0)

    # Define form factors
    ff_1 = ba.FormFactorCylinder(3*nm, 3*nm)
    ff_2 = ba.FormFactorCylinder(3*nm, 3*nm)

    # Define particles
    particle_1 = ba.Particle(material_Particle, ff_1)
    particle_2 = ba.Particle(material_Particle, ff_2)
    particle_2_position = kvector_t(12.5*nm, 12.5*nm, 0)
    particle_2.setPosition(particle_2_position)

    # Define composition of particles at specific positions
    particle_3 = ba.ParticleComposition()
    particle_3.addParticle(particle_1)
    particle_3.addParticle(particle_2)

    # Define 2D lattices
    lattice = ba.BasicLattice2D(25*nm, 25*nm, 90*deg, 0)

    # Define interference functions
    iff = ba.InterferenceFunction2DLattice(lattice)
    iff_pdf = ba.FTDecayFunction2DCauchy(48*nm, 16*nm, 0)
    iff.setDecayFunction(iff_pdf)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle_3, 1)
    layout.setInterferenceFunction(iff)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.0016)

    # Define layers
    layer_1 = ba.Layer(material_Vacuum)
    layer_1.addLayout(layout)
    layer_2 = ba.Layer(material_Substrate)

    # Define sample
    sample = ba.MultiLayer()
    sample.addLayer(layer_1)
    sample.addLayer(layer_2)

    return sample


def get_simulation(sample):
    beam = ba.Beam(1, 0.1*nm, ba.Direction(0.2*deg, 0))
    detector = ba.SphericalDetector(200, -2*deg, 2*deg, 200, 0, 2*deg)
    simulation = ba.GISASSimulation(beam, sample, detector)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
