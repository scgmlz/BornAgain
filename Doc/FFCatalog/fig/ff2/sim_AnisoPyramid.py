"""
Plot form factors.
"""
import bornagain as ba
from bornagain import nm, deg
import bornplot as bp

det = bp.Detector(200, 0, 5, 0, 5)
n = 4
results = []
for i in range(n):
    omega = 90*i/(n - 1)
    title = r'$\omega=%d^\circ$' % omega
    ff = ba.FormFactorAnisoPyramid(13*nm, 8*nm, 4.2*nm, 60.0*deg)
    trafo = ba.RotationZ(omega*deg)
    data = bp.run_simulation(det, ff, trafo)
    results.append(bp.Result(i, data, title))

bp.make_plot(results, det, "ff_AnisoPyramid")
