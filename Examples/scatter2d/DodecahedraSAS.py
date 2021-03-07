#!/usr/bin/env python3
"""
Basic example for regular small-angle scattering (SAS).
Sample is a dilute assembly of ordered dodecahedra.
"""

import bornagain as ba
from bornagain import deg, nm


def get_sample():
    m_vacuum = ba.HomogeneousMaterial("Vacuum", 0.0, 0.0)
    m_solution = ba.HomogeneousMaterial("Solution", 6e-6, 2e-8)
    m_particle = ba.HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # Finite sample layer, contains particles in solution:
    ff = ba.FormFactorDodecahedron(12*nm)
    particle = ba.Particle(m_particle, ff)
    layout = ba.ParticleLayout()
    layout.addParticle(particle)
    solution_layer = ba.Layer(m_solution, 1000*nm)
       # TODO: make intensity proportional to thickness,
       #       https://github.com/scgmlz/BornAgain/issues/1222
    solution_layer.addLayout(layout)

    # Flat sample layer sandwiched between semi-infinite vacuum layers:
    sample = ba.MultiLayer()
    sample.addLayer(ba.Layer(m_vacuum))
    sample.addLayer(solution_layer)
    sample.addLayer(ba.Layer(m_vacuum))
    return sample


def get_simulation(sample):
    # Beam from above (perpendicular to sample):
    beam = ba.Beam(1, 0.4*nm, ba.Direction(90*deg, 0.0*deg))

    # Detector opposite to source:
    detPos = 2000 # distance from sample center to detector in mm
    detWid =  500 # detector width in mm
    detPix =  200 # number of pixels per direction
    det = ba.RectangularDetector(detPix, detWid, detPix, detWid)
    det.setPerpendicularToDirectBeam(detPos, detWid/2, detWid/2)

    return ba.GISASSimulation(beam, sample, det)


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation, aspect='equal')
