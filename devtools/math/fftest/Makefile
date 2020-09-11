CC = g++ -ggdb -O3 -std=c++11 -Wall -I/G/ba/Core/FormFactors/ -I/G/ba/Core/Geometry -I/G/ba/Core/Tools -I/G/ba/Core/Samples -I/usr/include/eigen3

# LIBS=           -lm -lgslcblas -lgsl -lyaml-cpp

BIND = ./

all: $(BIND)runff

# source from BornAgain overwrites -lBornAgainCore, cf http://stackoverflow.com/questions/36667429
SRC = runff.cpp /G/ba/Core/FormFactors/FormFactorPolyhedron.cpp

DIAG = -D POLYHEDRAL_DIAGNOSTIC=ON

$(BIND)runff: $(SRC)
	$(CC) $(DIAG) -L../../../build/lib/ -l:_libBornAgainCore.so -o $(BIND)runff $(SRC)
