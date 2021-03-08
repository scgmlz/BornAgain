#!/usr/bin/env python3
"""
Plot form factors.
"""
import bornagain as ba
from bornagain import nm, deg
import bornplot as bp

det = ba.SphericalDetector(200, 5*deg, 2.5*deg, 2.5*deg)
n = 4
results = []
for i in range(n):
    omega = 45*i/(n - 1)
    title = r'$\omega=%d^\circ$' % omega
    ff = ba.FormFactorPyramid(10*nm, 4.2*nm, 60*deg)
    trafo = ba.RotationZ(omega*deg)
    data = bp.run_simulation(det, ff, trafo)
    results.append(bp.Result(i, data, title))

bp.make_plot(results, det, "ff_Pyramid")
