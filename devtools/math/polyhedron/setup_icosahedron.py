#!/usr/bin/env python3

# setup_icosahedron.py:
# Compute vertex coordinates of a regular icosahedron.
# Auxiliary program, used during implementation of icosahedron form factor in BornAgain.
# Joachim Wuttke, Forschungszentrum Jülich, 2016

from math import sqrt,sin,cos,pi

def distance(s,t):
    return sqrt((s[0]-t[0])**2+(s[1]-t[1])**2+(s[2]-t[2])**2)

c=sqrt(3)/2
q=sqrt(5)
ss=c
cc=.5

# a=pow(3*(3-q)/5, 1/3.) # edge for V=1
a=1.

R2=(5+q)/8*a**2
rb=a/sqrt(3)
b=a*sqrt((7+3*q)/24) # sqrt(R2-rb**2)
rd2=a**2*(3+q)/6 # (4*R2-a**2)/2/(1+cc)
rd=sqrt(rd2)
d=a*sqrt((3-q)/24) #sqrt(R2-rd2)

h=rb+sqrt(rb**2-(0.5*a)**2)
vol = 20 * h*a*b/6
print("a=%g, R=%g, rb=%g, rd=%g, b=%g, d=%g" % (a, sqrt(R2), rb, rd, b, d))
print("check P14=%g" % (sqrt( (rd*cc-rb)**2 + (rd*ss)**2 + (d-b)**2 )))
print("h=%g volume=%20.16g" % (h, vol) )

p=[None for i in range(12)]
p[ 0] = [ rb,          0,            -b]
p[ 1] = [-rb*cos(pi/3),+rb*sin(pi/3),-b]
p[ 2] = [-rb*cos(pi/3),-rb*sin(pi/3),-b]
p[ 3] = [-rd,          0,            -d]
p[ 4] = [ rd*cos(pi/3),+rd*sin(pi/3),-d]
p[ 5] = [ rd*cos(pi/3),-rd*sin(pi/3),-d]
p[ 6] = [ rd,          0,            +d]
p[ 7] = [-rd*cos(pi/3),+rd*sin(pi/3),+d]
p[ 8] = [-rd*cos(pi/3),-rd*sin(pi/3),+d]
p[ 9] = [-rb,          0,            +b]
p[10] = [ rb*cos(pi/3),+rb*sin(pi/3),+b]
p[11] = [ rb*cos(pi/3),-rb*sin(pi/3),+b]

for i in range(len(p)):
    print("        {%20.16g*a,%20.16g*a,%20.16g*a}," % (p[i][0], p[i][1], p[i][2]))

for i in range(len(p)):
    print("p%2i(%20.16g,%20.16g,%20.16g) at R=%20.16g" %
          (i, p[i][0], p[i][1], p[i][2], distance(p[i],[0,0,0])))

distcoll = {}
for i in range(len(p)):
    for j in range(i+1,len(p)):
        dist = distance(p[i],p[j])
        print("p%2i-%2i = %20.17g" % (i, j, dist))
        dist=round(dist*1e15)/10**15
        if not dist in distcoll:
            distcoll[dist] = 1
        else:
            distcoll[dist] += 1

for dist in sorted(distcoll.keys()):
    print( "%2i times %20.16g" % (distcoll[dist],dist) )
