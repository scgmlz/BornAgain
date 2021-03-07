#!/usr/bin/env python3
"""
Plot form factors.
"""
import bornagain as ba
from bornagain import nm, deg
import bornplot as bp
import math

det = ba.SphericalDetector(200, 10*deg, 0, 0)
n = 3
results = []
edge = 4.8

title = 'face normal'
trafo = ba.RotationY(48.1897*deg)
ff = ba.FormFactorIcosahedron(edge*nm)
data = bp.run_simulation(det, ff, trafo)
results.append(bp.Result(0, data, title))

title = 'vertex normal'
trafo = ba.RotationY(-52.6226*deg)
ff = ba.FormFactorIcosahedron(edge*nm)
data = bp.run_simulation(det, ff, trafo)
results.append(bp.Result(1, data, title))

title = 'edge normal'
trafo = ba.RotationY(69.0948*deg)
ff = ba.FormFactorIcosahedron(edge*nm)
data = bp.run_simulation(det, ff, trafo)
results.append(bp.Result(2, data, title))

bp.make_plot(results, det, "ff_Icosahedron_sym")
