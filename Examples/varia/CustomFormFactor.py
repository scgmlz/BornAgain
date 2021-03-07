#!/usr/bin/env python3
"""
Custom form factor in DWBA.
"""
import bornagain as ba
from bornagain import deg, angstrom, nm
import cmath


def sinc(x):
    if abs(x) == 0:
        return 1.
    else:
        return cmath.sin(x)/x


class CustomFormFactor(ba.IBornFF):
    """
    A custom defined form factor.
    The particle is a prism of height H,
    with a base in form of a Greek cross ("plus" sign) with side length L.
    """
    def __init__(self, L, H):
        ba.IBornFF.__init__(self)
        # parameters describing the form factor
        self.L = L
        self.H = H

    def clone(self):
        """
        IMPORTANT NOTE:
        The clone method needs to call transferToCPP() on the cloned object
        to transfer the ownership of the clone to the cpp code
        """
        cloned_ff = CustomFormFactor(self.L, self.H)
        cloned_ff.transferToCPP()
        return cloned_ff

    def evaluate_for_q(self, q):
        qzhH = 0.5*q.z()*self.H
        qxhL = 0.5*q.x()*self.L
        qyhL = 0.5*q.y()*self.L
        return 0.5*self.H*self.L**2*cmath.exp(complex(0., 1.)*qzhH)*\
               sinc(qzhH)*(sinc(0.5*qyhL)*(sinc(qxhL)-0.5*sinc(0.5*qxhL))+\
               sinc(0.5*qxhL)*sinc(qyhL))


def get_sample():
    """
    Returns a sample with particles, having a custom form factor, on a substrate.
    """
    # defining materials
    m_vacuum = ba.HomogeneousMaterial("Vacuum", 0, 0)
    m_substrate = ba.HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    ff = CustomFormFactor(20*nm, 15*nm)
    particle = ba.Particle(m_particle, ff)
    particle_layout = ba.ParticleLayout()
    particle_layout.addParticle(particle, 1)
    vacuum_layer = ba.Layer(m_vacuum)
    vacuum_layer.addLayout(particle_layout)
    substrate_layer = ba.Layer(m_substrate)

    # assemble multilayer
    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(vacuum_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer


def get_simulation(sample):
    beam = ba.Beam(1, 1*angstrom, ba.Direction(0.2*deg, 0*deg))
    det = ba.SphericalDetector(100, -1*deg, 1*deg, 100, 0*deg, 2*deg)
    simulation = ba.GISASSimulation(beam, sample, det)
    simulation.getOptions().setNumberOfThreads(
        -1)  # deactivate multithreading (why?)
    return simulation


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
