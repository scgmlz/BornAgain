set(executable_name MPITest)

# find libraries
message(STATUS "Configuring MPI test executable")
find_package(MPI REQUIRED)

# include dirs
include_directories(
    ${MPI_CXX_INCLUDE_PATH}
    ${EIGEN3_INCLUDE_DIRS}
    ${BornAgainCore_INCLUDE_DIRS}
    )

# executable and its dependencies
add_executable(${executable_name} mpitest.cpp)
target_link_libraries(${executable_name}
    ${MPI_CXX_LIBRARIES}
    ${BornAgainCore_LIBRARY}
    )

# compile and link flags
message(STATUS "MPI compile flags: ${MPI_CXX_COMPILE_FLAGS}")
message(STATUS "MPI link flags: ${MPI_CXX_LINK_FLAGS}")
if(MPI_CXX_COMPILE_FLAGS)
  set_target_properties(${executable_name} PROPERTIES
    COMPILE_FLAGS "${MPI_CXX_COMPILE_FLAGS}")
endif()

if(MPI_CXX_LINK_FLAGS)
  set_target_properties(${executable_name} PROPERTIES
    LINK_FLAGS "${MPI_CXX_LINK_FLAGS}")
endif()
