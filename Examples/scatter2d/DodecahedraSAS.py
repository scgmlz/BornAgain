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

    ff = ba.FormFactorDodecahedron(2*nm)
    particle = ba.Particle(m_particle, ff)
    layout = ba.ParticleLayout()
    layout.addParticle(particle)

    solution_layer = ba.Layer(m_solution, 1000*nm)
       # TODO: make intensity proportional to thickness,
       #       https://github.com/scgmlz/BornAgain/issues/1222
    solution_layer.addLayout(layout)

    multi_layer = ba.MultiLayer()
    multi_layer.addLayer(ba.Layer(m_vacuum))
    multi_layer.addLayer(solution_layer)
    multi_layer.addLayer(ba.Layer(m_vacuum))
    return multi_layer


def get_simulation(sample):
    beam = ba.Beam(1, 0.1*nm, ba.Direction(90*deg, 0.0*deg))
    detWid = 500
    detPix = 200
    det = ba.RectangularDetector(detPix, detWid, detPix, detWid)
    det.setPerpendicularToDirectBeam(2000, detWid/2, detWid/2)
    return ba.GISASSimulation(beam, sample, det)


if __name__ == '__main__':
    import ba_plot
    sample = get_sample()
    simulation = get_simulation(sample)
    ba_plot.run_and_plot(simulation)
