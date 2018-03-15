set(executable_name MPITest)

add_executable(${executable_name} mpitest.cpp)

# Find libraries
message(STATUS "Configuring with OpenMPI support")
find_package(MPI REQUIRED)
set(CMAKE_C_COMPILER mpicc)
set(CMAKE_CXX_COMPILER mpic++)

# BornAgain
target_link_libraries(${executable_name} ${BornAgainCore_LIBRARY})

include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${BornAgainCore_INCLUDE_DIRS}
    ${MPI_INCLUDE_PATH}
)

target_link_libraries(${executable_name}
    ${BornAgainCore_LIBRARY}
    ${MPI_LIBRARIES}
)
