#!/usr/bin/env python3

# setup_dodecahedron.py:
# Compute vertex coordinates of a regular dodecahedron.
# Auxiliary program, used during implementation of dodecahedron form factor in BornAgain.
# Joachim Wuttke, Forschungszentrum Jülich, 2016

from math import sqrt,sin,cos,pi

def distance(s,t):
    return sqrt((s[0]-t[0])**2+(s[1]-t[1])**2+(s[2]-t[2])**2)

q=sqrt(5)
# v=pi/5
# vv=2*v
c=(1+q)/4 # cos(v)
s=sqrt((5-q)/8) # sin(v)
cc=(q-1)/4 # cos(vv)
ss=sqrt((5+q)/8) # sin(vv)

def plane_rotate(k):
    t=p[k]
    ci = cc
    si = ss
    x = ci*t[0]-si*t[1]
    y = si*t[0]+ci*t[1]
    p[k+1] = [x, y,t[2]]
    p[k+4] = [x,-y,t[2]]
    ci = -c
    si = s
    x = ci*t[0]-si*t[1]
    y = si*t[0]+ci*t[1]
    p[k+2] = [x, y,t[2]]
    p[k+3] = [x,-y,t[2]]


# a=pow((7*q-15)/5, 1/3.) # edge for V=1
a=1.

rb=a/(2*s)
rd=a*c/s
R2a=(9+3*q)/8
b=a*sqrt(R2a-1/(4*s**2))
d=a*sqrt(R2a-(c/s)**2)

h=rb*c
vol = 12 * 5 * h*a*b/6
print("a=%g, R/a=%g, rb/a=%g, rd/a=%g, b/a=%g, d/a=%g" % (a, sqrt(R2a), rb/a, rd/a, b/a, d/a))
print("h=%g volume=%20.16g" % (h, vol) )

p=[None for i in range(20)]
p[ 0] = [+rb,0.,-b]
p[ 5] = [+rd,0.,-d]
p[10] = [-rd,0.,+d]
p[15] = [-rb,0.,+b]
for m in range(4):
    plane_rotate(m*5)

for i in range(len(p)):
    print("        {%20.16g*a,%20.16g*a,%20.16g*a}," % (p[i][0], p[i][1], p[i][2]))

for i in range(20):
    print("p%2i(%20.16g,%20.16g,%20.16g) at R=%20.16g" %
          (i, p[i][0], p[i][1], p[i][2], distance(p[i],[0,0,0])))

distcoll = {}
for i in range(20):
    for j in range(i+1,20):
        dist = distance(p[i],p[j])
        print("p%2i(%9.4g,%9.4g,%9.4g) - p%2i(%9.4g,%9.4g,%9.4g) = %20.17g" %
              (i, p[i][0], p[i][1], p[i][2], j, p[j][0], p[j][1], p[j][2], dist))
        dist=round(dist*1e14)/10**14
        if not dist in distcoll:
            distcoll[dist] = 1
        else:
            distcoll[dist] += 1

for dist in sorted(distcoll.keys()):
    print( "%2i times %20.16g" % (distcoll[dist],dist) )
