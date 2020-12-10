"""
Plot form factor.
"""
import bornagain as ba
from bornagain import nm, deg
import bornplot as bp

det = bp.Detector(200, -5, 5, -5, 5)
n = 4
results = []
for i in range(n):
    theta = 135*i/(n - 1)
    title = r'$\vartheta=%d^\circ$' % theta
    ff = ba.FormFactorCylinder(3*nm, 8.8*nm)
    trafo = ba.RotationY(theta*deg)
    data = bp.run_simulation(det, ff, trafo)
    results.append(bp.Result(i, data, title))

bp.make_plot(results, det, "ff_Cylinder")
