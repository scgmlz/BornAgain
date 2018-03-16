############################################################################
# Tests/Functional/Core/CMakeLists.txt
############################################################################

# add standard and special tests
add_subdirectory(CoreStandardTest)
add_subdirectory(CoreSpecial)

# build MPI test executable
if(BORNAGAIN_MPI)
    add_subdirectory(MPI)
endif()
