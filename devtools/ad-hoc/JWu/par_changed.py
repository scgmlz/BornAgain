"""
Plot form factors.
"""
import bornagain as ba
from   bornagain import nanometer, degree
import bornplot2 as bp
import math
import inspect

det = bp.DetPars( 400, -.25, .25, -.25, .25 )
n    = 3
results = []
edge = 30

title = 'E=30'
trafo = ba.RotationY(26.5651*degree)
ff = ba.FormFactorTruncatedCube(edge*nanometer,2*nanometer)
sim = bp.get_simulation(det,ff,trafo)

data = bp.run_sim( sim, det )
results.append( bp.Result(0, data, title) )

pool = ff.getParameterPool()
print( pool.getParameterNames() )
print( ff.getLength() )
print( ff.volume() )
pool.setParameterValue('Length', 10 )
print( ff.getLength() )
print( ff.volume() )

title = 'E=10'
data = bp.run_sim( sim, det )
results.append( bp.Result(1, data, title) )

bp.make_plot( results, det, "tmp" )
