"""
Plot form factor.
"""
import bornagain as ba
from bornagain import nm, deg
import bornplot as bp

det = bp.Detector(200, 0, 5, 0, 5)
n = 1
results = []
for i in range(n):
    ff = ba.FormFactorFullSphere(3.9*nm)
    data = bp.run_simulation(det, ff)
    results.append(bp.Result(i, data))

bp.make_plot(results, det, "ff_FullSphere")
