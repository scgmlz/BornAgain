# this script is used to manually tweak swig-generated wrapper

import sys
import os
import string

# compatibility with windows filename conventions
def windowsify(filename):
    if ( sys.platform == "win32" ):
        new_filename = filename.replace("/", "\\")
    else:
        new_filename = filename

    return os.path.abspath(new_filename)

if len(sys.argv) != 3:
    print("Usage: tweaks.py inputfile outputfile")
    exit(1)

in_name = windowsify(sys.argv[1])
out_name = windowsify(sys.argv[2])

print("tweaks.py:", in_name, out_name)

fd = open(in_name, "r")
text_in = fd.read().splitlines()
fd.close()

text_out = []
for line in text_in:
    line = line.replace("_libBornAgainCore.ICloneable_transferToCPP(self)", "self.__disown__()")
    line = line.replace("_libBornAgainCore.Histogram1D_getBinCenters(self)", "self.getBinCentersNumpy()")
    line = line.replace("_libBornAgainCore.Histogram1D_getBinErrors(self)", "self.getBinErrorsNumpy()")
    line = line.replace("_libBornAgainCore.Histogram1D_getBinValues(self)", "self.getBinValuesNumpy()")
    text_out.append(line)

# done the search/replace
fd = open(out_name, "w")
fd.write( "\n".join( text_out ) )
fd.close()
