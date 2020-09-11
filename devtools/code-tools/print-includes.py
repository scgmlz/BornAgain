#!/usr/bin/env python3

# Print names of included files.
# Report only includes of form "..", not <..>.

import glob, re, sys

def inspect( fn ):
    # print( "File " + fn )

    # read in
    fd = open( fn, 'r' )
    a = fd.read().split('\n')
    fd.close

    for line in a:
        m = re.search( r'#include\s+\"(.*)\"', line, re.M )
        if m:
            result.append( m.group(1) )

## Main

result = []
flist = sys.argv[1:]
for fn in flist:
    inspect( fn )

# remove duplicates and sort (how much more elegant would this be in Ruby...)
tmp = set(result)
result = list(tmp)
result.sort()

for fname in result:
    print( fname )
