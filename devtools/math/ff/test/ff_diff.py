#!/usr/bin/env python3

import re, sys
from math import sqrt

def read_file( fn ):
    fd = open( fn, 'r' )
    ti = fd.read().rstrip()
    fd.close
    ti = re.sub( r'^\s*#.*\n', '', ti, re.M )
    return ti.split("\n")

## Main

maxdiff = 0
fpair = sys.argv[1:3]
tpair = [ read_file( fn ) for fn in fpair ]
if len(tpair[0])!=len(tpair[1]):
    raise Exception( "tables differ in size" )
for i in range(len(tpair[0])):
    dpair = [ re.split(r'\s+', t[i]) for t in tpair]
    if len(dpair[0])!=len(dpair[1]):
        raise Exception( "lines %i differ in size" % i )
    for j in range(5):
        if dpair[0][j]!=dpair[1][j]:
            raise Exception( "lines %i differ in parameter %i" % (i,j) )
    xypair = [ [ float(d[8]), float(d[9]) ] for d in dpair ]
    out_of_range = False
    for x,y in xypair:
        if abs(x)>1e166 or abs(y)>1e166:
            out_of_range = True
            break
    if out_of_range:
        print( tpair[0][i] )
        print( tpair[1][i] )
        print( "result too large" )
        continue
    apair = [ sqrt(x**2+y**2) for x,y in xypair ]
    aval = (apair[0] + apair[1])/2
    diff = max( abs(xypair[0][0]-xypair[1][0]), abs(xypair[0][1]-xypair[1][1]) ) / aval
    maxdiff = max( maxdiff, diff )
    if diff>3.e-12:
        print( " ".join(dpair[0]+dpair[1][8:]+["%g" % diff]) )
print( "# maxdiff = %g" % maxdiff )
