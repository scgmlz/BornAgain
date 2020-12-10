#!/usr/bin/env python

"""

"""

import glob, re, sys
from io import open

if len(sys.argv)<3:
    print( """
Usage: count-line-length <max_mum_chars_per_line> <files>

Returns 1 if any given file
    - exceeds the given number of characters per line,
    - or contains a tab.
Returns 0 otherwise.
""" )
    sys.exit(-1)

fworst = ""
lworst = 0
totlin = 0
totexc = 0
tottab = 0
nftot = 0
nfexc = 0
nftab = 0

limit = int(sys.argv[1])
flist = sys.argv[2:]
for fn in flist:
    # read in
    fd = open( fn, 'r', encoding="utf-8" )
    txt = fd.read().split( '\n' )
    fd.close

    n = len(txt)
    maxlen = 0
    maxwhere = -1
    nexclin = 0
    ntablin = 0
    for i in range(n):
        lin = txt[i]
        if re.match(r'\s*\/\/', lin):
            continue # ignore comment lines
        if '\t' in lin:
            ntablin += 1
            lin = lin.replace( '\t', '    ' )
        l = len(lin)
        if l>maxlen:
            maxlen = l
            maxwhere = i
        if l>limit:
            nexclin += 1

    if nexclin>0:
        print( "%s: %i/%i lines too long, line %i longest with %i chars" %
               (fn, nexclin, n, maxwhere+1, maxlen) )
        totexc += nexclin
        nfexc += 1
    if ntablin>0:
        print( "%s: %i/%i lines contain a TAB" % (fn, ntablin, n) )
        tottab += ntablin
        nftab += 1
    totlin += n
    nftot += 1
    if maxlen>lworst:
        lworst = maxlen
        fworst = fn

exitval = 0
if nfexc>0:
    print( "total: %i/%i lines too long, in %i/%i files, longest in %s with %i chars" %
           (totexc, totlin, nfexc, nftot, fworst, lworst) )
    exitval = 1
if nftab>0:
    print( "total: %i/%i lines contain a TAB, in %i/%i files" %
           (tottab, totlin, nftab, nftot) )
    exitval = 1

sys.exit(exitval)
