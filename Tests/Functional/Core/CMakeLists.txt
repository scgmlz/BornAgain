############################################################################
# Tests/Functional/Core/CMakeLists.txt
############################################################################

# add standard and special tests
add_subdirectory(CoreStandardTest)
add_subdirectory(CoreSpecial)

# build OpenMPI test executable
if(BORNAGAIN_OPENMPI)
    add_subdirectory(MPI)
endif()
