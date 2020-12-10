"""
Plot form factors.
"""
import bornagain as ba
from bornagain import nm, deg
import bornplot as bp
import math

det = bp.Detector(200, -5, 5, -5, 5)
n = 3
results = []
edge = 4.8

title = 'default'
ff = ba.FormFactorIcosahedron(edge*nm)
data = bp.run_simulation(det, ff)
results.append(bp.Result(0, data, title))

title = 'rotated'
trafo = ba.RotationZ(13*deg)
ff = ba.FormFactorIcosahedron(edge*nm)
data = bp.run_simulation(det, ff, trafo)
results.append(bp.Result(1, data, title))

title = 'rotated, tilted'
trafo = ba.createProduct(ba.RotationX(9*deg), ba.RotationZ(13*deg))
ff = ba.FormFactorIcosahedron(edge*nm)
data = bp.run_simulation(det, ff, trafo)
results.append(bp.Result(2, data, title))

bp.make_plot(results, det, "ff_Icosahedron_asy")
