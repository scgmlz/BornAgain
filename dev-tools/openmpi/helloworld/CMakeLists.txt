# CC=mpicc CXX=mpicxx cmake ../


project(helloworld)

add_executable(helloworld helloworld.cpp)

# Require MPI for this project:
find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

target_link_libraries(helloworld ${MPI_LIBRARIES})
