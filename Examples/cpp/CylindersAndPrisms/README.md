This example demonstrates how to use the BornAgain core C++ API.

GISAS from mixture of uncorrelated cylinders and prisms is simulated,
and the result is stored in a file result.int.

How to compile and run the example.

-------------------------------------------------------------------------------
0) Update FindBornAgain.cmake
-------------------------------------------------------------------------------
Increment hard-coded BornAgain version in ../modules/FindBornAgain.cmake

-------------------------------------------------------------------------------
1) Install third party software
-------------------------------------------------------------------------------
Required:
* compilers: as for compiling BornAgain
* cmake, Eigen3: as for BornAgain

-------------------------------------------------------------------------------
2) Setup BornAgain library
-------------------------------------------------------------------------------
* install BornAgain library
* add BornAgain libraries to path by running: source <BornAgain_install_dir>/bin/thisbornagain.sh

-------------------------------------------------------------------------------
3) Build given example with CMake
-------------------------------------------------------------------------------
mkdir <build_dir>
cd <build_dir>
cmake <this_source_dir>
make

-------------------------------------------------------------------------------
4) Run the simulation
-------------------------------------------------------------------------------
cd <build_dir>
./CylindersAndPrisms

-------------------------------------------------------------------------------
5) Inspect result
-------------------------------------------------------------------------------
<bornagain>/Examples/python/utils/plot_int.py result.int