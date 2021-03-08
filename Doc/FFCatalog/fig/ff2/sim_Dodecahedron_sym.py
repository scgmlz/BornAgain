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
edge = 3.2

title = 'face normal'
trafo = ba.RotationY(26.5651*deg)
ff = ba.FormFactorDodecahedron(edge*nm)
data = bp.run_simulation(det, ff, trafo)
results.append(bp.Result(0, data, title))

title = 'vertex normal'
trafo = ba.RotationY(-52.6226*deg)
ff = ba.FormFactorDodecahedron(edge*nm)
data = bp.run_simulation(det, ff, trafo)
results.append(bp.Result(1, data, title))

title = 'edge normal'
trafo = ba.RotationY(58.2825*deg)
ff = ba.FormFactorDodecahedron(edge*nm)
data = bp.run_simulation(det, ff, trafo)
results.append(bp.Result(2, data, title))

bp.make_plot(results, det, "ff_Dodecahedron_sym")
