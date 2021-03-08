#!/usr/bin/env python3
"""
Cylindrical mesocrystal on a substrate
"""
import bornagain as ba
from bornagain import deg, nm, kvector_t


def get_sample():
    """
    Returns a sample with a cylindrically shaped mesocrystal on a substrate.
    """

    # Define materials
    material_Particle = ba.HomogeneousMaterial("Particle", 0.0006, 2e-08)
    material_Substrate = ba.HomogeneousMaterial("Substrate", 6e-06, 2e-08)
    material_Vacuum = ba.HomogeneousMaterial("Vacuum", 0, 0)

    # Define form factors
    ff_1 = ba.FormFactorFullSphere(2*nm)
    ff_2 = ba.FormFactorCylinder(20*nm, 50*nm)

    # Define particles
    particle_1 = ba.Particle(material_Particle, ff_1)

    # Define 3D lattices
    lattice = ba.Lattice3D(ba.kvector_t(5*nm, 0, 0),
                           ba.kvector_t(0, 5*nm, 0),
                           ba.kvector_t(0, 0, 5*nm))

    # Define crystals
    crystal = ba.Crystal(particle_1, lattice)

    # Define mesocrystals
    particle_2 = ba.MesoCrystal(crystal, ff_2)

    # Define particle layouts
    layout = ba.ParticleLayout()
    layout.addParticle(particle_2, 1)
    layout.setWeight(1)
    layout.setTotalParticleSurfaceDensity(0.01)

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
