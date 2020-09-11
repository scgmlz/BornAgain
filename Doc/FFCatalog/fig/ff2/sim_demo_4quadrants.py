"""
Plot form factor.
"""
import bornagain as ba
from   bornagain import nanometer, degree
import bornplot as bp

det = bp.Detector( 200, -5, 5, -5, 5 )
pars = [0,5,10,20]
n = len(pars)
results = []
for i in range(n):
    theta=pars[i]
    title = r'$\vartheta=%d^\circ$' % theta
    ff = ba.FormFactorTruncatedSphere(4.2*nanometer, 6.1*nanometer, 0)
    trafo = ba.RotationY(theta*degree)
    data = bp.run_simulation(det,ff,trafo)
    results.append( bp.Result(i, data, title) )
    
bp.make_plot( results, det, "ff_demo_4quadrants" )
